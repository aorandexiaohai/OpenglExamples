#pragma once
#include <iostream>
#include <mutex>

extern std::mutex log_lock;

#define DEBUG_LOG(x) {std::lock_guard<std::mutex> lg{log_lock}; std::cout<<"[debug]"<<"["<<__FILE__<<"]"<<"["<<__LINE__<<"]"<<"["<<__FUNCTION__<<"]:"<<(x)<<std::endl;}
#define WARN_LOG(x) {std::lock_guard<std::mutex> lg{log_lock}; std::cout<<"[warn]"<<"["<<__FILE__<<"]"<<"["<<__LINE__<<"]"<<"["<<__FUNCTION__<<"]:"<<(x)<<std::endl;}
#define ERROR_LOG(x) {std::lock_guard<std::mutex> lg{log_lock}; std::cout<<"[error]"<<"["<<__FILE__<<"]"<<"["<<__LINE__<<"]"<<"["<<__FUNCTION__<<"]:"<<(x)<<std::endl;}
