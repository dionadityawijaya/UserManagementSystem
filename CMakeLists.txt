cmake_minimum_required(VERSION 3.00)
project(UserManagementSystem)

set(CMAKE_CXX_STANDARD 14)  # Jika C++17 tidak berfungsi, coba gunakan C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/LENOVO/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_definitions(-D_WIN32_WINNT=0x0A00)


add_executable(run
    main.cpp
    src/auth.cpp
    src/user.cpp
)