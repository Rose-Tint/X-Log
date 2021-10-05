#ifndef X_LOG_STL_INCLUDES
#define X_LOG_STL_INCLUDES

#include <version>
#include <string>
#include <exception>
#include <ctime>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <initializer_list>

// ensure either filesystem xor experimental filesystem is included
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

namespace xlog
{
    typedef (volatile std::streambuf)* buffer_t;
    typedef std::unordered_map<std::string, std::string> str_umap;
    typedef std::lock_gaurd<std::mutex> lock_gaurd_t;
    typedef std::unique_lock<std::mutex> ulock_t;
    typedef unsigned int uint;
    typedef unsigned char uchar;

    // if there is c++20 support, use jthread because jthread is safer
#if __cplusplus > 201703L
    typedef std::jthread thread_t;
#else
    typedef std::thread thread_t;
#endif

    template<typename T>
    using ilist = const std::initializer_list<T>&;


    class Logger;
    class Format;
    class Error;
    class Handler;
    class Record;
    class LogStream;
}

#endif