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
    namespace Cubism
    {
        namespace Framework
        {
            namespace
            {
                // JSON keys
                const QString Meta = "Meta";
                const QString Duration = "Duration";
                const QString Loop = "Loop";
                const QString CurveCount = "CurveCount";
                const QString Fps = "Fps";
                const QString TotalSegmentCount = "TotalSegmentCount";
                const QString TotalPointCount = "TotalPointCount";
                const QString Curves = "Curves";
                const QString Target = "Target";
                const QString Id = "Id";
                const QString FadeInTime = "FadeInTime";
                const QString FadeOutTime = "FadeOutTime";
                const QString Segments = "Segments";
                const QString UserData = "UserData";
                const QString UserDataCount = "UserDataCount";
                const QString TotalUserDataSize = "TotalUserDataSize";
                const QString Time = "Time";
                const QString Value = "Value";
            } // namespace

            CubismMotionJson::CubismMotionJson(const QByteArray &buffer)
            {
                _json = QJsonDocument::fromJson(buffer).object();
            }

            CubismMotionJson::~CubismMotionJson()
            {
            }

            csmFloat32 CubismMotionJson::GetMotionDuration() const
            {
                return _json[Meta].toObject()[Duration].toVariant().toFloat();
            }

            bool CubismMotionJson::IsMotionLoop() const
            {
                return _json[Meta].toObject()[Loop].toBool();
            }

            int CubismMotionJson::GetMotionCurveCount() const
            {
                return _json[Meta].toObject()[CurveCount].toInt();
            }

            csmFloat32 CubismMotionJson::GetMotionFps() const
            {
                return _json[Meta].toObject()[Fps].toVariant().toFloat();
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
                return _json[Meta][FadeInTime].toVariant().toFloat();
            }

            csmFloat32 CubismMotionJson::GetMotionFadeOutTime() const
            {
                return _json[Meta][FadeOutTime].toVariant().toFloat();
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
                return _json[Curves].toArray()[curveIndex].toObject()[FadeInTime].toVariant().toFloat();
            }

            csmFloat32 CubismMotionJson::GetMotionCurveFadeOutTime(int curveIndex) const
            {
                return _json[Curves].toArray()[curveIndex].toObject()[FadeOutTime].toVariant().toFloat();
            }

            int CubismMotionJson::GetMotionCurveSegmentCount(int curveIndex) const
            {
                return _json[Curves].toArray()[curveIndex].toObject()[Segments].toArray().size();
            }

            csmFloat32 CubismMotionJson::GetMotionCurveSegment(int curveIndex, int segmentIndex) const
            {
                return _json[Curves].toArray()[curveIndex].toObject()[Segments].toArray()[segmentIndex].toVariant().toFloat();
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
                return _json[UserData].toArray()[userDataIndex].toObject()[Time].toVariant().toFloat();
            }

            const QString CubismMotionJson::GetEventValue(int userDataIndex) const
            {
                return _json[UserData].toArray()[userDataIndex].toObject()[Value].toString();
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
