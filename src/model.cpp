/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "model.hpp"

#include "app.hpp"
#include "apputils.hpp"
#include "config.hpp"
#include "textureloader.hpp"

#include <CubismDefaultParameterId.hpp>
#include <CubismModelSettingJson.hpp>
#include <Id/CubismIdManager.hpp>
#include <Motion/CubismMotion.hpp>
#include <Motion/CubismMotionQueueEntry.hpp>
#include <Physics/CubismPhysics.hpp>
#include <Rendering/OpenGL/CubismRenderer_OpenGLES2.hpp>
#include <Utils/CubismString.hpp>
#include <fstream>
#include <vector>

using namespace Live2D::Cubism::Framework;
using namespace Live2D::Cubism::Framework::DefaultParameterId;

Model::Model() : CubismUserModel(), _modelSetting(NULL), _userTimeSeconds(0.0f)
{
    _idParamAngleX = CubismFramework::GetIdManager()->GetId(ParamAngleX);
    _idParamAngleY = CubismFramework::GetIdManager()->GetId(ParamAngleY);
    _idParamAngleZ = CubismFramework::GetIdManager()->GetId(ParamAngleZ);
    _idParamBodyAngleX = CubismFramework::GetIdManager()->GetId(ParamBodyAngleX);
    _idParamEyeBallX = CubismFramework::GetIdManager()->GetId(ParamEyeBallX);
    _idParamEyeBallY = CubismFramework::GetIdManager()->GetId(ParamEyeBallY);
}

Model::~Model()
{
    _renderBuffer.DestroyOffscreenFrame();

    ReleaseMotions();
    ReleaseExpressions();

    for (int i = 0; i < _modelSetting->GetMotionGroupCount(); i++)
    {
        const QString &group = _modelSetting->GetMotionGroupName(i);
        ReleaseMotionGroup(group);
    }
    delete (_modelSetting);
}

void Model::LoadAssets(const QString &dir, const QString &fileName)
{
    _modelHomeDir = dir;
    // csmSizeInt size;
    const QString path = QString(dir) + fileName;
    AppUtils::FileContent_t buffer;
    AppUtils::readFileContent(path, buffer);
    ICubismModelSetting *setting = new CubismModelSettingJson(buffer);
    buffer.clear();
    SetupModel(setting);
    CreateRenderer();
    SetupTextures();
}

