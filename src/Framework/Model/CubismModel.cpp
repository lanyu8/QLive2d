/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismModel.hpp"

#include "Id/CubismId.hpp"
#include "Id/CubismIdManager.hpp"
#include "Rendering/CubismRenderer.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            static int IsBitSet(const csmUint8 byte, const csmUint8 mask)
            {
                return ((byte & mask) == mask);
            }

            CubismModel::CubismModel(Core::csmModel *model)
                : _model(model), _parameterValues(NULL), _parameterMaximumValues(NULL), _parameterMinimumValues(NULL), _partOpacities(NULL)
            {
            }

            CubismModel::~CubismModel()
            {
                CSM_FREE_ALLIGNED(_model);
            }

            csmFloat32 CubismModel::GetParameterValue(CubismIdHandle parameterId)
            {
                // 高速化のためにParameterIndexを取得できる機構になっているが、外部からの設定の時は呼び出し頻度が低いため不要
                const int parameterIndex = GetParameterIndex(parameterId);
                return GetParameterValue(parameterIndex);
            }

            void CubismModel::SetParameterValue(CubismIdHandle parameteId, csmFloat32 value, csmFloat32 weight)
            {
                const int index = GetParameterIndex(parameteId);
                SetParameterValue(index, value, weight);
            }

            void CubismModel::AddParameterValue(CubismIdHandle parameterId, csmFloat32 value, csmFloat32 weight)
            {
                const int index = GetParameterIndex(parameterId);
                AddParameterValue(index, value, weight);
            }

            void CubismModel::AddParameterValue(int parameterIndex, csmFloat32 value, csmFloat32 weight)
            {
                SetParameterValue(parameterIndex, (GetParameterValue(parameterIndex) + (value * weight)));
            }

            void CubismModel::MultiplyParameterValue(CubismIdHandle parameterId, csmFloat32 value, csmFloat32 weight)
            {
                const int index = GetParameterIndex(parameterId);
                MultiplyParameterValue(index, value, weight);
            }

            void CubismModel::MultiplyParameterValue(int parameterIndex, csmFloat32 value, csmFloat32 weight)
            {
                SetParameterValue(parameterIndex, (GetParameterValue(parameterIndex) * (1.0f + (value - 1.0f) * weight)));
            }

            void CubismModel::Update() const
            {
                // Update model.
                Core::csmUpdateModel(_model);

                // Reset dynamic drawable flags.
                Core::csmResetDrawableDynamicFlags(_model);
            }

            void CubismModel::SetPartOpacity(CubismIdHandle partId, csmFloat32 opacity)
            {
                // 高速化のためにPartIndexを取得できる機構になっているが、外部からの設定の時は呼び出し頻度が低いため不要
                const int index = GetPartIndex(partId);

                if (index < 0)
                {
                    return; // パーツが無いのでスキップ
                }

                SetPartOpacity(index, opacity);
            }

            void CubismModel::SetPartOpacity(int partIndex, csmFloat32 opacity)
            {
                if (_notExistPartOpacities.contains(partIndex))
                {
                    _notExistPartOpacities[partIndex] = opacity;
                    return;
                }

                //インデックスの範囲内検知
                CSM_ASSERT(0 <= partIndex && partIndex < GetPartCount());

                _partOpacities[partIndex] = opacity;
            }

            csmFloat32 CubismModel::GetPartOpacity(CubismIdHandle partId)
            {
                // 高速化のためにPartIndexを取得できる機構になっているが、外部からの設定の時は呼び出し頻度が低いため不要
                const int index = GetPartIndex(partId);

                if (index < 0)
                {
                    return 0; //パーツが無いのでスキップ
                }

                return GetPartOpacity(index);
            }

            csmFloat32 CubismModel::GetPartOpacity(int partIndex)
            {
                if (_notExistPartOpacities.contains(partIndex))
                {
                    // モデルに存在しないパーツIDの場合、非存在パーツリストから不透明度を返す
                    return _notExistPartOpacities[partIndex];
                }

                //インデックスの範囲内検知
                CSM_ASSERT(0 <= partIndex && partIndex < GetPartCount());

                return _partOpacities[partIndex];
            }

            int CubismModel::GetParameterCount() const
            {
                return Core::csmGetParameterCount(_model);
            }

            csmFloat32 CubismModel::GetParameterDefaultValue(csmUint32 parameterIndex) const
            {
                return Core::csmGetParameterDefaultValues(_model)[parameterIndex];
            }

            csmFloat32 CubismModel::GetParameterMaximumValue(csmUint32 parameterIndex) const
            {
                return Core::csmGetParameterMaximumValues(_model)[parameterIndex];
            }

            csmFloat32 CubismModel::GetParameterMinimumValue(csmUint32 parameterIndex) const
            {
                return Core::csmGetParameterMinimumValues(_model)[parameterIndex];
            }

            int CubismModel::GetParameterIndex(CubismIdHandle parameterId)
            {
                int parameterIndex;
                const int idCount = Core::csmGetParameterCount(_model);

                for (parameterIndex = 0; parameterIndex < idCount; ++parameterIndex)
                {
                    if (parameterId != _parameterIds[parameterIndex])
                    {
                        continue;
                    }

                    return parameterIndex;
                }

                // モデルに存在していない場合、非存在パラメータIDリスト内を検索し、そのインデックスを返す
                if (_notExistParameterId.contains(parameterId))
                {
                    return _notExistParameterId[parameterId];
                }

                // 非存在パラメータIDリストにない場合、新しく要素を追加する
                parameterIndex = Core::csmGetParameterCount(_model) + _notExistParameterId.size();

                _notExistParameterId[parameterId] = parameterIndex;
                //_notExistParameterValues.AppendKey(parameterIndex);

                return parameterIndex;
            }

            csmFloat32 CubismModel::GetParameterValue(int parameterIndex)
            {
                if (_notExistParameterValues.contains(parameterIndex))
                {
                    return _notExistParameterValues[parameterIndex];
                }

                //インデックスの範囲内検知
                CSM_ASSERT(0 <= parameterIndex && parameterIndex < GetParameterCount());

                return _parameterValues[parameterIndex];
            }

            void CubismModel::SetParameterValue(int parameterIndex, csmFloat32 value, csmFloat32 weight)
            {
                if (_notExistParameterValues.contains(parameterIndex))
                {
                    _notExistParameterValues[parameterIndex] =
                        (weight == 1) ? value : (_notExistParameterValues[parameterIndex] * (1 - weight)) + (value * weight);
                    return;
                }

                //インデックスの範囲内検知
                CSM_ASSERT(0 <= parameterIndex && parameterIndex < GetParameterCount());

                if (Core::csmGetParameterMaximumValues(_model)[parameterIndex] < value)
                {
                    value = Core::csmGetParameterMaximumValues(_model)[parameterIndex];
                }
                if (Core::csmGetParameterMinimumValues(_model)[parameterIndex] > value)
                {
                    value = Core::csmGetParameterMinimumValues(_model)[parameterIndex];
                }

                const auto val1 = _parameterValues[parameterIndex] = (_parameterValues[parameterIndex] * (1 - weight)) + (value * weight);
                _parameterValues[parameterIndex] = (weight == 1) ? value : val1;
            }

            csmFloat32 CubismModel::GetCanvasWidth() const
            {
                if (_model == NULL)
                {
                    return 0.0f;
                }

                Core::csmVector2 tmpSizeInPixels;
                Core::csmVector2 tmpOriginInPixels;
                csmFloat32 tmpPixelsPerUnit;

                Core::csmReadCanvasInfo(_model, &tmpSizeInPixels, &tmpOriginInPixels, &tmpPixelsPerUnit);

                return tmpSizeInPixels.X / tmpPixelsPerUnit;
            }

            csmFloat32 CubismModel::GetCanvasHeight() const
            {
                if (_model == NULL)
                {
                    return 0.0f;
                }

                Core::csmVector2 tmpSizeInPixels;
                Core::csmVector2 tmpOriginInPixels;
                csmFloat32 tmpPixelsPerUnit;

                Core::csmReadCanvasInfo(_model, &tmpSizeInPixels, &tmpOriginInPixels, &tmpPixelsPerUnit);

                return tmpSizeInPixels.Y / tmpPixelsPerUnit;
            }

            int CubismModel::GetDrawableIndex(CubismIdHandle drawableId) const
            {
                const int drawableCount = Core::csmGetDrawableCount(_model);

                for (int drawableIndex = 0; drawableIndex < drawableCount; ++drawableIndex)
                {
                    if (_drawableIds[drawableIndex] == drawableId)
                    {
                        return drawableIndex;
                    }
                }

                return -1;
            }

            const csmFloat32 *CubismModel::GetDrawableVertices(int drawableIndex) const
            {
                return reinterpret_cast<const csmFloat32 *>(GetDrawableVertexPositions(drawableIndex));
            }

            int CubismModel::GetPartIndex(CubismIdHandle partId)
            {
                int partIndex;
                const int idCount = Core::csmGetPartCount(_model);

                for (partIndex = 0; partIndex < idCount; ++partIndex)
                {
                    if (partId == _partIds[partIndex])
                    {
                        return partIndex;
                    }
                }

                const int partCount = Core::csmGetPartCount(_model);

                // モデルに存在していない場合、非存在パーツIDリスト内にあるかを検索し、そのインデックスを返す
                if (_notExistPartId.contains(partId))
                {
                    return _notExistPartId[partId];
                }

                // 非存在パーツIDリストにない場合、新しく要素を追加する
                partIndex = partCount + _notExistPartId.size();

                _notExistPartId[partId] = partIndex;
                //_notExistPartOpacities.AppendKey(partIndex);

                return partIndex;
            }

            void CubismModel::Initialize()
            {
                CSM_ASSERT(_model);

                _parameterValues = Core::csmGetParameterValues(_model);
                _partOpacities = Core::csmGetPartOpacities(_model);
                _parameterMaximumValues = Core::csmGetParameterMaximumValues(_model);
                _parameterMinimumValues = Core::csmGetParameterMinimumValues(_model);

                {
                    const auto parameterIds = Core::csmGetParameterIds(_model);
                    const int parameterCount = Core::csmGetParameterCount(_model);

                    for (int i = 0; i < parameterCount; ++i)
                    {
                        _parameterIds.append(CubismFramework::GetIdManager()->GetId(parameterIds[i]));
                    }
                }

                {
                    const auto partIds = Core::csmGetPartIds(_model);
                    const int partCount = Core::csmGetPartCount(_model);

                    for (int i = 0; i < partCount; ++i)
                    {
                        _partIds.append(CubismFramework::GetIdManager()->GetId(partIds[i]));
                    }
                }

                {
                    const auto drawableIds = Core::csmGetDrawableIds(_model);
                    const int drawableCount = Core::csmGetDrawableCount(_model);

                    for (int i = 0; i < drawableCount; ++i)
                    {
                        _drawableIds.append(CubismFramework::GetIdManager()->GetId(drawableIds[i]));
                    }
                }
            }

            CubismIdHandle CubismModel::GetDrawableId(int drawableIndex) const
            {
                const auto parameterIds = Core::csmGetDrawableIds(_model);
                return CubismFramework::GetIdManager()->GetId(parameterIds[drawableIndex]);
            }

            int CubismModel::GetPartCount() const
            {
                const int partCount = Core::csmGetPartCount(_model);
                return partCount;
            }

            const int *CubismModel::GetDrawableRenderOrders() const
            {
                const int *renderOrders = Core::csmGetDrawableRenderOrders(_model);
                return renderOrders;
            }

            int CubismModel::GetDrawableCount() const
            {
                const int drawableCount = Core::csmGetDrawableCount(_model);
                return drawableCount;
            }

            int CubismModel::GetDrawableTextureIndices(int drawableIndex) const
            {
                const int *textureIndices = Core::csmGetDrawableTextureIndices(_model);
                return textureIndices[drawableIndex];
            }

            int CubismModel::GetDrawableVertexIndexCount(int drawableIndex) const
            {
                const int *indexCounts = Core::csmGetDrawableIndexCounts(_model);
                return indexCounts[drawableIndex];
            }

            int CubismModel::GetDrawableVertexCount(int drawableIndex) const
            {
                const int *vertexCounts = Core::csmGetDrawableVertexCounts(_model);
                return vertexCounts[drawableIndex];
            }

            const csmUint16 *CubismModel::GetDrawableVertexIndices(int drawableIndex) const
            {
                const csmUint16 **indicesArray = Core::csmGetDrawableIndices(_model);
                return indicesArray[drawableIndex];
            }

            const Core::csmVector2 *CubismModel::GetDrawableVertexPositions(int drawableIndex) const
            {
                const Core::csmVector2 **verticesArray = Core::csmGetDrawableVertexPositions(_model);
                return verticesArray[drawableIndex];
            }

            const Core::csmVector2 *CubismModel::GetDrawableVertexUvs(int drawableIndex) const
            {
                const Core::csmVector2 **uvsArray = Core::csmGetDrawableVertexUvs(_model);
                return uvsArray[drawableIndex];
            }

            csmFloat32 CubismModel::GetDrawableOpacity(int drawableIndex) const
            {
                const csmFloat32 *opacities = Core::csmGetDrawableOpacities(_model);
                return opacities[drawableIndex];
            }

            int CubismModel::GetDrawableCulling(int drawableIndex) const
            {
                const Core::csmFlags *constantFlags = Core::csmGetDrawableConstantFlags(_model);
                return !IsBitSet(constantFlags[drawableIndex], Core::csmIsDoubleSided);
            }

            bool CubismModel::GetDrawableDynamicFlagIsVisible(int drawableIndex) const
            {
                const Core::csmFlags *dynamicFlags = Core::csmGetDrawableDynamicFlags(_model);
                return IsBitSet(dynamicFlags[drawableIndex], Core::csmIsVisible) != 0 ? true : false;
            }

            bool CubismModel::GetDrawableDynamicFlagVisibilityDidChange(int drawableIndex) const
            {
                const Core::csmFlags *dynamicFlags = Core::csmGetDrawableDynamicFlags(_model);
                return IsBitSet(dynamicFlags[drawableIndex], Core::csmVisibilityDidChange) != 0 ? true : false;
            }

            bool CubismModel::GetDrawableDynamicFlagOpacityDidChange(int drawableIndex) const
            {
                const Core::csmFlags *dynamicFlags = Core::csmGetDrawableDynamicFlags(_model);
                return IsBitSet(dynamicFlags[drawableIndex], Core::csmOpacityDidChange) != 0 ? true : false;
            }

            bool CubismModel::GetDrawableDynamicFlagDrawOrderDidChange(int drawableIndex) const
            {
                const Core::csmFlags *dynamicFlags = Core::csmGetDrawableDynamicFlags(_model);
                return IsBitSet(dynamicFlags[drawableIndex], Core::csmDrawOrderDidChange) != 0 ? true : false;
            }

            bool CubismModel::GetDrawableDynamicFlagRenderOrderDidChange(int drawableIndex) const
            {
                const Core::csmFlags *dynamicFlags = Core::csmGetDrawableDynamicFlags(_model);
                return IsBitSet(dynamicFlags[drawableIndex], Core::csmRenderOrderDidChange) != 0 ? true : false;
            }

            bool CubismModel::GetDrawableDynamicFlagVertexPositionsDidChange(int drawableIndex) const
            {
                const Core::csmFlags *dynamicFlags = Core::csmGetDrawableDynamicFlags(_model);
                return IsBitSet(dynamicFlags[drawableIndex], Core::csmVertexPositionsDidChange) != 0 ? true : false;
            }

            Rendering::CubismRenderer::CubismBlendMode CubismModel::GetDrawableBlendMode(int drawableIndex) const
            {
                const csmUint8 *constantFlags = Core::csmGetDrawableConstantFlags(_model);
                return (IsBitSet(constantFlags[drawableIndex], Core::csmBlendAdditive)) ?
                           Rendering::CubismRenderer::CubismBlendMode_Additive :
                           (IsBitSet(constantFlags[drawableIndex], Core::csmBlendMultiplicative)) ?
                           Rendering::CubismRenderer::CubismBlendMode_Multiplicative :
                           Rendering::CubismRenderer::CubismBlendMode_Normal;
            }

            bool CubismModel::GetDrawableInvertedMask(int drawableIndex) const
            {
                const csmUint8 *constantFlags = Core::csmGetDrawableConstantFlags(_model);
                return IsBitSet(constantFlags[drawableIndex], Core::csmIsInvertedMask) != 0 ? true : false;
            }

            const int **CubismModel::GetDrawableMasks() const
            {
                const int **masks = Core::csmGetDrawableMasks(_model);
                return masks;
            }

            const int *CubismModel::GetDrawableMaskCounts() const
            {
                const int *maskCounts = Core::csmGetDrawableMaskCounts(_model);
                return maskCounts;
            }

            void CubismModel::LoadParameters()
            {
                int parameterCount = Core::csmGetParameterCount(_model);
                const int savedParameterCount = _savedParameters.size();

                if (parameterCount > savedParameterCount)
                {
                    parameterCount = savedParameterCount;
                }

                for (int i = 0; i < parameterCount; ++i)
                {
                    _parameterValues[i] = _savedParameters[i];
                }
            }

            void CubismModel::SaveParameters()
            {
                const int parameterCount = Core::csmGetParameterCount(_model);
                const int savedParameterCount = _savedParameters.size();

                for (int i = 0; i < parameterCount; ++i)
                {
                    if (i < savedParameterCount)
                    {
                        _savedParameters[i] = _parameterValues[i];
                    }
                    else
                    {
                        _savedParameters.append(_parameterValues[i]);
                    }
                }
            }

            Core::csmModel *CubismModel::GetModel() const
            {
                return _model;
            }

            bool CubismModel::IsUsingMasking() const
            {
                for (int d = 0; d < Core::csmGetDrawableCount(_model); ++d)
                {
                    if (Core::csmGetDrawableMaskCounts(_model)[d] <= 0)
                    {
                        continue;
                    }
                    return true;
                }

                return false;
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
