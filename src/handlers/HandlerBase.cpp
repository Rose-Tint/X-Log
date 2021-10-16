#include "handler.hpp"


namespace xlog
{
    HandlerBase& get_handler() { return stdhdlr; }
    HandlerBase& get_handler(const string_t& name)
    {
        if (name == "" || name == "std")
            return stdhdlr;
        if (!HandlerBase::handlers.count(name))
            HandlerBase(name);
        return HandlerBase::handlers.at(name);
    }

    HandlerBase::HandlerBase(const string_t& name)
        : name(name)
    {
        handlers.insert({ name, this });
    }

    void HandlerBase::set_min(uchar mn)
    {
        if (mn > max) std::swap(mn, max);
        min = mn;
    }

    void HandlerBase::set_max(uchar mx)
    {
        if (mx < min) std::swap(mx, min);
        max = mx;
    }

    void HandlerBase::set_format(const string_t& fmt_name)
    {
        format_name = fmt_name;
    }

    void HandlerBase::set_filter(const string_t& filt_name)
    {
        filter_name = filt_name;
    }

    void HandlerBase::add_outstreams(buffer_t buf)
    {
        lstream.add_outstreams(buf);
    }

    template<class It, utils::EnableIterFor<buffer_t, It>>
    void HandlerBase::add_outstreams(It begin, It end)
    {
        lstream.add_outstreams(begin, end);
    }

    bool HandlerBase::handle(Record& rcd)
    {
        if (!filter()(rcd)) return false;
        lstream.write(rcd.get_msg());
        return true;
    }
}
