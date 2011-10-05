TEMPLATE=app
TARGET=qt-pairs

CONFIG+=qtopia
DEFINES+=QTOPIA

# I18n info
STRING_LANGUAGE=en_US
LANGUAGES=en_US

# Package info
pkg [
    name=qt-pairs
    desc="Find pairs game"
    license=GPLv2
    version=1.0
    maintainer="giotti"
]

# Input files
#FORMS +=\

HEADERS=\
    TBlock.h\
    TGameBoard.h

SOURCES=\
    main.cpp\
    TBlock.cpp\
    TGameBoard.cpp

RESOURCES += qt-pairs.qrc
TRANSLATIONS += translations/qt-pairs_en.ts

QT += xml

# Install rules
target [
    hint=sxe
    domain=untrusted
]

desktop [
    hint=desktop
    files=qt-pairs.desktop
    path=/apps/Games
]

pics [
    hint=pics
    files=pics/*
    path=/pics/qt-pairs
]

