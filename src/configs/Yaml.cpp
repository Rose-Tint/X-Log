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
        char8_t c = 0;
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
        uchar beg_scope = scope;
        char8_t c = seek.curr;
        if (seek.curr != u8' ')
            return scope;
        while (get(c))
        {
            // use if-else over switch to be allowed to break the loop
            if (c == ' ')
                add_idt_space(c);
            else if (c == '\n')
                endl();
            else break;
        }
        end_idt();
        if (exp_new_scope() && (scope <= beg_scope))
            ;// throw...
        return scope;
    }

    Map Yaml::get_map()
    {
        Map map;
        uchar beg_scope = parse_indent();
        scope += 1;
        scoping(false);

        while (scope > beg_scope)
            map.insert(get_key_value());
        map.map = std::move(map);
    }

    Array Yaml::get_array()
    {
        Array array;
        uchar beg_scope = 0;
        ValueType elem;
        String buf;

        if (newline())
            parse_indent();
        else skip_sp();
        beg_scope = scope++;
        // inc scope so the while executes.
        // scope will be fixed as soon as
        // end_idt() is called.
        // <sub>do-whiles are ugly</sub>

        while (scope > beg_scope)
        {
            parse_indent();
            buf = get_until(u8'\n');
            utils::trim(buf, u8' ');

            if (buf.size() == 0)
            {
                ;// throw...
            }
            if (buf.front() == u8'-')
            {
                buf = buf.substr(1);
                utils::trim(val, u8' ');
                auto colon_idx = buf.find(':');
                if (colon_idx != String::npos)
                {
                    if (colon_idx == buf.back())
                        elem.type = ValueType::MAP
                }

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
            String str = get_statement();
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

    String Yaml::get_key()
    {
        if (scoping())
            parse_indent();
        char8_t c = 0;
        key.clear();
        while (get(c))
        {
            if (c == ':')
                break;
            else if (c == '\n')
            {
                endl();
                file.unget();
            }
            else key.append(1, c);
        }
        return key;
    }

    std::pair<ValueType, ValueType> Yaml::get_key_value()
    {
        String key = get_key();
        ValueType::_Type type = ValueType::UNDETERMINED;
        ValueType value(type);
        String val_str;
        if (key.size() == 0)
            ;// throw...
        if (!eol())
        {
            val_str = get_until(u8'\n');
            utils::trim(val_str, u8' ');
            if (val_str.empty())
            {
                get(); // skip new line char
                auto is_dash_or_brace_or_bracket =
                    [](const char8_t& c) -> bool
                        { return (c == u8'-' || c == u8'{' || c ==  u8'['); };
                val_str = get_until(is_dash_or_brace_or_bracket);
                utils::trim(val_str, u8' ');
                switch (val_str.back())
                {
                  case (u8'['):
                  case (u8'-'):{
                    type = ValueType::ARRAY;
                  } break;
                  case (u8'{'):{
                    type = ValueType::MAP;
                  } break;
                  default: ;// throw...
                }
                get(); // skip [ { or -
            }
            else type = ValueType::STRING;
        }
        else ;// throw...

        value.type = type;
        get_value(value);
        return { ValueType(key), value };
    }
}
