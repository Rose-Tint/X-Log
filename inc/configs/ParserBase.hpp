#ifndef X_LOG_CONFIGS_BASICPARSERBASE_HPP
#define X_LOG_CONFIGS_BASICPARSERBASE_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class ParserBase
    {
      protected:
        typedef std::char_traits<char> Traits;
        typedef std::string _string_t;

        // ushort instead of uchar to future proof
        enum Flags : ushort
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
            char curr = 0;
            ushort line = 0;
            uchar column = 0;
            void inc(char);
        };

        friend inline Flags operator ~ (const Flags& flg)
            { return static_cast<typename Flags>(~static_cast<ushort>(flg)); }
        friend inline Flags operator | (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) | static_cast<ushort>(rhs)); }
        friend inline Flags operator & (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) & static_cast<ushort>(rhs)); }
        friend inline Flags operator ^ (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) ^ static_cast<ushort>(rhs)); }
        friend inline Flags operator |= (Flags& lhs, Flags rhs)
            { lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) | static_cast<ushort>(rhs)); }
        friend inline Flags operator &= (Flags& lhs, Flags rhs)
            { lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) & static_cast<ushort>(rhs)); }
        friend inline Flags operator ^= (Flags& lhs, Flags rhs)
            { lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) ^ static_cast<ushort>(rhs)); }

        const Delims delims;
        ifile_t file;
        Flags flags;
        Seek seek;

        char get();
        _string_t get_until(bool (*)(char));
        _string_t get_until(char);
        _string_t get_until(const _string_t&);
        _string_t get_through(const _string_t&);
        virtual ValueType get_value() = 0;
        virtual std::pair<ValueType, ValueType> get_key_value() = 0;
        virtual String get_string() = 0;
        virtual Map get_map() = 0;
        virtual Array get_array() = 0;

        bool get(char&);

        ParserBase(const fs::path& path, Delims);

      public:
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
}

#endif