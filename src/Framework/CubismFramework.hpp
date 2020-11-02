/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once
#include <QOpenGLFunctions>

//========================================================
//  Live2D Cubism Coreライブラリをインクルード
//========================================================
#include "Live2DCubismCore.hpp"

//========================================================
//  設定用ヘッダをインクルード
//========================================================
#include "CubismFrameworkConfig.hpp"

//========================================================
//  カスタムアロケータをインクルード
//========================================================
#include "ICubismAllocator.hpp"

#include <new>

#ifdef __linux__
    #include <cstdlib>
#endif

namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {

            class CubismAllocationTag
            {
            };

            class CubismAllocationAlignedTag
            {
            };

            inline CubismAllocationTag GlobalTag;
            inline CubismAllocationAlignedTag GloabalAlignedTag;

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D

// リリース用
// 何も追跡しない。

void *operator new(Live2D::Cubism::Framework::csmSizeType size, Live2D::Cubism::Framework::CubismAllocationTag tag);
void *operator new(Live2D::Cubism::Framework::csmSizeType size, Live2D::Cubism::Framework::csmUint32 alignment,
                   Live2D::Cubism::Framework::CubismAllocationAlignedTag tag);
void operator delete(void *address, Live2D::Cubism::Framework::CubismAllocationTag tag);
void operator delete(void *address, Live2D::Cubism::Framework::CubismAllocationAlignedTag tag);

template<typename T>
void CsmDelete(T *address)
{
    if (!address)
    {
        return;
    }

    address->~T();

    operator delete(reinterpret_cast<void *>(address), Live2D::Cubism::Framework::GlobalTag);
}

#define CSM_NEW new (Live2D::Cubism::Framework::GlobalTag)
#define CSM_DELETE_SELF(type, obj)                                                                                                              \
    do                                                                                                                                          \
    {                                                                                                                                           \
        if (!obj)                                                                                                                               \
        {                                                                                                                                       \
            break;                                                                                                                              \
        }                                                                                                                                       \
        obj->~type();                                                                                                                           \
        operator delete(obj, Live2D::Cubism::Framework::GlobalTag);                                                                             \
    } while (0)
#define CSM_DELETE(obj) CsmDelete(obj)
#define CSM_MALLOC(size) Live2D::Cubism::Framework::CubismFramework::Allocate(size)
#define CSM_MALLOC_ALLIGNED(size, align) Live2D::Cubism::Framework::CubismFramework::AllocateAligned(size, align)
#define CSM_FREE(ptr) Live2D::Cubism::Framework::CubismFramework::Deallocate(ptr)
#define CSM_FREE_ALLIGNED(ptr) Live2D::Cubism::Framework::CubismFramework::DeallocateAligned(ptr)

#define CSM_PLACEMENT_NEW(addrs) new ((addrs))

//========================================================
//  アーキテクチャ用型定義をインクルード
//========================================================
#include "Type/CubismBasicType.hpp"

//========================================================
//  IDマネージャの前方宣言
//========================================================
namespace Live2D::Cubism::Framework
{
    class CubismIdManager;
}

//========================================================
//  コンパイラに関する設定
//========================================================
#ifdef _MSC_VER
    #pragma warning(disable : 4100)
#endif

#ifndef NULL
    #define NULL 0
#endif

//========================================================
//  検証マクロ
//========================================================
/*
 * @brief  式が有効であることを保証する。
 *
 * @param  expression  検証する式。
 * @param  message     検証結果がfalseだった場合のログメッセージ。
 * @param  body        検証結果がfalseだった場合に実行する処理。
 */
#define CubismEnsure(expression, message, body)                                                                                                 \
    do                                                                                                                                          \
    {                                                                                                                                           \
        if (!(expression))                                                                                                                      \
        {                                                                                                                                       \
            CubismFramework::CoreLogFunction("[Cubism Framework] " message);                                                                    \
            body;                                                                                                                               \
        }                                                                                                                                       \
    } while (0);

//========================================================
//  名前空間のエイリアス
//========================================================
namespace Csm = Live2D::Cubism::Framework;

//--------- LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {
            // Framework内で使う定数の宣言
            namespace Constant
            {
                constexpr auto VertexOffset = 0;
                constexpr auto VertexStep = 2;
            } // namespace Constant

            class CubismFramework
            {
              public:
                class Option
                {
                  public:
                    enum LogLevel
                    {
                        LogLevel_Verbose = 0, ///<  詳細ログ
                        LogLevel_Debug,       ///<  デバッグログ
                        LogLevel_Info,        ///<  Infoログ
                        LogLevel_Warning,     ///<  警告ログ
                        LogLevel_Error,       ///<  エラーログ
                        LogLevel_Off          ///<  ログ出力無効
                    };

                    Core::csmLogFunction LogFunction; ///< ログ出力の関数ポインタ
                    LogLevel LoggingLevel;            ///< ログ出力レベル設定
                };

                static bool StartUp(ICubismAllocator *allocator, const Option *option = NULL);
                static void CleanUp();
                static bool IsStarted();
                static void Initialize();
                static void Dispose();
                static bool IsInitialized();
                static void CoreLogFunction(const char *message);
                static Option::LogLevel GetLoggingLevel();
                static CubismIdManager *GetIdManager();
                static void *Allocate(csmSizeType size);
                static void *AllocateAligned(csmSizeType size, csmUint32 alignment);
                static void Deallocate(void *address);
                static void DeallocateAligned(void *address);

              private:
                CubismFramework()
                {
                }
            };

        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
