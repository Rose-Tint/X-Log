#ifndef X_LOG_CONFIGS_HPP
#define X_LOG_CONFIGS_HPP

#include "fwd_declares.hpp"
#include "../../inc/configs/configtype.hpp"
#include "../../inc/configs/basicparserbase.hpp"
#include "utils.hpp"


namespace xlog::config
{
    template<class char_t>
    class Yaml : public BasicParserBase<char_t>, ConfigType
    {
        typedef str_umap<YamlType> _Map;
        typedef std::vector<YamlType> _Array;
        typedef string_t _String;

        struct YamlType
        {
            enum _Type : signed short
            {
                // d = determined, t = type, n = nested, b = block
                                  // d'tttt'n'b
                UNDETERMINED     = 0b1'0000'0'0,
                    NOT_STRING   = 0b1'1000'0'0,
                    NOT_ARRAY    = 0b1'0100'0'0,
                    NOT_MAP      = 0b1'0010'0'0,
                MAP              = 0b0'1101'0'0,
                    BLOCK_MAP    = 0b0'1101'0'1,
                ARRAY            = 0b0'1010'0'0,
                    NESTED_ARRAY = 0b0'1010'0'1,
                    BLOCK_ARRAY  = 0b0'1010'0'1,
                STRING           = 0b0'0110'0'0,
            };

            YamlType(_Type);
            YamlType& operator=(const _Array&);
            YamlType& operator=(const _Map&);
            YamlType& operator=(const _String&);
            YamlType& operator=(const _Type&);

            _Type type_e;
            union
            {
                _Map map;
                _Array array;
                _String string;
            };

            inline bool is_determined() const;
            inline bool is_map() const;
            inline bool is_array() const;
            inline bool is_string() const;
            inline bool is_block() const;
        };

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