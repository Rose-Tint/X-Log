#ifndef TESTS_FORMAT_HPP
#define TESTS_FORMAT_HPP

#include "X-Test.hpp"
#include "format.hpp"


TEST_CLASS(Format)
{
    TEST_CLASS_INIT
    DECLARE_TEST(call_op, std::string, std::string, xlog::FormatInfo)
};


DEFINE_RUN(Format)
{
    bool pass = true;
    pass &= TEST(Format, call_op)(
        "Hello, World!\n\tmsg: istg if this doesnt pass",
        "${arg1}, ${arg2}\n\tmsg: ${msg}",
        { __FILE__, __LINE__, { { "arg1", "Hello" }, { "arg2", "World!" } }, 10, "istg if this doesnt pass", "test 1" }
    );
    pass &= TEST(Format, call_op)(
        std::string("in ")+__FILE__+" at "+std::to_string(__LINE__)+" with level 10 from test logger 1:this better pass",
        "in ${file} at ${line} with level ${lvl} from ${lgr}: ${msg}",
        { __FILE__, __LINE__, { }, 10, "this better pass", "test 2" }
    );
    return pass;
}

#endif