set(GAME_OF_LIFE_SRCS
    GameBoard.cpp
)

set(MAIN_SRCS
    main.cpp
)

add_library(GAME_OF_LIFE ${GAME_OF_LIFE_SRCS})

add_executable(MAIN ${MAIN_SRCS})
target_link_libraries(MAIN GAME_OF_LIFE)