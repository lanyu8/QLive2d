#pragma once
#include "qdebug.h"

#include <CubismFramework.hpp>
#include <ICubismModelSetting.hpp>
#include <Model/CubismUserModel.hpp>
#include <QOpenGLFunctions>
#include <Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.hpp>
#include <Type/csmRectF.hpp>
class Model : public Csm::CubismUserModel
{
  public:
    Model();
    virtual ~Model();
    void LoadAssets(const QString &dir, const QString &fileName);
    void Update();
    void Draw();
    Csm::CubismMotionQueueEntryHandle StartMotion(const QString &group, int no, int priority,
                                                  Csm::ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = NULL);
    Csm::CubismMotionQueueEntryHandle StartRandomMotion(const QString &group, int priority,
                                                        Csm::ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = NULL);
    void SetExpression(const QString &expressionID);
    void SetRandomExpression();
    virtual bool HitTest(const QString &hitAreaName, Csm::csmFloat32 x, Csm::csmFloat32 y);
    virtual bool TestMouse(Csm::csmFloat32 x, Csm::csmFloat32 y);
    Csm::Rendering::CubismOffscreenFrame_OpenGLES2 &GetRenderBuffer();
    inline void move(long double x, long double y)
    {
        offsetx += x;
        offsety += y;
    }
    inline std::pair<long double, long double> getpos()
    {
        return std::make_pair(offsetx, offsety);
    }

  private:
    long double offsetx = 0.8;
    long double offsety = -0.5;
    void SetupModel(Csm::ICubismModelSetting *setting);
    void SetupTextures();
    void PreloadMotionGroup(const QString &group);
    void ReleaseMotionGroup(const QString &group) const;
    void ReleaseMotions();
    void ReleaseExpressions();

    Csm::ICubismModelSetting *_modelSetting;
    QString _modelHomeDir;
    Csm::csmFloat32 _userTimeSeconds;
    QVector<Csm::CubismIdHandle> _eyeBlinkIds;
    QVector<Csm::CubismIdHandle> _lipSyncIds;
    QMap<QString, Csm::ACubismMotion *> _motions;
    QMap<QString, Csm::ACubismMotion *> _expressions;
    QVector<Csm::csmRectF> _hitArea;
    QVector<Csm::csmRectF> _userArea;
    const Csm::CubismId *_idParamAngleX;
    const Csm::CubismId *_idParamAngleY;
    const Csm::CubismId *_idParamAngleZ;
    const Csm::CubismId *_idParamBodyAngleX;
    const Csm::CubismId *_idParamEyeBallX;
    const Csm::CubismId *_idParamEyeBallY;

    Csm::Rendering::CubismOffscreenFrame_OpenGLES2 _renderBuffer; ///< フレームバッファ以外の描画先
};
