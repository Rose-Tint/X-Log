#ifndef X_LOG_COMPONENTS_CONFIGS_OBJECT
#define X_LOG_COMPONENTS_CONFIGS_OBJECT
#endif

#include <string>
#include "X-Log.hpp"

using namespace xlog::cnfg;
using xlog::root;
using std::string;

Object()
    .Formats({
      FormatConfigItf()
        .Name("std")
        .Format("Testing function ${tfunc}: ${PorF}\n\texpected: ${exp}\n\tgot: ${res}\n\twith args: ${given}")
    });


int add(int lhs, int rhs)
{
    // intentionally wrong
    if (lhs == 0)
        return 0;
    else return rhs;
}

// for convenience
std::string tos(int n) { return std::to_string(n); }

void test_add(int exp, int arg1, int arg2)
{
    int result = add(arg1, arg2);
    root.log("", 0, { RCD_INFO,
    {
        { "tfunc", "int add(int lhs, int rhs)"              },
        { "res"  , tos(result)                              },
        { "exp"  , tos(exp)                                 },
        { "PorF" , (result == exp) ? "PASS" : "FAIL"        },
        { "given", tos(arg1).append(", ").append(tos(arg2)) },
    }});
}

int main()
{
    test_add(4, 2, 2);
    test_add(7, 3, 4);
    test_add(4622, 1200, 3422);
    test_add(38, 0, 38);
    test_add(92, 58, 34);
}
