#ifndef X_LOG_HPP
#define X_LOG_HPP

#include "X-Log/logger.hpp"

#ifndef X_LOG_NO_PREDEF_LOGGER
#include <iostream>
#include <string>
xlog::Logger main_lgr = xlog::Logger(std::string("main"), std::cout.rdbuf());
#endif

#ifndef X_LOG_NO_AUTO_LOG_MACRO
#define X_LOG_NO_AUTO_LOG_MACRO
#define LOG(msg, lvl) logger.log({lvl, #msg});
#endif

#ifndef X_LOG_NO_AUTO_INFO
#define X_LOG_NO_AUTO_INFO
#define __INFO__ xlog::FormatInfo { __FILE__, __LINE__ }
#endif

#ifdef X_LOG_AUTO_THROW_LOG
#ifndef CX_LOG_THROW_MSG
#define CX_LOG_THROW_MSG "Error thrown at ${file}, ${line}"
#endif
#define throw xlog::Logger::log_all({ CX_LOG_THROW_MSG, xlog::ERROR }, __INFO__); throw 
#endif

#endif