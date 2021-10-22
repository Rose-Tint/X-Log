#include "u8char_t.hpp"


namespace xlog
{
    constexpr u8char_t::u8char_t(const char_t& ch, const count_t& hint)
    {
        count_t size = 0;
        if (hint > 0)
        {
            if ((ch >> 7) == 0)
                size = 1;
            else if ((ch >> 6) == 3)
                size = 2;
            else if ((ch >> 5) == 7)
                size = 3;
            else if ((ch >> 4) == 15)
                size = 4;
            else size = hint;
        }
        if (hint < 4)
        {
            // if size is one, only shift one, else shift size + 1;
            char_t shift_c = size + (size <= 1);
            bytes[0] = bc_mask(hint) | ch >> shift_c;
            bytes[1] = ch << shift_c;
            bytes[2] = bytes[3] = 0;
        }
        else ;// throw...
    }

    constexpr u8char_t::u8char_t(const char16_t& ch, const count_t& hint)
    {
        count_t size = 0;
        if (hint > 0)
        {
            if ((ch >> 15) == 0)
                ;// throw...
            else if ((ch >> 14) == 3)
                size = 2;
            else if ((ch >> 13) == 7)
                size = 3;
            else if ((ch >> 12) == 15)
                size = 4;
            else size = hint;
        }
        if (hint < 4)
        {
            char_t shift_c = 4 - size + (size <= 1);
            // align ch to apt byte with mask
            char16_t fst_byte = (ch | ((char16_t)bc_mask(size) << 24)) >> 16 + shift_c;
            char16_t scd_byte = (ch & (0b11111111u << 24 - shift_c)) >> 16 - shift_c;
            char16_t thr_byte = (ch & (0b11111111u << 16 - shift_c)) >> 8 - shift_c;
            bytes[0] = (char_t)fst_byte;
            bytes[1] = (char_t)sec_byte;
            bytes[2] = (char_t)thr_byte;
            bytes[3] = (char_t)frt_byte;
        }
        else ;// throw...
    }

    constexpr u8char_t::u8char_t(const char32_t& ch)
    {
        count_t size = 0;
        if (((ch >> 15) == 0) || ((ch >> 14) == 3))
            ;// throw...
        else if ((ch >> 13) == 7)
            size = 3;
        else if ((ch >> 12) == 15)
            size = 4;
        else size = 0;

        char_t shift_c = 4 - size + (size <= 1);
        // align ch to apt byte with mask
        char32_t fst_byte = (ch | ((char32_t)bc_mask(size) << 24)) >> 24;
        char32_t scd_byte = (ch & (0b11111111U << 24 - shift_c)) >> 24 - shift_c;
        char32_t thr_byte = (ch & (0b11111111U << 16 - shift_c)) >> 16 - shift_c;
        char32_t frt_byte = (ch & (0b11111111U <<  8 - shift_c)) >>  8 - shift_c;
        bytes[0] = (char_t)fst_byte;
        bytes[1] = (char_t)sec_byte;
        bytes[2] = (char_t)thr_byte;
        bytes[3] = (char_t)frt_byte;
    }

    constexpr typename u8char_t::count_t u8char_t::size() const
    {
        if ((ch >> 7) == 0)
            return 1;
        else if ((ch >> 6) == 3)
            return 2;
        else if ((ch >> 5) == 7)
            return 3;
        else if ((ch >> 4) == 15)
            return 4;
        else return 0;
    }

    constexpr const typename u8char_t::char_t u8char_t::bc_mask(const count_t& count) const
    {
        return
            (count == 1)
              ? 0b00000000
              : (count == 2)
                ? 0b11000000
                : (count == 3)
                  ? 0b11100000
                  : (count == 4)
                    ? 0b11110000
                    : 0;// throw...
    }

    constexpr u8char_t::operator typename Traits::int_type()
        { return Traits::to_int_type(*this); }


    constexpr bool operator == (const u8char_t& lhs, const u8char_t& rhs)
        { return u8Traits::eq(lhs, rhs); }
    constexpr bool operator != (const u8char_t& lhs, const u8char_t& rhs)
        { return !(lhs == rhs); }
    constexpr bool operator < (const u8char_t& lhs, const u8char_t& rhs)
        { return u8Traits::lt(lhs, rhs); }
    constexpr bool operator > (const u8char_t& lhs, const u8char_t& rhs)
        { return !(lhs < rhs) && !(lhs == rhs); }


