cmake_minimum_required(VERSION 3.22)

project(files)

list(APPEND CMAKE_PREFIX_PATH "/media/psf/Home/DOCs/cpp/tlpi/tlpi" "/Users/wangfiox/DOCs/cpp/tlpi/tlpi")
list(APPEND tlpi_DIR "/media/psf/Home/DOCs/cpp/tlpi/tlpi/config" "/Users/wangfiox/DOCs/cpp/tlpi/tlpi/config")

find_package(tlpi REQUIRED)

add_executable(t_stat stat.c)
target_link_libraries(t_stat PRIVATE tlpi)
target_include_directories(t_stat PRIVATE ${tlpi_INCLUDE_DIRS})
