#include "handler.hpp"


namespace xlog
{
    void make_handler(const std::string name)
    {
        if (Handler::handlers.count(name) != 0)
            ;// throw...
        auto& hdlr = Handler(name);
    }

    Handler& get_handler(const std::string& name)
    {
        if (name == "")
            return find_handler("std");
        if (Handler::handlers.count(name) == 0)
            make_handler(name);
        return find_handler(name);
    }

    Handler& find_handler(const std::string& name)
    {
        if (Handler::handlers.count(name) == 0)
            ;//throw...
        return Handler::handlers[name];
    }

    Handler::Handler(const std::string& _name)
        : name(_name)
    {
        handlers.insert({ name, this });
    }

    Handler& Handler::operator=(Handler&& other)
    {
        if (this == &other) return *this;
        name = std::move(other.name);
        filter_name = std::move(other.filter_name);
        lstream = std::move(other.lstream);
        min = std::move(other.min);
        max = std::move(other.max);
        return *this;
    }

    Handler::Handler(Handler&& other)
    {
        name = std::move(other.name);
        filter_name = std::move(other.filter_name);
        lstream = std::move(other.lstream);
        min = std::move(other.min);
        max = std::move(other.max);
    }

    Handler::~Handler()
    {
        handlers.erase(name);
    }

    bool Handler::handle(Record& rcd)
    {
        if (!filter()(rcd)) return false;
        lstream.write(rcd.get_msg());
        return true;
    }

    Handler& Handler::set_min(uchar mn)
    {
        if (mn > max) std::swap(mn, max);
        min = mn;
        return *this;
    }

    Handler& Handler::set_max(uchar mx)
    {
        if (mx < min) std::swap(mx, min);
        max = mx;
        return *this;
    }

    Handler& Handler::set_filter(const std::string& filt_name)
    {
        filter_name = filt_name;
        return *this;
    }

    Handler& Handler::set_filter(const Filter& filt)
    {
        filter_name = filt.get_name();
        return *this;
    }

    Handler& Handler::add_buffer(buffer_t buf)
    {
        lstream.add_buffer(buf);
        return *this;
    }

    Handler& Handler::add_file(const fs::path& path)
    {
        std::ofstream ofs(path);
        add_buffer(ofs.rdbuf());
        return *this;
    }

    Handler& Handler::add_buffers(ilist<buffer_t> bufs)
    {
        for (buffer_t buf : bufs)
        {
            add_buffer(buf);
        }
        return *this;
    }

    Handler& Handler::add_files(ilist<fs::path> paths)
    {
        for (fs::path path : paths)
        {
            add_file(path);
        }
        return *this;
    }
}
