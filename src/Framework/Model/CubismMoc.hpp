/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "CubismFramework.hpp"

namespace Live2D
{
    namespace Cubism::Framework
    {
        class CubismModel;
        class CubismMoc
        {
            friend class CubismModel;

          public:
            static CubismMoc *Create(const QByteArray &buffer);
            static void Delete(CubismMoc *moc);
            CubismModel *CreateModel();
            void DeleteModel(CubismModel *model);

          private:
            CubismMoc(Core::csmMoc *moc);
            virtual ~CubismMoc();

            Core::csmMoc *_moc; ///< Mocデータ
            int _modelCount;    ///< Mocデータから作られたモデルの個数
        };

    } // namespace Cubism::Framework
} // namespace Live2D
