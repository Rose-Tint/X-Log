#ifndef X_LOG_NO_AUTO_LOG_MACRO
#define X_LOG_NO_AUTO_LOG_MACRO
#endif

#include "X-Log.hpp"
#include "configs/Json.hpp"


using xlog::root, xlog::get_logger;


xlog::Config("config.json");
auto exlgr = get_logger("example logger");

int main()
{
    exlgr.log("First Log! Hello, World!", 4, {RCD_INFO});
    root.log("This should print to the console.", 0, {RCD_INFO});
    exlgr.log("This should not print at all", 0, {RCD_INFO})
}
