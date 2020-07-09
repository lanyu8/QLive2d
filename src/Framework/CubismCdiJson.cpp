/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismCdiJson.hpp"

//--------- LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            namespace
            {
                // JSON keys
                // const QString &Version = "Version";
                const QString Parameters = "Parameters";
                const QString ParameterGroups = "ParameterGroups";
                const QString Parts = "Parts";
                const QString Id = "Id";
                const QString GroupId = "GroupId";
                const QString Name = "Name";
            } // namespace

            CubismCdiJson::CubismCdiJson(const QByteArray &buffer)
            {
                _json = QJsonDocument::fromJson(buffer).object();
            }

            CubismCdiJson::~CubismCdiJson()
            {
            }

            // キーが存在するかどうかのチェック
            bool CubismCdiJson::IsExistParameters() const
            {
                const auto &node = _json[Parameters];
                return !node.isNull() && !node.isUndefined();
            }

            bool CubismCdiJson::IsExistParameterGroups() const
            {
                const auto &node = _json[ParameterGroups];
                return !node.isNull() && !node.isUndefined();
            }

            bool CubismCdiJson::IsExistParts() const
            {
                const auto &node = _json[Parts];
                return !node.isNull() && !node.isUndefined();
            }

            // パラメータについて
            int CubismCdiJson::GetParametersCount()
            {
                if (!IsExistParameters())
                    return 0;
                return _json[Parameters].toArray().size();
            }

            const QString CubismCdiJson::GetParametersId(int index)
            {
                return _json[Parameters].toArray()[index].toObject()[Id].toString();
            }

            const QString CubismCdiJson::GetParametersGroupId(int index)
            {
                return _json[Parameters].toArray()[index].toObject()[GroupId].toString();
            }

            const QString CubismCdiJson::GetParametersName(int index)
            {
                return _json[Parameters].toArray()[index].toObject()[Name].toString();
            }

            // パラメータグループについて
            int CubismCdiJson::GetParameterGroupsCount()
            {
                if (!IsExistParameterGroups())
                    return 0;
                return _json[ParameterGroups].toArray().size();
            }

            const QString CubismCdiJson::GetParameterGroupsId(int index)
            {
                return _json[ParameterGroups].toArray()[index].toObject()[Id].toString();
            }

            const QString CubismCdiJson::GetParameterGroupsGroupId(int index)
            {
                return _json[ParameterGroups].toArray()[index].toObject()[GroupId].toString();
            }

            const QString CubismCdiJson::GetParameterGroupsName(int index)
            {
                return _json[ParameterGroups].toArray()[index].toObject()[Name].toString();
            }

            // パーツについて
            int CubismCdiJson::GetPartsCount()
            {
                if (!IsExistParts())
                    return 0;
                return _json[Parts].toArray().size();
            }

            const QString CubismCdiJson::GetPartsId(int index)
            {
                return _json[Parts].toArray()[index].toObject()[Id].toString();
            }

            const QString CubismCdiJson::GetPartsName(int index)
            {
                return _json[Parts].toArray()[index].toObject()[Name].toString();
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
