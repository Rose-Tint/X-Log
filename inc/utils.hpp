#ifndef X_LOG_UTILS_HPP
#define X_LOG_UTILS_HPP

#include "fwd_declares.hpp"


namespace xlog::utils
{
    bool case_ins_eq(const std::string&, const std::string&);

    void trim(string_t&, char_t);

    template<class I>
    using iter_tag = typename std::iterator_traits<I>::iterator_category;

    template<class I>
    using iter_type = typename std::iterator_traits<I>::value_type;

    template<bool Condition>
    using EnableIf = typename std::enable_if<Condition, bool>::type;

    template<class V, class I>
    using EnableIterFor = EnableIf<std::is_convertible<iter_type<I>, V>::value>;

    template<class V, class I>
    using EnableConvertible = EnableIf<std::is_convertible<I, V>>;
}

#endif