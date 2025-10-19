cmake_minimum_required(VERSION 3.31)
include(ExportHelper)

file(GLOB LIB_SRC "*.cpp")

find_package(Threads REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS headers url)
find_package(OpenSSL REQUIRED SSL Crypto)

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE ${LIB_SRC})
install(TARGETS ${PROJECT_NAME})

target_link_libraries(
  ${PROJECT_NAME} PRIVATE
        Threads::Threads
        Boost::headers
        Boost::url
        OpenSSL::SSL
        OpenSSL::Crypto)

add_exported_target(${PROJECT_NAME} SUPPORTED_COMPONENTS)

