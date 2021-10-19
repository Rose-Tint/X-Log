#include "configs/ParserBase.hpp"

using std::pair;

// TODO: continue to update


namespace xlog::cnfg
{
    ParserBase::ParserBase(const fs::path& path, pair<char, char> , pair<char, char>, pair<char, char>)
        : delims()
    {
        if (!fs::is_regular_path(path))
            ;// throw...
        file.open(path);
    }

    char ParserBase::get()
    {
        char c;
        get(c);
        return c;
    }

    bool ParserBase::get(char& c)
    {
        newline(eol());
        file.get(c);
        eol(Traits::eq(c, stmt_delim));
        eof(file.eof());
        seek.inc(c);
        return (bool)file;
    }

    void ParserBase::Seek::inc(char c)
    {
        curr = c;
        line += Traits::eq(c, '\n');
        column = (!Traits::eq(c, '\n') * (column + 1));
    }

    string_t ParserBase::get_until(bool (*pred)(char))
    {
        char c = 0;
        string_t str;
        while (get(c))
        {
            if (pred(c))
                return str;
            str.append(1, c);
        }
    }

    string_t ParserBase::get_until(char delim)
    {
        char c = 0;
        string_t str;
        while (get(c))
        {
            if (Traits::eq(c, delim))
                return str;
            str.append(1, c);
        }
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
        char c = 0;
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
