cmake_minimum_required(VERSION 3.10)

project(NotificationsService)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

include_directories("jwt-cpp/include")
include_directories("libraries/libpqxx/include")
include_directories("/opt/homebrew/opt/openssl@3/include")
include_directories("/opt/homebrew/opt/libpqxx/include")

add_executable(NotificationsService main.cpp
        backend/multithread_notification_scheduler/Time_scheduler.cpp
        backend/email_sender/Email_sender.cpp
        backend/request_handler/RequestHandler.cpp
        backend/auxiliary_functions/AuxiliaryFunctions.cpp
        postgres/PostgresProcessing.cpp)

target_link_libraries(NotificationsService PRIVATE CURL::libcurl
        /opt/homebrew/opt/openssl@3/lib/libssl.dylib
        /opt/homebrew/opt/openssl@3/lib/libcrypto.dylib
        /opt/homebrew/opt/libpqxx/lib/libpqxx.dylib)