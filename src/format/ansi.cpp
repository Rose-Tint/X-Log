#include "format/ansi_format.hpp"


namespace xlog
{
    std::string ansi_format(const char* cstr)
    {
        std::string str = dtl::ansi_pref;
        str.append(cstr, std::strlen(cstr));
        str.append(1, 'm');
        return str;
    }

    void ansi_format(std::string& str)
    {
        str.insert(0, dtl::ansi_pref);
        str.append(1, 'm');
    }

    std::string ansi_format(AnsiOption opt)
    {
        std::string optstr = std::to_string(static_cast<short>(opt));
        optstr.append(1, ';');
        return optstr;
    }

    void ansi_format(std::string& str, AnsiOption opt)
    {
        str.append(ansi_format(opt));
        ansi_format(str);
    }

    void ansi_format(std::string& str, ilist<AnsiOption> opts)
    {
        for (auto opt : opts)
            str.append(ansi_format(opt));
        ansi_format(str);
    }

    std::string operator "" _ansi(const char* cstr) { return ansi_format(cstr); }
}
