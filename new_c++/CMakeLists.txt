option(BUILD_DOC "Build documentation" ON)
option(LIFT_DOCS "Lift docs to folder build_docs" ON)
option(TESTING "Enable testing" ON)

project(${CMAKE_PROJECT_NAME} VERSION "0.0.1")
message("${CMAKE_PROJECT_NAME} VERSION: ${CMAKE_PROJECT_VERSION}")

message("PROJECT_DESCRIPTION: ${CMAKE_PROJECT_DESCRIPTION}")

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include(cmake/Postsets.cmake)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake")

IF (BUILD_DOC)
    include(cmake/Doxygen.cmake)
    enable_doxygen()
ENDIF (BUILD_DOC)

set(SRC
	"${CMAKE_PROJECT_NAME}/src/main.cpp"
)

set(HEADERS
	"${CMAKE_PROJECT_NAME}/include/example.h"
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC} ${HEADERS})

#IF (${CMAKE_TESTING})
	#add_subdirectory (tests)
#ENDIF (${CMAKE_TESTING})

IF (TESTING)
	add_executable("tests" "tests/tests.cpp" ${HEADERS})
ENDIF (TESTING)

