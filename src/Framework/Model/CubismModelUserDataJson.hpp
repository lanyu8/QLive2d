/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Id/CubismIdManager.hpp"
#include "Model/CubismModel.hpp"
#include "Utils/CubismJson.hpp"

//--------- LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            class CubismModelUserDataJson
            {
              public:
                /**
                 * @brief コンストラクタ
                 *
                 * コンストラクタ。
                 *
                 * @param[in]   buffer  userdata3.jsonが読み込まれているバッファ
                 * @param[in]   size    バッファのサイズ
                 */
                CubismModelUserDataJson(const QByteArray &buffer);

                /**
                 * @brief デストラクタ
                 *
                 * デストラクタ。
                 */
                virtual ~CubismModelUserDataJson();

                /**
                 * @brief ユーザデータ個数の取得
                 *
                 * userdata3.jsonに入っていたユーザデータの個数を取得する。
                 *
                 * @return  ユーザデータの個数
                 */
                int GetUserDataCount() const;

                /**
                 * @brief ユーザデータ総文字列数の取得
                 *
                 * ユーザデータ総文字列数の取得する。
                 *
                 * @return  ユーザデータ総文字列数
                 */
                int GetTotalUserDataSize() const;

                /**
                 * @brief ユーザデータのタイプの取得
                 *
                 * 指定番目のユーザデータのタイプの取得を取得する。
                 *
                 * @param[in]   i    インデックス
                 *
                 * @return      ユーザデータのタイプ
                 */
                QString GetUserDataTargetType(int i) const;

                /**
                 * @brief ユーザデータのターゲットIDの取得
                 *
                 * 指定番目のユーザデータのターゲットIDの取得を取得する。
                 *
                 * @param[in]   i    インデックス
                 *
                 * @return      ユーザデータターゲットID
                 */
                CubismIdHandle GetUserDataId(int i) const;

                /**
                 * @brief ユーザデータの文字列の取得
                 *
                 * 指定番目のユーザデータの文字列の取得を取得する。
                 *
                 * @param[in]   i    インデックス
                 *
                 * @return      ユーザデータ
                 */
                const QString GetUserDataValue(int i) const;

              private:
                Utils::CubismJson _json;
            };

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
