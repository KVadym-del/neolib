#pragma once

#ifdef __linux__
#include <sys/mman.h>
#elif _WIN32
#include <windows.h>
#else
#error "Unsupported platform"
#endif

#include "types.hpp"

namespace neostd::memory
{
void *allocate(types::size size);
template <typename T> inline T *allocate(types::size size)
{
#ifdef __linux__
    return static_cast<T *>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
#elif _WIN32
    return static_cast<T *>(VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
#endif
}

void deallocate(void *ptr, types::size size);
template <typename T> inline void deallocate(T *ptr, types::size size)
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

void *operator new(neostd::types::size size);
void *operator new[](neostd::types::size size);

void operator delete(void *ptr) noexcept;
void operator delete(void *ptr, neostd::types::size size) noexcept;
void operator delete[](void *ptr) noexcept;
void operator delete[](void *ptr, neostd::types::size size) noexcept;

namespace neostd::memory
{
template <typename T> class UniquePtr
{
  public:
    UniquePtr() : m_ptr(nullptr), m_size(0)
    {
    }
    inline UniquePtr(types::size size) : m_size(size)
    {
        this->m_ptr = allocate<T>(m_size);
    }
    UniquePtr(const UniquePtr &other) = delete;
    inline UniquePtr(UniquePtr &&other) noexcept
    {
        this->m_ptr = other.m_ptr;
        this->m_size = other.m_size;
        other.m_ptr = nullptr;
        other.m_size = 0;
    }
    inline ~UniquePtr()
    {
        deallocate(m_ptr, m_size);
    }

    UniquePtr &operator=(const UniquePtr &other) = delete;
    inline UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            deallocate(m_ptr, m_size);
            this->m_ptr = other.m_ptr;
            this->m_size = other.m_size;
            other.m_ptr = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    inline static UniquePtr make(types::size size)
    {
        return UniquePtr<T>(size);
    }

    inline T *get()
    {
        return m_ptr;
    }

    inline T *operator->()
    {
        return m_ptr;
    }

    inline T &operator*()
    {
        return *m_ptr;
    }

  private:
    T *m_ptr;
    types::size m_size;
};
} // namespace neostd::memory
