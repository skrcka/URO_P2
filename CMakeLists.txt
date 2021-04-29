cmake_minimum_required(VERSION 3.8)
project(krcoo71_projekt_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

add_compile_options(-Wall -Wextra -pedantic)

# Use main.cpp to call and debug your code
add_executable(main main.cpp gui.cpp bills_widget.cpp orders_widget.cpp stock_widget.cpp login_widget.cpp gui.ui login_widget.ui orders_widget.ui stock_widget.ui bills_widget.ui)
target_link_libraries(main PRIVATE Qt6::Widgets)
