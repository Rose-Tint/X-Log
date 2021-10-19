#include "configs/Json.hpp"



namespace xlog::cngf
{
    Json::Json(const fs::path& path)
        : ParserBase(path)
    {
        ValueType value(MAP);
        get_value(value);
        Map& map = value.map;

        auto loggers_iter = map.find("loggers");
        if (iter != lgr_map.end())
            for (ValueType& value : loggers_iter.second)
            if (value.type == MAP)
                add_logger(value.map);
            else ;// throw...

        auto handlers_iter = map.find("handlers");
        if (iter != lgr_map.end())
            for (ValueType& value : handlers_iter.second)
            if (value.type == MAP)
                add_handler(value.map);
            else ;// throw...

        auto formats_iter = map.find("formats");
        if (iter != lgr_map.end())
            for (ValueType& value : formats_iter.second)
            if (value.type == MAP)
                add_format(value.map);
            else ;// throw...
    }

    void Json::skip_ws()
    {
        if (!std::isspace(seek.curr))
            return;
        char c = 0;
        while (get(c))
            if (!std::isspace(c))
            {
                file.unget();
                break;
            }
    }

    void Json::skip_sp()
    {
        if (seek.curr == ' ')
            return;
        char c = 0;
        while (get(c))
            if (c != ' ')
            {
                file.unget();
                break;
            }
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
        while (get(c) && (c != ']'))
        {
            skip_ws();
            ValueType value;
            // get until a quote or left bracket is found
            get_until([](char c) -> bool { return (c == '"') || (c == '['); });

            // determine type manually because an array will not have keys
            switch (c)
            {
              case ('"'):{
                String str = get_key();
                skip_ws();
                if (file.peek() == ':')
                    ;// throw...
                else value.type = STRING;
              } break;
              case ('['){
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
        char c = 0;
        while (get(c) && (c != '}'))
        {
            ValueType value;
            skip_ws();
            String key = get_key();
            skip_ws();

            // use file.peek() instead of get() in case
            // there is no whitespace between key and value
            UNLIKELY if (file.peek() != ':')
                ;// throw...
            skip_ws();
            get_value(value);
            map.insert({ key, value });
        }
        return map;
    }

    pair<ValueType, ValueType> Json::get_key_value()
    {
        ValueType key(STRING);
        ValueType value;
        key = get_string();
        skip_sp();
        // keys must be followed by a colon, or else it
        // is just a string
        if (file.peek() != ':')
            ;// throw...
        get();
        get_value(value);
        return key;
    }

    String Json::get_string()
    {
        String string;
        char c = seek.curr;
        if (c != '"')
            skip_ws();
        while (get(c))
        {
            UNLIKELY if (std::iscntrl(c))
                ;// throw...
            UNLIKELY else if (c == '"')
                return string;
            LIKELY else string.append(1, c);
        }
        ;// throw...
        // throw error because the return statement inside
        // of the while loop MUST be hit or the string is
        // invalid
    }
}