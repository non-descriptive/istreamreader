cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

set(PROJ_MAIN istreamreader)

project(${PROJ_MAIN}
    LANGUAGES CXX)

include_directories(include)

set(HEADERS
    include/IReadStream.hpp
    include/FileReadStream.hpp
    include/Exceptions.hpp
)

set(SOURCE
    main.cpp
    src/IReadStream.cpp
    src/FileReadStream.cpp
)


add_executable(${PROJ_MAIN} ${SOURCE} ${HEADERS})

#tests target
set(PROJ_TESTS StreamReaderTests)

add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    SET(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    SET(GOOGLETEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sub/googletest")
    message(STATUS "${GOOGLETEST_DIR}")
endif ()

if (EXISTS ${GOOGLETEST_DIR})
    SET(GTestSrc ${GOOGLETEST_DIR}/googletest)
    SET(GMockSrc ${GOOGLETEST_DIR}/googlemock)
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()


include_directories(${GTestSrc}
    ${GTestSrc}/include
    ${GMockSrc}
    ${GMockSrc}/include)

set(TEST_CLASSES
    src/FileReadStream.cpp)

set(SOURCE_TESTS
    tests/main.cpp
    ${TEST_CLASSES}
    tests/tst_streamreadertest.h
)

add_executable(${PROJ_TESTS}
    ${SOURCE_TESTS}
    ${GTestSrc}/src/gtest-all.cc
    ${GMockSrc}/src/gmock-all.cc)
add_test(${PROJ_TESTS} COMMAND ${PROJ_TESTS})
target_link_libraries(${PROJ_TESTS} PRIVATE Threads::Threads)
