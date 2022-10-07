#include "GameEngine.hpp"
#include <iostream>

void GameEngine::Menu() const
{
    std::cout << "\t================MAIN MENU================\t" << std::endl;
    std::cout << "\t0. End Game" << std::endl;
    std::cout << "\t1. Add pieces" << std::endl;
    std::cout << "\t2. Print pieces" << std::endl;
    std::cout << "\t3. Clear pieces" << std::endl;
    std::cout << "\t4. Run Simulation for 10 Rounds" << std::endl;
};

void GameEngine::Input()
{
    MenuInput input = [&] -> MenuInput
    {
        int userInput;
        std::cin >> userInput;
        return static_cast<MenuInput>(userInput);
    }();

    auto it = m_menuOptions.find(input);
    if (it == m_menuOptions.end())
    {
        std::cerr << "BAD MENU OPTION" << std::endl;
        std::cerr << "Try Again" << std::endl;
        return;
    }

    it->second();
    std::system("clear");
};

void GameEngine::PrintPieces()
{
    std::system("clear");
    std::cout << "\tCurrent Game Pieces" << std::endl;
    std::cout << "\t==========================================" << std::endl;

    for (auto &p : m_pieces)
        std::cout << "\tx: " << p.first << "\t"
                  << "y: " << p.second << std::endl;

    std::cout << "\npress any button to continue" << std::endl;
    uint8_t x = 0;
    std::cin >> x;
}

void GameEngine::InputPiece()
{
    int64_t x = 0;
    int64_t y = 0;
    std::cout << "Input two integers delimted by a space" << std::endl;
    std::cout << "X Value: ";
    std::cin >> x;
    std::cout << "Y Value: ";
    std::cin >> y;
    m_pieces.insert({x, y});
};

void GameEngine::ClearPieces(){
    m_pieces.clear();
};