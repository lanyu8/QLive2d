#include "app.hpp"
#pragma comment(lib, "Live2DCubismCore_MT.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "bass.lib")
#pragma comment(lib, "Propsys.lib")
#pragma comment(lib, "Shlwapi.lib")
#include "musicplayer.hpp"
#include "qdebug.h"

#include <QApplication>
#include <QScreen>
#include <QThread>
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QSize scrsize = app.screens()[0]->size();
    if (!App::Initialize(scrsize.width(), scrsize.height()))
        return 0;
    while (1)
    {
        ApplicationInstance->dowork();
        app.processEvents();
        QThread::msleep(10);
    }
    return 0;
}
