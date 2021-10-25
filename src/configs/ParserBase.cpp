#include "configs/ParserBase.hpp"

using std::pair;

// TODO: continue to update


namespace xlog::cnfg
{
    ParserBase::ParserBase(const fs::path& path)
    {
        if (!fs::is_regular_path(path))
            ;// throw...
        file.open(path);
    }

    char8_t ParserBase::get()
    {
        char8_t c;
        get(c);
        return c;
    }

    bool ParserBase::get(char8_t& c)
    {
        newline(eol());
        auto i = file.snextc();
        if (i == std::char_traits<char8_t>::eof())
        {
            eof(true);
            return false;
        }
        c = std::char_traits<char8_t>::to_char_type(i));
        eol(c == u8'\n'));
        eof(false);
        seek.inc(c);
        return (bool)file;
    }

    void ParserBase::Seek::inc(const char8_t& c)
    {
        curr = c;
        line += (c == '\n');
        column = ((c != '\n') * (column + 1));
    }

    string_t ParserBase::get_until(bool (*pred)(const char8_t&))
    {
        char8_t c = seek.curr;
        string_t str;
        while ((pred(c)) && get(c))
            str.append(1, c);
        return str;
    }

    string_t ParserBase::get_until(const char8_t& delim)
    {
        char8_t c = seek.curr;
        string_t str;
        while ((c != delim) && get(c))
            str.append(1, c);
        return str;
    }

    string_t ParserBase::get_until(const string_t& delim_s)
    {
        string_t str = get_through(delim_s);
        return str.substr(0, str.size() - delim_s.size());
    }

    string_t ParserBase::get_through(const string_t& delim_s)
    {
        const std::size_t d_size = delim_s.size();
        std::size_t cmp_idx = 0;
        char8_t c = 0;
        string_t str;
        str.reserve(d_size);
        while (get(c))
        {
            cmp_idx = (str.size() < d_size) ? str.size() : str.size() - d_size;
            if (str.substr(cmp_idx, d_size) == delim_s)
                break;
            str.append(1, c);
        }
        return str;
    }
}
