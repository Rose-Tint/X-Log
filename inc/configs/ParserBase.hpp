#ifndef X_LOG_CONFIGS_BASICPARSERBASE_HPP
#define X_LOG_CONFIGS_BASICPARSERBASE_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class ParserBase
    {
      protected:
        // ushort instead of uchar to future proof for flag additions
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
            u8char_t curr = 0;
            ushort line = 0;
            uchar column = 0;
            void inc(u8char_t);
        };

        friend constexpr Flags operator ~ (const Flags& flg)
            { return static_cast<typename Flags>(~static_cast<ushort>(flg)); }
        friend constexpr Flags operator | (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) | static_cast<ushort>(rhs)); }
        friend constexpr Flags operator & (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) & static_cast<ushort>(rhs)); }
        friend constexpr Flags operator ^ (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) ^ static_cast<ushort>(rhs)); }
        friend constexpr Flags operator |= (Flags& lhs, Flags rhs)
            { lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) | static_cast<ushort>(rhs)); }
        friend constexpr Flags operator &= (Flags& lhs, Flags rhs)
            { lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) & static_cast<ushort>(rhs)); }
        friend constexpr Flags operator ^= (Flags& lhs, Flags rhs)
            { lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) ^ static_cast<ushort>(rhs)); }

        filebuf_t file;
        Flags flags;
        Seek seek;

        u8char_t get();
        string_t get_until(bool (*)(const u8char_t&));
        string_t get_until(const u8char_t&);
        string_t get_until(const string_t&);
        string_t get_through(const string_t&);
        virtual ValueType get_value() = 0;
        virtual std::pair<ValueType, ValueType> get_key_value() = 0;
        virtual String get_string() = 0;
        virtual Map get_map() = 0;
        virtual Array get_array() = 0;

        bool get(u8char_t&);

        ParserBase(const fs::path&);

      public:
        inline bool eol(void) const { return (flags & EOL) != 0; }
        inline bool eof(void) const { return (flags & EOF) != 0 ; }
        inline bool scoping(void) const { return (flags & SCOPING) != 0 ; }
        inline bool reading(void) const { return (flags & READING) != 0 ; }
        inline bool newline(void) const { return (flags & NEWLINE) != 0 ; }
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