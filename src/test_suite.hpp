#ifndef TEST_SUITE_HPP
#define TEST_SUITE_HPP

#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "spdlog/spdlog.h"
#include "test.hpp"

using json = nlohmann::json;

class TestSuite {
private:
    std::string name;
    int test_count;
    std::vector<Test> tests;
    double time_in_second;
public:
    static std::vector<TestSuite> convert_json_array_to_testsuite_vector(json::array_t array){
        std::vector<TestSuite> test_suites;

        for(auto element : array){
            
            std::string name = element.at("name").get<std::string>();
            int test_count = element.at("tests").get<int>();
            json::array_t test_array = element.at("testsuite").get<json::array_t>();
            std::string time_in_second = element.at("time").get<std::string>();

            spdlog::info("Load test suites by name {0} with {1} tests", name, test_count);

            test_suites.push_back(
                TestSuite(
                    name, 
                    test_count, 
                    Test::convert_json_array_to_test_vector(test_array),
                    std::stod(time_in_second.substr(0, time_in_second.length() - 1))
                )
            );
        }

        return test_suites;
    }

    TestSuite(std::string name, int test_count, std::vector<Test> tests, double time_in_second) : name(name), test_count(test_count), tests(tests), time_in_second(time_in_second) {

    }

    void print_header(){
        std::cout << "[----------]" << " " << test_count << " tests from " << name << std::endl;
    }

    void print_result(){
        for(Test test : tests){
            test.print_result();
        }
    }
    
    void print_footer(){
        std::cout << "[----------]" << " " << test_count << " tests from " << name << " (" << time_in_second << " s)" << std::endl << std::endl;
    }
};

#endif