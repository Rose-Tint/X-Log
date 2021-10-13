#ifndef X_LOG_CONFIGS_HPP
#define X_LOG_CONFIGS_HPP

#include "fwd_declares.hpp"


namespace xlog::config
{
    template<class char_t>
    class BasicParserBase
    {
      protected:
        typedef std::char_traits<char_t> Traits;
        typedef uchar flags_base_t;
        typedef std::basic_string<char_t> string_t;

        enum Flags_e : flags_base_t
        {
            EOL           = 1 << 0, // if seek is at end of a line
            EOF           = 1 << 1, // if the end of a file has been reached
            SCOPING       = 1 << 2, // if parsing scope
            READING_VALUE = 1 << 3, // if parsing a value, and not an indent
            NEW_LINE      = 1 << 4, // if seek is at the beginning of a line
            EXP_NEW_SCOPE = 1 << 5, // if entering a new scope is expected
        };

        struct Seek
        {
            char_t curr = 0;
            ushort line = 0;
            uchar column = 0;
            void inc(char_t);
        };

        friend inline Flags_e operator ~ (const Flags_e& flg)
            { return static_cast<typename Flags_e>(~static_cast<flags_base_t>(flg)); }
        friend inline Flags_e operator | (const Flags_e& lhs, const Flags_e& rhs)
            { return static_cast<typename Flags_e>(static_cast<flags_base_t>(lhs) | static_cast<flags_base_t>(rhs)); }
        friend inline Flags_e operator & (const Flags_e& lhs, const Flags_e& rhs)
            { return static_cast<typename Flags_e>(static_cast<flags_base_t>(lhs) & static_cast<flags_base_t>(rhs)); }
        friend inline Flags_e operator ^ (const Flags_e& lhs, const Flags_e& rhs)
            { return static_cast<typename Flags_e>(static_cast<flags_base_t>(lhs) ^ static_cast<flags_base_t>(rhs)); }
        friend inline Flags_e operator |= (Flags_e& lhs, Flags_e rhs)
            { lhs = static_cast<typename Flags_e>(static_cast<flags_base_t>(lhs) | static_cast<flags_base_t>(rhs)); }
        friend inline Flags_e operator &= (Flags_e& lhs, Flags_e rhs)
            { lhs = static_cast<typename Flags_e>(static_cast<flags_base_t>(lhs) & static_cast<flags_base_t>(rhs)); }
        friend inline Flags_e operator ^= (Flags_e& lhs, Flags_e rhs)
            { lhs = static_cast<typename Flags_e>(static_cast<flags_base_t>(lhs) ^ static_cast<flags_base_t>(rhs)); }

        std::basic_ifstream<char_t> file;
        Flags_e flags;
        Seek seek;
        uchar scope;
        char_t stmt_delim;

        char_t get();
        string_t get_word(); // skips non alpha chars
        string_t get_until(char_t);
        string_t get_until(const string_t&);
        string_t get_through(const string_t&);
        string_t get_statement();

        bool get(char_t&);

      public:
        explicit BasicParserBase(const fs::path& path, char_t line_end_char)
            : file(path), stmt_delim(line_end_char) { }

        inline bool eol(void) const { return flags & EOL; }
        inline bool eof(void) const { return flags & EOF ; }
        inline bool scoping(void) const { return flags & SCOPING ; }
        inline bool reading(void) const { return flags & READING ; }
        inline bool newline(void) const { return flags & NEWLINE ; }
        inline bool exp_new_scope() const { return flags & EXP_NEW_SCOPE ; }
        inline void eol(bool val) { flags |= (val) ? EOL: flags; }
        inline void eof(bool val) { flags |= (val) ? EOF : flags; }
        inline void scoping(bool val) { flags |= (val) ? SCOPING : flags; }
        inline void reading(bool val) { flags |= (val) ? READING : flags; }
        inline void newline(bool val) { flags |= (val) ? NEWLINE : flags; }
        inline void exp_new_scope(bool val) { flags |= (val) ? EXP_NEW_SCOPE : flags; }
    };

    typedef BasicParserBase<char> ParserBase;
    typedef BasicParserBase<wchar_t> wParserBase;

    template<class char_t> inline BasicParserBase<char_t>::Flags_e operator ! (const BasicParserBase<char_t>::Flags_e&);
    template<class char_t> inline BasicParserBase<char_t>::Flags_e operator | (const BasicParserBase<char_t>::Flags_e&, const BasicParserBase<char_t>::Flags_e&);
    template<class char_t> inline BasicParserBase<char_t>::Flags_e operator & (const BasicParserBase<char_t>::Flags_e&, const BasicParserBase<char_t>::Flags_e&);
    template<class char_t> inline BasicParserBase<char_t>::Flags_e operator ^ (const BasicParserBase<char_t>::Flags_e&, const BasicParserBase<char_t>::Flags_e&);
}

#endif