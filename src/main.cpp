#include <fstream>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <string>

#include "report.hpp"
#include "test_suite.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]){
    if(argc < 2){
        spdlog::error("Need report file. Exit.");
        return -1;
    }
    
    std::string report_file = std::string(argv[1]);

    spdlog::info("Got Google report file. [{0}]", report_file);

    std::ifstream f(report_file, std::ios::in);

    if(!f.good()){
        spdlog::error("Failed to open file. Exit.");
        return -1;
    }

    try {

        json report_json = json::parse(f);

        int tests = report_json.at("tests").get<int>();
        json::array_t test_suites_array = report_json["testsuites"].get<json::array_t>();
        std::string time_in_second = report_json["time"].get<std::string>();

        Report report(
            tests,
            TestSuite::convert_json_array_to_testsuite_vector(test_suites_array),
            std::stod(time_in_second.substr(0, time_in_second.length() - 1))
        );

        report.print_result();

    } catch (json::parse_error e){
        spdlog::error("Parse error on json file. Exit.");
        spdlog::error("Error: {0}", e.what());
    }


}