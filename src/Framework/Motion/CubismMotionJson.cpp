/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismMotionJson.hpp"

#include "Id/CubismId.hpp"
#include "Id/CubismIdManager.hpp"

namespace Live2D
{
    namespace Cubism::Framework
    {
        // JSON keys
        constexpr auto Meta = "Meta";
        constexpr auto Duration = "Duration";
        constexpr auto Loop = "Loop";
        constexpr auto CurveCount = "CurveCount";
        constexpr auto Fps = "Fps";
        constexpr auto TotalSegmentCount = "TotalSegmentCount";
        constexpr auto TotalPointCount = "TotalPointCount";
        constexpr auto Curves = "Curves";
        constexpr auto Target = "Target";
        constexpr auto Id = "Id";
        constexpr auto FadeInTime = "FadeInTime";
        constexpr auto FadeOutTime = "FadeOutTime";
        constexpr auto Segments = "Segments";
        constexpr auto UserData = "UserData";
        constexpr auto UserDataCount = "UserDataCount";
        constexpr auto TotalUserDataSize = "TotalUserDataSize";
        constexpr auto Time = "Time";
        constexpr auto Value = "Value";

        CubismMotionJson::CubismMotionJson(const QByteArray &buffer) : _json(QJsonDocument::fromJson(buffer).object())
        {
        }

        CubismMotionJson::~CubismMotionJson()
        {
        }

        csmFloat32 CubismMotionJson::GetMotionDuration() const
        {
            return QJsonIO::GetValue(_json, Meta, Duration).toDouble();
        }

        bool CubismMotionJson::IsMotionLoop() const
        {
            return QJsonIO::GetValue(_json, Meta, Loop).toBool();
        }

        int CubismMotionJson::GetMotionCurveCount() const
        {
            return _json[Meta].toObject()[CurveCount].toInt();
        }

        csmFloat32 CubismMotionJson::GetMotionFps() const
        {
            return _json[Meta].toObject()[Fps].toDouble();
        }

        int CubismMotionJson::GetMotionTotalSegmentCount() const
        {
            return _json[Meta][TotalSegmentCount].toInt();
        }

        int CubismMotionJson::GetMotionTotalPointCount() const
        {
            return _json[Meta][TotalPointCount].toInt();
        }

        bool CubismMotionJson::IsExistMotionFadeInTime() const
        {
            return !_json[Meta][FadeInTime].isNull();
        }

        bool CubismMotionJson::IsExistMotionFadeOutTime() const
        {
            return !_json[Meta][FadeOutTime].isNull();
        }

        csmFloat32 CubismMotionJson::GetMotionFadeInTime() const
        {
            return _json[Meta][FadeInTime].toDouble();
        }

        csmFloat32 CubismMotionJson::GetMotionFadeOutTime() const
        {
            return _json[Meta][FadeOutTime].toDouble();
        }

        const QString CubismMotionJson::GetMotionCurveTarget(int curveIndex) const
        {
            return _json[Curves].toArray()[curveIndex].toObject()[Target].toString();
        }

        CubismIdHandle CubismMotionJson::GetMotionCurveId(int curveIndex) const
        {
            return CubismFramework::GetIdManager()->GetId(_json[Curves].toArray()[curveIndex].toObject()[Id].toString());
        }

        bool CubismMotionJson::IsExistMotionCurveFadeInTime(int curveIndex) const
        {
            return !_json[Curves].toArray()[curveIndex].toObject()[FadeInTime].isNull();
        }

        bool CubismMotionJson::IsExistMotionCurveFadeOutTime(int curveIndex) const
        {
            return !_json[Curves].toArray()[curveIndex].toObject()[FadeOutTime].isNull();
        }

        csmFloat32 CubismMotionJson::GetMotionCurveFadeInTime(int curveIndex) const
        {
            return _json[Curves].toArray()[curveIndex].toObject()[FadeInTime].toDouble();
        }

        csmFloat32 CubismMotionJson::GetMotionCurveFadeOutTime(int curveIndex) const
        {
            return _json[Curves].toArray()[curveIndex].toObject()[FadeOutTime].toDouble();
        }

        int CubismMotionJson::GetMotionCurveSegmentCount(int curveIndex) const
        {
            return _json[Curves].toArray()[curveIndex].toObject()[Segments].toArray().size();
        }

        csmFloat32 CubismMotionJson::GetMotionCurveSegment(int curveIndex, int segmentIndex) const
        {
            return _json[Curves].toArray()[curveIndex].toObject()[Segments].toArray()[segmentIndex].toDouble();
        }

        int CubismMotionJson::GetEventCount() const
        {
            return _json[Meta][UserDataCount].toInt();
        }

        int CubismMotionJson::GetTotalEventValueSize() const
        {
            return _json[Meta][TotalUserDataSize].toInt();
        }

        csmFloat32 CubismMotionJson::GetEventTime(int userDataIndex) const
        {
            return _json[UserData].toArray()[userDataIndex].toObject()[Time].toDouble();
        }

        const QString CubismMotionJson::GetEventValue(int userDataIndex) const
        {
            return _json[UserData].toArray()[userDataIndex].toObject()[Value].toString();
        }
    } // namespace Cubism::Framework
} // namespace Live2D
