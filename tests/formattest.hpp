#ifndef TESTS_FORMAT_HPP
#define TESTS_FORMAT_HPP

#include "TestBase.hpp"
#include "format.hpp"


class FormatTests final : private xtst::TestBase
{
    using TestBase::TestBase;
    static bool test_Format(std::string, std::string, xlog::FormatInfo);
    bool run() override final;
};


bool FormatTests::run()
{
    bool pass = true;
    pass &= test_Format(
        "Hello, World!\n\tmsg: istg if this doesnt pass",
        "${arg1}, ${arg2}\n\tmsg: ${msg}",
        { __FILE__, __LINE__, { { "arg1", "Hello" }, { "arg2", "World!" } }, 10, "istg if this doesnt pass", "test logger 2" }
    );
    pass &= test_Format(
        (std::string("in ")+__FILE__+" at "+std::to_string(__LINE__)+" with level 10 from test logger 1:this better pass"),
        "in ${file} at ${line} with level ${lvl} from ${lgr_name}: ${msg}",
        { __FILE__, __LINE__, { }, 10, "this better pass", "test logger 1" }
    );
    return pass;
}

#endif