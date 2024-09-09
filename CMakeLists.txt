cmake_minimum_required(VERSION 3.27)

project(NotificationsService)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(NotificationsService main.cpp
        backend/multithread_notification_scheduler/Time_scheduler.cpp
        backend/email_sender/Email_sender.cpp
        backend/request_handler/RequestHandler.cpp
        backend/auxiliary_functions/AuxiliaryFunctions.cpp)

target_link_libraries(NotificationsService CURL::libcurl)