#include <cstdlib>
#include <io.hpp>
#include <memory.hpp>
#include <string.hpp>

#include <iostream>

#include <string>

using namespace neostd;

types::int32 main(void)
{
    memory::UniquePtr<int> a;

    a = memory::UniquePtr<int>::make((sizeof(int) * 10) + 1);

    a.get()[0] = 20;

    std::cout << a.get()[0] << std::endl;

    types::string s1("Hello");
    types::string s2(" World!!!");
    types::string s3 = s1 + s2;
    std::cout << s3.c_str() << std::endl;
    return 0;
}
