# Add Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(${PROJECT_NAME}_tests
    test_main.cpp
    # Add test source files here
)

# Link with gtest and the main library
target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
        gtest_main
        ${PROJECT_NAME}
)

# Include directories
target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Enable testing
#disable_testing()  # Disable automatic test discovery
#add_test(NAME ${PROJECT_NAME}_tests
#    COMMAND $<TARGET_FILE:${PROJECT_NAME}_tests>
#)
