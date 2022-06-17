/**
 * @brief 
 * @author      xiaowenxuan
 * @date        2022/6/17 17:26      
 * @copyright   Copyright （C）2022 xiaowenxuan All rights reserved. 
 *              email:18710760109@163.com
 */

#ifndef HYBRIDNETS_TENSORRT_UTIL_HPP
#define HYBRIDNETS_TENSORRT_UTIL_HPP

#include <iostream>
#include <string>
#include <memory>

template<typename... Args>
std::string string_format(const std::string &format, Args... args) {
    size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1;
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);
}

#endif //HYBRIDNETS_TENSORRT_UTIL_HPP