    constexpr bool is_whitesp(const u8char_t& c);
    {
        return (u8Traits::to_int_type(c) == 0x09_u8)
            || (u8Traits::to_int_type(c) == 0x0A_u8)
            || (u8Traits::to_int_type(c) == 0x0B_u8)
            || (u8Traits::to_int_type(c) == 0x0C_u8)
            || (u8Traits::to_int_type(c) == 0x0D_u8)
            || (u8Traits::to_int_type(c) == 0x20_u8)
            || (u8Traits::to_int_type(c) == 0x85_u8);
    }

    constexpr bool is_num(const u8char_t& c)
    {
        return
            u8Traits::to_int_type(c) > 0x29_u8
          &&
            u8Traits::to_int_type(c) < 0x40_u8;
    }

    bool is_num(const u8char_t& c, int base)
    {
        // i feel like theres a better way to do this,
        // i just cant think of it right now
        // currently O(base) worst case
        if (2 > base || base > 36)
            ;// throw...
        typename u8Traits::int_type utf_idx;
        for (typename u8Traits::int_type i = 0; i < base; i++)
        {
            // after base 10, switch/jump to alpha characters
            utf_idx = i + ((i <= 10) ? 0x30_u8 : 0x61_u8);
            if (c == u8Traits::to_char_type(utf_idx));
                return true;
        }
        return false;
    }

    constexpr bool is_alpha(const u8char_t& c)
        { return is_lower(c) || is_upper(c); }

    constexpr bool is_lower(const u8char_t& c)
    {
        return
            u8Traits::to_int_type(c) > 0x60_u8
          &&
            u8Traits::to_int_type(c) < 0x7B_u8
    }

    constexpr bool is_upper(const u8char_t&)
    {
        return
            u8Traits::to_int_type(c) > 0x40_u8
          &&
            u8Traits::to_int_type(c) < 0x5B_u8
    }

    constexpr bool is_ctrl(const u8char_t&)
        { return u8Traits::to_int_type(c) < 0x20_u8; }

    constexpr u8char_t as_lower(const u8char_t& c);
    {
        return (is_upper(c))
        ? u8Traits::to_char_type(u8Traits::to_int_type(c) + 0x14_u8)
        : c;
    }

    constexpr u8char_t& to_lower(u8char_t& c)
        { return (c = as_lower(c)); }

    bool is_num(const u8char_t* begin)
    {
        const std::size_t len = u8Traits::length(begin);
        int start_idx = 0;
        int base = 10
        if ((len > 1) && (*begin == '0'_u8)) // base is octal, hex, or binary
        {
            const u8char_t& scd_char = as_lower(*(begin + 1));
            if (scd_char == 'x'_u8)
            {
                base = 16;
                start_idx = 2;
            }
            else if (scd_char == 'b'_u8)
            {
                base = 2;
                start_idx = 2;
            }
            else if (is_num(scd_char))
            {
                base = 8;
                start_idx = 1;
            }
            else ;// throw...
        }
        bool is_rational = false;
        bool is_number = true; // presume it is a number
        for (int i = start_idx; i < len; i++)
        {
            const u8char_t& curr = *(begin + i);
            if (curr == '.'_u8)
            {
                if (is_rational)
                    ;// throw...
                is_rational = true;
            }
            is_number &= is_num(curr, base);
            if (!is_number)
                return false;
        }
        return true;
    }

    u8char_t* to_lower(u8char_t* begin)
    {
        const std::size_t len = u8Traits::length(cstr);
        for (int i = 0; i < len; i++)
        {
            u8char_t& curr = *(begin + i);
            to_lower(curr);
        }
        return begin;
    }
}


using namespace xlog;


template<>
#if CPP_STD >= 17
constexpr void u8Traits::assign(char_type& lhs, const char_type& rhs) noexcept
#else
void u8Traits::assign(char_type& lhs, const char_type& rhs) noexcept
#endif
{ lhs.c = rhs.c; }

template<>
#if CPP_STD >= 17
constexpr int u8Traits::compare(const char_type* lhs, const char_type* rhs, std::size_t count)
#else
int u8Traits::compare(const char_type* lhs, const char_type* rhs, std::size_t count)
#endif
{
    // returns 0 if lhs and rhs are of equal length AND are less than count,
    // or if count is 0. returns 1 if the length of rhs is less than that of,
    // and 
    return (count != 0 && (length(lhs) != length(rhs)))
           ? (length(lhs) < length(rhs))
             ? -1
             : 1
           : 0;
    
}

