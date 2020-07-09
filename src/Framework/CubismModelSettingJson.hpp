/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "ICubismModelSetting.hpp"
#include "Id/CubismId.hpp"
#include "Utils/CubismJson.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            /**
             * @brief Model3Jsonパーサー.
             *
             * model3.jsonファイルをパースして値を取得する。
             *
             */
            class CubismModelSettingJson : public ICubismModelSetting
            {
              public:
                /**
                 *
                 * @brief 引数付きコンストラクタ
                 *
                 * 引数付きコンストラクタ。
                 *
                 * @param[in] buffer     Model3Jsonをバイト配列として読み込んだデータバッファ
                 * @param[in] size       Model3Jsonのデータサイズ
                 *
                 */
                CubismModelSettingJson(const QByteArray &buffer);

                /**
                 * @brief デストラクタ
                 *
                 * デストラクタ。
                 */
                virtual ~CubismModelSettingJson();

                /**
                 * @brief   CubismJsonオブジェクトのポインタを取得する
                 *
                 * @return  CubismJsonのポインタ
                 */
                Utils::CubismJson *GetJsonPointer() const;

                const QString GetModelFileName() const override;

                int GetTextureCount() const override;

                const QString GetTextureDirectory() const override;

                const QString GetTextureFileName(int index) const override;

                int GetHitAreasCount() const override;

                CubismIdHandle GetHitAreaId(int index) const override;

                const QString GetHitAreaName(int index) const override;

                const QString GetPhysicsFileName() const override;

                const QString GetPoseFileName() const override;

                int GetExpressionCount() const override;

                const QString GetExpressionName(int index) const override;

                const QString GetExpressionFileName(int index) const override;

                int GetMotionGroupCount() const override;

                const QString GetMotionGroupName(int index) const override;

                int GetMotionCount(const QString &groupName) const override;

                const QString GetMotionFileName(const QString &groupName, int index) const override;

                const QString GetMotionSoundFileName(const QString &groupName, int index) const override;

                csmFloat32 GetMotionFadeInTimeValue(const QString &groupName, int index) const override;

                csmFloat32 GetMotionFadeOutTimeValue(const QString &groupName, int index) const override;

                const QString GetUserDataFile() const override;

                bool GetLayoutMap(QMap<QString, csmFloat32> &outLayoutMap) const override;

                int GetEyeBlinkParameterCount() const override;

                CubismIdHandle GetEyeBlinkParameterId(int index) const override;

                int GetLipSyncParameterCount() const override;

                CubismIdHandle GetLipSyncParameterId(int index) const override;

              private:
                enum FrequentNode
                {
                    FrequentNode_Groups = 0,      ///< GetRoot()[Groups]
                    FrequentNode_Moc = 1,         ///< GetRoot()[FileReferences][Moc]
                    FrequentNode_Motions = 2,     ///< GetRoot()[FileReferences][Motions]
                    FrequentNode_Expressions = 3, ///< GetRoot()[FileReferences][Expressions]
                    FrequentNode_Textures = 4,    ///< GetRoot()[FileReferences][Textures]
                    FrequentNode_Physics = 5,     ///< GetRoot()[FileReferences][Physics]
                    FrequentNode_Pose = 6,        ///< GetRoot()[FileReferences][Pose]
                    FrequentNode_HitAreas = 7,    ///< GetRoot()[HitAreas]
                };

                /**
                 * @brief        モデルファイルのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistModelFile() const;

                /**
                 * @brief        テクスチャファイルのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistTextureFiles() const;

                /**
                 * @brief        当たり判定のキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistHitAreas() const;

                /**
                 * @brief        物理演算ファイルのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistPhysicsFile() const;

                /**
                 * @brief        ポーズ設定ファイルのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistPoseFile() const;

                /**
                 * @brief        表情設定ファイルのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistExpressionFile() const;

                /**
                 * @brief        モーショングループのキーが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistMotionGroups() const;

                /**
                 * @brief        引数で指定したモーショングループのキーが存在するかどうかを確認する
                 *
                 * @param[in]    groupName  グループ名
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistMotionGroupName(const QString &groupName) const;

                /**
                 * @brief        引数で指定したモーションに対応するサウンドファイルのキーが存在するかどうかを確認する
                 *
                 * @param[in]    groupName  グループ名
                 * @param[in]    index   配列のインデックス値
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistMotionSoundFile(const QString &groupName, int index) const;

                /**
                 * @brief        引数で指定したモーションに対応するフェードイン時間のキーが存在するかどうかを確認する
                 *
                 * @param[in]    groupName  グループ名
                 * @param[in]    index   配列のインデックス値
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistMotionFadeIn(const QString &groupName, int index) const;

                /**
                 * @brief        引数で指定したモーションに対応するフェードアウト時間のキーが存在するかどうかを確認する
                 *
                 * @param[in]    groupName  グループ名
                 * @param[in]    index   配列のインデックス値
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistMotionFadeOut(const QString &groupName, int index) const;

                /**
                 * @brief        UserDataのファイル名が存在するか確認
                 *
                 * @retval       true   キーが存在する
                 * @retval       false  キーが存在しない
                 */
                bool IsExistUserDataFile() const;

                /**
                 * @brief        目パチに対応付けられたパラメータが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistEyeBlinkParameters() const;

                /**
                 * @brief        リップシンクに対応付けられたパラメータが存在するかどうかを確認する
                 *
                 * @retval       true  -> キーが存在する
                 * @retval       false -> キーが存在しない
                 */
                bool IsExistLipSyncParameters() const;

                Utils::CubismJson _json; ///< モデルデータjson
                QList<QJsonValue> frequentJsonValues;
            };
        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
