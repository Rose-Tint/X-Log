#ifndef X_LOG_CONFIGS_BASICPARSERBASE_HPP
#define X_LOG_CONFIGS_BASICPARSERBASE_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class ParserBase
    {
        // ushort instead of uchar to future proof for additional flags
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
            char8_t curr = 0;
            ushort line = 0;
            uchar column = 0;
            void inc(char8_t);
        };

        friend constexpr Flags operator ~ (const Flags& flg)
            { return static_cast<typename Flags>(~static_cast<ushort>(flg)); }
        friend constexpr Flags operator | (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) | static_cast<ushort>(rhs)); }
        friend constexpr Flags operator & (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) & static_cast<ushort>(rhs)); }
        friend constexpr Flags operator ^ (const Flags& lhs, const Flags& rhs)
            { return static_cast<typename Flags>(static_cast<ushort>(lhs) ^ static_cast<ushort>(rhs)); }
        friend constexpr Flags& operator |= (Flags& lhs, const Flags& rhs)
            { return (lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) | static_cast<ushort>(rhs))); }
        friend constexpr Flags& operator &= (Flags& lhs, const Flags& rhs)
            { return (lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) & static_cast<ushort>(rhs))); }
        friend constexpr Flags& operator ^= (Flags& lhs, const Flags& rhs)
            { return (lhs = static_cast<typename Flags>(static_cast<ushort>(lhs) ^ static_cast<ushort>(rhs))); }


        explicit ParserBase(const fs::path&);

        filebuf_t file;
        Flags flags;
        Seek seek;

        char8_t get();
        string_t get_until(bool (*)(char8_t));
        string_t get_until(char8_t);
        string_t get_until(const string_t&);
        string_t get_through(const string_t&);
        virtual ValueType get_value() = 0;
        virtual std::pair<ValueType, ValueType> get_key_value() = 0;
        virtual String get_string() = 0;
        virtual Map get_map() = 0;
        virtual Array get_array() = 0;

        bool get(char8_t&);

        constexpr bool eol          (void) const { return (flags & EOL) != 0; }
        constexpr bool eof          (void) const { return (flags & EOF) != 0; }
        constexpr bool scoping      (void) const { return (flags & SCOPING) != 0; }
        constexpr bool reading      (void) const { return (flags & READING) != 0; }
        constexpr bool newline      (void) const { return (flags & NEWLINE) != 0; }
        constexpr bool exp_new_scope(void) const { return (flags & EXP_NEW_SCOPE) != 0; }
        constexpr void eol          (bool val) { flags |= (val) ? EOL: flags; }
        constexpr void eof          (bool val) { flags |= (val) ? EOF : flags; }
        constexpr void scoping      (bool val) { flags |= (val) ? SCOPING : flags; }
        constexpr void reading      (bool val) { flags |= (val) ? READING : flags; }
        constexpr void newline      (bool val) { flags |= (val) ? NEWLINE : flags; }
        constexpr void exp_new_scope(bool val) { flags |= (val) ? EXP_NEW_SCOPE : flags; }
        constexpr const Flags& set_flg(Flags flg, bool val)
            { return (flags &= (val) ? (flags | flg) : (~flg)); }
        constexpr const Flags& flip_flg(Flags flg)
            { return (flags = ((flags & flg) == 0) ? flags | flg : flags & !flg); }
    };
}

#endif