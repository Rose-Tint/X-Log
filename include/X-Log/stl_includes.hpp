#ifndef X_LOG_STL_INCLUDES
#define X_LOG_STL_INCLUDES

#include <version>
#include <string>
#include <exception>
#include <utility>
#include <format>
#include <ctime>

#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <initializer_list>

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
namespace xlog { namespace fs = ::std::experimental::filesystem; }
#undef INC_STD_FS_EXP
#else
#include <filesystem>
namespace xlog { namespace fs = ::std::filesystem; }
#undef INC_STD_FS_EXP
#endif
#endif

namespace xlog
{
    typedef std::streambuf* buffer_t;

    template<typename T>
    using ilist = const std::initializer_list<T>&;
}

#endif