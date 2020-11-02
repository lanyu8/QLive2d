/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "CubismModelUserDataJson.hpp"

#include "CubismModelUserData.hpp"

//--------- LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            namespace
            {
                constexpr auto Meta = "Meta";
                constexpr auto UserDataCount = "UserDataCount";
                constexpr auto TotalUserDataSize = "TotalUserDataSize";
                constexpr auto UserData = "UserData";
                constexpr auto Target = "Target";
                constexpr auto Id = "Id";
                constexpr auto Value = "Value";
            } // namespace
            CubismModelUserDataJson::CubismModelUserDataJson(const QByteArray &buffer)
            {
                _json = QJsonDocument::fromJson(buffer).object();
            }

            CubismModelUserDataJson::~CubismModelUserDataJson()
            {
            }

            int CubismModelUserDataJson::GetUserDataCount() const
            {
                return QJsonIO::GetValue(_json, Meta, UserDataCount).toInt();
            }

            int CubismModelUserDataJson::GetTotalUserDataSize() const
            {
                return QJsonIO::GetValue(_json, Meta, TotalUserDataSize).toInt();
            }

            QString CubismModelUserDataJson::GetUserDataTargetType(const int i) const
            {
                return QJsonIO::GetValue(_json, UserData, i, Target).toString();
            }

            CubismIdHandle CubismModelUserDataJson::GetUserDataId(const int i) const
            {
                const auto str = QJsonIO::GetValue(_json, UserData, i, Id).toString();
                return CubismFramework::GetIdManager()->GetId(str);
            }

            const QString CubismModelUserDataJson::GetUserDataValue(const int i) const
            {
                return QJsonIO::GetValue(_json, UserData, i, Value).toString();
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
