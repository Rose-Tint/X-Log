#ifndef X_LOG_FWD_DECLARES
#define X_LOG_FWD_DECLARES

#ifndef CPP_STD
#  if __cplusplus == 202002L
#    define CPP_STD 20
#    ifndef CPP20
#      define CPP20
#    endif
#  elif __cplusplus == 201703L
#    define CPP_STD 17
#    ifndef CPP17
#      define CPP17
#    endif
#  elif __cplusplus == 201402L
#    define CPP_STD 14
#    ifndef CPP14
#      define CPP14
#    endif
#  elif __cplusplus == 201103L
#    define CPP_STD 11
#    ifndef CPP11
#      define CPP11
#    endif
#  else
#    error "X-Log: Standard must be c++11 or later"
#endif


#if CPP_STD == 20
#  include <version>
#  ifndef LIKELY
#    define LIKELY [[likely]]
#  endif
#  ifndef UNLIKELY
#    define UNLIKELY [[unlikely]]
#  endif
#  if CPP_STD >= 17
#    ifndef FALLTHROUGH
#      define FALLTHROUGH [[fallthrough]]
#    endif
#  endif
#  if CPP_STD >= 14
#    ifndef DEPRECATED
#      define DEPRECATED [[deprecated]]
#    endif
#  endif
#endif

#ifndef LIKELY
#  define LIKELY
#endif
#ifndef UNLIKELY
#  define UNLIKELY
#endif
#ifndef FALLTHROUGH
#  define FALLTHROUGH
#endif
#ifndef DEPRECATED
#  define DEPRECATED
#endif

// exceptions
#include <exception>
#include <stdexcept>

// miscellaneous
#include <ctime>
#include <memory>
#include <cctype>
#include <type_traits>

// iostreaming
#include <iostream>
#include <fstream>

// containers
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <initializer_list>

// Multithreading
#include <thread>
#include <mutex>

#include "u8char_t.hpp"


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
#    error "Could not find system header \"<filesystem>\" or \"<experimental/filesystem>\""
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
#ifdef _WIN32
    typedef wchar_t os_char_t;
#else
    typedef char os_char_t;
#endif

    typedef std::basic_string<u8char_t> u8String;
    typedef std::string string_t;
    typedef std::basic_string<os_char_t> os_string_t;

    template<class T>
    using uptr_t = std::unique_ptr<T>;
    template<class T>
    using ilist = const std::initializer_list<T>&;
    template<class K, V>
    using umap = std::unordered_map<K, V>;
    template<class T>
    using str_umap = std::unordered_map<string_t, T>;
    template<class T>
    using lookup_map = std::unordered_map<string_t, uptr_t<T>>;
    template<class T>
    using uset = std::unordered_set<T>;


    typedef unsigned long long ullong;
    typedef unsigned long ulong;
    typedef unsigned int uint;
    typedef unsigned short ushort;
    typedef unsigned char uchar;

    typedef uset<string_t> str_uset_t;
    typedef str_umap<string_t> arg_map_t;
    typedef std::pair<string_t, string_t> str_pair_t;

    typedef std::basic_ostream<u8char_t> ostream_t;
    typedef std::basic_streambuf<u8char_t>* buffer_t;
    typedef std::basic_fstream<u8char_t> file_t;
    typedef std::basic_ifstream<u8char_t> ifile_t;
    typedef std::basic_ofstream<u8char_t> ofile_t;
    typedef std::basic_filebuf<u8char_t>* filebuf_t;

    typedef std::mutex mutex_t;
    typedef std::lock_guard<mutex_t> lock_gaurd_t;
    typedef std::unique_lock<mutex_t> ulock_t;


    enum struct Components : char
    {
        Json,
        Yaml,
        Object,
    };

    namespace dtl
    {
        constexpr const u8char_t* c_ansi_pref = "\033["_u8;
#ifdef CPP20
        constexpr string_t ansi_pref(c_ansi_pref);
#else
        const string_t ansi_pref(c_ansi_pref);
#endif
    }

    class Logger;
    class Record;
    class Filter;
    class Error;
    class Config;
    class Thread;
    class HandlerBase;
        class FileHandler;
    class Format;
        class DateTimeFormat;
        enum struct AnsiOption : char;
    class LogStreamBase;
        class LogFile;

    namespace cnfg
    {
        class ParserBase;
        class ConfigTypeBase;
        class TypeConfigItfBase;
        class LoggerConfigItf;
        class HandlerConfigItf;
        class FilterConfigItf;
        class FormatConfigItf;
        class Object;
        class Yaml;
        class Json;
    }


    extern Logger root;
    extern Handler stdhdlr;
    extern Format stdfmt;
    extern Filter stdfilt;


    Logger& get_logger();
    Logger& get_logger(const string_t&);

    Handler& get_handler();
    Handler& get_handler(const string_t&);

    Format& get_format();
    Format& get_format(const string_t&);

    Filter& get_filter();
    Filter& get_filter(const string_t&);


    typedef void (*pre_filter_f)(Record&);
    typedef bool (*filter_f)(const Record&);
    typedef void (*post_filter_f)(Record&);
}

#endif