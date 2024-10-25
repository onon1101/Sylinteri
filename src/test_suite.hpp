#ifndef TEST_SUITE_HPP
#define TEST_SUITE_HPP

#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "score.hpp"
#include "spdlog/spdlog.h"
#include "test.hpp"

using json = nlohmann::json;

class TestSuite {
private:
    std::string name;
    int test_count;
    std::vector<Test> tests;
    double time_in_second;
    double score = 0;
public:
    static std::vector<TestSuite> convert_json_array_to_testsuite_vector(json::array_t array, Score &score){
        std::vector<TestSuite> test_suites;

        for(auto element : array){
            
            std::string name = element.at("name").get<std::string>();
            int test_count = element.at("tests").get<int>();
            json::array_t test_array = element.at("testsuite").get<json::array_t>();
            std::string time_in_second = element.at("time").get<std::string>();

            spdlog::info("Load test suites by name {0} with {1} tests", name, test_count);

            std::vector<Test> tests = Test::convert_json_array_to_test_vector(test_array, score.get_score_by_testsuite_name(name)*1.0/test_count);

            test_suites.push_back(
                TestSuite(
                    name, 
                    test_count, 
                    tests,
                    std::stod(time_in_second.substr(0, time_in_second.length() - 1)),
                    Test::get_total_score_by_test_vector(tests)
                )
            );
        }

        return test_suites;
    }

    TestSuite(std::string name, int test_count, std::vector<Test> tests, double time_in_second, double score) : 
        name(name), 
        test_count(test_count), 
        tests(tests), 
        time_in_second(time_in_second),
        score(score)
    {

    }

    double get_score(){
        return this->score;
    }

    void print_header(){
        std::cout << GREEN << "[----------]" << RESET << " ";
        if(score != 0){
            std::cout << GREEN << "[ " << std::round(score * 100) / 100 << " pt ] " << RESET;
        }

        std::cout << test_count << " tests from " << name <<std::endl;
    }

    void print_result(){
        for(Test test : tests){
            test.print_result();
        }
    }
    
    void print_footer(){
        std::cout << GREEN << "[----------]" << RESET << " " << test_count << " tests from " << name << " (" << time_in_second << " s)" << std::endl << std::endl;
    }
};

#endif