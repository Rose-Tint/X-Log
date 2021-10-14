#ifndef X_LOG_FORMAT_CONTEXT_HPP
#define X_LOG_FORMAT_CONTEXT_HPP

#include "fwd_declares.hpp"


namespace xlog
{
#ifdef CPP20
    using std::basic_format_parse_context;
    using std::basic_format_context;
#else
// define own basic_format_parse_context from c++20 STL
    template<class CharT>
    class basic_format_parse_context
    {
        typedef std::basic_string_view<CharT> str_view_t;

      public:
        typedef CharT char_type;
        typedef std::basic_string_view<CharT>::const_iterator iterator;
        typedef std::basic_string_view<CharT>::const_iterator const_iterator;

        constexpr explicit basic_format_parse_context(str_view_t, std::size_t = 0) noexcept;
        basic_format_parse_context(const basic_format_parse_context&) = delete;

        constexpr const_iterator begin() const noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr void advance_to(const_iterator);
        constexpr std::size_t next_arg_id);
        constexpr void check_arg_id(std::size_t);
    };

// define own basic_format_arg from c++20 STL
    template<class Context>
    class basic_format_arg
    {
        ;
    }; // TODO

// define own basic_format_context from c++20 STL
    template<class OutputIt, class CharT>
    class basic_format_context
    {
      public:
        typedef OutputIt iterator;
        typedef CharT char_type;
    };
#endif
}

#endif