void Model::SetupModel(ICubismModelSetting *setting)
{
    _updating = true;
    _initialized = false;
    _modelSetting = setting;
    AppUtils::FileContent_t buffer;

    if (!_modelSetting->GetModelFileName().isEmpty())
    {
        QString path = _modelSetting->GetModelFileName();
        path = _modelHomeDir + path;
        AppUtils::readFileContent(path, buffer);
        LoadModel(buffer);
    }

    // Expression
    if (_modelSetting->GetExpressionCount() > 0)
    {
        const int count = _modelSetting->GetExpressionCount();
        for (int i = 0; i < count; i++)
        {
            QString name = _modelSetting->GetExpressionName(i);
            QString path = _modelSetting->GetExpressionFileName(i);
            path = _modelHomeDir + path;

            AppUtils::readFileContent(path, buffer);
            ACubismMotion *motion = LoadExpression(buffer, name);

            if (_expressions[name] != NULL)
            {
                ACubismMotion::Delete(_expressions[name]);
                _expressions[name] = NULL;
            }
            _expressions[name] = motion;
        }
    }

    // Physics
    if (!_modelSetting->GetPhysicsFileName().isEmpty())
    {
        QString path = _modelSetting->GetPhysicsFileName();
        path = _modelHomeDir + path;
        AppUtils::readFileContent(path, buffer);
        LoadPhysics(buffer);
    }

    // Pose
    if (!_modelSetting->GetPoseFileName().isEmpty())
    {
        const auto path = _modelHomeDir + _modelSetting->GetPoseFileName();
        AppUtils::readFileContent(path, buffer);
        LoadPose(buffer);
    }

    // EyeBlink
    if (_modelSetting->GetEyeBlinkParameterCount() > 0)
    {
        _eyeBlink = CubismEyeBlink::Create(_modelSetting);
    }
    // Breath
    {
        _breath = CubismBreath::Create();

        QVector<CubismBreath::BreathParameterData> breathParameters;

        breathParameters.append(CubismBreath::BreathParameterData(_idParamAngleX, 0.0f, 15.0f, 6.5345f, 0.5f));
        breathParameters.append(CubismBreath::BreathParameterData(_idParamAngleY, 0.0f, 8.0f, 3.5345f, 0.5f));
        breathParameters.append(CubismBreath::BreathParameterData(_idParamAngleZ, 0.0f, 10.0f, 5.5345f, 0.5f));
        breathParameters.append(CubismBreath::BreathParameterData(_idParamBodyAngleX, 0.0f, 4.0f, 15.5345f, 0.5f));
        breathParameters.append(
            CubismBreath::BreathParameterData(CubismFramework::GetIdManager()->GetId(ParamBreath), 0.5f, 0.5f, 3.2345f, 0.5f));

        _breath->SetParameters(breathParameters);
    }

    // UserData
    if (!_modelSetting->GetUserDataFile().isEmpty())
    {
        QString path = _modelSetting->GetUserDataFile();
        path = _modelHomeDir + path;
        AppUtils::readFileContent(path, buffer);
        LoadUserData(buffer);
    }

    // EyeBlinkIds
    {
        int eyeBlinkIdCount = _modelSetting->GetEyeBlinkParameterCount();
        for (int i = 0; i < eyeBlinkIdCount; ++i)
        {
            _eyeBlinkIds.append(_modelSetting->GetEyeBlinkParameterId(i));
        }
    }

    // LipSyncIds
    {
        int lipSyncIdCount = _modelSetting->GetLipSyncParameterCount();
        for (int i = 0; i < lipSyncIdCount; ++i)
        {
            _lipSyncIds.append(_modelSetting->GetLipSyncParameterId(i));
        }
    }

    // Layout
    QMap<QString, csmFloat32> layout;
    _modelSetting->GetLayoutMap(layout);
    _modelMatrix->SetupFromLayout(layout);
    _model->SaveParameters();
    for (int i = 0; i < _modelSetting->GetMotionGroupCount(); i++)
    {
        const QString &group = _modelSetting->GetMotionGroupName(i);
        PreloadMotionGroup(group);
    }
    _motionManager->StopAllMotions();

    _updating = false;
    _initialized = true;
}

void Model::PreloadMotionGroup(const QString &group)
{
    const int count = _modelSetting->GetMotionCount(group);

    for (int i = 0; i < count; i++)
    {
        // ex) idle_0
        auto name = group + "_" + QString::number(i); // Utils::CubismString::GetFormatedString("%s_%d", group, i);
        auto path = _modelHomeDir + _modelSetting->GetMotionFileName(group, i);

        AppUtils::FileContent_t buffer;
        // csmSizeInt size;

        AppUtils::readFileContent(path, buffer);
        CubismMotion *tmpMotion = static_cast<CubismMotion *>(LoadMotion(buffer, name));

        csmFloat32 fadeTime = _modelSetting->GetMotionFadeInTimeValue(group, i);
        if (fadeTime >= 0.0f)
        {
            tmpMotion->SetFadeInTime(fadeTime);
        }

        fadeTime = _modelSetting->GetMotionFadeOutTimeValue(group, i);
        if (fadeTime >= 0.0f)
        {
            tmpMotion->SetFadeOutTime(fadeTime);
        }
        tmpMotion->SetEffectIds(_eyeBlinkIds, _lipSyncIds);

        if (_motions[name] != NULL)
        {
            ACubismMotion::Delete(_motions[name]);
        }
        _motions[name] = tmpMotion;
    }
}

void Model::ReleaseMotionGroup(const QString &group) const
{
    const int count = _modelSetting->GetMotionCount(group);
    for (int i = 0; i < count; i++)
    {
        QString voice = _modelSetting->GetMotionSoundFileName(group, i);
        if (!voice.isEmpty())
        {
            QString path = voice;
            path = _modelHomeDir + path;
        }
    }
}

