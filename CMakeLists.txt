cmake_minimum_required(VERSION 3.5.0)
project(order_book VERSION 0.1.0 LANGUAGES C CXX)

add_executable(order_book src/order_book.h src/order_book.cpp src/main.cpp)
add_library(order SHARED src/order_book.h src/order_book.cpp)