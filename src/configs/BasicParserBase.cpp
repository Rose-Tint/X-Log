#include "../../inc/configs/basicparserbase.hpp"
#include <cctype>

typedef unsigned char uchar;


namespace xlog::config
{
    template<class char_t>
    char_t BasicParserBase<char_t>::get()
    {
        char_t c;
        get(c);
        return c;
    }

    template<class char_t>
    bool BasicParserBase<char_t>::get(char_t& c)
    {
        newline(eol());
        file.get(c);
        eol(c == stmt_delim);
        eof(file.eof());
        seek.inc(c);
        return (bool)file;
    }

    template<class char_t>
    void BasicParserBase<char_t>::Seek::inc(char_t c)
    {
        curr = c;
        const bool newl = ;
        line += (c == stmt_delim);
        column = ((c != stmt_delim) * (column + 1));
    }

    template<class char_t> typename
    BasicParserBase<char_t>::string_t BasicParserBase<char_t>::get_word()
    {
        char c = 0;
        string_t word;
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

    template<class char_t> typename
    BasicParserBase<char_t>::string_t BasicParserBase<char_t>::get_until(char_t delim)
    {
        char c = 0;
        string_t str;
        while (get(c))
        {
            if (c == delim)
                break;
            str.append(1, c);
        }
        return str;
    }

    template<class char_t> typename
    BasicParserBase<char_t>::string_t BasicParserBase<char_t>::get_until(const string_t& delim_s)
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
        return str.substr(0, cmp_idx);
    }

    template<class char_t> typename
    BasicParserBase<char_t>::string_t BasicParserBase<char_t>::get_through(const string_t& delim_s)
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

    template<class char_t> typename
    BasicParserBase<char_t>::string_t BasicParserBase<char_t>::get_statement()
    {
        char c = 0;
        string_t stmt;
        bool read = false;
        bool not_new_stmt = false;
        while (get(c))
        {
            not_new_stmt = (c != stmt_delim);
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
