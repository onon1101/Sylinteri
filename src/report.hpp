#ifndef REPORT_HPP
#define REPORT_HPP

#include <vector>

#include <iostream>
#include <nlohmann/json.hpp>

#include "test_suite.hpp"

using json = nlohmann::json;

class Report {
private:
    int tests;
    std::vector<TestSuite> test_suites;
    double time_in_second;
public:
    Report(int tests, std::vector<TestSuite> test_suites, double time_in_second) : tests(tests), test_suites(test_suites), time_in_second(time_in_second) {
        
    }

    void print_result(){
        std::cout << "[==========]" << " " << "Running " << tests << " tests from " << tests << " test suites" << std::endl;
        std::cout << "[----------]" << " " << "Global test environment set-up." << std::endl;
        for(TestSuite test_suite : test_suites){
            test_suite.print_header();
            test_suite.print_result();
            test_suite.print_footer();
        }
        std::cout << "[----------]" << " " << "Global test environment tear-down." << std::endl;
        std::cout << "[==========]" << " " << "Running " << tests << " tests from " << tests << " test suites" << " (" << time_in_second << " s total)" << std::endl;
    }
};

#endif