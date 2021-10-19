#include "configs/ValueType.hpp"


namespace xlog::cnfg
{
    inline constexpr VType operator ~ (VType type)
        { return ~static_cast<char>(type); }
    inline constexpr VType operator | (VType lhs, VType rhs) // clearly unfinished
    {
        return (lhs != rhs)
            ? ()
                ? (is_determined(lhs)) // if lhs is determined
                    ? lhs | (is_determined(rhs)) // if rhs is determined
                        ? rhs
                        : ()
                            ? 
                            : 
                    : 
                :
            : lhs
    }
    inline constexpr VType operator & (VType lhs, VType rhs)
        { return static_cast<char>(lhs) & static_cast<char>(rhs); }
    inline constexpr VType operator ^ (VType lhs, VType rhs)
        { return static_cast<char>(lhs) ^ static_cast<char>(rhs); }
    inline constexpr bool operator == (VType lhs, VType rhs)
        { return static_cast<char>(lhs) == static_cast<char>(rhs); }
    inline constexpr bool is_determined(VType type)
        { return ((static_cast<char>(type) >> (sizeof(type) - 1)) == 0); }
    inline constexpr bool is_array(VType);
    inline constexpr bool is_string(VType);
    inline constexpr bool is_map(VType);

    ValueType::ValueType(VType type)
        : type(type)
    {
        switch (type)
        {
          case (ARRAY):
            array = Array();
            break;

          case (MAP):
            map = Map();
            break;

          case (STRING):
            string = String();
            break;

          default:
            ;
        }
    }

    ValueType& ValueType::operator=(const Array& arr)
    {
        type = ARRAY;
        array = arr;
    }

    ValueType& ValueType::operator=(const Map& _map)
    {
        type = MAP;
        map = _map;
    }

    ValueType& ValueType::operator=(const String& str)
    {
        type = STRING;
        string = str;
    }

    ValueType& ValueType::operator=(VType _type)
    {
        type = _type;
        switch (type)
        {
          case (BLOCK_ARRAY): FALLTHROUGH
          case (NESTED_ARRAY): FALLTHROUGH
          case (ARRAY):
            array = Array();
            break;

          case (BLOCK_MAP): FALLTHROUGH
          case (MAP):
            map = Map();
            break;

          case (STRING):
            string = String();
            break;

          default:
            ;
        }
    }
}
