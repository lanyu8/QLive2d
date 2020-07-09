/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Id/CubismId.hpp"
#include "Utils/CubismJson.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            /**
             * @brief motion3.jsonのコンテナ。
             *
             * motion3.jsonのコンテナ。
             */
            class CubismMotionJson
            {
              public:
                /**
                 * @brief コンストラクタ
                 *
                 * コンストラクタ。
                 *
                 * @param[in]   buffer  motion3.jsonが読み込まれているバッファ
                 * @param[in]   size    バッファのサイズ
                 */
                CubismMotionJson(const QByteArray &buffer);

                /**
                 * @brief デストラクタ
                 *
                 * デストラクタ。
                 */
                virtual ~CubismMotionJson();

                /**
                 * @brief モーションの長さの取得
                 *
                 * モーションの長さを取得する。
                 *
                 * @return モーションの長さ[秒]
                 */
                csmFloat32 GetMotionDuration() const;

                /**
                 * @brief モーションのループ情報の取得
                 *
                 * モーションがループするかどうか？
                 *
                 * @retval  true    ループする
                 * @retval  false   ループしない
                 */
                bool IsMotionLoop() const;

                /**
                 * @brief モーションカーブの個数の取得
                 *
                 * モーションカーブの個数を取得する。
                 *
                 * @return モーションカーブの個数
                 */
                int GetMotionCurveCount() const;

                /**
                 * @brief モーションのフレームレートの取得
                 *
                 * モーションのフレームレートを取得する。
                 *
                 * @return フレームレート[FPS]
                 */
                csmFloat32 GetMotionFps() const;

                /**
                 * @brief モーションのセグメントの総合計の取得
                 *
                 * モーションのセグメントの総合計を取得する。
                 *
                 * @return モーションのセグメントの総合計
                 */
                int GetMotionTotalSegmentCount() const;

                /**
                 * @brief モーションのカーブの制御点の総合計の取得
                 *
                 * モーションのカーブの制御点の総合計を取得する。
                 *
                 * @return モーションのカーブの制御点の総合計
                 */
                int GetMotionTotalPointCount() const;

                /**
                 * @brief モーションのフェードイン時間の存在
                 *
                 * モーションにフェードイン時間が設定されているかどうか？
                 *
                 * @retval  true    存在する
                 * @retval  false   存在しない
                 */
                bool IsExistMotionFadeInTime() const;

                /**
                 * @brief モーションのフェードアウト時間の存在
                 *
                 * モーションにフェードアウト時間が設定されているかどうか？
                 *
                 * @retval  true    存在する
                 * @retval  false   存在しない
                 */
                bool IsExistMotionFadeOutTime() const;

                /**
                 * @brief モーションのフェードイン時間の取得
                 *
                 * モーションのフェードイン時間を取得する。
                 *
                 * @return  フェードイン時間[秒]
                 */
                csmFloat32 GetMotionFadeInTime() const;

                /**
                 * @brief モーションのフェードアウト時間の取得
                 *
                 * モーションのフェードアウト時間を取得する。
                 *
                 * @return  フェードアウト時間[秒]
                 */
                csmFloat32 GetMotionFadeOutTime() const;

                /**
                 * @brief モーションのカーブの種類の取得
                 *
                 * モーションのカーブの種類を取得する。
                 *
                 * @param[in]   curveIndex   カーブのインデックス
                 * @return カーブの種類
                 */
                const QString GetMotionCurveTarget(int curveIndex) const;

                /**
                 * @brief モーションのカーブのIDの取得
                 *
                 * モーションのカーブのIDを取得する。
                 *
                 * @param[in]   curveIndex   カーブのインデックス
                 * @return カーブのID
                 */
                CubismIdHandle GetMotionCurveId(int curveIndex) const;

                /**
                 * @brief モーションのカーブのフェードイン時間の存在
                 *
                 * モーションのカーブにフェードイン時間が設定されているかどうか？
                 *
                 * @param[in]   curveIndex   カーブのインデックス
                 * @retval  true    存在する
                 * @retval  false   存在しない
                 */
                bool IsExistMotionCurveFadeInTime(int curveIndex) const;

                /**
                 * @brief モーションのカーブのフェードアウト時間の存在
                 *
                 * モーションのカーブにフェードアウト時間が設定されているかどうか？
                 *
                 * @param[in]   curveIndex   カーブのインデックス
                 * @retval  true    存在する
                 * @retval  false   存在しない
                 */
                bool IsExistMotionCurveFadeOutTime(int curveIndex) const;

                /**
                 * @brief モーションのカーブのフェードイン時間の取得
                 *
                 * モーションのカーブのフェードイン時間を取得する。
                 *
                 * @param[in]   curveIndex   カーブのインデックス
                 * @return  フェードイン時間[秒]
                 */
                csmFloat32 GetMotionCurveFadeInTime(int curveIndex) const;

                /**
                 * @brief モーションのカーブのフェードアウト時間の取得
                 *
                 * モーションのカーブのフェードアウト時間を取得する。
                 *
                 * @param[in]   curveIndex   カーブのインデックス
                 * @return  フェードアウト時間[秒]
                 */
                csmFloat32 GetMotionCurveFadeOutTime(int curveIndex) const;

                /**
                 * @brief モーションのカーブのセグメントの個数の取得
                 *
                 * モーションのカーブのセグメントの個数を取得する。
                 *
                 * @param[in]   curveIndex   カーブのインデックス
                 * @return  モーションのカーブのセグメントの個数
                 */
                int GetMotionCurveSegmentCount(int curveIndex) const;

                /**
                 * @brief モーションのカーブのセグメントの値の取得
                 *
                 * モーションのカーブのセグメントの値を取得する、
                 *
                 * @param[in]   curveIndex      カーブのインデックス
                 * @param[in]   segmentIndex    セグメントのインデックス
                 * @return  セグメントの値
                 */
                csmFloat32 GetMotionCurveSegment(int curveIndex, int segmentIndex) const;

                /**
                 * @brief イベントの個数の取得
                 *
                 * イベントの個数の取得する。
                 *
                 * @return  イベントの個数
                 */
                int GetEventCount() const;

                /**
                 * @brief イベントの総文字数の取得
                 *
                 * イベントの総文字数の取得する。
                 *
                 * @return  イベントの総文字数
                 */
                int GetTotalEventValueSize() const;

                /**
                 * @brief イベントの時間の取得
                 *
                 * イベントの時間の取得する。
                 *
                 * @param[in]   userDataIndex イベントのインデックス
                 * @return  イベントの時間[秒]
                 */
                csmFloat32 GetEventTime(int userDataIndex) const;

                /**
                 * @brief イベントの取得
                 *
                 * イベントの取得する。
                 *
                 * @param[in]   userDataIndex    イベントのインデックス
                 * @return  イベントの文字列
                 */
                const QString GetEventValue(int userDataIndex) const;

              private:
                Utils::CubismJson _json; ///< motion3.jsonデータ
            };

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
