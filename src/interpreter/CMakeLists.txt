# Add the main executable
add_executable(${PROJECT_NAME}
        ../main.cpp
        Interpreter.cpp
        parser.cpp
        lexer.cpp
)

# Set include directories for this target
target_include_directories(${PROJECT_NAME} PRIVATE
        ../../include
)

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Link with spdlog
target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog::spdlog
    magic_enum::magic_enum
)

# Install the executable
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
