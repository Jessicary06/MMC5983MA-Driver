cmake_minimum_required(VERSION 3.19)

# Defining a variable for the source files for the MMC5983MA library
set(MMC5983MA_SOURCE MMC5983MA.cpp MMC5983MA.h)

# Creating a static library (means the library will be linked at compile time)
# Includes the source files in the MMC5983MA_SOURCE variable
add_library(MMC5983MA STATIC ${MMC5983MA_SOURCE})

# Specifying the include directory for the library
# Saying, include everything in the current directory
target_include_directories(MMC5983MA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the library with mbed-core-flags library
target_link_libraries(MMC5983MA mbed-core-flags)