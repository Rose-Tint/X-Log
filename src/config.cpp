#include "config.hpp"

namespace xlog
{
    void config(const fs::path& path)
    {
        std::string ext = path.extension();
#ifdef X_LOG_CONFIGS_YAML_HPP
        if (ext == ".yaml" || ext == ".yml")
            cnfg::config_yaml(path);
#endif
    }
}
