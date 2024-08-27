#include <cstdlib>
#include <memory.hpp>

#include <iostream>

using namespace neostd;

types::int32 main(void)
{
    memory::UniquePtr<int> a;

    a = memory::UniquePtr<int>::make((sizeof(int) * 10) + 1);

    a.get()[0] = 20;

    std::cout << a.get()[0] << std::endl;

    return 0;
}
