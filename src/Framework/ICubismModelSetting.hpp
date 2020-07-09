/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "CubismFramework.hpp"
#include "Id/CubismId.hpp"
#include "Type/csmMap.hpp"

//--------- LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            /**
             * @brief モデル設定情報を取り扱う関数を宣言した純粋仮想クラス。
             *
             * このクラスを継承することで、モデル設定情報を取り扱うクラスになる。
             *
             */
            class ICubismModelSetting
            {
              public:
                /**
                 * @brief デストラクタ
                 *
                 * デストラクタ。
                 */
                virtual ~ICubismModelSetting()
                {
                }

                /**
                 * @brief  Mocファイルの名前を取得する
                 *
                 * @return Mocファイルの名前
                 */
                virtual const QString GetModelFileName() const = 0;

                /**
                 * @brief  モデルが使用するテクスチャの数を取得する
                 *
                 * @return テクスチャの数
                 */
                virtual int GetTextureCount() const = 0;

                /**
                 * @brief  テクスチャが配置されたディレクトリの名前を取得する
                 *
                 * @return テクスチャが配置されたディレクトリの名前
                 */
                virtual const QString GetTextureDirectory() const = 0;

                /**
                 * @brief  モデルが使用するテクスチャの名前を取得する
                 *
                 * @param[in]   index    配列のインデックス値
                 * @return      テクスチャの名前
                 */
                virtual const QString GetTextureFileName(int index) const = 0;

                /**
                 * @brief        モデルに設定された当たり判定の数を取得する
                 *
                 * @return       モデルに設定された当たり判定の数
                 */
                virtual int GetHitAreasCount() const = 0;

                /**
                 * @brief        当たり判定に設定されたIDを取得する
                 *
                 * @param[in]    index   配列のインデックス値
                 * @return       当たり判定に設定されたID
                 */
                virtual CubismIdHandle GetHitAreaId(int index) const = 0;

                /**
                 * @brief        当たり判定に設定された名前を取得する
                 *
                 * @param[in]    index   配列のインデックス値
                 * @return       当たり判定に設定された名前
                 */
                virtual const QString GetHitAreaName(int index) const = 0;

                /**
                 * @brief        物理演算設定ファイルの名前を取得する
                 *
                 * @return       物理演算設定ファイルの名前
                 */
                virtual const QString GetPhysicsFileName() const = 0;

                /**
                 * @brief        パーツ切り替え設定ファイルの名前を取得する
                 *
                 * @return       パーツ切り替え設定ファイルの名前
                 */
                virtual const QString GetPoseFileName() const = 0;

                /**
                 * @brief        表情設定ファイルの数を取得する
                 *
                 * @return       表情設定ファイルの数
                 */
                virtual int GetExpressionCount() const = 0;

                /**
                 * @brief        表情設定ファイルを識別する名前（別名）を取得する
                 *
                 * @param[in]    index   配列のインデックス値
                 * @return       表情の名前
                 */
                virtual const QString GetExpressionName(int index) const = 0;

                /**
                 * @brief        表情設定ファイルの名前を取得する
                 *
                 * @param[in]    index   配列のインデックス値
                 * @return       表情設定ファイルの名前
                 */
                virtual const QString GetExpressionFileName(int index) const = 0;

                /**
                 * @brief        モーショングループの数を取得する
                 *
                 * @return       モーショングループの数
                 */
                virtual int GetMotionGroupCount() const = 0;

                /**
                 * @brief        モーショングループの名前を取得する
                 *
                 * @param[in]    index   配列のインデックス値
                 * @return       モーショングループの名前
                 */
                virtual const QString GetMotionGroupName(int index) const = 0;

                /**
                 * @brief        モーショングループに含まれるモーションの数を取得する
                 *
                 * @param[in]    groupName      モーショングループの名前
                 * @return       モーショングループの名前
                 */
                virtual int GetMotionCount(const QString &groupName) const = 0;

                /**
                 * @brief        グループ名とインデックス値からモーションファイルの名前を取得する
                 *
                 * @param[in]    groupName      モーショングループの名前
                 * @param[in]    index          配列のインデックス値
                 * @return       モーションファイルの名前
                 */
                virtual const QString GetMotionFileName(const QString &groupName, int index) const = 0;

                /**
                 * @brief        モーションに対応するサウンドファイルの名前を取得する
                 *
                 * @param[in]    groupName      モーショングループの名前
                 * @param[in]    index          配列のインデックス値
                 * @return       サウンドファイルの名前
                 */
                virtual const QString GetMotionSoundFileName(const QString &groupName, int index) const = 0;

                /**
                 * @brief        モーション開始時のフェードイン処理時間を取得する
                 *
                 * @param[in]    groupName      モーショングループの名前
                 * @param[in]    index          配列のインデックス値
                 * @return       フェードイン処理時間[秒]
                 */
                virtual csmFloat32 GetMotionFadeInTimeValue(const QString &groupName, int index) const = 0;

                /**
                 * @brief        モーション終了時のフェードアウト処理時間を取得する
                 *
                 * @param[in]    groupName      モーショングループの名前
                 * @param[in]    index          配列のインデックス値
                 * @return       フェードアウト処理時間[秒]
                 */
                virtual csmFloat32 GetMotionFadeOutTimeValue(const QString &groupName, int index) const = 0;

                /**
                 * @brief        ユーザデータのファイル名を取得する
                 *
                 * @return       ユーザデータのファイル名
                 */
                virtual const QString GetUserDataFile() const = 0;

                /**
                 * @brief        レイアウト情報を取得する
                 *
                 * @param[out]   outLayoutMap      csmMapクラスのインスタンス
                 * @retval       true  -> レイアウト情報が存在する
                 * @retval       false -> レイアウト情報が存在しない
                 */
                virtual bool GetLayoutMap(QMap<QString, csmFloat32> &outLayoutMap) const = 0;

                /**
                 * @brief        目パチに関連付けられたパラメータの数を取得する
                 *
                 * @return       目パチに関連付けられたパラメータの数
                 */
                virtual int GetEyeBlinkParameterCount() const = 0;

                /**
                 * @brief        目パチに関連付けられたパラメータのIDを取得する
                 *
                 * @param[in]    index          配列のインデックス値
                 * @return       パラメータID
                 */
                virtual CubismIdHandle GetEyeBlinkParameterId(int index) const = 0;

                /**
                 * @brief        リップシンクに関連付けられたパラメータの数を取得する
                 *
                 * @return       リップシンクに関連付けられたパラメータの数
                 */
                virtual int GetLipSyncParameterCount() const = 0;

                /**
                 * @brief        リップシンクに関連付けられたパラメータのIDを取得する
                 *
                 * @param[in]    index          配列のインデックス値
                 * @return       パラメータID
                 */
                virtual CubismIdHandle GetLipSyncParameterId(int index) const = 0;
            };
        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