/**
 * @brief すべてのモーションデータの解放
 *
 * すべてのモーションデータを解放する。
 */
void Model::ReleaseMotions()
{
    for (auto iter = _motions.begin(); iter != _motions.end(); ++iter)
    {
        ACubismMotion::Delete(iter.value());
    }

    _motions.clear();
}

/**
 * @brief すべての表情データの解放
 *
 * すべての表情データを解放する。
 */
void Model::ReleaseExpressions()
{
    for (auto iter = _expressions.begin(); iter != _expressions.end(); ++iter)
    {
        ACubismMotion::Delete(iter.value());
    }

    _expressions.clear();
}

void Model::Update()
{
    const csmFloat32 deltaTimeSeconds = AppUtils::GetDeltaTime();
    _userTimeSeconds += deltaTimeSeconds;

    bool motionUpdated = false;

    _model->LoadParameters(); // 前回セーブされた状態をロード
    if (_motionManager->IsFinished())
    {
        StartRandomMotion(MotionGroupIdle, PriorityIdle);
    }
    else
    {
        motionUpdated = _motionManager->UpdateMotion(_model, deltaTimeSeconds); // モーションを更新
    }
    _model->SaveParameters(); // 状態を保存
    //-----------------------------------------------------------------

    // まばたき
    if (!motionUpdated)
    {
        if (_eyeBlink != NULL)
        {
            // メインモーションの更新がないとき
            _eyeBlink->UpdateParameters(_model, deltaTimeSeconds); // 目パチ
        }
    }

    if (_expressionManager != NULL)
    {
        _expressionManager->UpdateMotion(_model, deltaTimeSeconds); // 表情でパラメータ更新（相対変化）
    }

    if (_breath != NULL)
    {
        _breath->UpdateParameters(_model, deltaTimeSeconds);
    }

    // 物理演算の設定
    if (_physics != NULL)
    {
        _physics->Evaluate(_model, deltaTimeSeconds);
    }

    // リップシンクの設定
    if (_lipSync)
    {
        csmFloat32 value = 0; // リアルタイムでリップシンクを行う場合、システムから音量を取得して0〜1の範囲で値を入力します。

        for (auto i = 0; i < _lipSyncIds.size(); ++i)
        {
            _model->AddParameterValue(_lipSyncIds[i], value, 0.8f);
        }
    }

    // ポーズの設定
    if (_pose != NULL)
    {
        _pose->UpdateParameters(_model, deltaTimeSeconds);
    }

    _model->Update();
}

CubismMotionQueueEntryHandle Model::StartMotion(const QString &group, int no, int priority,
                                                ACubismMotion::FinishedMotionCallback onFinishedMotionHandler)
{
    if (priority == PriorityForce)
    {
        _motionManager->SetReservePriority(priority);
    }
    else if (!_motionManager->ReserveMotion(priority))
    {
        return InvalidMotionQueueEntryHandleValue;
    }

    const QString fileName = _modelSetting->GetMotionFileName(group, no);

    // ex) idle_0
    QString name = group + "_" + QString::number(no); // Utils::CubismString::GetFormatedString("%s_%d", group, no);
    CubismMotion *motion = static_cast<CubismMotion *>(_motions[name]);
    bool autoDelete = false;

    if (motion == NULL)
    {
        QString path = fileName;
        path = _modelHomeDir + path;

        AppUtils::FileContent_t buffer;
        // csmSizeInt size;
        AppUtils::readFileContent(path, buffer);
        motion = static_cast<CubismMotion *>(LoadMotion(buffer, NULL, onFinishedMotionHandler));
        csmFloat32 fadeTime = _modelSetting->GetMotionFadeInTimeValue(group, no);
        if (fadeTime >= 0.0f)
        {
            motion->SetFadeInTime(fadeTime);
        }

        fadeTime = _modelSetting->GetMotionFadeOutTimeValue(group, no);
        if (fadeTime >= 0.0f)
        {
            motion->SetFadeOutTime(fadeTime);
        }
        motion->SetEffectIds(_eyeBlinkIds, _lipSyncIds);
        autoDelete = true; // 終了時にメモリから削除
    }
    else
    {
        motion->SetFinishedMotionHandler(onFinishedMotionHandler);
    }

    // voice
    QString voice = _modelSetting->GetMotionSoundFileName(group, no);
    if (!voice.isEmpty())
    {
        QString path = voice;
        path = _modelHomeDir + path;
    }

    return _motionManager->StartMotionPriority(motion, autoDelete, priority);
}

