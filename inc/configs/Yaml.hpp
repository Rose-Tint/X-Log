#ifndef X_LOG_CONFIGS_HPP
#define X_LOG_CONFIGS_HPP

#include "fwd_declares.hpp"
#include "configs/TypeConfigItf.hpp"
#include "configs/ParserBase.hpp"
#include "configs/ValueType.hpp"


namespace xlog::cnfg
{
    class Yaml : public ParserBase, ConfigType
    {
        typedef ValueType YamlType;
        std::vector<uchar> idt_widths;
        uchar indent_width;
        uchar indent_lvl;

        uchar parse_indent(bool&);
        LoggerConfigItf make_logger();
        HandlerConfigItf make_handler();
        FormatConfigItf make_format();
        // template<class T> extract_array_to(std::vector<T>&); // TODO
        void add_idt_space(); // TOFIN
        void end_indentation();
        void end_of_line();
        void get_key();
        void extract_map(YamlType&); // TOFIN?
        void extract_block_map(YamlType&); // TODO
        void extract_array(YamlType&); // TOFIN
        void extract_block_array(YamlType&); // TODO
        void extract_value(YamlType&); // TOFIN?

      public:
        explicit Yaml(const fs::path&);
    };
}

#endif