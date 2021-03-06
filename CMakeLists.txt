cmake_minimum_required(VERSION 3.1)
project(ai4_engines)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(PERFT_SRCS ../src/Board.hpp ../src/perft.cpp)
add_executable(perft ${PERFT_SRCS})

set(RANDOM_SRCS ../src/Board.hpp ../src/UCIEngine.hpp ../src/random_engine.cpp)
add_executable(random_engine ${RANDOM_SRCS})
target_link_libraries(random_engine PRIVATE Threads::Threads)

set(ABP_SRCS ../src/Board.hpp ../src/UCIEngine.hpp ../src/abp_engine.cpp)
add_executable(abp_engine ${ABP_SRCS})
target_link_libraries(abp_engine PRIVATE Threads::Threads)

set(ABPQ_SRCS ../src/Board.hpp ../src/UCIEngine.hpp ../src/abpq_engine.cpp)
add_executable(abpq_engine ${ABPQ_SRCS})
target_link_libraries(abpq_engine PRIVATE Threads::Threads)

set(ABP_V2_SRCS ../src/Board.hpp ../src/UCIEngine.hpp ../src/abp_v2_engine.cpp)
add_executable(abp_v2_engine ${ABP_V2_SRCS})
target_link_libraries(abp_v2_engine PRIVATE Threads::Threads)

set(MINIMAX_SRCS ../src/Board.hpp ../src/UCIEngine.hpp ../src/minimax_engine.cpp)
add_executable(minimax_engine ${MINIMAX_SRCS})
target_link_libraries(minimax_engine PRIVATE Threads::Threads)

set(MCTS_SRCS ../src/Board.hpp ../src/UCIEngine.hpp ../src/mcts_engine.cpp)
add_executable(mcts_engine ${MCTS_SRCS})
target_link_libraries(mcts_engine PRIVATE Threads::Threads)

#set(SCORE_PRUNING_SRCS ../src/Board.hpp ../src/UCIEngine.hpp ../src/score_pruning_engine.cpp)
#add_executable(score_pruning_engine ${SCORE_PRUNING_SRCS})
#target_link_libraries(score_pruning_engine PRIVATE Threads::Threads)

#set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Wshadow -pedantic -g -Og -lpthread")
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Wshadow -pedantic -g -O3 -lpthread")
