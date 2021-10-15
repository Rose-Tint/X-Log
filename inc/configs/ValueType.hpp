#ifndef X_LOG_CONFIGS_VALUETYPE_HPP
#define X_LOG_CONFIGS_VALUETYPE_HPP


namespace xlog::cnfg
{
    class ValueType;

    typedef str_umap<ValueType, std::hash<ValueType>, utils::case_ins_eq> _Map;
    typedef std::vector<ValueType> _Array;
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

        ValueType(_Type);
        ValueType& operator=(const _Array&);
        ValueType& operator=(const _Map&);
        ValueType& operator=(const _String&);
        ValueType& operator=(const _Type&);

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