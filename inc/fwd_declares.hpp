#ifndef X_LOG_STL_INCLUDES
#define X_LOG_STL_INCLUDES

#ifndef CPP_STD
#  if __cplusplus == 202002L
#    define CPP_STD 20
#  elif __cplusplus == 201703L
#    define CPP_STD 17
#  elif __cplusplus == 201402L
#    define CPP_STD 14
#  else
#    define CPP_STD 11
#  endif
#endif


#if CPP_STD == 20
#  include <version>
#  ifndef LIKELY
#    define LIKELY [[likely]]
#  endif
#  ifndef UNLIKELY
#    define UNLIKELY [[unlikely]]
#  endif
#  if CPP_STD > 17
#    ifndef FALLTHROUGH
#      define FALLTHROUGH [[fallthrough]]
#    endif
#  endif
#  if CPP_STD > 14
#    ifndef DEPRECATED
#      define DEPRECATED [[deprecated]]
#    endif
#  endif
   // if there is c++20 support, use jthread because jthread is safer
   namespace xlog { typedef std::jthread thread_t; }
#else
   namespace xlog { typedef std::thread thread_t; }
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
#include <unordered_multimap>
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
#ifdef _WIN32
    typedef wchar_t char_t;
#else
    typedef char char_t;
#endif
    typedef std::basic_string<char_t> string_t;

    template<class It>
    using iter_tag = typename std::iterator_traits<It>::iterator_category;
    template<class T>
    using uptr_t = std::unique_ptr<T>;
    template<class T>
    using ilist = const std::initializer_list<T&>&;
    template<class T>
    using str_umap = std::unordered_map<string_t, T>;
    template<class T>
    using lookup_map = std::unordered_map<string_t, uptr_t<T>>;
    template<class T>
    using lookup_multimap = std::unordered_multimap<string_t, uptr_t<T>>;


    typedef unsigned long long ullong;
    typedef unsigned long ulong;
    typedef unsigned int uint;
    typedef unsigned short ushort;
    typedef unsigned char uchar;

    typedef std::unordered_set<string_t> str_uset_t;
    typedef str_umap<string_t> arg_map_t;
    typedef std::pair<string_t, string_t> str_pair_t;

    typedef std::basic_ostream<char_t> ostream_t;
    typedef std::basic_streambuf<char_t>* buffer_t;
    typedef std::basic_fstream<char_t> file_t;
    typedef std::basic_ifstream<char_t> ifile_t;
    typedef std::basic_ofstream<char_t> ofile_t;
    typedef std::basic_filebuf<char_t>* filebuf_t;

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