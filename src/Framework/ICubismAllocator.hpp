/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Type/CubismBasicType.hpp"

namespace Live2D
{
    namespace Cubism::Framework
    {
        class ICubismAllocator
        {
          public:
            virtual ~ICubismAllocator()
            {
            }
            virtual void *Allocate(const csmSizeType size) = 0;
            virtual void Deallocate(void *memory) = 0;
            virtual void *AllocateAligned(const csmSizeType size, const csmUint32 alignment) = 0;
            virtual void DeallocateAligned(void *alignedMemory) = 0;
        };
    } // namespace Cubism::Framework
} // namespace Live2D
