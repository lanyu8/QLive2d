#include "glwidget.hpp"

#include "app.hpp"
#include "apputils.hpp"
#include "config.hpp"
#include "model.hpp"
#include "openglhelper.hpp"
#include "qdebug.h"

#include <QApplication>
#include <QBitmap>
#include <QLabel>
#include <QMimeData>
#include <QMouseEvent>
#include <QTimer>
//#include <Shlwapi.h>
//#include <Windows.h>
GLWidget::GLWidget(int w, int h) : QOpenGLWidget(nullptr)
{
    Q_UNUSED(w)
    Q_UNUSED(h)
    this->setAttribute(Qt::WA_TranslucentBackground);
    // this->setWindowFlag(Qt::FramelessWindowHint);
    // this->setAttribute(Qt::WA_TransparentForMouseEvents); /// Will set for the whole widget, I only need part of it...
    //
    this->setWindowFlag(Qt::WindowType::MSWindowsOwnDC, false);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_QuitOnClose);
    //    this->setAcceptDrops(true);
    this->show();

    // this->setGeometry(0, 0, w, h);
    this->makeCurrent();
    OpenGLHelper::get()->initializeOpenGLFunctions();
    OpenGLHelper::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLHelper::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    OpenGLHelper::get()->glEnable(GL_BLEND);
    OpenGLHelper::get()->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void GLWidget::initializeGL()
{
    OpenGLHelper::get()->initializeOpenGLFunctions();
}
void GLWidget::resizeGL(int, int)
{
}
void GLWidget::testMouse()
{
#ifdef Q_OS_WIN32
    HWND hWnd = (HWND)(this->winId());
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    long double x, y;
    x = pt.x * 2.0 / width() - 1.0;
    y = 1.0 - pt.y * 2.0 / height();
    bool res = ApplicationInstance->GetModel()->TestMouse(x, y);
    if (res)
        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLongW(hWnd, GWL_EXSTYLE) & (~WS_EX_TRANSPARENT));
    else
        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLongW(hWnd, GWL_EXSTYLE) | WS_EX_TRANSPARENT);
    DragAcceptFiles(hWnd, true);
#endif
}
void GLWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
    {
        // if(menu.IsShown())return;
        auto pos = ApplicationInstance->GetModel()->getpos();
        int cx = (pos.first + 1.0) * this->width() / 2;
        int cy = (1.0 - pos.second) * this->height() / 2;
        if (cx > 100)
            menu.moveto(QPoint(cx - 100, cy - 300));
        else
            menu.moveto(QPoint(cx + 100, cy - 300));
        if (!menu.IsShown())
            menu.AnimatedShow();
        return;
    }
    if (e->button() == Qt::LeftButton)
    {
        if (menu.IsShown())
            menu.AnimatedHide();
        is_dragging = true;
        oldx = e->x();
        oldy = e->y();
    }
}
void GLWidget::mouseReleaseEvent(QMouseEvent *)
{
    is_dragging = false;
}
void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!e->buttons().testFlag(Qt::MouseButton::LeftButton))
    {
        mouseReleaseEvent(e);
        return;
    }
    if (!is_dragging)
        mousePressEvent(e);
    double x, y;
    x = (e->x() - oldx) * 2.0 / width();
    y = -(e->y() - oldy) * 2.0 / height();
    oldx = e->x();
    oldy = e->y();
    // this->move(mapToGlobal(e->pos()));
    ApplicationInstance->GetModel()->move(x, y);
}
void GLWidget::paintGL()
{
    ApplicationInstance->Repaint();
}
void GLWidget::clear()
{
    OpenGLHelper::get()->glViewport(0, 0, width(), height());
    OpenGLHelper::get()->glClearColor(0, 0, 0, 0.0);
    OpenGLHelper::get()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    OpenGLHelper::get()->glClearDepthf(1.0);
}
bool GLWidget::nativeEvent(const QByteArray &b, void *m, long *r)
{
#ifdef Q_OS_WIN32
    MSG *msg = reinterpret_cast<MSG *>(m);
    if (msg->message == WM_MOUSEACTIVATE)
    {
        *r = MA_NOACTIVATE;
        return true;
    }
    if (msg->message == WM_QUERYENDSESSION)
    {
        // std::atomic_bool lock = true;
        //        std::thread thread([&lock]() {
        //            PluginLoader::unload.lock();
        //            PluginLoader::unloadall();
        //            lock = false;
        //        });
        // while (lock) QApplication::instance()->processEvents();
        *r = TRUE;
        return true;
    }
    if (msg->message == WM_ACTIVATE)
    {
        if (LOWORD(msg->wParam))
        {
            this->clearFocus();
            *r = 1;
            return true;
        }
    }
    //    if (msg->message == WM_HOTKEY)
    //    {
    //        int id = static_cast<int>(msg->wParam);
    //        HotKey::Run(id);
    //    }

    if (msg->message == WM_DROPFILES)
    {
        //        UINT count = DragQueryFileW(reinterpret_cast<HDROP>(msg->wParam), 0xFFFFFFFF, NULL, 0);
        //        if (count == 0)
        //            return true;
        //        if (count > 1)
        //        {
        //            wchar_t **files = reinterpret_cast<wchar_t **>(malloc(sizeof(wchar_t *) * count));
        //            for (UINT i = 0; i < count; i++)
        //            {
        //                UINT size = DragQueryFileW(reinterpret_cast<HDROP>(msg->wParam), i, NULL, 0);
        //                files[i] = reinterpret_cast<wchar_t *>(malloc(sizeof(wchar_t) * (size + 1)));
        //                DragQueryFileW(reinterpret_cast<HDROP>(msg->wParam), i, files[i], size + 1);
        //                files[i][size] = L'\0';
        //            }
        //            // PluginLoader::ondropfiles(count, files);
        //            return true;
        //        }
        //        UINT size = DragQueryFileW(reinterpret_cast<HDROP>(msg->wParam), 0, NULL, 0);
        //        wchar_t *filename = reinterpret_cast<wchar_t *>(malloc(sizeof(wchar_t) * (size + 1)));
        //        DragQueryFileW(reinterpret_cast<HDROP>(msg->wParam), 0, filename, size + 1);
        //        filename[size] = L'\0';

        //        if (GetFileAttributesW(filename) & FILE_ATTRIBUTE_DIRECTORY)
        //        {
        //            PluginLoader::ondropdir(filename);
        //        }
        //        else
        //        {
        //            PluginLoader::ondropfile(filename);
        //        }
        //        return true;
    }
#endif
    return QOpenGLWidget::nativeEvent(b, m, r);
}
