#ifndef X_LOG_CONFIGS_HPP
#define X_LOG_CONFIGS_HPP

#include "fwd_declares.hpp"
#include "configs/TypeConfigItf.hpp"
#include "configs/ParserBase.hpp"
#include "configs/ValueType.hpp"


namespace xlog::cnfg
{
    class Yaml : public ParserBase, public ConfigTypeBase
    {
        std::vector<uchar> idt_widths;
        uchar indent_width;
        uchar indent_lvl;

        uchar parse_indent(bool&);
        LoggerConfigItf make_logger();
        HandlerConfigItf make_handler();
        FormatConfigItf make_format();
        void add_idt_space(); // TOFIN
        void end_indentation();
        void end_of_line();
        void get_key();
        void extract_map(ValueType&); // TOFIN?
        void extract_block_map(ValueType&); // TODO
        void extract_array(ValueType&); // TOFIN
        void extract_block_array(ValueType&); // TODO
        void extract_value(ValueType&); // TOFIN?

      public:
        explicit Yaml(const fs::path&);
    };
}

#endif