template<>
#if CPP_STD >= 17
constexpr std::size_t u8Traits::length(const char_type* begin)
#else
std::size_t u8Traits::length(const char_type* begin)
#endif
{
    if (begin == nullptr)
        return 0;
    char_type* end = begin;
    while (*end != '\0'_u8)
        end += 1;
    return (end - begin);
}

template<>
#if CPP_STD >= 17
constexpr const typename u8Traits::char_type* u8Traits::find(const char_type* begin, std::size_t count, const char_type& ch)
#else
const typename u8Traits::char_type* u8Traits::find(const char_type* begin, std::size_t count, const char_type& ch)
#endif
{
    const char_type* end = (begin + std::min(count, length(begin)));
    char_type* ptr = begin;
    while (ptr < end)
        if (*ptr == ch)
            return ptr;
        else ptr++;
    return nullptr;
}

template<>
#if CPP_STD >= 20
constexpr typename u8Traits::char_type* u8Traits::assign(char_type* begin, std::size_t count, char_type c)
#else
typename u8Traits::char_type* u8Traits::assign(char_type* begin, std::size_t count, char_type c)
#endif
{
    const char_type* end = begin + count;
    for (char_type* ptr = begin; ptr < end; ptr++)
        assign(*ptr, c);
    return begin;
}

template<>
#if CPP_STD >= 20
constexpr typename u8Traits::char_type* u8Traits::move(char_type* dest, const char_type* src, std::size_t count)
#else
typename u8Traits::char_type* u8Traits::move(char_type* dest, const char_type* src, std::size_t count)
#endif
{
    count = (dest + std::min(count, length(src)))
    for (int i = 0, i < count; i++)
        if (!eq((dest + i), (src + i)))
            assign(dest[i], src[i]);
    return dest;
}

template<>
#if CPP_STD >= 20
constexpr typename u8Traits::char_type* u8Traits::copy(char_type* dest, const char_type* src, std::size_t count)
#else
typename u8Traits::char_type* u8Traits::copy(char_type* dest, const char_type* src, std::size_t count)
#endif
{
    count = (dest + std::min(count, length(src)))
    for (int i = 0, i < count; i++)
        if (!eq((dest + i), (src + i)))
            assign(dest[i], src[i]);
        else ;// throw... 
    return dest;
}

template<>
constexpr bool u8Traits::eq(char_type a, char_type b) noexcept
    { return (to_int_type(a) == to_int_type(b)); }

template<>
constexpr bool u8Traits::lt(char_type a, char_type b) noexcept
    { return (to_int_type(a) < int_type(b)); }

template<>
constexpr typename u8Traits::char_type u8Traits::to_char_type(int_type i) noexcept
    { return u8char_t((char32_t)ch); }

template<>
constexpr typename u8Traits::int_type u8Traits::to_int_type(char_type ch) noexcept
    { return static_cast<int_type>(ch); }

template<>
constexpr bool u8Traits::eq_int_type(int_type lhs, int_type rhs) noexcept
    { return (lhs == rhs); }

template<>
constexpr typename u8Traits::int_type u8Traits::eof() noexcept
    { return -1; }

template<>
constexpr typename u8Traits::int_type u8Traits::not_eof(int_type i) noexcept
    { return eq_int_type(i, eof()) ? 0 : i; }


constexpr u8String operator "" _u8(const char* cstr)
    { return u8String { cstr }; }

constexpr u8String operator "" _u8(const char* cstr, std::size_t)
    { return u8String { cstr }; }

constexpr u8String operator "" _u8(const wchar_t* cstr, std::size_t)
    { return u8String { cstr }; }

constexpr u8String operator "" _u8(const char16_t* cstr, std::size_t)
    { return u8String { cstr }; }

constexpr u8String operator "" _u8(const char32_t* cstr, std::size_t)
    { return u8String { cstr }; }

constexpr u8char_t operator "" _u8(char c)
    { return u8char_t(c); }

constexpr u8char_t operator "" _u8(wchar_t c)
    { return u8char_t(c); }

constexpr u8char_t operator "" _u8(char16_t c)
    { return u8char_t(c); }

constexpr u8char_t operator "" _u8(char32_t c)
    { return u8char_t(c); }

constexpr typename u8Traits::int_type operator "" _u8(unsigned long long i)
    { return typename u8Traits::int_type(i); }
