#ifndef TEST_HPP
#define TEST_HPP

#include "spdlog/spdlog.h"
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


enum TestResult {
    OK,
    FAILED
};

class Test {
private:
    std::string class_name;
    std::string name;
    TestResult result;
    double time_in_second;
    std::string error;

public:
    static std::vector<Test> convert_json_array_to_test_vector(json::array_t array){
        std::vector<Test> tests;

        for(auto element : array){
            std::string class_name = element.at("classname").get<std::string>();
            std::string name = element.at("name").get<std::string>();
            std::string time_str = element.at("time").get<std::string>();
            std::string error = element.contains("failures") ? element.at("failures").get<json::array_t>()[0].at("failure").get<std::string>() : "";

            spdlog::debug("Load test suites by name {0} with {1} time and error message {2}", name, time_str, error);

            double time_in_second = std::stod(time_str.substr(0, time_str.length() - 1));

            Test test(
                class_name,
                name, 
                error == "" ? TestResult::OK : TestResult::FAILED,
                time_in_second,
                error
            );

            tests.push_back(test);
        }

        return tests;
    }

    Test(std::string class_name, std::string name, TestResult result, double time_in_second, std::string error) : 
        class_name(class_name), 
        name(name), 
        result(result), 
        time_in_second(time_in_second), 
        error(error) 
    {

    }

    bool is_passed(){
        return result == TestResult::OK;
    }

    std::string get_test_name(){
        return class_name + "." + name;
    }

    void print_result(){
        std::cout << "[ RUN      ] " << get_test_name() << std::endl;
        
        if(!is_passed()){
            std::cout << error << std::endl;
            std::cout << "[  FAILED  ] "; 
        }else{
            std::cout << "[       OK ] ";
        }

        std::cout << get_test_name() << " (" << time_in_second << " s)" << std::endl;
    }
};

#endif