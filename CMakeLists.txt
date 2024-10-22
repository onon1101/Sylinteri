cmake_minimum_required(VERSION 3.20)
project(SYLINTERI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -g")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -Og")

include(FetchContent)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)
set (JSON_LIBRARIES "${CMAKE_BINARY_DIR}/_deps/json-src/include")

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.14.1 # or the version you want to use
)
FetchContent_MakeAvailable(spdlog)
set (SPDLOG_LIBRARIES "${CMAKE_BINARY_DIR}/_deps/spdlog-src/include")

set(SRC
    src/main.cpp
)


add_executable(SYLINTERI "${SRC}")
target_include_directories(SYLINTERI PRIVATE ${JSON_LIBRARIES})
target_include_directories(SYLINTERI PRIVATE ${SPDLOG_LIBRARIES})
