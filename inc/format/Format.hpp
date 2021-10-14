#ifndef X_LOG_FORMAT_FORMAT_HPP
#define X_LOG_FORMAT_FORMAT_HPP

#include "format/context.hpp"
#include "format/DateTimeFormat.hpp"
#include "format/CharOutputIter.hpp"


namespace xlog
{
    class Format final
    {
        /*  named requirements goals:
          *   - DefaultConstructible
          *   - CopyConstructible
          *   - CopyAssignable
          *   - Destructible
          *   - Swappable
          *   - Swappable
          *   - Arg, a formatting argument type
          *   - CharT, a character type
          *   - OutputIt, a LegacyOutputIterator type
          *   - formatter, a value of type Formatter
          *   - arg, an lvalue of type Arg
          *   - ParseContext, an alias of std::basic_format_parse_context<CharT>
          *   - FormatContext, an alias of std::basic_format_context<OutputIt, CharT>
          *   - member function ParseContext::iterator parse(ParseContext ctx) must:
          *     - Parses the format-spec [ctx.begin(), ctx.end()) for type Arg until the first unmatched
          *         character.
          *     - Throws std::format_error unless the whole range is parsed.
          *     - Stores the parsed format specifiers in formatter and returns an end iterator of the
          *         parsed range.
          *   - member function FormatContext::iterator format(const Arg& arg, FormatContext ctx) must:
          *     - Formats t according to the specifiers stored in formatter, writes the output to ctx.out()
          *         and returns an end iterator of the output range.
          *     - The output shall only depend on
          *       - arg,
          *       - ctx.locale(),
          *       - the range [parse_context.begin(), parse_context.end()) from the
          *           last call to formatter.parse(parse_context), and
          *       - ctx.arg(n) for any value n of type std::size_t.
           */
      public:
        typedef const Record& Arg;
        typedef char_t CharT;
        typedef CharOutputIter OutputIt;
        typedef basic_format_parse_context<CharT> ParseContext;
        typedef basic_format_context<CharT> FormatContext;

        friend Format& get_format(const string_t&);
        friend const Format& find_format(const string_t&);

      private:
        static lookup_map<Format> formats;

        string_t name;
        DateTimeFormat dt_fmt = def_dtf;
        string_t fmt = def_fmt;

        arg_map_t get_args(Arg) const;

      public:
        Format() = delete;
        explicit Format(const string_t&);

        static inline const DateTimeFormat def_dtf = { "H:m:S:s", "Y/M/D", "H:m:S:s - Y/M/D" }
        static inline const string_t def_fmt = "${date} | ${file} - line ${line}:\n -- ${msg}";

        string_t operator()(Arg) const;
        const string_t& get_name() const;
        typename ParseContext::iterator parse(ParseContext);
        typename FormatContext::iterator format(Arg, FormatContext);
        void set_fmt(const string_t& format);
        void set_time(const string_t& tfmt);
        void set_date(const string_t& tfmt);
        void set_dtime(const string_t& tfmt);
    };
}

#endif