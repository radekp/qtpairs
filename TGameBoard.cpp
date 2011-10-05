/* Copyright Andrey N. Kuznetsov (Андрей Николаевич Кузнецов), linmedsoft@narod.ru,
Almaty
01-03 March 2010
28 June 2010

Qt-Pairs - classical memory game "Find the pairs".

This programme is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.
This programme is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this programme.  */
//------------------------------------------------------------
//********comment to try without phone*******
#define MOBILE
//*******************************************

#include "TGameBoard.h"
#include "TBlock.h"
//-----------------------------------------------------------
#include <QtGui>
#include <QMenu>
#ifdef MOBILE
#include <qsoftmenubar.h>
#endif
//-----------------------------------------------------------
#include <ctime>
//-----------------------------------------------------------
void Delay(unsigned int uimSeconds)
{
    clock_t GoalTime = uimSeconds + clock();
    while(GoalTime > clock()){};
}
//-----------------------------------------------------------
TGameBoard::TGameBoard(QWidget* pParent, Qt::WindowFlags Flag)
    : QWidget(pParent, Flag)
{
    srand(time(NULL));

    //--- init blocks array
    for( int i=0; i<4; i++ )
        for(int j=0; j<4; j++)
    pBlocksArray[i][j] = NULL;

    pMainLayout = new QVBoxLayout(this);

    //--- create game grid
    pGridLayout = new QGridLayout();
    pGridLayout->setSpacing(3);

#ifdef MOBILE
    //QSoftMenuBar::setLabel(field, Qt::Key_Select, QSoftMenuBar::Select);
    QMenu *contextMenu = QSoftMenuBar::menuFor(this);
    contextMenu->addAction( QIcon(":image/dead"), tr( "NewGame" ),
                            this, SLOT(initGame()) );
    contextMenu->addAction( QIcon(":image/dead"), tr( "Quit" ),
                            this, SLOT(close()) );
    contextMenu->addSeparator();

    //--- create menu
    QMenu* imagesMenu = new QMenu("ImageSet", this);

    //--- create actions
    QAction* beerAction     = new QAction("Beer",this);
    beerAction->setCheckable(true);
    QAction* softwareAction     = new QAction("Software",this);
    softwareAction->setCheckable(true);
    QAction* puppetsAction  = new QAction("Puppets",this);
    puppetsAction->setCheckable(true);
    QAction* titsAction  = new QAction("Tits",this);
    titsAction->setCheckable(true);

    //--- set default image set
    beerAction->setChecked(true);

    imageSetActionsGroup = new QActionGroup(this);
    imageSetActionsGroup->addAction(beerAction);
    imageSetActionsGroup->addAction(softwareAction);
    imageSetActionsGroup->addAction(puppetsAction);
    imageSetActionsGroup->addAction(titsAction);

    connect( imageSetActionsGroup, SIGNAL(triggered(QAction*)), this, SLOT(changedImageSetInfo(QAction*)));

    imagesMenu->addActions( imageSetActionsGroup->actions() );   //FIXME: needed???

    contextMenu->addMenu( imagesMenu );
#else
    //--- create menu
    QMenu* fileMenu = new QMenu("File", this);

    QAction* newGameAction = new QAction("New Game",this);
    connect(newGameAction, SIGNAL(triggered()), this, SLOT(initGame()));

    QAction* exitAction = new QAction("Exit",this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    fileMenu->addAction(newGameAction);
    fileMenu->addAction(exitAction);

    QMenu* imagesMenu = new QMenu("ImageSet", this);

    QAction* beerAction     = new QAction("Beer",this);
    beerAction->setCheckable(true);
    QAction* softwareAction     = new QAction("Software",this);
    softwareAction->setCheckable(true);
    QAction* puppetsAction  = new QAction("Puppets",this);
    puppetsAction->setCheckable(true);
    QAction* titsAction  = new QAction("Tits",this);
    titsAction->setCheckable(true);

    imageSetActionsGroup = new QActionGroup(this);
    imageSetActionsGroup->addAction(beerAction);
    imageSetActionsGroup->addAction(softwareAction);
    imageSetActionsGroup->addAction(puppetsAction);
    imageSetActionsGroup->addAction(titsAction);

    beerAction->setChecked(true);

    imagesMenu->addActions( imageSetActionsGroup->actions() );   //FIXME: needed???

    connect( imageSetActionsGroup, SIGNAL(triggered(QAction*)), this, SLOT(changedImageSetInfo(QAction*)));

    QMenuBar* menuBar = new QMenuBar(this);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(imagesMenu);
    pMainLayout->addWidget(menuBar);
#endif

    pMainLayout->addLayout(pGridLayout);

    initGame();
}
//-----------------------------------------------------------
void TGameBoard::initGame()
{
    this->SetPositions();

    //find which image set to use
    QString imageSet = imageSetActionsGroup->checkedAction()->text();

    int iBlocks = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if( pBlocksArray[i][j] )
                delete pBlocksArray[i][j];

            TBlock* pBlock = new TBlock(this);
            pBlock->SetImageSet(imageSet);
            pBlocksArray[i][j] = pBlock;
            pBlock->setFrameStyle(QFrame::Panel | QFrame::Raised);
            pBlock->setLineWidth(3);
            pGridLayout->addWidget(pBlock, i, j);
            connect(pBlock, SIGNAL(clicked(int, int)), this, SLOT(ClickedBlockSlot(int, int)));
            pBlock->iRow = i;
            pBlock->iCol = j;
            if(iPositions[iBlocks] <= 7) pBlock->iNumber = iPositions[iBlocks];
            else if(iPositions[iBlocks] > 7) pBlock->iNumber = iPositions[iBlocks] - 8;
            pBlock->SetImage();
            iBlocks++;
        }
    }
    pGridLayout->setSizeConstraint(QLayout::SetNoConstraint);

    this->iSelected = 0;
    this->pFirstOfPair = NULL;
    this->pSecondOfPair = NULL;
    this->iFreeCells = 8;
    this->iMoves = 0;
}

