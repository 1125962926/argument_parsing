/*
 * @Author: Li RF
 * @Date: 2025-01-14 19:05:32
 * @LastEditors: Li RF
 * @LastEditTime: 2025-03-14 11:45:37
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2025 Li RF, All Rights Reserved.
 */
#ifndef _PARSE_CONFIG_HPP_
#define _PARSE_CONFIG_HPP_

#include <iostream>
#include <string>
using namespace std;

enum hwaccels {
    LETTERBOX = 1,
    RGA = 2,
};

/* 定义命令行参数结构体 */ 
struct AppConfig {
    std::string model_path = "";  // rknn 模型路径
    std::string input = "";       // 输入源
    int hwaccels = RGA;           // 硬件加速，默认为 RGA
    int threads = 1;              // 线程数，默认为1
    bool opencl = true;           // 是否使用opencl
    bool verbose = false;         // 是否打印命令行参数
};

/* 定义配置解析类 */
class ConfigParser {
    public:
        // 显示帮助信息
        void print_help(const string &program_name) const;
        // 打印配置信息
        void printConfig(const AppConfig &config) const;
        // 解析命令行参数
        AppConfig parse_arguments(int argc, char *argv[]) const;

    private:
        // 私有成员（如果有需要可以添加）
    };

#endif
