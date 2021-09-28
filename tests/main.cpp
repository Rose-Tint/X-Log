#include "./format.hpp"
#include <ctime>


int main()
{
    xtst::TestBase::register_buffer(std::cout.rdbuf());

    auto t = std::time(nullptr);
    xtst::TestBase::print_stack(std::ctime(&t));
    xtst::TestBase::inc_idt();

    FormatTests fmt_tests();

    xtst::TestBase::run_tests();

    return 0;
}