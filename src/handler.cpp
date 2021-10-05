#include "handler.hpp"


namespace xlog
{
    Handler::Handler(uchar minimum)
        : min(minimum) {}

    void Handler::handle(const Record& rcd) const
    {
        if (!filter(rcd)) return;
        lstream.write(rcd.msg);
    }

    Handler& Handler::set_max(uchar mx)
    {
        max = mx;
        return *this;
    }

    Handler& Handler::set_filter(const Filter& filt)
    {
        filter = filt;
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
