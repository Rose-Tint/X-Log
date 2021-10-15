#include "record.hpp"

namespace xlog
{
    Record::Record(const string_t& fl, uint ln, const string_t& fn, ilist<str_pair_t> arg_pairs)
        : file(fl), line(ln), func(fn)
    {
        insert_args(arg_pairs.begin(), arg_pairs.end());
    }

#ifdef CPP20
    Record::Record(const std::source_location& info, ilist<str_pair_t> arg_pairs)
        : file(info.file_name()),
          line(info.line()),
          func(info.function_name())
    {
        insert_args(pairs);
    }
#endif

    arg_map_t Record::get_dict() const
    {
        arg_map_t dict
        {
            { "msg" , msg                  },
            { "lgr" , lgr                  },
            { "file", file                 },
            { "lvl" , std::to_string(lvl)  },
            { "line", std::to_string(line) },
        };
        dict.insert(args.begin(), args.end());
        return dict;
    }

    void Record::insert_args(const string_t& key, const string_t& value)
    {
        args.insert({ key, value });
    }

    void Record::insert_args(str_pair_t pair)
    {
        insert_args(pair.first, pair.second);
    }

    void Record::insert_args(ilist<str_pair_t> pairs)
    {
        for (auto pair : pairs)
            insert_args(pair);
    }

    template<class It>
    void Record::insert_args(It begin, It end, iter_tag<It>*)
    {
        for (auto iter = begin; iter < end; iter++)
            insert_args(iter);
    }
}
