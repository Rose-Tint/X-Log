#include "fwd_declares.hpp"
#include "configs/basicparserbase.hpp"
#include "configs/yaml.hpp"
#include "utils.hpp"


// IN THE MIDDLE OF BEGINNING TO USE std::char_traits


namespace xlog::cnfg
{
    Yaml::Yaml(const fs::path& path)
        : ParserBase(path, '\n')
    {
        char c = 0;
        while (file)
        {
            parse_indent();
            std::string line = get_statement();
            utils::trim(line, ' ');

            if (utils::case_ins_eq(line, "loggers"))
                // extract_array_to<LoggerConfigItf>(loggers);
            else if (utils::case_ins_eq(line, "handlers"))
                // extract_array_to<HandlerConfigItf>(handlers);
            else if (utils::case_ins_eq(line, "formats"))
                // extract_array_to<FormatConfigItf>(formats);
            else;// throw...
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
    void Yaml::end_indentation()
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

    void Yaml::end_of_line()
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
                end_of_line();
            else break;
        }
        end_indentation();
        if (exp_new_scope() && (scope <= beginning_scope))
            ;// throw...
        return scope;
    }

    void Yaml::extract_map(YamlType& map_v)
    {
        map_v = _Map();
        uchar beg_scope = parse_indent();
        uchar new_scope = scope;
        scoping(false);
        YamlType::_Type type = YamlType::UNDETERMINED;
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
                    type = YamlType::BLOCK_MAP;
                else type = YamlType::STRING;
            }

            scoping(true);
            YamlType value { { }, type };
            extract_value(value); // recurse
            map[key] = value;
        }
        map_v.map = std::move(map);
    }

    void Yaml::extract_array(YamlType& array_v)
    {
        array_v = _Array();
        uchar beg_scope = parse_indent();
        uchar new_scope = scope;
        scoping(false);
        YamlType::_Type type = YamlType::UNDETERMINED;
        YamlType value;
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
                type = YamlType::ARRAY;
                value = _Array();
                extract_array(value); // i think?
                _String val = val.substr(1, val.size() - 1);
                utils::trim(val, ' ');
                value.array.insert(0, { val, YamlType::STRING });
                array_v.array.push_back(value);
                continue;
            }
            else if (Traits::eq(val.front(), '[') && Traits::eq(val.back(), ']'))
                type = YamlType::BLOCK_ARRAY;
            else if (Traits::eq(val.front(), '{') || Traits::eq(val.back(), '}'))
                type = YamlType::BLOCK_MAP;
            else if (Traits::eq(val.back(), ':'))
                type = YamlType::MAP;

            else type = YamlType::STRING;
            extract_value(value);
            array_v.array.push_back(value);
        }
    }

    void Yaml::extract_value(YamlType& value)
    {
        switch (value.type_e)
        {
          // parse looking for a string
          case (YamlType::STRING):{
            exp_new_scope(false);
            _String str = get_statement();
            utils::trim(str, ' ');
            value.string = str;
            } break;

          // parse looking for a map
          case (YamlType::BLOCK_MAP):
            extract_block_map(value);
            break;
          case (YamlType::MAP):
            extract_map(value);
            break;

          // parse looking for an array
          case (YamlType::BLOCK_ARRAY):
            extract_block_array(value);
            break;
          case (YamlType::ARRAY):
            extract_array(value);
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
                end_of_line();
                file.unget();
            }
            else key.append(1, c);
        }
        return key;
    }

    LoggerConfigItf Yaml::make_logger(const Yaml::_Map& map)
    {
        LoggerConfigItf logger;
        set_or_throw(logger.name, map, "name", "Name field required");
        auto hdlrs_arr_iter = map.find("handlers");
        if (hdlrs_arr_iter != map.end())
        {
            YamlType hdlr_arr = { { }, YamlType::ARRAY };
            file >> hdlr_arr;
            for (YamlType hdlr_v : hdlr_arr.first)
            {
                if (hdlr_v.type_e != YamlType::STRING)
                    ;// throw...
                logger.handlers.push_back(hdlr_v.first);
            }
        }
        return logger;
    }

    HandlerConfigItf Yaml::make_handler(const Yaml::_Map& map)
    {
        HandlerConfigItf handler;
        set_or_throw(handler.name, map, "name", "Name field required");
        try_set(handler.min, map, "min");
        try_set(handler.max, map, "max");
        auto file_arr_iter = map.find("files");
        if (file_arr_iter != map.end())
        {
            YamlType file_arr = { { }, YamlType::ARRAY };
            file >> file_arr;
            for (YamlType file_v : file_arr.array)
            {
                if (file_v.type_e != YamlType::STRING)
                    ;// throw...
                handler.files.push_back(file_v.first);
            }
        }
        return handler;
    }

    FormatConfigItf Yaml::make_format(const _Map& map)
    {
        FormatConfigItf format
        set_or_throw(format.name, map, "name", "Name field required");
        try_set(format.fmt, map, "fmt");
        try_set(format.date, map, "date");
        try_set(format.time, map, "time");
        try_set(format.datetime, map, "datetime");
        return format;
    }
}
