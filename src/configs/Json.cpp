#include "configs/Json.hpp"



namespace xlog::cngf
{
    Json::Json(const fs::path& path)
        : ParserBase(path, ',')
    {
        char c = 0;
        while (get(c))
        {
            ;
        }
    }
}