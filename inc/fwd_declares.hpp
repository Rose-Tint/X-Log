#ifndef X_LOG_STL_INCLUDES
#define X_LOG_STL_INCLUDES


#if __cplusplus > 201703L
#include <version>
#  ifndef CPP20
#    define CPP20
#  endif
#  ifndef LIKELY
#    define LIKELY [[likely]]
#  endif
#  ifndef UNLIKELY
#    define UNLIKELY [[unlikely]]
#  endif
#  ifndef FALLTHROUGH
#    define FALLTHROUGH [[fallthrough]]
#  endif
   // if there is c++20 support, use jthread because jthread is safer
   namespace xlog { typedef std::jthread thread_t; }
#else
#  ifndef LIKELY
#    define LIKELY
#  endif
#  ifndef UNLIKELY
#    define UNLIKELY
#  endif
#  ifndef FALLTHROUGH
#    define FALLTHROUGH
#  endif
#  ifndef consteval
#    define consteval constexpr
#  endif
   namespace xlog { typedef std::thread thread_t; }
#endif

#include <exception>
#include <stdexcept>

#include <ctime>
#include <memory>
#include <cctype>
#include <type_traits>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <initializer_list>

#include <thread>
#include <mutex>


// ensure that filesystem xor experimental filesystem is included
#ifndef INC_STD_FS_EXP
#  ifdef __cpp_lib_filesystem
#    define INC_STD_FS_EXP 0
#  elif defined( __cpp_lib_experimental_filesystem )
#    define INC_STD_FS_EXP 1
#  elif !defined( __has_include )
#    define INC_STD_FS_EXP 1
#  elif __has_include(<filesystem>)
#    ifdef _MSC_VER
#      if __has_include(<yvals_core.h>)
#        include <yvals_core.h>
#        if defined(_HAS_CXX17) && _HAS_CXX17
#          define INC_STD_FS_EXP 0
#        endif
#      endif
#      ifndef INC_STD_FS_EXP
#        define INC_STD_FS_EXP 1
#      endif
#    else
#      define INC_STD_FS_EXP 0
#    endif
#  elif __has_include( <experimental/filesystem> )
#    define INC_STD_FS_EXP 1
#  else
#    error Could not find system header "<filesystem>" or "<experimental/filesystem>"
#  endif
#  if INC_STD_FS_EXP
#    include <experimental/filesystem>
     namespace xlog { namespace fs = std::experimental::filesystem; }
#  else
#    include <filesystem>
     namespace xlog { namespace fs = std::filesystem; }
#  endif
#endif


namespace xlog
{
    template<class T>
    using uptr_t = std::unique_ptr<T>;
    template<class T>
    using ilist = const std::initializer_list<T>&;
    template<class T>
    using str_umap = std::unordered_map<std::string, T>;
    template<class T>
    using lookup_map = std::unordered_map<std::string, uptr_t<T>>;


    typedef unsigned long long ullong;
    typedef unsigned long ulong;
    typedef unsigned int uint;
    typedef unsigned short ushort;
    typedef unsigned char uchar;
    typedef std::unordered_set<std::string> str_uset_t;
    typedef str_umap<std::string> arg_map_t;
    typedef std::pair<std::string, std::string> str_pair_t;
    typedef std::streambuf* buffer_t;
    typedef std::filebuf* fbuffer_t;
    typedef std::mutex mutex_t;
    typedef std::lock_guard<mutex_t> lock_gaurd_t;
    typedef std::unique_lock<mutex_t> ulock_t;


    class Logger;
    class Handler;
    class Format;
    class Filter;
    class Error;
    class LogStream;
    class Record;
    namespace config
    {
        class Object;
    }


    extern Logger& root;
    extern Handler& stdhdlr;
    extern Format& stdfmt;
    extern Filter& stdfilt;


    Logger& get_logger();
    Logger& get_logger(const std::string&);
    const Logger& find_logger();
    const Logger& find_logger(const std::string&);

    Handler& get_handler();
    Handler& get_handler(const std::string&);
    const Handler& find_handler();
    const Handler& find_handler(const std::string&);

    Format& get_format();
    Format& get_format(const std::string&);
    const Format& find_format();
    const Format& find_format(const std::string&);

    Filter& get_filter();
    Filter& get_filter(const std::string&);
    const Filter& find_filter();
    const Filter& find_filter(const std::string&);


    typedef void (*pre_filter_f)(Record&);
    typedef bool (*filter_f)(const Record&);
    typedef void (*post_filter_f)(Record&);
}

#endif