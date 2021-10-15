#ifndef X_LOG_UTILS_HPP
#define X_LOG_UTILS_HPP

#include "fwd_declares.hpp"


namespace xlog::utils
{
    bool case_ins_eq(const std::string&, const std::string&);

    void trim(string_t&, char_t);
}

#endif