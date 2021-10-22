#include "configs/ParserBase.hpp"



namespace xlog::cnfg
{
    ParserBase::ParserBase(const fs::path& path)
    {
        if (!fs::is_regular_path(path))
            ;// throw...
        file.open(path);
    }

    u8char_t ParserBase::get()
    {
        u8char_t c;
        get(c);
        return c;
    }

    bool ParserBase::get(u8char_t& c)
    {
        newline(eol());
        u8Traits::int_type i = file.snextc();
        if (u8Traits::eq(i, u8Traits::eof()))
        {
            eof(true);
            return false;
        }
        u8Traits::assign(c, u8Traits::to_char_type(i));
        eol(u8Traits::eq(c, '\n'_u8));
        eof(file.eof());
        seek.inc(c);
        return (bool)file;
    }

    void ParserBase::Seek::inc(const u8char_t& c)
    {
        u8Traits::assign(curr, c);
        line += u8Traits::eq(c, '\n'_u8);
        column = (!u8Traits::eq(c, '\n'_u8) * (column + 1));
    }

    string_t ParserBase::get_until(bool (*pred)(const u8char_t&))
    {
        u8char_t c;
        string_t str;
        while (get(c) && (pred(c)))
            str.append(1, c);
        return str;
    }

    string_t ParserBase::get_until(const u8char_t& delim)
    {
        u8char_t c;
        string_t str;
        while (get(c) && !(u8Traits::eq(c, delim)))
            str.append(1, c);
        file.sungetc();
        return str;
    }

    string_t ParserBase::get_until(const string_t& delim_str)
    {
        const std::size_t d_size = delim_str.size();
        std::size_t cmp_idx = 0;
        u8char_t c;
        string_t buffer(d_size, ' '_u8);
        string_t result;
        while (get(c) && (buffer != delim_str))
        {
            result.append(1, buffer.front());
            buffer.erase(0, 1);
            buffer.append(1, c);
        }
        file.sungetc();
        return result;
    }

    string_t ParserBase::get_through(const string_t& delim_str)
    {
        const std::size_t d_size = delim_str.size();
        std::size_t cmp_idx = 0;
        u8char_t c;
        string_t str(d_size, ' '_u8);
        while (get(c))
        {
            cmp_idx = (str.size() < d_size) ? 0 : str.size() - d_size;
            if (str.substr(cmp_idx) == delim_str)
                return str;
            str.append(1, c);
        }
    }
}
