#include "configs/ValueType.hpp"


namespace xlog::cnfg
{
    ValueType::ValueType(_Type type)
        : type_e(type)
    {
        switch (type_e)
        {
          case (BLOCK_ARRAY): FALLTHROUGH
          case (NESTED_ARRAY): FALLTHROUGH
          case (ARRAY):
            array = _Array();
            break;

          case (BLOCK_MAP): FALLTHROUGH
          case (MAP):
            map = _Map();
            break;

          case (STRING):
            string = _String();
            break;

          default:
            ;
        }
    }

    ValueType& ValueType::operator=(const _Array& arr)
    {
        type_e = ARRAY;
        array = arr;
    }

    ValueType& ValueType::operator=(const _Map& _map)
    {
        type_e = MAP;
        map = _map;
    }

    ValueType& ValueType::operator=(const _String& str)
    {
        type_e = STRING;
        string = str;
    }

    ValueType& ValueType::operator=(const _Type& _type)
    {
        type_e = _type;
        switch (type_e)
        {
          case (BLOCK_ARRAY): FALLTHROUGH
          case (NESTED_ARRAY): FALLTHROUGH
          case (ARRAY):
            array = _Array();
            break;

          case (BLOCK_MAP): FALLTHROUGH
          case (MAP):
            map = _Map();
            break;

          case (STRING):
            string = _String();
            break;

          default:
            ;
        }
    }
}
