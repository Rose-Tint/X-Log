#ifndef X_LOG_UTILS_HPP
#define X_LOG_UTILS_HPP

#include "fwd_declares.hpp"


namespace xlog::utils
{
    bool case_ins_eq(const std::string&, const std::string&);

    void trim(string_t&, char_t);

    template<class It>
    using iter_tag = typename std::iterator_traits<It>::iterator_category;

    template<class It>
    using iter_type = typename std::iterator_traits<It>::value_type;

    template<bool Condition>
    using EnableIf = typename std::enable_if<Condition, bool>::type;

    template<class ValueType, class It>
    using EnableIterFor = EnableIf<std::is_convertible<It, ValueType>>;
}

#endif