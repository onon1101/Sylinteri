#include <cmath>
#include <fstream>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <string>

#include "report.hpp"
#include "test_suite.hpp"
#include "score.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]){
    if(argc < 2){
        spdlog::error("Need report file. Exit.");
        return -1;
    }
    
    if(argc < 3){
        spdlog::error("Need score configuration file. Exit.");
        return -1;
    }

    std::string report_file = std::string(argv[1]);

    spdlog::info("Got Google report file. [{0}]", report_file);

    std::string score_configuration_file = std::string(argv[2]);

    spdlog::info("Got score configuration file. [{0}]", score_configuration_file);

    std::ifstream report_f(report_file, std::ios::in);

    if(!report_f.good()){
        spdlog::error("Failed to open report file. Exit.");
        return -1;
    }

    std::ifstream score_cnf_f(score_configuration_file, std::ios::in);

    if(!score_cnf_f.good()){
        spdlog::error("Failed to open score configuration file. Exit.");
        return -1;
    }

    Score score;

    try {
        json score_configuration_json = json::parse(score_cnf_f);
        json::array_t score_cnf_array = score_configuration_json.get<json::array_t>();

        score = Score(
            ScoreItem::convert_score_cnf_json_array_to_scoreitem_vector(score_cnf_array)
        );

        score.print_info();

    } catch (json::parse_error e){
        spdlog::error("Parse error on score configuration file. Exit.");
        spdlog::error("Error: {0}", e.what());
    }

    try {

        json report_json = json::parse(report_f);

        int tests = report_json.at("tests").get<int>();
        json::array_t test_suites_array = report_json["testsuites"].get<json::array_t>();
        std::string time_in_second = report_json["time"].get<std::string>();

        Report report(
            tests,
            TestSuite::convert_json_array_to_testsuite_vector(test_suites_array, score),
            std::stod(time_in_second.substr(0, time_in_second.length() - 1))
        );

        std::cout << std::endl;

        report.print_result();

        std::cout << std::endl;

        spdlog::info("Total score: {0}", std::round(report.get_total_score() * 100) / 100);

    } catch (json::parse_error e){
        spdlog::error("Parse error on report file. Exit.");
        spdlog::error("Error: {0}", e.what());
    }

}