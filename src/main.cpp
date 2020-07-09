#ifdef Q_OS_WIN
    #pragma comment(lib, "Live2DCubismCore_MT.lib")
    #pragma comment(lib, "user32.lib")
    #pragma comment(lib, "gdi32.lib")
    #pragma comment(lib, "Propsys.lib")
    #pragma comment(lib, "Shlwapi.lib")
#endif
#include "app.hpp"
#include "musicplayer.hpp"
#include "qdebug.h"

#include <QApplication>
#include <QScreen>
#include <QThread>
#include <iostream>
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QSize scrsize = app.screens()[0]->size();
    if (!App::Initialize(scrsize.width(), scrsize.height()))
        return 0;
    app.setQuitOnLastWindowClosed(true);
    while (1)
    {
        ApplicationInstance->dowork();
        app.processEvents();
        QThread::msleep(10);
    }
    return 0;
}
