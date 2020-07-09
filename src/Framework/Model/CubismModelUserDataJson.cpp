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
                const QString &Meta = "Meta";
                const QString &UserDataCount = "UserDataCount";
                const QString &TotalUserDataSize = "TotalUserDataSize";
                const QString &UserData = "UserData";
                const QString &Target = "Target";
                const QString &Id = "Id";
                const QString &Value = "Value";
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
                return _json[Meta].toObject()[UserDataCount].toInt();
            }

            int CubismModelUserDataJson::GetTotalUserDataSize() const
            {
                return _json[Meta].toObject()[TotalUserDataSize].toInt();
            }

            QString CubismModelUserDataJson::GetUserDataTargetType(const int i) const
            {
                return _json[UserData].toArray()[i].toObject()[Target].toString();
            }

            CubismIdHandle CubismModelUserDataJson::GetUserDataId(const int i) const
            {
                return CubismFramework::GetIdManager()->GetId(_json[UserData].toArray()[i].toObject()[Id].toString());
            }

            const QString CubismModelUserDataJson::GetUserDataValue(const int i) const
            {
                return _json[UserData].toArray()[i].toObject()[Value].toString();
            }

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
