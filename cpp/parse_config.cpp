/*
 * @Author: Li RF
 * @Date: 2025-01-14 19:05:32
 * @LastEditors: Li RF
 * @LastEditTime: 2025-03-15 10:58:53
 * @Description: 
 * Email: 1125962926@qq.com
 * Copyright (c) 2025 Li RF, All Rights Reserved.
 */
#include <iostream>
#include <cstdlib>
#include <getopt.h>

#include "parse_config.hpp"


/**
 * @Description: 显示帮助信息
 * @param {char} *program_name: 程序名称
 * @return {*}
 */
void ConfigParser::print_help(const string &program_name) const { // 常量成员函数承诺不会修改调用它的对象的任何成员变量（函数内只有只读操作）
    cout << "Usage: " << program_name << " [options]" << endl;
    cout << "Options:" << endl;
    cout << "  -m, --model_path <string, require> || Set rknn model path. need to be set" << endl;
    cout << "  -i, --input <int or string, require> || Set input source. int: Camera index, like 0; String: video path. need to be set" << endl;
    cout << "  -a, --hwaccels <int> || Configure the hardware acceleration mode. 1:letterbox, 2:RGA. default: 2" << endl;
    cout << "  -t, --threads <string> || Set threads number. default: 1" << endl;
    cout << "  -c, --opencl <bool or int> || Configure the opencl mode. true(1):use opencl, fals(0):use cpu. default: True(1)" << endl;
    cout << "  -v, --verbose || Enable verbose output" << endl;
    cout << "  -h, --help || Show this help message" << endl;
}

/**
 * @Description: 打印配置信息
 * @param {AppConfig} config: 配置信息
 * @return {*}
 */
// 打印配置信息
void ConfigParser::printConfig(const AppConfig &config) const {
    cout << "​*************************" << endl;
    cout << "Parse Information:" << endl;
    cout << "    Model path: " << config.model_path << endl;
    cout << "    Input source: " << config.input << endl;
    cout << "    Hwaccels: " << config.hwaccels << endl;
    cout << "    Threads: " << config.threads << endl;
    cout << "    Opencl: " << boolalpha << config.opencl << endl; // boolalpha: 将 bool 类型以 true/false 形式输出
}

/**
 * @Description: 解析命令行参数
 * @param {int} argc: 命令行参数个数
 * @param {char} *argv: 命令行参数数组
 * @return {*}
 */
AppConfig ConfigParser::parse_arguments(int argc, char *argv[]) const {
    if (argc < 2) {
        this->print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    AppConfig config;


    /* 定义长选项 */ 
    struct option long_options[] = {
        {"model_path", required_argument, nullptr, 'm'},
        {"input",      required_argument, nullptr, 'i'},
        {"hwaccels",   required_argument, nullptr, 'a'},
        {"threads",    required_argument, nullptr, 't'},
        {"opencl",     required_argument, nullptr, 'c'},
        {"verbose",    no_argument,       nullptr, 'v'},
        {"help",       no_argument,       nullptr, 'h'},
        {nullptr,      0,                 nullptr, 0}
    };

    /* 解析参数 */ 
    int opt;
    // 支持短选项和长选项
    // : 表示该选项需要一个参数，v 和 h 不需要
    // 如果解析到长选项，返回 val 字段的值（即第四列）
    while ((opt = getopt_long(argc, argv, "m:i:a:t:c:vh", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'm':
                config.model_path = optarg;
                break;
            case 'i':
                config.input = optarg;
                break;
            case 'a':{
                try {
                    config.hwaccels = std::stoi(optarg);
                    if (config.hwaccels != LETTERBOX && config.hwaccels != RGA) 
                        throw std::invalid_argument("Unsupported hwaccel type.");
                } catch (const std::exception &e) {
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 't':
                config.threads = std::stoi(optarg);
                break;
            case 'c': {
                if (optarg == "true" || optarg == "1")
                    config.opencl = true;
                 else if (optarg == "false" || optarg == "0") 
                    config.opencl = false;
            }
            case 'v':
                config.verbose = true;
                break;
            case 'h':
                this->print_help(argv[0]);
                exit(EXIT_SUCCESS);
            default:
                this->print_help(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (config.verbose)
        this->printConfig(config);

    return config;
}

