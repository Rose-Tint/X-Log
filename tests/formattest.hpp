#ifndef TESTS_FORMAT_HPP
#define TESTS_FORMAT_HPP
#include "X-Test.hpp"
#include "X-Log.hpp"


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
        (std::string("in ")+__FILE__+" at "+std::to_string(__LINE__)+" with level 10 from test logger 1:this better pass"),
        "in ${file} at ${line} with level ${lvl} from ${lgr_name}: ${msg}",
        { __FILE__, __LINE__, "this better pass", "test logger 1", 10 }
    );
    pass &= test_Format(
        (std::string("file: ")+__FILE__+"\nline: "+std::to_string(__LINE__)+"\nlvl: 10\nlgr_name: test logger 2\nmsg: istg if this doesnt pass"),
        "file: ${file}\nline: ${line}\nlvl: ${lvl}\nlgr_name: ${lgr_name}\nmsg: ${msg}",
        { __FILE__, __LINE__, "istg if this doesnt pass", "test logger 2", 10 }
    );
    return pass;
}
#endif