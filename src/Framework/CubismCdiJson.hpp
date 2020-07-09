/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Utils/CubismJson.hpp"

//--------- LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            class CubismCdiJson
            {
              public:
                /**
                 * @brief コンストラクタ
                 *
                 * コンストラクタ。
                 *
                 * @param[in]   buffer  cdi3.jsonが読み込まれているバッファ
                 * @param[in]   size    バッファのサイズ
                 */
                CubismCdiJson(const QByteArray &buffer);

                /**
                 * @brief デストラクタ
                 *
                 * デストラクタ。
                 */
                virtual ~CubismCdiJson();

                // Parameters

                int GetParametersCount();

                const QString GetParametersId(int index);
                const QString GetParametersGroupId(int index);
                const QString GetParametersName(int index);

                // ParameterGroups

                int GetParameterGroupsCount();

                const QString GetParameterGroupsId(int index);
                const QString GetParameterGroupsGroupId(int index);
                const QString GetParameterGroupsName(int index);

                // Parts

                int GetPartsCount();

                const QString GetPartsId(int index);
                const QString GetPartsName(int index);

              private:
                /**
                 * @brief        パラメータのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistParameters() const;

                /**
                 * @brief        パラメータグループのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistParameterGroups() const;

                /**
                 * @brief        パーツのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistParts() const;

                Utils::CubismJson _json;
            };

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
