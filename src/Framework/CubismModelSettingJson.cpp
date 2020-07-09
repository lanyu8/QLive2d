/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismModelSettingJson.hpp"

#include "CubismFramework.hpp"
#include "Id/CubismId.hpp"
#include "Id/CubismIdManager.hpp"
#include "Type/csmMap.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            /**
             * @brief   Model3Jsonのキー文字列
             *
             */
            namespace
            {

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused-variable"
#endif

                // JSON keys
                // const QString &Version = "Version";
                constexpr auto FileReferences = "FileReferences";
                constexpr auto Groups = "Groups";
                constexpr auto Layout = "Layout";
                constexpr auto HitAreas = "HitAreas";

                constexpr auto Moc = "Moc";
                constexpr auto Textures = "Textures";
                constexpr auto Physics = "Physics";
                constexpr auto Pose = "Pose";
                constexpr auto Expressions = "Expressions";
                constexpr auto Motions = "Motions";

                constexpr auto UserData = "UserData";
                constexpr auto Name = "Name";
                constexpr auto FilePath = "File";
                constexpr auto Id = "Id";
                constexpr auto Ids = "Ids";
                // const QString &Target = "Target";

                // Motions
                // const QString &Idle = "Idle";
                // const QString &TapBody = "TapBody";
                // const QString &PinchIn = "PinchIn";
                // const QString &PinchOut = "PinchOut";
                // const QString &Shake = "Shake";
                // const QString &FlickHead = "FlickHead";
                // const QString &Parameter = "Parameter";

                constexpr auto SoundPath = "Sound";
                constexpr auto FadeInTime = "FadeInTime";
                constexpr auto FadeOutTime = "FadeOutTime";

                // Layout
                // const QString &CenterX = "CenterX";
                // const QString &CenterY = "CenterY";
                // const QString &X = "X";
                // const QString &Y = "Y";
                // const QString &Width = "Width";
                // const QString &Height = "Height";

                constexpr auto LipSync = "LipSync";
                constexpr auto EyeBlink = "EyeBlink";

                // const QString &InitParameter = "init_param";
                // const QString &InitPartsVisible = "init_parts_visible";
                // const QString &Val = "val";

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
            } // namespace

            // キーが存在するかどうかのチェック
            bool CubismModelSettingJson::IsExistModelFile() const
            {
                const auto &node = frequentJsonValues[FrequentNode_Moc];
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistTextureFiles() const
            {
                const auto &node = frequentJsonValues[FrequentNode_Textures];
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistHitAreas() const
            {
                const auto &node = (frequentJsonValues[FrequentNode_HitAreas]);
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistPhysicsFile() const
            {
                const auto &node = (frequentJsonValues[FrequentNode_Physics]);
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistPoseFile() const
            {
                const auto &node = (frequentJsonValues[FrequentNode_Pose]);
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistExpressionFile() const
            {
                const auto &node = (frequentJsonValues[FrequentNode_Expressions]);
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistMotionGroups() const
            {
                const auto &node = frequentJsonValues[FrequentNode_Motions];
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistMotionGroupName(const QString &groupName) const
            {
                const auto node = (frequentJsonValues[FrequentNode_Motions]).toObject()[groupName];
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistMotionSoundFile(const QString &groupName, int index) const
            {
                const auto node = (frequentJsonValues[FrequentNode_Motions]).toObject()[groupName].toArray()[index].toObject()[SoundPath];
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistMotionFadeIn(const QString &groupName, int index) const
            {
                const auto node = (frequentJsonValues[FrequentNode_Motions]).toObject()[groupName].toArray()[index].toObject()[FadeInTime];
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistMotionFadeOut(const QString &groupName, int index) const
            {
                const auto node = (frequentJsonValues[FrequentNode_Motions]).toObject()[groupName].toArray()[index].toObject()[FadeOutTime];
                return !node.isUndefined() && !node.isNull();
            }
            bool CubismModelSettingJson::IsExistUserDataFile() const
            {
                return !_json[FileReferences][UserData].isNull();
            }

            bool CubismModelSettingJson::IsExistEyeBlinkParameters() const
            {
                if (frequentJsonValues[FrequentNode_Groups].isNull() || frequentJsonValues[FrequentNode_Groups].isUndefined())
                {
                    return false;
                }

                for (int i = 0; i < frequentJsonValues[FrequentNode_Groups].toArray().size(); ++i)
                {
                    if (frequentJsonValues[FrequentNode_Groups].toArray()[i].toObject()[Name].toString() == EyeBlink)
                    {
                        return true;
                    }
                }
                return false;
            }

            bool CubismModelSettingJson::IsExistLipSyncParameters() const
            {
                if (frequentJsonValues[FrequentNode_Groups].isNull() || frequentJsonValues[FrequentNode_Groups].isUndefined())
                {
                    return false;
                }

                for (int i = 0; i < frequentJsonValues[FrequentNode_Groups].toArray().size(); ++i)
                {
                    if (frequentJsonValues[FrequentNode_Groups].toArray()[i].toObject()[Name].toString() == LipSync)
                    {
                        return true;
                    }
                }
                return false;
            }

            CubismModelSettingJson::CubismModelSettingJson(const QByteArray &buffer)
            {
                _json = QJsonDocument::fromJson(buffer).object();

                frequentJsonValues.clear();

                // 順番はenum FrequentNodeと一致させる
                //
                frequentJsonValues = { (_json[Groups]),
                                       (_json[FileReferences].toObject()[Moc]),
                                       (_json[FileReferences].toObject()[Motions]),
                                       (_json[FileReferences].toObject()[Expressions]),
                                       (_json[FileReferences].toObject()[Textures]),
                                       (_json[FileReferences].toObject()[Physics]),
                                       (_json[FileReferences].toObject()[Pose]),
                                       (_json[HitAreas]) };
            }

            CubismModelSettingJson::~CubismModelSettingJson()
            {
            }

            const QString CubismModelSettingJson::GetModelFileName() const
            {
                if (!IsExistModelFile())
                    return "";
                return frequentJsonValues[FrequentNode_Moc].toString();
            }

            // テクスチャについて
            int CubismModelSettingJson::GetTextureCount() const
            {
                if (!IsExistTextureFiles())
                    return 0;
                return (frequentJsonValues[FrequentNode_Textures]).toArray().size();
            }

            const QString CubismModelSettingJson::GetTextureDirectory() const
            {
                return (frequentJsonValues[FrequentNode_Textures]).toString();
            }

            const QString CubismModelSettingJson::GetTextureFileName(int index) const
            {
                return (frequentJsonValues[FrequentNode_Textures]).toArray()[index].toString();
            }

            // あたり判定について
            int CubismModelSettingJson::GetHitAreasCount() const
            {
                if (!IsExistHitAreas())
                    return 0;
                return (frequentJsonValues[FrequentNode_HitAreas]).toArray().size();
            }

            CubismIdHandle CubismModelSettingJson::GetHitAreaId(int index) const
            {
                return CubismFramework::GetIdManager()->GetId(
                    (frequentJsonValues[FrequentNode_HitAreas]).toArray()[index].toObject()[Id].toString());
            }

            const QString CubismModelSettingJson::GetHitAreaName(int index) const
            {
                return (frequentJsonValues[FrequentNode_HitAreas]).toArray()[index].toObject()[Name].toString();
            }

            // 物理演算、パーツ切り替え、表情ファイルについて
            const QString CubismModelSettingJson::GetPhysicsFileName() const
            {
                if (!IsExistPhysicsFile())
                    return "";
                return (frequentJsonValues[FrequentNode_Physics]).toString();
            }

            const QString CubismModelSettingJson::GetPoseFileName() const
            {
                if (!IsExistPoseFile())
                    return "";
                return (frequentJsonValues[FrequentNode_Pose]).toString();
            }

            int CubismModelSettingJson::GetExpressionCount() const
            {
                if (!IsExistExpressionFile())
                    return 0;
                return (frequentJsonValues[FrequentNode_Expressions]).toArray().size();
            }

            const QString CubismModelSettingJson::GetExpressionName(int index) const
            {
                return (frequentJsonValues[FrequentNode_Expressions]).toArray()[index].toObject()[Name].toString();
            }

            const QString CubismModelSettingJson::GetExpressionFileName(int index) const
            {
                return (frequentJsonValues[FrequentNode_Expressions]).toArray()[index].toObject()[FilePath].toString();
            }

            // モーションについて
            int CubismModelSettingJson::GetMotionGroupCount() const
            {
                if (!IsExistMotionGroups())
                {
                    return 0;
                }
                return (frequentJsonValues[FrequentNode_Motions]).toArray().size();
            }

            const QString CubismModelSettingJson::GetMotionGroupName(int index) const
            {
                if (!IsExistMotionGroups())
                {
                    return {};
                }
                return (frequentJsonValues[FrequentNode_Motions]).toObject().keys()[index];
            }

            int CubismModelSettingJson::GetMotionCount(const QString &groupName) const
            {
                if (!IsExistMotionGroupName(groupName))
                    return 0;
                return (frequentJsonValues[FrequentNode_Motions]).toObject()[groupName].toArray().size();
            }

            const QString CubismModelSettingJson::GetMotionFileName(const QString &groupName, int index) const
            {
                if (!IsExistMotionGroupName(groupName))
                    return "";
                return (frequentJsonValues[FrequentNode_Motions]).toObject()[groupName].toArray()[index].toObject()[FilePath].toString();
            }

            const QString CubismModelSettingJson::GetMotionSoundFileName(const QString &groupName, int index) const
            {
                if (!IsExistMotionSoundFile(groupName, index))
                    return "";
                return (frequentJsonValues[FrequentNode_Motions]).toObject()[groupName].toArray()[index].toObject()[SoundPath].toString();
            }

            csmFloat32 CubismModelSettingJson::GetMotionFadeInTimeValue(const QString &groupName, int index) const
            {
                if (!IsExistMotionFadeIn(groupName, index))
                    return -1.0f;
                return (frequentJsonValues[FrequentNode_Motions])
                    .toObject()[groupName]
                    .toArray()[index]
                    .toObject()[FadeInTime]
                    .toVariant()
                    .toFloat();
            }

            csmFloat32 CubismModelSettingJson::GetMotionFadeOutTimeValue(const QString &groupName, int index) const
            {
                if (!IsExistMotionFadeOut(groupName, index))
                    return -1.0f;
                return (frequentJsonValues[FrequentNode_Motions])
                    .toObject()[groupName]
                    .toArray()[index]
                    .toObject()[FadeOutTime]
                    .toVariant()
                    .toFloat();
            }

            const QString CubismModelSettingJson::GetUserDataFile() const
            {
                if (!IsExistUserDataFile())
                {
                    return "";
                }
                return _json[FileReferences].toObject()[UserData].toString();
            }

            bool CubismModelSettingJson::GetLayoutMap(QMap<QString, csmFloat32> &outLayoutMap) const
            {
                auto /* csmMap<QString, Utils::Value *>*/ map = _json[Layout].toVariant().toMap();
                if (map.isEmpty())
                {
                    return false;
                }
                bool ret = false;
                for (auto map_ite = map.begin(); map_ite != map.end(); ++map_ite)
                {
                    outLayoutMap[map_ite.key()] = map_ite.value().toFloat();
                    ret = true;
                }
                return ret;
            }

            int CubismModelSettingJson::GetEyeBlinkParameterCount() const
            {
                if (!IsExistEyeBlinkParameters())
                {
                    return 0;
                }

                int num = 0;
                for (int i = 0; i < frequentJsonValues[FrequentNode_Groups].toArray().size(); i++)
                {
                    const QJsonValue refI = frequentJsonValues[FrequentNode_Groups].toArray()[i];
                    if (refI.isNull() || refI.isUndefined())
                    {
                        continue;
                    }

                    if (refI.toObject()[Name].toString() == EyeBlink)
                    {
                        num = refI.toObject()[Ids].toArray().size();
                        break;
                    }
                }

                return num;
            }

            CubismIdHandle CubismModelSettingJson::GetEyeBlinkParameterId(int index) const
            {
                if (!IsExistEyeBlinkParameters())
                {
                    return NULL;
                }

                for (int i = 0; i < frequentJsonValues[FrequentNode_Groups].toArray().size(); i++)
                {
                    const QJsonValue refI = frequentJsonValues[FrequentNode_Groups].toArray()[i];
                    if (refI.isNull() || refI.isUndefined())
                    {
                        continue;
                    }

                    if (refI.toObject()[Name].toString() == EyeBlink)
                    {
                        return CubismFramework::GetIdManager()->GetId(refI.toObject()[Ids].toArray()[index].toString());
                    }
                }
                return NULL;
            }

            int CubismModelSettingJson::GetLipSyncParameterCount() const
            {
                if (!IsExistLipSyncParameters())
                {
                    return 0;
                }

                int num = 0;
                for (int i = 0; i < frequentJsonValues[FrequentNode_Groups].toArray().size(); i++)
                {
                    const QJsonValue refI = frequentJsonValues[FrequentNode_Groups].toArray()[i];
                    if (refI.isNull() || refI.isUndefined())
                    {
                        continue;
                    }

                    if (refI.toObject()[Name].toString() == LipSync)
                    {
                        num = refI.toObject()[Ids].toArray().size();
                        break;
                    }
                }

                return num;
            }

            CubismIdHandle CubismModelSettingJson::GetLipSyncParameterId(int index) const
            {
                if (!IsExistLipSyncParameters())
                {
                    return NULL;
                }

                for (int i = 0; i < frequentJsonValues[FrequentNode_Groups].toArray().size(); i++)
                {
                    const QJsonValue refI = frequentJsonValues[FrequentNode_Groups].toArray()[i];
                    if (refI.isNull() || refI.isUndefined())
                    {
                        continue;
                    }

                    if (refI.toObject()[Name].toString() == LipSync)
                    {
                        return CubismFramework::GetIdManager()->GetId(refI.toObject()[Ids].toArray()[index].toString());
                    }
                }
                return NULL;
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
