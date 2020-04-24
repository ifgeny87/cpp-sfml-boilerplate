cmake_minimum_required(VERSION 3.5)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)")
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(SFML_FirstSteps VERSION 1.0.1)

message("  -- PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("  -- PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message("  -- CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

include_directories("${PROJECT_BINARY_DIR}")

# Define source and executable
set(EXECUTABLE_NAME "hellosfml")

set(SOURCES
		src/main.cpp)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Delete and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# Find any version 2.X of SFML
# See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
	include_directories(${SMFL_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Execute custom command after build
add_custom_command(
	TARGET ${EXECUTABLE_NAME}
	POST_BUILD
	COMMAND ln -fs ${PROJECT_SOURCE_DIR}/assets/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

# Setup properties
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
include(CPack)