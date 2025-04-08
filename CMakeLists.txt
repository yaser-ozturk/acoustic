cmake_minimum_required(VERSION 3.30)
project(AcusticModem)

set(CMAKE_CXX_STANDARD 20)

add_executable(AcusticModem
        main.cpp
        serialport/SimpleSerial.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/modem_driver/
        ${CMAKE_CURRENT_LIST_DIR}/serialport/

)