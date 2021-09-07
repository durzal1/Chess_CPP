cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 14)


include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES main.cpp board.h board.cpp getPossibleMoves.h getPossibleMoves.cpp types.h ai.h ai.cpp piece.h piece.cpp random.h evaluate.h evaluate.cpp uci.cpp uci.h TranspositionTable.cpp TranspositionTable.h)
add_executable(Chess ${SOURCE_FILES})
target_link_libraries(Chess mingw32)
