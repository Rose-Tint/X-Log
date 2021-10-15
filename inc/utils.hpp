#ifndef X_LOG_UTILS_HPP
#define X_LOG_UTILS_HPP

#include "fwd_declares.hpp"


namespace xlog::utils
{
    bool case_ins_eq(const std::string&, const std::string&);

    template<class CharT>
    void trim(std::basic_string<CharT>&, CharT);
}

#endif