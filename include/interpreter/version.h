#pragma once

#include <string>

namespace interpreter {

/**
 * @brief Get the project version as a string
 * @return Version string in the format "MAJOR.MINOR.PATCH"
 */
inline std::string get_version_string() {
    return std::to_string(PROJECT_VERSION_MAJOR) + "." +
           std::to_string(PROJECT_VERSION_MINOR) + "." +
           std::to_string(PROJECT_VERSION_PATCH);
}

} // namespace interpreter
