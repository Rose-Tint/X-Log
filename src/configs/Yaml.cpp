#include "fwd_declares.hpp"
#include "configs/basicparserbase.hpp"
#include "configs/yaml.hpp"
#include "utils.hpp"


// TODO: update completely


namespace xlog::cnfg
{
    Yaml::Yaml(const fs::path& path)
        : ParserBase(path)
    {
        u8char_t c = 0;
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
        if (idt_widths.size() > indent_lvl)
        {
            indent_width += 1;
            if (idt_widths[indent_lvl] == indent_width)
            {
                indent_width = 0;
                indent_lvl += 1;
            }
        }
        else if (idt_widths.size() == indent_lvl)
            idt_widths.back() += 1;
        else idt_widths.push_back(indent_width);
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
        if (u8Traits::eq(seek.curr, ' '_u8))
            return scope;
        else while (get(c))
        {
            if (u8Traits::eq(c, ' '_u8))
                add_idt_space(c);
            else if (u8Traits::eq(c, '\n'_u8))
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
        String key;
        String val;

        while (1)
        {
            new_scope = parse_indent();
            if (beg_scope == new_scope)
                break;
            key = get_key();
            if (key.size() == 0)
                ;// throw...
            if (u8Traits::eq(seek.curr, '\n'_u8) || eol())
                exp_new_scope(true);
            else
            {
                val = get_until('\n'_u8);
                utils::trim<u8char_t>(val, ' '_u8);
                if (u8Traits::eq(val.front(), '{'_u8) && u8Traits::eq(val.back(), '}'_u8))
                    type = ValueType::MAP;
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
        String val;

        while (1)
        {
            new_scope = parse_indent();
            if (beg_scope >= new_scope)
                break;
            if (u8Traits::eq(seek.curr, '-'_u8))
                ;// throw...
            val = get_until('\n'_u8);
            utils::trim<u8char_t>(val, ' '_u8);

            if (val.size() == 0)
                ;// throw...
            if (u8Traits::eq(val.front(), '-'_u8))
            {
                type = ValueType::ARRAY;
                value = _Array();
                get_array(value); // i think?
                String val = val.substr(1, val.size() - 1);
                utils::trim<u8char_t>(val, ' '_u8);
                value.array.insert(0, { val, ValueType::STRING });
                array_v.array.push_back(value);
                continue;
            }
            else if (u8Traits::eq(val.front(), '['_u8) && u8Traits::eq(val.back(), ']'_u8))
                type = ValueType::ARRAY;
            else if (u8Traits::eq(val.front(), '{'_u8) && u8Traits::eq(val.back(), '}'_u8))
                type = ValueType::MAP;
            else if (u8Traits::eq(val.back(), ':'_u8))
                type = ValueType::MAP;
            else type = ValueType::STRING;
            get_value(value);
            array_v.array.push_back(value);
        }
    }

    void Yaml::get_value(ValueType& value)
    {
        switch (value.type)
        {
          case (ValueType::STRING):{
            exp_new_scope(false);
            String str = get_until('\n'_u8);
            utils::trim<u8char_t>(str, ' '_u8);
            value.string = str;
          } break;
          case (ValueType::MAP):
            get_map(value);
            break;
          case (ValueType::ARRAY):
            extract_block_array(value);
            break;
          case (ValueType::ARRAY):
            get_array(value);
            break;
          default:
            ;// throw...
        }
    }

    Yaml::String Yaml::get_key()
    {
        if (scoping())
            parse_indent();
        u8char_t c = 0;
        key.clear();
        while (get(c))
        {
            if (u8Traits::eq(c, ':'_u8))
                break;
            else if (u8Traits::eq(c, '\n'_u8))
            {
                endl();
                file.sungetc();
            }
            else key.append(1, c);
        }
        return key;
    }

    LoggerConfigItf Yaml::make_logger(const _Map& map)
    {
        LoggerConfigItf itf;
        if (map.count("name"_u8))
            itf.Name(map.at("name"_u8));
        else ;// throw...

        if (map.count("filter"_u8))
            itf.Filter(map.at("filter"_u8));

        if (map.count("handlers"_u8))
        {
            ValueType array = { { }, ValueType::ARRAY };
            get_array(array);
            for (ValueType hvalue : array.first)
            {
                if (hvalue.type != ValueType::STRING)
                    ;// throw...
                itf.Handlers({ hvalue.string });
            }
        }
        return itf;
    }

    HandlerConfigItf Yaml::make_handler(const _Map& map)
    {
        HandlerConfigItf itf;
        if (map.count("name"_u8))
            itf.Name(map.at("name"_u8));
        else ;// throw...

        if (map.count("filter"_u8))
            itf.Filter(map.at("filter"_u8));
        if (map.count("format"_u8))
            itf.Format(map.at("format"_u8));
        if (map.count("min"_u8))
            itf.Min(map.at("min"_u8));
        if (map.count("max"_u8))
            itf.Max(map.at("max"_u8));

        // files...

        return handler;
    }
}
