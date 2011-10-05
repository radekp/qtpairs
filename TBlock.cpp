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
#include "TBlock.h"
//-----------------------------------------------------------
#include <QMouseEvent>
//-----------------------------------------------------------
TBlock::TBlock(QWidget* pParent) :
    QLabel(pParent)
{
    this->setAlignment(Qt::AlignCenter);
    this->setAutoFillBackground(true);
    this->setScaledContents(true);
    this->setFixedSize(QSize(94, 94));

    Background.load(":/images/find.png");
    this->setPixmap(Background);
    this->bIsOpened = false;
}
//-----------------------------------------------------------
void TBlock::SetImage()
{
    QString sImage;

    QString imagedir = ":/images/" + ImageSet + "/";

    switch(this->iNumber)
    {
        case 0:
        {
            sImage = imagedir + "0.png";
            break;
        }
        case 1:
        {
            sImage = imagedir + "1.png";
            break;
        }
        case 2:
        {
            sImage = imagedir + "2.png";
            break;
        }
        case 3:
        {
            sImage = imagedir + "3.png";
            break;
        }
        case 4:
        {
            sImage = imagedir + "4.png";
            break;
        }
        case 5:
        {
            sImage = imagedir + "5.png";
            break;
        }
        case 6:
        {
            sImage = imagedir + "6.png";
            break;
        }
        case 7:
        {
            sImage = imagedir + "7.png";
            break;
        }
    }

    Image.load(sImage);
}
//-----------------------------------------------------------
void TBlock::mouseReleaseEvent(QMouseEvent* pMouseEvent)
{
    if(rect().contains(pMouseEvent->pos()))
    {
        if(!bIsOpened)
        {
            this->setPixmap(this->Image);
            this->bIsOpened = true;
            emit this->clicked(iRow, iCol);
        }
    }
}
//-----------------------------------------------------------
