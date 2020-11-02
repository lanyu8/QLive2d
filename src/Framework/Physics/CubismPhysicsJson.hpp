/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Id/CubismId.hpp"
#include "Math/CubismVector2.hpp"
#include "Utils/CubismJson.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            /**
             * @brief physics3.jsonのコンテナ
             *
             * physics3.jsonのコンテナ。
             */
            class CubismPhysicsJson
            {
              public:
                CubismPhysicsJson(const QByteArray &buffer);
                virtual ~CubismPhysicsJson();
                CubismVector2 GetGravity() const;
                CubismVector2 GetWind() const;
                int GetSubRigCount() const;
                int GetTotalInputCount() const;
                int GetTotalOutputCount() const;
                int GetVertexCount() const;
                csmFloat32 GetNormalizationPositionMinimumValue(int physicsSettingIndex) const;
                csmFloat32 GetNormalizationPositionMaximumValue(int physicsSettingIndex) const;
                csmFloat32 GetNormalizationPositionDefaultValue(int physicsSettingIndex) const;
                csmFloat32 GetNormalizationAngleMinimumValue(int physicsSettingIndex) const;
                csmFloat32 GetNormalizationAngleMaximumValue(int physicsSettingIndex) const;
                csmFloat32 GetNormalizationAngleDefaultValue(int physicsSettingIndex) const;
                int GetInputCount(int physicsSettingIndex) const;
                csmFloat32 GetInputWeight(int physicsSettingIndex, int inputIndex) const;
                bool GetInputReflect(int physicsSettingIndex, int inputIndex) const;
                const QString GetInputType(int physicsSettingIndex, int inputIndex) const;
                CubismIdHandle GetInputSourceId(int physicsSettingIndex, int inputIndex) const;
                int GetOutputCount(int physicsSettingIndex) const;
                int GetOutputVertexIndex(int physicsSettingIndex, int outputIndex) const;
                csmFloat32 GetOutputAngleScale(int physicsSettingIndex, int outputIndex) const;
                csmFloat32 GetOutputWeight(int physicsSettingIndex, int outputIndex) const;
                CubismIdHandle GetOutputsDestinationId(int physicsSettingIndex, int outputIndex) const;
                const QString GetOutputType(int physicsSettingIndex, int outputIndex) const;
                bool GetOutputReflect(int physicsSettingIndex, int outputIndex) const;
                int GetParticleCount(int physicsSettingIndex) const;
                csmFloat32 GetParticleMobility(int physicsSettingIndex, int vertexIndex) const;
                csmFloat32 GetParticleDelay(int physicsSettingIndex, int vertexIndex) const;
                csmFloat32 GetParticleAcceleration(int physicsSettingIndex, int vertexIndex) const;
                csmFloat32 GetParticleRadius(int physicsSettingIndex, int vertexIndex) const;
                CubismVector2 GetParticlePosition(int physicsSettingIndex, int vertexIndex) const;

              private:
                const Utils::CubismJson _json; ///< physics3.jsonデータ
            };

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
