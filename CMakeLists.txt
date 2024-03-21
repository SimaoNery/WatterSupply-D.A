cmake_minimum_required(VERSION 3.22)
project(DA_water_supply)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(DA_water_supply src/main.cpp
        src/utils/Dataset.cpp
        src/utils/Dataset.h
        src/models/VertexEdge.cpp
        src/models/VertexEdge.h
        src/models/Graph.cpp
        src/models/Graph.h
        src/managers/FlowManager.cpp
        src/views/Menu.h
        src/views/MainMenu.cpp
        src/views/MainMenu.h
        src/views/ReliabilityMenu.cpp
        src/views/ReliabilityMenu.h
        src/views/MetricsMenu.cpp
        src/views/MetricsMenu.h
        src/managers/ReliabilityManager.cpp
        src/managers/ReliabilityManager.h
)

# Doxygen Build
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if (NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif ()

    set(DOXYGEN_IN "docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif (DOXYGEN_FOUND)
