QT       += core gui opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
INCLUDEPATH += $$PWD/src/Framework/
INCLUDEPATH += $$PWD/3rdparty/include
LIBPATH += $$PWD/3rdparty/libs

unix: !macx {
    LIBS += -lLive2DCubismCore
}

macx {
    LIBS += -lLive2DCubismCore-macx
}
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src

SOURCES += \
    $$PWD/src/Framework/CubismCdiJson.cpp \
    $$PWD/src/Framework/CubismDefaultParameterId.cpp \
    $$PWD/src/Framework/CubismFramework.cpp \
    $$PWD/src/Framework/CubismModelSettingJson.cpp \
    $$PWD/src/Framework/Effect/CubismBreath.cpp \
    $$PWD/src/Framework/Effect/CubismEyeBlink.cpp \
    $$PWD/src/Framework/Effect/CubismPose.cpp \
    $$PWD/src/Framework/Id/CubismId.cpp \
    $$PWD/src/Framework/Id/CubismIdManager.cpp \
    $$PWD/src/Framework/Math/CubismMath.cpp \
    $$PWD/src/Framework/Math/CubismMatrix44.cpp \
    $$PWD/src/Framework/Math/CubismModelMatrix.cpp \
    $$PWD/src/Framework/Math/CubismTargetPoint.cpp \
    $$PWD/src/Framework/Math/CubismVector2.cpp \
    $$PWD/src/Framework/Math/CubismViewMatrix.cpp \
    $$PWD/src/Framework/Model/CubismMoc.cpp \
    $$PWD/src/Framework/Model/CubismModel.cpp \
    $$PWD/src/Framework/Model/CubismModelUserData.cpp \
    $$PWD/src/Framework/Model/CubismModelUserDataJson.cpp \
    $$PWD/src/Framework/Model/CubismUserModel.cpp \
    $$PWD/src/Framework/Motion/ACubismMotion.cpp \
    $$PWD/src/Framework/Motion/CubismExpressionMotion.cpp \
    $$PWD/src/Framework/Motion/CubismMotion.cpp \
    $$PWD/src/Framework/Motion/CubismMotionJson.cpp \
    $$PWD/src/Framework/Motion/CubismMotionManager.cpp \
    $$PWD/src/Framework/Motion/CubismMotionQueueEntry.cpp \
    $$PWD/src/Framework/Motion/CubismMotionQueueManager.cpp \
    $$PWD/src/Framework/Physics/CubismPhysics.cpp \
    $$PWD/src/Framework/Physics/CubismPhysicsJson.cpp \
    $$PWD/src/Framework/Rendering/CubismRenderer.cpp \
    $$PWD/src/Framework/Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.cpp \
    $$PWD/src/Framework/Rendering/OpenGL/CubismRenderer_OpenGLES2.cpp \
    $$PWD/src/Framework/Type/csmRectF.cpp \
    $$PWD/src/Framework/Type/csmString.cpp \
    $$PWD/src/Framework/Utils/CubismDebug.cpp \
    $$PWD/src/Framework/Utils/CubismJson.cpp \
    $$PWD/src/Framework/Utils/CubismString.cpp \
    $$PWD/src/app.cpp \
    $$PWD/src/apputils.cpp \
    $$PWD/src/glwidget.cpp \
    $$PWD/src/main.cpp \
    $$PWD/src/menu.cpp \
    $$PWD/src/model.cpp \
    $$PWD/src/textureloader.cpp

HEADERS += \
    $$PWD/src/Framework/CubismCdiJson.hpp \
    $$PWD/src/Framework/CubismDefaultParameterId.hpp \
    $$PWD/src/Framework/CubismFramework.hpp \
    $$PWD/src/Framework/CubismFrameworkConfig.hpp \
    $$PWD/src/Framework/CubismModelSettingJson.hpp \
    $$PWD/src/Framework/Effect/CubismBreath.hpp \
    $$PWD/src/Framework/Effect/CubismEyeBlink.hpp \
    $$PWD/src/Framework/Effect/CubismPose.hpp \
    $$PWD/src/Framework/ICubismAllocator.hpp \
    $$PWD/src/Framework/ICubismModelSetting.hpp \
    $$PWD/src/Framework/Id/CubismId.hpp \
    $$PWD/src/Framework/Id/CubismIdManager.hpp \
    $$PWD/src/Framework/Live2DCubismCore.hpp \
    $$PWD/src/Framework/Math/CubismMath.hpp \
    $$PWD/src/Framework/Math/CubismMatrix44.hpp \
    $$PWD/src/Framework/Math/CubismModelMatrix.hpp \
    $$PWD/src/Framework/Math/CubismTargetPoint.hpp \
    $$PWD/src/Framework/Math/CubismVector2.hpp \
    $$PWD/src/Framework/Math/CubismViewMatrix.hpp \
    $$PWD/src/Framework/Model/CubismMoc.hpp \
    $$PWD/src/Framework/Model/CubismModel.hpp \
    $$PWD/src/Framework/Model/CubismModelUserData.hpp \
    $$PWD/src/Framework/Model/CubismModelUserDataJson.hpp \
    $$PWD/src/Framework/Model/CubismUserModel.hpp \
    $$PWD/src/Framework/Motion/ACubismMotion.hpp \
    $$PWD/src/Framework/Motion/CubismExpressionMotion.hpp \
    $$PWD/src/Framework/Motion/CubismMotion.hpp \
    $$PWD/src/Framework/Motion/CubismMotionInternal.hpp \
    $$PWD/src/Framework/Motion/CubismMotionJson.hpp \
    $$PWD/src/Framework/Motion/CubismMotionManager.hpp \
    $$PWD/src/Framework/Motion/CubismMotionQueueEntry.hpp \
    $$PWD/src/Framework/Motion/CubismMotionQueueManager.hpp \
    $$PWD/src/Framework/Physics/CubismPhysics.hpp \
    $$PWD/src/Framework/Physics/CubismPhysicsInternal.hpp \
    $$PWD/src/Framework/Physics/CubismPhysicsJson.hpp \
    $$PWD/src/Framework/Rendering/CubismRenderer.hpp \
    $$PWD/src/Framework/Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.hpp \
    $$PWD/src/Framework/Rendering/OpenGL/CubismRenderer_OpenGLES2.hpp \
    $$PWD/src/Framework/Type/CubismBasicType.hpp \
    $$PWD/src/Framework/Type/csmMap.hpp \
    $$PWD/src/Framework/Type/csmRectF.hpp \
    $$PWD/src/Framework/Type/csmString.hpp \
    $$PWD/src/Framework/Type/csmVector.hpp \
    $$PWD/src/Framework/Utils/CubismDebug.hpp \
    $$PWD/src/Framework/Utils/CubismJson.hpp \
    $$PWD/src/Framework/Utils/CubismString.hpp \
    $$PWD/src/allocator.hpp \
    $$PWD/src/app.hpp \
    $$PWD/src/apputils.hpp \
    $$PWD/src/config.hpp \
    $$PWD/src/glwidget.hpp \
    $$PWD/src/menu.hpp \
    $$PWD/src/model.hpp \
    $$PWD/src/musicplayer.hpp \
    $$PWD/src/openglhelper.hpp \
    $$PWD/src/textureloader.hpp
