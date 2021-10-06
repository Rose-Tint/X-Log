#ifndef X_LOG_STL_INCLUDES
#define X_LOG_STL_INCLUDES


#if __cplusplus > 201703L
#include <version>
#endif

#include <exception>
#include <ctime>

#include <iostream>
#include <fstream>
#include <boost/json.hpp>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <initializer_list>

#include <thread>
#include <mutex>


// ensure that filesystem xor experimental filesystem is included
#ifndef INC_STD_FS_EXP
#ifdef __cpp_lib_filesystem
#define INC_STD_FS_EXP 0
#elif defined( __cpp_lib_experimental_filesystem )
#define INC_STD_FS_EXP 1
#elif !defined( __has_include )
#define INC_STD_FS_EXP 1
#elif __has_include(<filesystem>)
#ifdef _MSC_VER
#if __has_include(<yvals_core.h>)
#include <yvals_core.h>
#if defined(_HAS_CXX17) && _HAS_CXX17
#define INC_STD_FS_EXP 0
#endif
#endif
#ifndef INC_STD_FS_EXP
#define INC_STD_FS_EXP 1
#endif
#else
#define INC_STD_FS_EXP 0
#endif
#elif __has_include( <experimental/filesystem> )
#define INC_STD_FS_EXP 1
#else
#error Could not find system header "<filesystem>" or "<experimental/filesystem>"
#endif
#if INC_STD_FS_EXP
#include <experimental/filesystem>
namespace xlog::fs = std::experimental::filesystem;
#undef INC_STD_FS_EXP
#else
#include <filesystem>
namespace xlog::fs = std::filesystem;
#undef INC_STD_FS_EXP
#endif
#endif


#if __cplusplus > 201703L

#ifndef LIKELY
#define LIKELY [[likely]]
#endif
#ifndef UNLIKELY
#define UNLIKELY [[unlikely]]
#endif

#else

#ifndef LIKELY
#define LIKELY
#endif
#ifndef UNLIKELY
#define UNLIKELY
#endif
#ifndef consteval
#define consteval constexpr
#endif

#endif


namespace xlog
{
    typedef std::unordered_set<std::string> str_uset_t;
    typedef std::streambuf* buffer_t;
    typedef std::filebuf* fbuffer_t;
    typedef unsigned int uint;
    typedef unsigned char uchar;

// if there is c++20 support, use jthread because jthread is safer
#if __cplusplus > 201703L
    typedef std::jthread thread_t;
#else
    typedef std::thread thread_t;
#endif
    typedef std::mutex mutex_t;
    typedef std::lock_gaurd<mutex_t> lock_gaurd_t;
    typedef std::unique_lock<mutex_t> ulock_t;

    template<typename T>
    using ilist = const std::initializer_list<T>&;
    template<typename T>
    using str_umap = std::unordered_map<std::string, T>;
    template<typename T>
    using lookup_map = std::unordered_map<std::string, T*>


    class Logger;
    class Format;
    class Error;
    class Handler;
    class LogStream;
    class Record;
}

#endif