#include "GameBoard.hpp"
#include <iostream>

GameBoard::GameBoard(){
    // std::string playerInput
    // std::cin >> playerInput;
};

void GameBoard::Menu(){
    std::cout << "\t================MAIN MENU================\t" << std::endl;
    std::cout << "\t1. Add pieces" << std::endl;
    std::cout << "\t2. Clear pieces" << std::endl;
    std::cout << "\t3. Run Simulation for 10 Rounds" << std::endl;
    std::cin >> x;
};