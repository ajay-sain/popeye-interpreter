# This file is for adding external dependencies to the project
# Add external dependencies using FetchContent or find_package here

# Example of adding an external dependency:
#
# include(FetchContent)
# FetchContent_Declare(
#     some_library
#     GIT_REPOSITORY https://github.com/username/some_library.git
#     GIT_TAG v1.0.0
# )
# FetchContent_MakeAvailable(some_library)

# Or using find_package:
#
# find_package(SomeLibrary REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SomeLibrary::SomeLibrary)

add_subdirectory(spdlog)
add_subdirectory(magic_enum)

message(STATUS "External dependencies directory configured")
