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

        void end_idt();
        void add_space();
        void make_format();
        void make_logger();
        void make_handler();
        uchar parse_indent();
        _Map get_block_map();
        _Array get_block_array();
        virtual _Map get_map() override;
        virtual _String get_key() override;
        virtual _Array get_array() override;
        virtual _String get_string() override;
        virtual ValueType get_value() override;
        virtual void on_eol() override;
        virtual void on_() override;
        virtual void on_() override;

      public:
        explicit Yaml(const fs::path&);
    };
}

#endif