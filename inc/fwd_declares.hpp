throw err::InvalidArgName(curr_var);#ifndef X_LOG_FWD_DECLARES
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
#    error "Standard must be c++11 or later"
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
#include <locale>

// iostreaming
#include <iostream>
#include <fstream>

// containers
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <initializer_list>

// Multithreading
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
#ifdef _WIN32
    typedef wchar_t char_t;
#else
    typedef char char_t;
#endif
    typedef std::basic_string<char_t> string_t;

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

    typedef std::unordered_set<string_t> str_uset_t;
    typedef str_umap<string_t> arg_map_t;
    typedef std::pair<string_t, string_t> str_pair_t;

    // use char instead of char_t because encoding will have to be utf-8
    typedef std::basic_ostream<char> ostream_t;
    typedef std::basic_streambuf<char>* buffer_t;
    typedef std::basic_fstream<char> file_t;
    typedef std::basic_ifstream<char> ifile_t;
    typedef std::basic_ofstream<char> ofile_t;
    typedef std::basic_filebuf<char>* filebuf_t;

    typedef std::mutex mutex_t;
    typedef std::lock_guard<mutex_t> lock_gaurd_t;
    typedef std::unique_lock<mutex_t> ulock_t;


    namespace components
    {
        namespace config
        {
            static constexpr bool json;
            static constexpr bool yaml;
            static constexpr bool object;
        };
    }


    class Logger;
    class HandlerBase;
      class HandlerWatcher;
      class FileHandler;
    class Record;;
    class Format;
      class CharOutputIter;
      class DateTimeFormat;
      typedef string_t (*var_fmt_f)(const Record&);
    class Filter;
    class Error;
    class LogStreamBase;
      class LogStreamIter;
    class Thread;

    namespace cnfg
    {
        class ParserBase;
        class ConfigTypeBase;
        class TypeConfigItfBase;
        class LoggerConfigItf;
        class HandlerConfigItf;
        class FilterConfigItf;
        class FormatConfigItf;
        class Yaml;
        class Json;

        void config_yaml(const fs::path&);
        void config_json(const fs::path&);
    }
    void config(const fs::path&);
    DEPRECATED void config(const ConfigTypeBase&);


    extern Logger& root;
    extern Handler& stdhdlr;
    extern Format& stdfmt;
    extern Filter& stdfilt;


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