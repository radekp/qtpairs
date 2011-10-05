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
#include "TGameBoard.h"
//------------------------------------------------------------
//#include <QApplication>
#include <QtGui/QApplication>
#include <QMessageBox>
//------------------------------------------------------------
#ifdef QTOPIA
#include <QtopiaServiceRequest>
#include <QValueSpaceItem>
#include <qtopiaapplication.h>

QTOPIA_ADD_APPLICATION(QTOPIA_TARGET,TGameBoard)
QTOPIA_MAIN
#else
int main(int iArgc, char* psArgv[])
{
    QApplication application(iArgc, psArgv);

    TGameBoard gameBoard;

    gameBoard.show();

    return application.exec();
}
#endif
