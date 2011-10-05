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
#ifndef _TGameBoard_h_
#define _TGameBoard_h_
//-----------------------------------------------------------
#include <QWidget>
#include <QVBoxLayout>
#include <QActionGroup>
//-----------------------------------------------------------
class QGridLayout;
class QTimer;
class TBlock;
//-----------------------------------------------------------
class TGameBoard : public QWidget
{
    Q_OBJECT

public:
    TGameBoard(QWidget* pParent = 0, Qt::WindowFlags Flag = Qt::Widget);

    int iFreeCells;
    void Shuffle();

    int iMoves;
    QActionGroup* imageSetActionsGroup;

signals:
    void GameFinished();
    void NewGame();
    void Clicked(int);

private:
    int iPositions[16];
    TBlock* pBlocksArray[4][4];
    TBlock* pFirstOfPair;
    TBlock* pSecondOfPair;
    int iSelected;

    QGridLayout* pGridLayout;
    QVBoxLayout* pMainLayout;

    void SetPositions();

private slots:
    void ClickedBlockSlot(int, int);

protected slots:
    void initGame();
    void changedImageSetInfo(QAction*);
};
//-----------------------------------------------------------
#endif
