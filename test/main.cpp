#include <cstdlib>
#include <io.hpp>
#include <memory.hpp>
#include <static_array.hpp>
#include <string.hpp>

#include <array>
#include <iostream>

using namespace neostd;

types::int32 main(void)
{
    memory::UniquePtr<int> a;

    a = memory::UniquePtr<int>::make((sizeof(int) * 10) + 1);

    a.get()[0] = 20;

    std::cout << a.get()[0] << std::endl;

    types::string str = "Hello, World! This is a test string!";

    neostd::types::static_array<int, 5> arr;
    arr.fill(1);

    neostd::types::static_array<types::string, 5> arr2{"1", "2", "3", "4"};

    for (int i = 0; i < 5; i++)
    {
        std::cout << arr2[i].c_str() << std::endl;
    }

    std::cout << arr2.size() << std::endl;
    std::cout << arr2.lengh() << std::endl;
    return 0;
}
