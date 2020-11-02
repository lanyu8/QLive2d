/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Math/CubismVector2.hpp"
#include "Type/CubismBasicType.hpp"

#include <cmath>

namespace Live2D
{
    namespace Cubism::Framework
    {
        class CubismMath
        {
          public:
            static const csmFloat32 Pi;
            static csmFloat32 RangeF(csmFloat32 value, csmFloat32 min, csmFloat32 max)
            {
                if (value < min)
                    value = min;
                else if (value > max)
                    value = max;
                return value;
            };

            static csmFloat32 SinF(csmFloat32 x)
            {
                return sinf(x);
            };
            static csmFloat32 CosF(csmFloat32 x)
            {
                return cosf(x);
            };

            static csmFloat32 AbsF(csmFloat32 x)
            {
                return std::fabs(x);
            };

            static csmFloat32 SqrtF(csmFloat32 x)
            {
                return sqrtf(x);
            };

            static csmFloat32 GetEasingSine(csmFloat32 value)
            {
                if (value < 0.0f)
                    return 0.0f;
                else if (value > 1.0f)
                    return 1.0f;

                return static_cast<csmFloat32>(0.5f - 0.5f * CosF(value * Pi));
            }

            static csmFloat32 Max(csmFloat32 l, csmFloat32 r)
            {
                return (l > r) ? l : r;
            }
            static csmFloat32 Min(csmFloat32 l, csmFloat32 r)
            {
                return (l > r) ? r : l;
            }

            static csmFloat32 DegreesToRadian(csmFloat32 degrees);
            static csmFloat32 RadianToDegrees(csmFloat32 radian);
            static csmFloat32 DirectionToRadian(CubismVector2 from, CubismVector2 to);
            static csmFloat32 DirectionToDegrees(CubismVector2 from, CubismVector2 to);
            static CubismVector2 RadianToDirection(csmFloat32 totalAngle);

          private:
            CubismMath();
        };
    } // namespace Cubism::Framework
} // namespace Live2D
