#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <CubismFramework.hpp>
#include <ICubismAllocator.hpp>
#include <cstdlib>
#include <memory>
using namespace Csm;
class Allocator
    : public Csm::ICubismAllocator
    , private std::allocator<std::byte>
{
  public:
    inline void *Allocate(const Csm::csmSizeType size)
    {
        return malloc(size);
    }
    inline void Deallocate(void *memory)
    {
        free(memory);
    }
    inline void *AllocateAligned(const Csm::csmSizeType size, const Csm::csmUint32 alignment)
    {
        size_t offset, shift, alignedAddress;
        void *allocation;
        void **preamble;

        offset = alignment - 1 + sizeof(void *);
        allocation = Allocate(size + static_cast<csmUint32>(offset));
        alignedAddress = reinterpret_cast<size_t>(allocation) + sizeof(void *);
        shift = alignedAddress % alignment;

        if (shift)
        {
            alignedAddress += (alignment - shift);
        }

        preamble = reinterpret_cast<void **>(alignedAddress);
        preamble[-1] = allocation;

        return reinterpret_cast<void *>(alignedAddress);
    }
    inline void DeallocateAligned(void *alignedMemory)
    {
        void **preamble;
        preamble = static_cast<void **>(alignedMemory);
        Deallocate(preamble[-1]);
    }
};

#endif // ALLOCATOR_H
