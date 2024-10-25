#ifndef SCORE_H
#define SCORE_H

#include "nlohmann/json_fwd.hpp"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScoreItem {
private:
    std::string name;
    int score;
public:
    ScoreItem(std::string name, int score){
        this->name = name;
        this->score = score;
    }

    static std::vector<ScoreItem> convert_score_cnf_json_array_to_scoreitem_vector(json::array_t array){
        std::vector<ScoreItem> items;

        for(size_t i = 0; i < array.size(); i++){
            json object = array.at(i);
            std::string name = object.at("testsuite").get<std::string>();
            int score = object.at("score").get<int>();

            items.push_back(ScoreItem(name, score));
        }

        return items;
    }

    std::string get_name() const {
        return name;
    }

    double get_score() const {
        return score;
    }
    
    bool operator==(const ScoreItem &item) const {
        return this->name == item.name;
    }
};

class Score {
private:
    std::vector<ScoreItem> items;

public:
    Score() = default;

    Score(std::vector<ScoreItem> items){
        this->items = items;
    }
    double get_score_by_testsuite_name(std::string testsuite_name){
        for(ScoreItem item : items){
            if(item.get_name() == testsuite_name){
                return item.get_score();
            }
        }
        spdlog::error("Score of testsuite {0} not found.", testsuite_name);
        return 0;
    }

    void print_info(){
        spdlog::info("Score configuration: ");
        for(ScoreItem item : items){
            spdlog::info(" - {0} -> {1}", item.get_name(), item.get_score());
        }
    }
};

#endif