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
    const Format& stdfmt = get_format("std");
    const Filter& stdfilt = get_filter("std");
    const Handler& stdhdlr = get_handler("std").add_buffer(std::cout.rdbuf()).set_filter("std").set_filter("stdfilt");
    const Logger& root = get_logger("root").add_handler("std");
}

#ifndef __FUNCTION_NAME__
#  ifdef __PRETTY_FUNCTION__
#    define __FUNCTION_NAME__ __PRETTY_FUNCTION__
#  else
#    ifdef __FUNCTION__
#      define __FUNCTION_NAME__ __FUNCTION__
#    endif
#  else
#    define __FUNCTION_NAME__ "unavailable"
#  endif
#endif

#ifndef RCD_INFO
#  ifndef X_LOG_NO_AUTO_INFO
#    define X_LOG_NO_AUTO_INFO
#    ifndef CPP20
#      define RCD_INFO __FILE__ , __LINE__, __FUNCTION_NAME__
#    else
#      define RCD_INFO std::source_location::current()
#    endif
#  endif
#endif

#ifndef X_LOG_NO_AUTO_LOG_MACRO
#  define X_LOG_NO_AUTO_LOG_MACRO
#  define LOG(msg, lvl, ...) logger.log(#msg, #lvl, { RCD_INFO, { #__VA_ARGS__ } });
#endif

#endif