#include "handler.hpp"


namespace xlog
{
    Handler& get_handler(const std::string& name)
    {
        if (name == "")
        {
            return *(Handler::handlers["std"]);
        }
        if (Handler::handlers.count(name) == 0)
        {
            Handler new_hdlr = Handler(name);
        }
        return *(Handler::handlers[name]);
    }

    Handler::Handler(const std::string& _name, uchar minimum = 0)
        : name(_name), min(minimum)
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

    Handler& Handler::set_max(uchar mx)
    {
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
