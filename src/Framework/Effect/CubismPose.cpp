/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismPose.hpp"

#include "Id/CubismIdManager.hpp"

using namespace Live2D::Cubism::Framework;

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            namespace
            {
                const csmFloat32 Epsilon = 0.001f;
                const csmFloat32 DefaultFadeInSeconds = 0.5f;

                // Pose.jsonのタグ
                const QString FadeIn = "FadeInTime";
                const QString Link = "Link";
                const QString Groups = "Groups";
                const QString Id = "Id";
            } // namespace

            CubismPose::PartData::PartData()
            {
            }

            CubismPose::PartData::~PartData()
            {
            }

            CubismPose::PartData::PartData(const PartData &v) : ParameterIndex(0), PartIndex(0)
            {
                PartId = v.PartId;

                for (QVector<PartData>::const_iterator ite = v.Link.begin(); ite != v.Link.end(); ++ite)
                {
                    Link.append(*ite);
                }
            }

            CubismPose::PartData &CubismPose::PartData::operator=(const PartData &v)
            {
                PartId = v.PartId;

                for (QVector<PartData>::const_iterator ite = v.Link.begin(); ite != v.Link.end(); ++ite)
                {
                    Link.append(*ite);
                }

                return (*this);
            }

            void CubismPose::PartData::Initialize(CubismModel *model)
            {
                ParameterIndex = model->GetParameterIndex(PartId);
                PartIndex = model->GetPartIndex(PartId);

                model->SetParameterValue(ParameterIndex, 1);
            }

            CubismPose::CubismPose() : _fadeTimeSeconds(DefaultFadeInSeconds), _lastModel(NULL)
            {
            }

            CubismPose::~CubismPose()
            {
            }

            CubismPose *CubismPose::Create(const QByteArray &data)
            {
                CubismPose *ret = CSM_NEW CubismPose();
                QJsonDocument d = QJsonDocument::fromJson(data);
                Utils::CubismJson root = d.object();

                // フェード時間の指定
                if (!root[FadeIn].isNull())
                {
                    ret->_fadeTimeSeconds = root[FadeIn].toDouble(DefaultFadeInSeconds);

                    if (ret->_fadeTimeSeconds < 0.0f)
                    {
                        ret->_fadeTimeSeconds = DefaultFadeInSeconds;
                    }
                }

                // パーツグループ
                const auto poseListInfo = root[Groups].toArray();
                const int poseCount = poseListInfo.size();

                for (int poseIndex = 0; poseIndex < poseCount; ++poseIndex)
                {
                    const auto idListInfo = poseListInfo[poseIndex].toArray();
                    const int idCount = idListInfo.size();
                    int groupCount = 0;

                    for (int groupIndex = 0; groupIndex < idCount; ++groupIndex)
                    {
                        const auto partInfo = idListInfo[groupIndex].toObject();
                        PartData partData;
                        const CubismIdHandle parameterId = CubismFramework::GetIdManager()->GetId(partInfo[Id].toString());

                        partData.PartId = parameterId;

                        // リンクするパーツの設定
                        if (!partInfo[Link].isUndefined())
                        {
                            const auto linkListInfo = partInfo[Link].toArray();
                            const int linkCount = linkListInfo.size();

                            for (int linkIndex = 0; linkIndex < linkCount; ++linkIndex)
                            {
                                PartData linkPart;
                                const CubismIdHandle linkId = CubismFramework::GetIdManager()->GetId(linkListInfo[linkIndex].toString());

                                linkPart.PartId = linkId;

                                partData.Link.append(linkPart);
                            }
                        }

                        ret->_partGroups.append(partData);

                        ++groupCount;
                    }

                    ret->_partGroupCounts.append(groupCount);
                }

                // Utils::CubismJson::Delete(json);

                return ret;
            }

            void CubismPose::Delete(CubismPose *pose)
            {
                CSM_DELETE_SELF(CubismPose, pose);
            }

            void CubismPose::Reset(CubismModel *model)
            {
                int beginIndex = 0;

                for (auto i = 0; i < _partGroupCounts.size(); ++i)
                {
                    const int groupCount = _partGroupCounts[i];

                    for (int j = beginIndex; j < beginIndex + groupCount; ++j)
                    {
                        _partGroups[j].Initialize(model);

                        const int partsIndex = _partGroups[j].PartIndex;
                        const int paramIndex = _partGroups[j].ParameterIndex;

                        if (partsIndex < 0)
                        {
                            continue;
                        }

                        model->SetPartOpacity(partsIndex, (j == beginIndex ? 1.0f : 0.0f));
                        model->SetParameterValue(paramIndex, (j == beginIndex ? 1.0f : 0.0f));

                        for (auto k = 0; k < _partGroups[j].Link.size(); ++k)
                        {
                            _partGroups[j].Link[k].Initialize(model);
                        }
                    }

                    beginIndex += groupCount;
                }
            }

            void CubismPose::CopyPartOpacities(CubismModel *model)
            {
                for (auto groupIndex = 0; groupIndex < _partGroups.size(); ++groupIndex)
                {
                    PartData &partData = _partGroups[groupIndex];

                    if (partData.Link.size() == 0)
                    {
                        continue; // 連動するパラメータはない
                    }

                    const int partIndex = _partGroups[groupIndex].PartIndex;
                    const csmFloat32 opacity = model->GetPartOpacity(partIndex);

                    for (auto linkIndex = 0; linkIndex < partData.Link.size(); ++linkIndex)
                    {
                        PartData &linkPart = partData.Link[linkIndex];
                        const int linkPartIndex = linkPart.PartIndex;

                        if (linkPartIndex < 0)
                        {
                            continue;
                        }

                        model->SetPartOpacity(linkPartIndex, opacity);
                    }
                }
            }

            void CubismPose::DoFade(CubismModel *model, csmFloat32 deltaTimeSeconds, int beginIndex, int partGroupCount)
            {
                int visiblePartIndex = -1;
                csmFloat32 newOpacity = 1.0f;

                const csmFloat32 Phi = 0.5f;
                const csmFloat32 BackOpacityThreshold = 0.15f;

                // 現在、表示状態になっているパーツを取得
                for (int i = beginIndex; i < beginIndex + partGroupCount; ++i)
                {
                    const int partIndex = _partGroups[i].PartIndex;
                    const int paramIndex = _partGroups[i].ParameterIndex;

                    if (model->GetParameterValue(paramIndex) > Epsilon)
                    {
                        if (visiblePartIndex >= 0)
                        {
                            break;
                        }

                        visiblePartIndex = i;
                        newOpacity = model->GetPartOpacity(partIndex);

                        // 新しい不透明度を計算
                        newOpacity += (deltaTimeSeconds / _fadeTimeSeconds);

                        if (newOpacity > 1.0f)
                        {
                            newOpacity = 1.0f;
                        }
                    }
                }

                if (visiblePartIndex < 0)
                {
                    visiblePartIndex = 0;
                    newOpacity = 1.0f;
                }

                //  表示パーツ、非表示パーツの不透明度を設定する
                for (int i = beginIndex; i < beginIndex + partGroupCount; ++i)
                {
                    const int partsIndex = _partGroups[i].PartIndex;

                    //  表示パーツの設定
                    if (visiblePartIndex == i)
                    {
                        model->SetPartOpacity(partsIndex, newOpacity); // 先に設定
                    }
                    // 非表示パーツの設定
                    else
                    {
                        csmFloat32 opacity = model->GetPartOpacity(partsIndex);
                        csmFloat32 a1; // 計算によって求められる不透明度

                        if (newOpacity < Phi)
                        {
                            a1 = newOpacity * (Phi - 1) / Phi + 1.0f; // (0,1),(phi,phi)を通る直線式
                        }
                        else
                        {
                            a1 = (1 - newOpacity) * Phi / (1.0f - Phi); // (1,0),(phi,phi)を通る直線式
                        }

                        // 背景の見える割合を制限する場合
                        const csmFloat32 backOpacity = (1.0f - a1) * (1.0f - newOpacity);

                        if (backOpacity > BackOpacityThreshold)
                        {
                            a1 = 1.0f - BackOpacityThreshold / (1.0f - newOpacity);
                        }

                        if (opacity > a1)
                        {
                            opacity = a1; // 計算の不透明度よりも大きければ（濃ければ）不透明度を上げる
                        }

                        model->SetPartOpacity(partsIndex, opacity);
                    }
                }
            }

            void CubismPose::UpdateParameters(CubismModel *model, csmFloat32 deltaTimeSeconds)
            {
                // 前回のモデルと同じではないときは初期化が必要
                if (model != _lastModel)
                {
                    // パラメータインデックスの初期化
                    Reset(model);
                }

                _lastModel = model;

                // 設定から時間を変更すると、経過時間がマイナスになることがあるので、経過時間0として対応。
                if (deltaTimeSeconds < 0.0f)
                {
                    deltaTimeSeconds = 0.0f;
                }

                int beginIndex = 0;

                for (auto i = 0; i < _partGroupCounts.size(); i++)
                {
                    const int partGroupCount = _partGroupCounts[i];

                    DoFade(model, deltaTimeSeconds, beginIndex, partGroupCount);

                    beginIndex += partGroupCount;
                }

                CopyPartOpacities(model);
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
