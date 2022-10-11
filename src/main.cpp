#include "GameEngine.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

enum class MenuInput{
    End=0,
    PrintPieces=1,
    ClearPieces=2,
    RunSim=3,
    ReadConfig=4,
    PrintState=5,
    DisplayState=6,
};//enum to manage menu

bool IsOver=false;//Is the game over

void Menu();//print menu
void InputPiece(GameEngine& e);//use cin to input a piece
void ReadFiles(GameEngine& e);//Read a bunch of files from config/

int main()
{
  GameEngine game;

  //trying to avoid a long switch statement
  const std::unordered_map<MenuInput, std::function<void()>> MenuOptions{
      {MenuInput::PrintPieces, [&](){game.PrintPieces();}},
      {MenuInput::ClearPieces, [&](){game.ClearPieces();}},
      {MenuInput::RunSim, [&](){game.RunSim();}},
      {MenuInput::End, [&](){IsOver = true;}},
      {MenuInput::ReadConfig, [&](){ReadFiles(game);}},
      {MenuInput::PrintState, [&](){game.PrintState();}},
      {MenuInput::DisplayState, [&](){game.PrintBoard();}}
  };

  while(!IsOver){
    Menu();//print Menu

    int userInput;
    std::cin >> userInput;
    MenuInput input = static_cast<MenuInput>(userInput);

    auto it = MenuOptions.find(input);
    if (it == MenuOptions.end())
    {
        std::cerr << "Menu Error: Try Again" << std::endl;
        continue;
    }

    it->second();
  }
}

void Menu()
{
    std::cout << "\t================MAIN MENU================\t" << std::endl;
    std::cout << "\t1. Print pieces" << std::endl;
    std::cout << "\t2. Clear pieces" << std::endl;
    std::cout << "\t3. Run Simulation for 10 Rounds" << std::endl;
    std::cout << "\t4. Read in configuration file" << std::endl;
    std::cout << "\t5. Print the current state to life file" << std::endl;
    std::cout << "\t6. Print the Game Board" << std::endl;
    std::cout << "\tAny other button to end game" << std::endl;
};

void ReadFiles(GameEngine& e)
{
    using namespace std::filesystem;
    std::vector<path> configFiles;
    int x = 0;
    std::cout << "\tSelect a file" << std::endl;
    for (const directory_entry &dir_entry : recursive_directory_iterator("../../configs"))
    {
        std::cout << "\t" << x++ << ". " << dir_entry.path().filename() << std::endl;
        configFiles.push_back(dir_entry);
    }
    std::cout << std::endl;

    size_t choice = 0;
    std::cin >> choice;
    if ((choice < 0) && (choice > configFiles.size()))
    {
        std::cerr << "Bad File Choice!" << std::endl;
        std::cin >> x;
        return;
    }

    std::string line;
    std::ifstream file;
    file.open(configFiles[choice]);
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int64_t x, y;
        if (!(iss >> x >> y))
        {
            break;
        }
        e.InputPiece({x, y});
    }
};
