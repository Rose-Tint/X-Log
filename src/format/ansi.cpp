#include "format/ansi_format.hpp"


namespace xlog
{
    string_t ansi_format(const char* cstr)
    {
        string_t str = dtl::ansi_pref;
        str.append(cstr, std::strlen(cstr));
        str.append(1, 'm');
        return str;
    }

    void ansi_format(string_t& str)
    {
        str.insert(0, dtl::ansi_pref);
        str.append(1, 'm');
    }

    string_t ansi_format(AnsiOption opt)
    {
        string_t optstr = std::to_string(static_cast<short>(opt));
        optstr.append(1, ';');
        return optstr;
    }

    void ansi_format(string_t& str, AnsiOption opt)
    {
        str.append(ansi_format(opt));
        ansi_format(str);
    }

    void ansi_format(string_t& str, ilist<AnsiOption> opts)
    {
        for (auto opt : opts)
            str.append(ansi_format(opt));
        ansi_format(str);
    }

    string_t operator "" _ansi(const char* cstr) { return ansi_format(cstr); }
}
