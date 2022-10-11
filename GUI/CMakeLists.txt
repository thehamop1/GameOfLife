set(GUI_SRCS
    GUI.cpp
    MainWindow.cpp
)


add_executable(GUI ${GUI_SRCS})
target_link_libraries(GUI Qt5::Widgets GAME_OF_LIFE)