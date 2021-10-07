#ifndef X_LOG_HPP
#define X_LOG_HPP

#include "fwd_declares.hpp"
#include "errors.hpp"
#include "format.hpp"
#include "handler.hpp"
#include "logger.hpp"
#include "logstream.hpp"
#include "record.hpp"

namespace xlog
{
    Filter stdfilt = Filter("std");
    Handler stdhdlr = std::move(Handler("std").add_buffer(std::cout.rdbuf()).set_filter("std"));
    Logger root = std::move(Logger("root").add_handler("std"));
}

#ifndef X_LOG_NO_AUTO_INFO
#define X_LOG_NO_AUTO_INFO
#define RCD_INFO __FILE__ , __LINE__
#endif

#ifndef X_LOG_NO_AUTO_LOG_MACRO
#define X_LOG_NO_AUTO_LOG_MACRO
#define LOG(msg, lvl, ...) logger.log(#msg, #lvl, { RCD_INFO, { #__VA_ARGS__ } });
#endif

#ifdef X_LOG_AUTO_THROW_LOG
#ifndef CX_LOG_THROW_MSG
#define CX_LOG_THROW_MSG "Error thrown"
#endif
#define throw xlog::Logger::log_all( CX_LOG_THROW_MSG, 100, { RCD_INFO }); throw up
#endif

#endif