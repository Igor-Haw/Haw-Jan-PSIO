TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        src/blackjack.cpp \
        src/button.cpp \
        src/casino.cpp \
        src/clickergame.cpp \
        main.cpp \
        src/roulette.cpp \
        src/slots.cpp

INCLUDEPATH += "C:/SFML-2.5.1/include"
INCLUDEPATH += include
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}



HEADERS += \
    include/blackjack.h \
    include/button.h \
    include/casino.h \
    include/clickergame.h \
    include/minigame.h \
    include/roulette.h \
    include/slots.h
