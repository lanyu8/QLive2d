/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Type/CubismBasicType.hpp"

#include <QString>
namespace Live2D::Cubism::Framework
{
    struct CubismId;

    /**
     * @brief ID名の管理
     *
     * ID名を管理する。
     */
    class CubismIdManager
    {
        friend struct CubismId;

      public:
        CubismIdManager();
        ~CubismIdManager();

        //        /**
        //         * @brief ID名をリストから登録
        //         *
        //         * ID名をリストから登録する。
        //         *
        //         * @param[in]   ids     ID名リスト
        //         * @param[in]   count   IDの個数
        //         */
        //        void RegisterIds(const QString &ids, int count);

        //        /**
        //         * @brief ID名をリストから登録
        //         *
        //         * ID名をリストから登録する。
        //         *
        //         * @param[in]   ids     ID名リスト
        //         */
        //        void RegisterIds(const QVector<QString> &ids);

        /**
         * @brief ID名を登録
         *
         * ID名を登録する。
         *
         * @param[in]   id  ID名
         */
        const CubismId *RegisterId(const QString &id);

        /**
         * @brief ID名からIDを取得する。
         *
         * ID名からIDを取得する。
         *
         * @param[in]   id  ID名
         *
         * @note 未登録のID名の場合、登録も行う。
         */
        const CubismId *GetId(const QString &id);
        bool IsExist(const QString &id) const;

      private:
        CubismIdManager(const CubismIdManager &);
        CubismIdManager &operator=(const CubismIdManager &);

        /**
         * @brief ID名からIDを検索
         *
         * ID名からIDを検索する。
         *
         * @param[in]   id  ID名
         * @return  登録されているID。なければNULL。
         */
        CubismId *FindId(const QString &id) const;

        QVector<CubismId *> _ids; ///< 登録されているIDのリスト
    };

} // namespace Live2D::Cubism::Framework
