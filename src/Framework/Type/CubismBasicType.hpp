/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

/**
 * @brief CubismFrameworkで用いる基本型の定義
 *
 */

#include <QChar>
#include <QVector>
#include <cstddef>

namespace Live2D
{
    namespace Cubism::Framework
    {
        typedef unsigned char csmUchar;       ///< 符号なし文字型
        typedef unsigned char csmByte;        ///< バイト型
        typedef signed char csmInt8;          ///< 符号付き文字型
        typedef unsigned char csmUint8;       ///< 8ビット符号なし整数型
        typedef signed short csmInt16;        ///< 16ビット符号付き整数型
        typedef unsigned short csmUint16;     ///< 16ビット符号なし整数型
        typedef signed int csmInt32;          ///< 32ビット符号付き整数型
        typedef unsigned int csmUint32;       ///< 32ビット符号なし整数型
        typedef signed long long csmInt64;    ///< 64ビット符号付き整数型
        typedef unsigned long long csmUint64; ///< 64ビット符号なし整数型
        typedef float csmFloat32;             ///< 32ビット浮動小数点数型
        typedef unsigned int csmSizeInt;      ///< size_t型
        typedef std::size_t csmSizeType;
    } // namespace Cubism::Framework
} // namespace Live2D
