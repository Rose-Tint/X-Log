#ifndef X_LOG_U8CHAR_T_HPP
#define X_LOG_U8CHAR_T_HPP

#include <cstddef>
#include <cctype>
#include <string>


namespace xlog
{
    // psuedo utf-8
    class u8char_t
    {
        using Traits = std::char_traits<u8char_t>;
        template<> friend class std::char_traits<u8char_t>;
        friend constexpr u8String operator "" _u8(const char*);
        friend constexpr u8char_t operator "" _u8(const wchar_t*);
        friend constexpr u8char_t operator "" _u8(const char16_t*);
        friend constexpr u8char_t operator "" _u8(const char32_t*);
        friend constexpr u8char_t operator "" _u8(char);
        friend constexpr u8char_t operator "" _u8(wchar_t);
        friend constexpr u8char_t operator "" _u8(char16_t);
        friend constexpr u8char_t operator "" _u8(char32_t);
        friend constexpr typename Traits::int_type operator "" _u8(unsigned long long);

        typedef unsigned char char_t;
        typedef std::uint_fast8_t count_t;

        static constexpr char_t bc_mask(const count_t&) const;

        char_t bytes[4] = {'\0'};

        constexpr count_t size() const;

        constexpr u8char_t(const char_t&, const count_t&);
        constexpr u8char_t(const char16_t&, const count_t&);

      public:
        constexpr u8char_t() : c('\0'_u8) { }
        constexpr u8char_t(const wchar_t&);
        constexpr u8char_t(const char16_t&);
        constexpr u8char_t(const char32_t&);
        explicit operator typename Traits::int_type();
    };

    typedef std::char_traits<u8char_t> u8Traits;
    typedef std::basic_string<u8char_t, u8Traits> u8String;

    constexpr bool operator == (const u8char_t&, const u8char_t&);
    constexpr bool operator != (const u8char_t&, const u8char_t&);
    constexpr bool operator <  (const u8char_t&, const u8char_t&);

    constexpr bool is_whitesp(const u8char_t&);
    constexpr bool is_num(const u8char_t&);
    constexpr bool is_alpha(const u8char_t&);
    constexpr bool is_lower(const u8char_t&);
    constexpr bool is_upper(const u8char_t&);
    constexpr bool is_ctrl(const u8char_t&);
    constexpr u8char_t as_lower(const u8char_t&);
    constexpr u8char_t& to_lower(u8char_t&);
    bool is_num(const u8char_t&, int base);
    bool is_num(const u8char_t*);
    u8char_t* to_lower(u8char_t*);
}


template<>
struct std::char_traits<xlog::u8char_t>
{
    typedef xlog::u8char_t char_type;
    typedef unsigned int int_type;
    typedef std::fpos<std::char_traits<char_type>>::state_type pos_type;
    typedef std::streamoff off_type;
    typedef std::mbstate_t state_type;

// these functions change in c++17
#if CPP_STD >= 17
    static constexpr void assign(char_type&, const char_type&) noexcept;
    static constexpr int compare(const char_type*, const char_type*, std::size_t);
    static constexpr std::size_t length(const char_type*);
    static constexpr const char_type* find(const char_type*, std::size_t, const char_type&);
#else
    static void assign(char_type&, const char_type&) noexcept;
    static int compare(const char_type*, const char_type*, std::size_t);
    static std::size_t length(const char_type*);
    static const char_type* find(const char_type*, std::size_t, const char_type&);
#endif

// these functions change in c++20
#if CPP_STD >= 20
    static constexpr char_type* assign(char_type*, std::size_t, char_type);
    static constexpr char_type* move(char_type*, const char_type*, std::size_t);
    static constexpr char_type* copy(char_type*, const char_type*, std::size_t);
#else
    static char_type* assign(char_type*, std::size_t, char_type);
    static char_type* move(char_type*, const char_type*, std::size_t);
    static char_type* copy(char_type*, const char_type*, std::size_t);
#endif

// these functions have not changed since c++11
    static constexpr bool eq(char_type, char_type) noexcept;
    static constexpr bool lt(char_type, char_type) noexcept;
    static constexpr char_type to_char_type(int_type) noexcept;
    static constexpr int_type to_int_type(char_type) noexcept;
    static constexpr bool eq_int_type(int_type, int_type) noexcept;
    static constexpr int_type eof() noexcept;
    static constexpr int_type not_eof(int_type) noexcept;
};


constexpr const xlog::u8String operator "" _u8(const char*);
constexpr const xlog::u8String operator "" _u8(const char*, std::size_t);
constexpr xlog::u8char_t operator "" _u8(char);
constexpr typename xlog::u8Traits::int_type operator "" _u8(unsigned long long);

#endif