//-----------------------------------------------------------
void TGameBoard::SetPositions()
{
    for(int i = 0; i < 16; i++)
    {
        iPositions[i] = -1;
    }
    int iNumber = 0;
    while(iNumber < 16)
    {
        int iPosition = rand() % 16;
        for( ; ; )
        {
            if((iPosition == 15) && (iPositions[iPosition] != -1))
            {
                iPosition = 0;
            }

            if(iPositions[iPosition] == -1)
            {
                iPositions[iPosition] = iNumber;
                iNumber++;
                break;
            }
            else iPosition++;
        }
    }
}
//-----------------------------------------------------------
void TGameBoard::ClickedBlockSlot(int iRow, int iCol)
{
    ++iMoves;
    emit Clicked(iMoves);
    if(iSelected == 0)
    {
        this->pFirstOfPair = pBlocksArray[iRow][iCol];
        iSelected++;
    }
    else if(iSelected == 1)
    {
        this->pSecondOfPair = pBlocksArray[iRow][iCol];
        int iCounter = 0;
        while(1)
	{
		if(iCounter >= 2) break;
		this->pSecondOfPair->show();
		this->pSecondOfPair->repaint();
		Delay(250000);
		iCounter++;
        }
        if(pFirstOfPair->iNumber == pSecondOfPair->iNumber)
        {
            this->pFirstOfPair->hide();
            this->pSecondOfPair->hide();
            this->iFreeCells--;
            if(iFreeCells == 0)
            {
                QString sScores = QString::number(iMoves);
                sScores = tr("Congratulations! You found all pairs!\nYour scores: ") + QString::number(iMoves) + tr("\nOnce again?");
                int iAnswer = QMessageBox::information(this, tr("Victory!"), sScores, QMessageBox::Yes, QMessageBox::No);
                if(iAnswer == QMessageBox::Yes)
                {
			connect(this,   SIGNAL(NewGame()),        this,   SLOT(initGame()));
			emit NewGame();
		}
                else 
		{
			connect(this,   SIGNAL(GameFinished()),   this,   SLOT(close()));
			emit GameFinished();
		}
            }
        }
        else
        {
            this->pFirstOfPair->setPixmap(pFirstOfPair->Background);
            this->pSecondOfPair->setPixmap(pFirstOfPair->Background);
            this->pFirstOfPair->bIsOpened = false;
            this->pSecondOfPair->bIsOpened = false;
        }
        this->iSelected = 0;
    }
}
//-----------------------------------------------------------
void TGameBoard::Shuffle()
{
    this->SetPositions();
    int iBlocks = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(iPositions[iBlocks] <= 7) pBlocksArray[i][j]->iNumber = iPositions[iBlocks];
            else if(iPositions[iBlocks] > 7) pBlocksArray[i][j]->iNumber = iPositions[iBlocks] - 8;
            pBlocksArray[i][j]->SetImage();
            pBlocksArray[i][j]->setPixmap(pBlocksArray[i][j]->Background);
            pBlocksArray[i][j]->bIsOpened = false;
            pBlocksArray[i][j]->show();
            iBlocks++;
        }
    }
    this->iMoves = 0;
}
//-----------------------------------------------------------
void TGameBoard::changedImageSetInfo(QAction* act)
{
    if( act->text() == "Tits" )
        QMessageBox::information(this,
                                 tr("Info"),
                                 "So you like tits, right? Start a new game to catch boobs!!!",
                                 QMessageBox::Ok);
    else
        QMessageBox::information(this,
                                 tr("Info"),
                                 "Image set updated. Start a new game to try it.",
                                 QMessageBox::Ok);
}

