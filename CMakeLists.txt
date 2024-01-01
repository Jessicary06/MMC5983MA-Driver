cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

# Initialize Mbed OS build system. 
# Note: This block must be before the include of app.cmake
set(MBED_APP_JSON_PATH mbed_app.json)

# Sets up the Mbed-Tool chain file to make CMake expect the ARM compiler
# Loads compiler and flags
include(cmake/UploadMethodConfig.cmake)
include(mbed-os/tools/cmake/app.cmake)

# add_subdirectory(custom_targets)
add_subdirectory(mbed-os)

project(Mag-test)

# add subdirectories and build targets here
add_subdirectory(MMC5983MA)

add_executable(test_MMC5983MA test_MMC5983MA.cpp)
target_link_libraries(test_MMC5983MA MMC5983MA mbed-os)
mbed_set_post_build(test_MMC5983MA)


mbed_finalize_build()