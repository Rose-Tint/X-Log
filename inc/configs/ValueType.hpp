#ifndef X_LOG_CONFIGS_VALUETYPE_HPP
#define X_LOG_CONFIGS_VALUETYPE_HPP


namespace xlog::cnfg
{
    typedef str_umap<YamlType> _Map;
    typedef std::vector<YamlType> _Array;
    typedef string_t _String;

    struct ValueType
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
}

#endif