#include "record.hpp"

namespace xlog
{
    
    Recod::Record(const std::string& fl, const uchar& ln, const std::string fn, str_pair_t arg_pairs)
        : file(fl), line(ln), func(fn), args(arg_pairs.begin(), arg_pairs.end()) { }

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

#ifdef CPP20
    Record::Record(const std::source_location& info, const arg_map_t& arg_pairs)
        : file(info.file_name()),
          line(info.line()),
          func(info.function_name()),
          args(arg_pairs.begin(), arg_pairs.end()) { }
#endif
}
