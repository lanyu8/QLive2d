/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Math/CubismVector2.hpp"

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            class CubismModel;
            struct CubismPhysicsRig;

            class CubismPhysics
            {
              public:
                struct Options
                {
                    CubismVector2 Gravity;
                    CubismVector2 Wind;
                };
                static CubismPhysics *Create(const QByteArray &buffer);
                static void Delete(CubismPhysics *physics);
                void Evaluate(CubismModel *model, csmFloat32 deltaTimeSeconds);
                void SetOptions(const Options &options);
                const Options &GetOptions() const;

              private:
                CubismPhysics();
                virtual ~CubismPhysics();
                //
                Q_DISABLE_COPY(CubismPhysics);
                //
                void Parse(const QByteArray &buffer);
                void Initialize();

                CubismPhysicsRig *_physicsRig; ///< 物理演算のデータ
                Options _options;              ///< オプション
            };

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
