#ifndef X_LOG_UTILS_HPP
#define X_LOG_UTILS_HPP

#include "fwd_declares.hpp"


namespace xlog::utils
{
    template<
        class _map_t,
        class _value_t = _map_t::mapped_type,
        class _key_t = _map_t::key_type
    > bool set_or_default(const _map_t&, const _key_t&, _value_t& const _value_t&);

    template<
        class _map_t,
        class _value_t = _map_t::mapped_type,
        class _key_t = _map_t::key_type
    > bool set_or_default(const _map_t&, const _key_t&, _value_t&, _value_t&&);

    template<
        class _map_t,
        class _value_t = _map_t::mapped_type,
        class _key_t = _map_t::key_type
    > bool try_set(const _map_t&, const _key_t&, _value_t&);

    template<
        class _map_t,
        class _error_t = std::out_of_range,
        class _value_t = _map_t::mapped_type,
        class _key_t = _map_t::key_type
    > void set_or_throw(const _map_t&, const _key_t&, _value_t&, const std::string&);

    bool case_ins_eq(const std::string&, const std::string&);

    template<class CharT>
    void trim(std::basic_string<CharT>&, CharT);
}

#endif