CubismMotionQueueEntryHandle Model::StartRandomMotion(const QString &group, int priority,
                                                      ACubismMotion::FinishedMotionCallback onFinishedMotionHandler)
{
    if (_modelSetting->GetMotionCount(group) == 0)
        return InvalidMotionQueueEntryHandleValue;
    int no = rand() % _modelSetting->GetMotionCount(group);
    return StartMotion(group, no, priority, onFinishedMotionHandler);
}

void Model::Draw()
{
    if (_model == NULL)
        return;
    CubismMatrix44 matrix;
    matrix.Translate(offsetx, offsety);
    matrix.Scale(1, 1);
    matrix.MultiplyByMatrix(_modelMatrix);
    GetRenderer<Rendering::CubismRenderer_OpenGLES2>()->SetMvpMatrix(&matrix);
    GetRenderer<Rendering::CubismRenderer_OpenGLES2>()->DrawModel();
}
bool Model::TestMouse(Csm::csmFloat32 x, Csm::csmFloat32 y)
{
    if (_opacity < 1)
    {
        return false;
    }
    const int count = _modelSetting->GetHitAreasCount();
    for (int i = 0; i < count; i++)
    {
        const CubismIdHandle drawID = _modelSetting->GetHitAreaId(i);
        if (IsHit(drawID, x - offsetx, y - offsety))
            return true;
    }
    return false;
}
bool Model::HitTest(const QString &hitAreaName, csmFloat32 x, csmFloat32 y)
{
    if (_opacity < 1)
    {
        return false;
    }
    const int count = _modelSetting->GetHitAreasCount();
    for (int i = 0; i < count; i++)
    {
        if (_modelSetting->GetHitAreaName(i) == hitAreaName)
        {
            const CubismIdHandle drawID = _modelSetting->GetHitAreaId(i);
            return IsHit(drawID, x, y);
        }
    }
    return false; // 存在しない場合はfalse
}

void Model::SetExpression(const QString &expressionID)
{
    ACubismMotion *motion = _expressions[expressionID];
    if (motion != NULL)
    {
        _expressionManager->StartMotionPriority(motion, false, PriorityForce);
    }
}

void Model::SetRandomExpression()
{
    if (_expressions.size() == 0)
    {
        return;
    }

    int no = rand() % _expressions.size();
    int i = 0;
    for (auto map_ite = _expressions.begin(); map_ite != _expressions.end(); map_ite++)
    {
        if (i == no)
        {
            QString name = map_ite.key();
            SetExpression(name);
            return;
        }
        i++;
    }
}

void Model::SetupTextures()
{
    for (int modelTextureNumber = 0; modelTextureNumber < _modelSetting->GetTextureCount(); modelTextureNumber++)
    {
        // テクスチャ名が空文字だった場合はロード・バインド処理をスキップ
        if (_modelSetting->GetTextureFileName(modelTextureNumber).isEmpty())
        {
            continue;
        }

        QString texturePath = _modelSetting->GetTextureFileName(modelTextureNumber);
        texturePath = _modelHomeDir + texturePath;

        GLuint texture = TextureLoader::CreateTextureFromPngFile(texturePath);
        GetRenderer<Rendering::CubismRenderer_OpenGLES2>()->BindTexture(modelTextureNumber, texture);
    }
    GetRenderer<Rendering::CubismRenderer_OpenGLES2>()->IsPremultipliedAlpha(false);
}

Csm::Rendering::CubismOffscreenFrame_OpenGLES2 &Model::GetRenderBuffer()
{
    return _renderBuffer;
}
