# Include FetchContent for managing dependencies
include(FetchContent)

# Add magic_enum
FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG v0.9.5  # Using a stable version
)
FetchContent_MakeAvailable(magic_enum)

message(STATUS "magic_enum configured")
