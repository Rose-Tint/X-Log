#include "record.hpp"

namespace xlog
{
    void Record::init_rest(const std::string& message, const std::string&,  const uchar& level)
        : msg(message), lgr(lname), lvl(level) { }
}
