#include "include/memory.hpp"

namespace neostd::memory
{
void *allocate(types::size size)
{
#ifdef __linux__
    return mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#elif _WIN32
    return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#endif
}

void deallocate(void *ptr, types::size size)
{
    if (ptr == nullptr || size == 0)
    {
        return;
    }
#ifdef __linux__
    munmap(ptr, size);
#elif _WIN32
    VirtualFree(ptr, 0, MEM_RELEASE);
#endif
}
} // namespace neostd::memory

void *operator new(neostd::types::size size)
{
    return neostd::memory::allocate(size);
}

void *operator new[](neostd::types::size size)
{
    return neostd::memory::allocate(size);
}

void operator delete(void *ptr) noexcept
{
    neostd::memory::deallocate(ptr, 0);
}

void operator delete(void *ptr, neostd::types::size size) noexcept
{
    neostd::memory::deallocate(ptr, size);
}

void operator delete[](void *ptr) noexcept
{
    neostd::memory::deallocate(ptr, 0);
}

void operator delete[](void *ptr, neostd::types::size size) noexcept
{
    neostd::memory::deallocate(ptr, size);
}
