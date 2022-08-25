#pragma once
#include <assert.h>
#include <iostream>
#include <mutex>
#include <stdexcept>

extern std::mutex log_lock;

#define DEBUG_LOG(x)                                                                                                   \
    {                                                                                                                  \
        std::lock_guard<std::mutex> lg{log_lock};                                                                      \
        std::cout << "[debug]"                                                                                         \
                  << "[" << __FILE__ << "]"                                                                            \
                  << "[" << __LINE__ << "]"                                                                            \
                  << "[" << __FUNCTION__ << "]:" << (x) << std::endl;                                                  \
    }
#define WARN_LOG(x)                                                                                                    \
    {                                                                                                                  \
        std::lock_guard<std::mutex> lg{log_lock};                                                                      \
        std::cout << "[warn]"                                                                                          \
                  << "[" << __FILE__ << "]"                                                                            \
                  << "[" << __LINE__ << "]"                                                                            \
                  << "[" << __FUNCTION__ << "]:" << (x) << std::endl;                                                  \
    }
#define ERROR_LOG(x)                                                                                                   \
    {                                                                                                                  \
        std::lock_guard<std::mutex> lg{log_lock};                                                                      \
        std::cout << "[error]"                                                                                         \
                  << "[" << __FILE__ << "]"                                                                            \
                  << "[" << __LINE__ << "]"                                                                            \
                  << "[" << __FUNCTION__ << "]:" << (x) << std::endl;                                                  \
    }
#define ERROR_LOG_AND_ASSERT(x)                                                                                        \
    {                                                                                                                  \
        ERROR_LOG(x);                                                                                                  \
        assert(false);                                                                                                 \
        throw std::runtime_error("runtime_error");                                                                     \
    }
#define ERROR_LOG_AND_ASSERT_IF_FALSE(x)                                                                               \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            ERROR_LOG_AND_ASSERT(#x);                                                                                  \
        }                                                                                                              \
    }
#define ERROR_LOG_AND_ASSERT_IF_TRUE(x)                                                                                \
    {                                                                                                                  \
        if ((x))                                                                                                       \
        {                                                                                                              \
            ERROR_LOG_AND_ASSERT(#x);                                                                                  \
        }                                                                                                              \
    }
