#include "utils.hpp"


namespace xlog::utils
{
    template<class _map_t, class _value_t, class _key_t>
    bool set_or_default(const _map_t& map, const _key_t& key, _value_t& value, const _value_t& def)
    {
        auto iter = map.find(key);
        bool is_found = iter != map.end();
        value = (is_found) ? iter.second : def;
        return is_found;
    }

    template<class _map_t, class _value_t, class _key_t>
    bool set_or_default(const _map_t& map, const _key_t& key, _value_t& value, _value_t&& def)
    {
        auto iter = map.find(key);
        bool is_found = iter != map.end();
        value = (is_found) ? iter.second : std::move(def);
        return is_found;
    }


    template<class _map_t, class _value_t, class _key_t>
    bool try_set(const _map_t& map, const _key_t& key, _value_t& value)
    {
        auto iter = map.find(key);
        bool is_found = iter != map.end();
        if (is_found)
            value = iter.second;
        return is_found;
    }

    template<class _map_t, class _value_t, class _key_t, class _error_t>
    void set_or_throw(const _map_t& map, const _key_t& key, _value_t& value, const std::string& msg)
    {
        auto iter = map.find(key);
        bool is_found = iter != map.end();
        if (is_found)
            value = iter.second;
        else throw _error_t(msg);
    }

    bool case_ins_eq(const std::string& lhs, const std::string& rhs)
    {
        std::size_t l_size = lhs.size();
        if (rhs.size() != l_size)
            return false;
        for (unsigned int i = 0; i < l_size; ++i)
            if (std::tolower(lhs[i]) != std::tolower(rhs[i]))
                return false;
        return true;
    }

    template<class CharT>
   void trim(std::basic_string<CharT>& str, CharT c)
    {
        static const auto npos = std::basic_string<CharT>::npos;
        auto first = str.find_first_not_of(c);
        auto scd = str.find_last_not_of(c);
        if (first == npos)
            first = 0;
        if (scd == npos)
            scd = str.size();
        auto count = scd - first;
        str = str.substr(first, count);
    }
}

#include <map>

template<class T, class ...Args>
struct Pattern
{
    typedef bool (*matcher_f)(T);
    typedef void (*matched_f)(Args...);
    std::map<matcher_f, matched_f> patterns;
    void operator()(const T& arg, Args& ...args)
    {
        for (auto pair : patterns)
        {
            if (pair.first(arg))
            {
                pair.second(args...);
            }
        }
    }
};
