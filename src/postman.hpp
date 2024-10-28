#ifndef POSTMAN_H
#define POSTMAN_H

#include <cstdint>
#include <cstdlib>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

void post_result(std::string student_id, std::string homework_name, std::string semester, uint64_t submitted_at, double grade){
    CURL *curl;
    CURLcode res;

    json payload;
    payload["student_id"] = student_id;
    payload["homework_name"] = homework_name;
    payload["semester"] = semester;
    payload["submitted_at"] = submitted_at;
    payload["grade"] = grade;

    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "http://140.124.181.133:7000/api/submit");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + std::string(getenv("SECRET_KEY"))).c_str());

        std::string payload_str = payload.dump();

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)payload_str.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

#endif
