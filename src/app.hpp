#pragma once

#include "allocator.hpp"
#include "glwidget.hpp"
#include "model.hpp"
#include "openglhelper.hpp"

class App
{
  public:
    static bool Initialize(int w, int h);
    void Repaint();
    GLuint CreateShader();
    inline Model *GetModel()
    {
        return _model;
    }
    inline GLWidget *GetWindow()
    {
        return _window;
    }
    inline bool IsReady()
    {
        return initialized;
    };
    inline void dowork()
    {
        _window->update();
        _window->testMouse();
    }

  private:
    explicit App()
    {
    }
    inline ~App()
    {
        _window->deleteLater();
        OpenGLHelper::release();
        Csm::CubismFramework::Dispose();
        _model->DeleteRenderer();
        delete _model;
    }
    bool initialized = false;
    bool InitializeCubism(int, int);
    bool CheckShader(GLuint shaderId);

    Allocator _cubismAllocator;
    Csm::CubismFramework::Option _cubismOption;
    GLWidget *_window = nullptr;
    Model *_model;
};

inline App *ApplicationInstance = nullptr;
