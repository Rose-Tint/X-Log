#include "configs/Json.hpp"

// TODO: allow `get_value` to determine type



namespace xlog::cngf
{
    Json::Json(const fs::path& path)
        : ParserBase(path)
    {
        ValueType value(MAP);
        get_value(value);
        Map& map = value.map;

        auto loggers_iter = map.find("loggers"_u8);
        if (iter != lgr_map.end())
            for (ValueType& value : loggers_iter.second)
            if (value.type == MAP)
                add_logger(value.map);
            else ;// throw...

        auto handlers_iter = map.find("handlers"_u8);
        if (iter != lgr_map.end())
            for (ValueType& value : handlers_iter.second)
            if (value.type == MAP)
                add_handler(value.map);
            else ;// throw...

        auto formats_iter = map.find("formats"_u8);
        if (iter != lgr_map.end())
            for (ValueType& value : formats_iter.second)
            if (value.type == MAP)
                add_format(value.map);
            else ;// throw...
    }

    void Json::skip_ws()
    {
        if (!is_whitesp(seek.curr))
            return;
        u8char_t c;
        while (get(c) && (!is_whitesp(c)))
            ; // do nothign
        file.sungetc();
    }

    void Json::skip_sp()
    {
        if (u8Traits::eq(seek.curr, ' '_u8))
            return;
        u8char_t c;
        while (get(c) && (u8Traits::eq(c, ' '_u8))
            ; // do nothing
        file.sungetc();
    }

    void Json::get_value(ValueType& value)
    {
        if (is_array(value.type)
            value.array = get_array();
        else if (is_map(value.type))
            value.map = get_map();
        else if (is_string(value.type))
            value.string = get_string();
        else ;// throw...
    }

    ValueType Json::get_value(VType type)
    {
        ValueType value(type);
        get_value(type);
        return value;
    }

    Array Json::get_array()
    {
        Array array;
        while (get(c) && !(u8Traits::eq(c, ']'_u8)))
        {
            skip_ws();
            ValueType value;
            // get until a quote or left bracket is found
            auto is_rbracket_or_quote = [](const u8char_t& c) -> bool
                { return u8Traits::eq(c, '"'_u8) || u8Traits::eq(c,'['_u8); }
            get_until(is_rbracket_or_quote);

            // determine type manually because an array will not have keys
            switch (c)
            {
              case ('"'_u8):{
                String str = get_key();
                skip_ws();
                if (next_is_colon())
                    value.type = STRING;
                else ;// throw...
              } break;
              case ('['_u8){
                value.type = ARRAY;
              } break;
              default:
                ;// throw...
            }
            get_value(value);
            array.push_back(value);
        }
        return array;
    }

    Map Json::get_map()
    {
        Map map;
        u8char_t c;
        while (get(c) && !(u8Traits::eq(c, '}'_u8)))
        {
            auto key_val = get_key_value();
            map.insert(std::move(key_val));
        }
        return map;
    }

    std::pair<ValueType, ValueType> Json::get_key_value()
    {
        ValueType key(STRING);
        ValueType value;
        key = get_key();
        skip_sp();
        UNLIKELY if (!next_is_colon())
            ;// throw...
        get();
        get_value(value);
        return { key, value };
    }

    String Json::get_string()
    {
        String string;
        u8char_t c;
        u8Traits::assign(c, seek.curr);
        if (!(u8Traits::eq(c, '"'_u8))
            skip_ws();
        while (get(c))
        {
            UNLIKELY if (is_cntrl(c))
                ;// throw...
            UNLIKELY else if (u8Traits::eq(c, '"'_u8))
                return string;
            LIKELY else string.append(1, c);
        }
        ;// throw...
        // throw error because the return statement inside
        // of the while loop MUST be hit or the string is
        // invalid
    }

    bool Json::next_is_colon() const
    {
        // use file.sgetc() instead of get() in case
        // there is no whitespace between the key and colon
        u8char_t nextc;
        u8Traits::assign(nextc, u8Traits::to_char_type(file.sgetc()));
        return u8Traits::eq(nextc, ':'_u8);
    }
}