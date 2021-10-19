#include "fwd_declares.hpp"
#include "configs/basicparserbase.hpp"
#include "configs/yaml.hpp"
#include "utils.hpp"


// TODO: update completely


namespace xlog::cnfg
{
    Yaml::Yaml(const fs::path& path)
        : ParserBase(path, { '\n' })
    {
        char c = 0;
        while (file)
        {
            // ...
        }
        file.close();
    }

    // if the scope is greater than or equal to the current level and
    // the current indent width matches the expected width for this scope
    // reset the current width and increment the current level
    void Yaml::add_idt_space()
    {
        scope = 0;
        scoping(true);
        if (idt_widths.size() >= indent_lvl)
        {
            indent_width += 1;
            if (idt_widths[indent_lvl] == indent_width)
            {
                indent_width = 0;
                indent_lvl += 1;
            }
        }
        else // TODO
    }

    // if the scope is greater than the current level and there is
    // no leftover/trailing white space, remove (end) the last scope.
    // else if the scope is less than the current indent level, enter
    // a new scope
    void Yaml::end_idt()
    {
        scoping(false);
        if (idt_widths.size() > indent_lvl)
        {
            if (indent_width != 0)
                ;// throw...
            idt_widths.pop_back();
        }
        else if (idt_widths.size() < indent_lvl)
        {
            idt_widths.push_back(indent_width);
            indent_width = 0;
        }
        scope = idt_widths.size();
    }

    void Yaml::endl()
    {
        indent_lvl = 0;
        indent_width = 0;
        eol(true);
    }

    uchar Yaml::parse_indent()
    {
        uchar beginning_scope = scope;
        if (Traits::eq(seek.curr, ' '))
            return scope;
        else while (get(c))
        {
            // use if-else over switch to be allowed to break the loop
            if (Traits::eq(c, ' '))
                add_idt_space(c);
            else if (Traits::eq(c, '\n'))
                endl();
            else break;
        }
        end_idt();
        if (exp_new_scope() && (scope <= beginning_scope))
            ;// throw...
        return scope;
    }

    ValueType Yaml::get_map()
    {
        map_v = _Map();
        uchar beg_scope = parse_indent();
        uchar new_scope = scope;
        scoping(false);
        ValueType::_Type type = ValueType::UNDETERMINED;
        _String key;
        _String val;

        while (1)
        {
            new_scope = parse_indent();
            if (beg_scope == new_scope)
                break;
            key = get_key();
            if (key.size() == 0)
                ;// throw...
            if (Traits::eq(seek.curr, '\n') || eol())
                exp_new_scope(true);
            else
            {
                val = get_statement();
                utils::trim(val, ' ');
                if (Traits::eq(val.front(), '{') && Traits::eq(val.back(), '}'))
                    type = ValueType::BLOCK_MAP;
                else type = ValueType::STRING;
            }

            scoping(true);
            ValueType value { { }, type };
            get_value(value); // recurse
            map[key] = value;
        }
        map_v.map = std::move(map);
    }

    ValueType Yaml::get_array()
    {
        array_v = _Array();
        uchar beg_scope = parse_indent();
        uchar new_scope = scope;
        scoping(false);
        ValueType::_Type type = ValueType::UNDETERMINED;
        ValueType value;
        _String val;

        while (1)
        {
            new_scope = parse_indent();
            if (beg_scope >= new_scope)
                break;
            if (Traits::eq(seek.curr, '-'))
                ;// throw...
            val = get_statement();
            utils::trim(val, ' ');

            if (val.size() == 0)
                ;// throw...
            if (Traits::eq(val.front(), '-'))
            {
                type = ValueType::ARRAY;
                value = _Array();
                get_array(value); // i think?
                _String val = val.substr(1, val.size() - 1);
                utils::trim(val, ' ');
                value.array.insert(0, { val, ValueType::STRING });
                array_v.array.push_back(value);
                continue;
            }
            else if (Traits::eq(val.front(), '[') && Traits::eq(val.back(), ']'))
                type = ValueType::BLOCK_ARRAY;
            else if (Traits::eq(val.front(), '{') || Traits::eq(val.back(), '}'))
                type = ValueType::BLOCK_MAP;
            else if (Traits::eq(val.back(), ':'))
                type = ValueType::MAP;

            else type = ValueType::STRING;
            get_value(value);
            array_v.array.push_back(value);
        }
    }

    void Yaml::get_value(ValueType& value)
    {
        switch (value.type_e)
        {
          // parse looking for a string
          case (ValueType::STRING):{
            exp_new_scope(false);
            _String str = get_statement();
            utils::trim(str, ' ');
            value.string = str;
            } break;

          // parse looking for a map
          case (ValueType::BLOCK_MAP):
            extract_block_map(value);
            break;
          case (ValueType::MAP):
            get_map(value);
            break;

          // parse looking for an array
          case (ValueType::BLOCK_ARRAY):
            extract_block_array(value);
            break;
          case (ValueType::ARRAY):
            get_array(value);
            break;

            default:
                ;// throw...
        }
    }

    Yaml::_String Yaml::get_key()
    {
        if (scoping())
            parse_indent();
        char c = 0;
        key.clear();
        while (get(c))
        {
            if (Traits::eq(c, ':'))
                break;
            else if (Traits::eq(c, '\n'))
            {
                endl();
                file.unget();
            }
            else key.append(1, c);
        }
        return key;
    }

    LoggerConfigItf Yaml::make_logger(const _Map& map)
    {
        LoggerConfigItf itf;
        if (map.count("name"))
            itf.Name(map.at("name"));
        else ;// throw...

        if (map.count("filter"))
            itf.Filter(map.at("filter"));

        if (map.count("handlers"))
        {
            ValueType array = { { }, ValueType::ARRAY };
            get_array(array);
            for (ValueType hvalue : array.first)
            {
                if (hvalue.type_e != ValueType::STRING)
                    ;// throw...
                itf.Handlers({ hvalue.string });
            }
        }
        return itf;
    }

    HandlerConfigItf Yaml::make_handler(const _Map& map)
    {
        HandlerConfigItf itf;
        if (map.count("name"))
            itf.Name(map.at("name"));
        else ;// throw...

        if (map.count("filter"))
            itf.Filter(map.at("filter"));
        if (map.count("format"))
            itf.Format(map.at("format"));
        if (map.count("min"))
            itf.Min(map.at("min"));
        if (map.count("max"))
            itf.Max(map.at("max"));

        // files...

        return handler;
    }
}
