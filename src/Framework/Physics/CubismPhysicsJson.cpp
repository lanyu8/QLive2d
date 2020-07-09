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
    namespace Cubism
    {
        namespace Framework
        {

            /// Physics Json Constants
            namespace
            {
                // JSON keys
                const QString Position = "Position";
                const QString X = "X";
                const QString Y = "Y";
                const QString Angle = "Angle";
                const QString Type = "Type";
                const QString Id = "Id";

                // Meta
                const QString Meta = "Meta";
                const QString EffectiveForces = "EffectiveForces";
                const QString TotalInputCount = "TotalInputCount";
                const QString TotalOutputCount = "TotalOutputCount";
                const QString PhysicsSettingCount = "PhysicsSettingCount";
                const QString Gravity = "Gravity";
                const QString Wind = "Wind";
                const QString VertexCount = "VertexCount";

                // PhysicsSettings
                const QString PhysicsSettings = "PhysicsSettings";
                const QString Normalization = "Normalization";
                const QString Minimum = "Minimum";
                const QString Maximum = "Maximum";
                const QString Default = "Default";
                const QString Reflect = "Reflect";
                const QString Weight = "Weight";

                // Input
                const QString Input = "Input";
                const QString Source = "Source";

                // Output
                const QString Output = "Output";
                const QString Scale = "Scale";
                const QString VertexIndex = "VertexIndex";
                const QString Destination = "Destination";

                // Particle
                const QString Vertices = "Vertices";
                const QString Mobility = "Mobility";
                const QString Delay = "Delay";
                const QString Radius = "Radius";
                const QString Acceleration = "Acceleration";
            } // namespace

            CubismPhysicsJson::CubismPhysicsJson(const QByteArray &buffer)
            {
                _json = QJsonDocument::fromJson(buffer).object();
            }

            CubismPhysicsJson::~CubismPhysicsJson()
            {
            }

            CubismVector2 CubismPhysicsJson::GetGravity() const
            {
                CubismVector2 ret;
                ret.X = _json[Meta][EffectiveForces][Gravity][X].toVariant().toFloat();
                ret.Y = _json[Meta][EffectiveForces][Gravity][Y].toVariant().toFloat();
                return ret;
            }

            CubismVector2 CubismPhysicsJson::GetWind() const
            {
                CubismVector2 ret;
                ret.X = _json[Meta][EffectiveForces][Wind][X].toVariant().toFloat();
                ret.Y = _json[Meta][EffectiveForces][Wind][Y].toVariant().toFloat();
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
                return _json[PhysicsSettings][physicsSettingIndex][Normalization][Position][Minimum].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetNormalizationPositionMaximumValue(int physicsSettingIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Normalization][Position][Maximum].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetNormalizationPositionDefaultValue(int physicsSettingIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Normalization][Position][Default].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetNormalizationAngleMinimumValue(int physicsSettingIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Normalization][Angle][Minimum].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetNormalizationAngleMaximumValue(int physicsSettingIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Normalization][Angle][Maximum].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetNormalizationAngleDefaultValue(int physicsSettingIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Normalization][Angle][Default].toVariant().toFloat();
            }

            int CubismPhysicsJson::GetInputCount(int physicsSettingIndex) const
            {
                return static_cast<int>(_json[PhysicsSettings][physicsSettingIndex][Input].toArray().size());
            }

            csmFloat32 CubismPhysicsJson::GetInputWeight(int physicsSettingIndex, int inputIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Input][inputIndex][Weight].toVariant().toFloat();
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
                return CubismFramework::GetIdManager()->GetId(
                    _json[PhysicsSettings][physicsSettingIndex][Input][inputIndex][Source][Id].toString());
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
                return _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][Scale].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetOutputWeight(int physicsSettingIndex, int outputIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][Weight].toVariant().toFloat();
            }

            CubismIdHandle CubismPhysicsJson::GetOutputsDestinationId(int physicsSettingIndex, int outputIndex) const
            {
                return CubismFramework::GetIdManager()->GetId(
                    _json[PhysicsSettings][physicsSettingIndex][Output][outputIndex][Destination][Id].toString());
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
                return _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Mobility].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetParticleDelay(int physicsSettingIndex, int vertexIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Delay].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetParticleAcceleration(int physicsSettingIndex, int vertexIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Acceleration].toVariant().toFloat();
            }

            csmFloat32 CubismPhysicsJson::GetParticleRadius(int physicsSettingIndex, int vertexIndex) const
            {
                return _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Radius].toVariant().toFloat();
            }

            CubismVector2 CubismPhysicsJson::GetParticlePosition(int physicsSettingIndex, int vertexIndex) const
            {
                return CubismVector2(_json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Position][X].toVariant().toFloat(),
                                     _json[PhysicsSettings][physicsSettingIndex][Vertices][vertexIndex][Position][Y].toVariant().toFloat());
            }
        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
