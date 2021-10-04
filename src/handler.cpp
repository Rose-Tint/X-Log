#include "handler.hpp"


namespace xlog
{
    void Handler::init(uint lvl, PreFilter pref, Filter filt, PostFilter postf)
        : level(lvl), pre(pref), filter(filt), post(postf) { }

    Handler::Handler(uint lvl, PreFilter pref, Filter filt, PostFilter postf)
        : init(lvl, pref, filt, postf) { }

    Handler::Handler(uint lvl, ilist<buffer_t> buffers, PreFilter pref, Filter filt, PostFilter postf);
        : init(lvl, pref, filt, postf)
    {
        for (buffer_t buffer : buffers)
        {
            lstream.buffers.push_back(buffer);
        }
    }

    Handler::Handler(uint lvl, ilist<fs::path> paths, PreFilter pref, Filter filt, PostFilter postf);
        : init(lvl, pref, filt, postf)
    {
        for (fs::path path : paths)
        {
            lstream.buffers.push_back(std::fstream(path).rdbuf());
        }
    }

    void Handler::handle(const Record& rcd) const
    {
        prefilter(rcd);
        if (!filter(rcd))
        {
            return;
        }
        postfilter(rcd);

        lstream.write(rcd.msg);
    }
}
