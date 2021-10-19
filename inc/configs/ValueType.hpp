#ifndef X_LOG_CONFIGS_VALUETYPE_HPP
#define X_LOG_CONFIGS_VALUETYPE_HPP


namespace xlog::cnfg
{
    class ValueType;

    typedef umap<std::string, ValueType, std::hash<std::string>, utils::case_ins_eq> Map;
    typedef std::vector<ValueType> Array;
    typedef string_t String;

    enum VType : char
    {
        // u = undetermined, t = type
                          // u'ttt
        STRING           = 0b0'100,
        MAP              = 0b0'010,
        ARRAY            = 0b0'001,
        UNDETERMINED     = 0b1'000,
          NOT_STRING     = 0b1'011, // == ARRAY | MAP | UNDETERMINED
          NOT_ARRAY      = 0b1'110, // == STRING | MAP | UNDETERMINED
          NOT_MAP        = 0b1'101, // == STRING | ARRAY | UNDETERMINED
    };

    inline constexpr VType operator ~  (VType);
    inline constexpr VType operator |  (VType, VType);
    inline constexpr VType operator &  (VType, VType);
    inline constexpr VType operator ^  (VType, VType);
    inline constexpr bool operator == (VType, VType);
    inline constexpr bool is_determined(VType);
    inline constexpr bool is_array(VType);
    inline constexpr bool is_string(VType);
    inline constexpr bool is_map(VType);

    struct ValueType
    {
        ValueType(VType);
        ValueType& operator=(const Array&);
        ValueType& operator=(const Map&);
        ValueType& operator=(const String&);
        ValueType& operator=(VType);

        VType type;
        union
        {
            Map map;
            Array array;
            String string;
        };

        inline bool is_determined() const;
        inline bool is_map() const;
        inline bool is_array() const;
        inline bool is_string() const;
        inline bool is_block() const;
    };
}

#endif