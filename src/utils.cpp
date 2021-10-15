#include "utils.hpp"


namespace xlog::utils
{
    bool case_ins_eq(const string_t& lhs, const string_t& rhs)
    {
        std::size_t l_size = lhs.size();
        if (rhs.size() != l_size)
            return false;
        for (unsigned int i = 0; i < l_size; ++i)
            if (std::tolower(lhs[i]) != std::tolower(rhs[i]))
                return false;
        return true;
    }

    void trim(string_t& str, char_t c)
    {
        static const auto npos = string_t::npos;
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
