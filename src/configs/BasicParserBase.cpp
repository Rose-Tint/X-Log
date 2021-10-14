#include "configs/BasicParserBase.hpp"


namespace xlog::cnfg
{
    char BasicParserBase::get()
    {
        char c;
        get(c);
        return c;
    }

    bool BasicParserBase::get(char& c)
    {
        newline(eol());
        file.get(c);
        eol(Traits::eq(c, stmt_delim));
        eof(file.eof());
        seek.inc(c);
        return (bool)file;
    }

    void BasicParserBase::Seek::inc(char c)
    {
        curr = c;
        line += Traits::eq(c, stmt_delim);
        column = (!Traits::eq(c, stmt_delim) * (column + 1));
    }

    std::string BasicParserBase::get_word()
    {
        char c = 0;
        std::string word;
        bool read = false;
        bool is_space = true;
        while (get(c))
        {
            is_space = std::isspace(c);
            if (read)
            {
                if (is_space)
                    break;
                word.append(1, c);
            }
            else read |= !is_space;
        }
        return word;
    }

    std::string BasicParserBase::get_until(char delim)
    {
        char c = 0;
        std::string str;
        while (get(c))
        {
            if (Traits::eq(c, delim))
                break;
            str.append(1, c);
        }
        return str;
    }

    std::string BasicParserBase::get_until(const std::string& delim_s)
    {
        std::string str = get_through(delim_s);
        return str.substr(0, str.size() - delim_s.size());
    }

    std::string BasicParserBase::get_through(const std::string& delim_s)
    {
        const std::size_t d_size = delim_s.size();
        std::size_t cmp_idx = 0;
        char c = 0;
        std::string str;
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

    std::string BasicParserBase::get_statement()
    {
        char c = 0;
        std::string stmt;
        bool read = false;
        bool not_new_stmt = false;
        while (get(c))
        {
            not_new_stmt = !Traits::eq(c, stmt_delim);
            if (read)
            {
                if (not_new_stmt)
                    stmt.append(1, c);
                else break;
            }
            else read |= not_new_stmt;
        }
        return stmt;
    }
}
