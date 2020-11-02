/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismPhysicsJson.hpp"

#include "Id/CubismIdManager.hpp"

namespace Live2D
{
    namespace Cubism::Framework
    {

        /// Physics Json Constants
        namespace
        {
            // JSON keys
            constexpr auto Position = "Position";
            constexpr auto X = "X";
            constexpr auto Y = "Y";
            constexpr auto Angle = "Angle";
            constexpr auto Type = "Type";
            constexpr auto Id = "Id";

            // Meta
            constexpr auto Meta = "Meta";
            constexpr auto EffectiveForces = "EffectiveForces";
            constexpr auto TotalInputCount = "TotalInputCount";
            constexpr auto TotalOutputCount = "TotalOutputCount";
            constexpr auto PhysicsSettingCount = "PhysicsSettingCount";
            constexpr auto Gravity = "Gravity";
            constexpr auto Wind = "Wind";
            constexpr auto VertexCount = "VertexCount";

            // PhysicsSettings
            constexpr auto PhysicsSettings = "PhysicsSettings";
            constexpr auto Normalization = "Normalization";
            constexpr auto Minimum = "Minimum";
            constexpr auto Maximum = "Maximum";
            constexpr auto Default = "Default";
            constexpr auto Reflect = "Reflect";

            constexpr auto Weight = "Weight";

            // Input
            constexpr auto Input = "Input";
            constexpr auto Source = "Source";

            // Output
            constexpr auto Output = "Output";
            constexpr auto Scale = "Scale";
            constexpr auto VertexIndex = "VertexIndex";
            constexpr auto Destination = "Destination";

            // Particle
            constexpr auto Vertices = "Vertices";
            constexpr auto Mobility = "Mobility";
            constexpr auto Delay = "Delay";
            constexpr auto Radius = "Radius";
            constexpr auto Acceleration = "Acceleration";
        } // namespace

        CubismPhysicsJson::CubismPhysicsJson(const QByteArray &buffer) : _json(QJsonDocument::fromJson(buffer).object())
        {
        }

        CubismPhysicsJson::~CubismPhysicsJson()
        {
        }

        CubismVector2 CubismPhysicsJson::GetGravity() const
        {
            CubismVector2 ret;
            ret.X = _json[Meta][EffectiveForces][Gravity][X].toDouble();
            ret.Y = _json[Meta][EffectiveForces][Gravity][Y].toDouble();
            return ret;
        }

        CubismVector2 CubismPhysicsJson::GetWind() const
        {
            CubismVector2 ret;
            ret.X = _json[Meta][EffectiveForces][Wind][X].toDouble();
            ret.Y = _json[Meta][EffectiveForces][Wind][Y].toDouble();
            return ret;
        }

        int CubismPhysicsJson::GetSubRigCount() const
        {
            return _json[Meta][PhysicsSettingCount].toInt();
        }

        int CubismPhysicsJson::GetTotalInputCount() const
        {
            return _json[Meta][TotalInputCount].toInt();
        }

        int CubismPhysicsJson::GetTotalOutputCount() const
        {
            return _json[Meta][TotalOutputCount].toInt();
        }

        int CubismPhysicsJson::GetVertexCount() const
        {
            return _json[Meta][VertexCount].toInt();
        }

        // Input
        csmFloat32 CubismPhysicsJson::GetNormalizationPositionMinimumValue(int physicsSettingIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Normalization][Position][Minimum].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetNormalizationPositionMaximumValue(int physicsSettingIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Normalization][Position][Maximum].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetNormalizationPositionDefaultValue(int physicsSettingIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Normalization][Position][Default].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetNormalizationAngleMinimumValue(int physicsSettingIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Normalization][Angle][Minimum].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetNormalizationAngleMaximumValue(int physicsSettingIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Normalization][Angle][Maximum].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetNormalizationAngleDefaultValue(int physicsSettingIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Normalization][Angle][Default].toDouble();
        }

        int CubismPhysicsJson::GetInputCount(int physicsSettingIndex) const
        {
            return static_cast<int>(_json[PhysicsSettings][physicsSettingIndex][Input].toArray().size());
        }

        csmFloat32 CubismPhysicsJson::GetInputWeight(int physicsSettingIndex, int inputIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Input][inputIndex][Weight].toDouble();
        }

        bool CubismPhysicsJson::GetInputReflect(int physicsSettingIndex, int inputIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Input][inputIndex][Reflect].toBool();
        }

        const QString CubismPhysicsJson::GetInputType(int physicsSettingIndex, int inputIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Input][inputIndex][Type].toString();
        }

        CubismIdHandle CubismPhysicsJson::GetInputSourceId(int physicsSettingIndex, int inputIndex) const
        {
            return CubismFramework::GetIdManager()->GetId(_json[PhysicsSettings][physicsSettingIndex][Input][inputIndex][Source][Id].toString());
        }

        // Output
        int CubismPhysicsJson::GetOutputCount(int physicsSettingIndex) const
        {
            return static_cast<int>(_json[PhysicsSettings][physicsSettingIndex][Output].toArray().size());
        }

        int CubismPhysicsJson::GetOutputVertexIndex(int physicsSettingIndex, int outputIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][VertexIndex].toInt();
        }

        csmFloat32 CubismPhysicsJson::GetOutputAngleScale(int physicsSettingIndex, int outputIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][Scale].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetOutputWeight(int physicsSettingIndex, int outputIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][Weight].toDouble();
        }

        CubismIdHandle CubismPhysicsJson::GetOutputsDestinationId(int physicsSettingIndex, int outputIndex) const
        {
            const auto str = _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][Destination][Id].toString();
            return CubismFramework::GetIdManager()->GetId(str);
        }

        const QString CubismPhysicsJson::GetOutputType(int physicsSettingIndex, int outputIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][Type].toString();
        }

        bool CubismPhysicsJson::GetOutputReflect(int physicsSettingIndex, int outputIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][Reflect].toBool();
        }

        // Particle
        int CubismPhysicsJson::GetParticleCount(int physicsSettingIndex) const
        {
            return static_cast<int>(_json[PhysicsSettings][physicsSettingIndex][Vertices].toArray().size());
        }

        csmFloat32 CubismPhysicsJson::GetParticleMobility(int physicsSettingIndex, int vertexIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Mobility].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetParticleDelay(int physicsSettingIndex, int vertexIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Delay].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetParticleAcceleration(int physicsSettingIndex, int vertexIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Acceleration].toDouble();
        }

        csmFloat32 CubismPhysicsJson::GetParticleRadius(int physicsSettingIndex, int vertexIndex) const
        {
            return _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Radius].toDouble();
        }

        CubismVector2 CubismPhysicsJson::GetParticlePosition(int physicsSettingIndex, int vertexIndex) const
        {
            return CubismVector2(_json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Position][X].toDouble(),
                                 _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Position][Y].toDouble());
        }
    } // namespace Cubism::Framework
} // namespace Live2D
