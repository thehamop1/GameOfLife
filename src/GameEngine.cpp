#include "GameEngine.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

void GameEngine::Menu() const
{
    std::cout << "\t================MAIN MENU================\t" << std::endl;
    std::cout << "\t0. End Game" << std::endl;
    std::cout << "\t1. Add pieces" << std::endl;
    std::cout << "\t2. Print pieces" << std::endl;
    std::cout << "\t3. Clear pieces" << std::endl;
    std::cout << "\t4. Run Simulation for 10 Rounds" << std::endl;
    std::cout << "\t5. Read in configuration file" << std::endl;
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
        std::cout << "\tx: " << p.first << "\t" << "y: " << p.second << std::endl;

    std::cout << "\npress any button to continue" << std::endl;
    uint8_t x = 0;
    std::cin >> x;
}

void GameEngine::InputPiece()
{
    int64_t x = 0;
    int64_t y = 0;
    int state = 0;
    std::cout << "Input two integers delimted by a space" << std::endl;
    std::cout << "\tX Value: ";
    std::cin >> x;
    std::cout << "\tY Value: ";
    std::cin >> y;
    std::cout << "\tAlive (1) or False(0): ";
    std::cin >> state;
    m_pieces.insert({x, y});
};

void GameEngine::ClearPieces()
{
    m_pieces.clear();
};

void GameEngine::RunSim()
{
    for (int x = 0; x < 10; x++)
    {
        std::shared_ptr<GameEngine::GameBoard> epochChecks = GetEpochPieces();
        Epoch(epochChecks);
    }
};

std::shared_ptr<GameEngine::GameBoard> GameEngine::GetEpochPieces(){
    auto set = std::make_shared<GameEngine::GameBoard>();
    for (auto &piece : m_pieces)
    {
        for(auto& n : m_nieghbors){
            set->insert({(piece.first + n.first), (piece.second + n.second)});
        }
    }
    return set;
};

size_t GameEngine::CheckNeighbors(const Piece& p) const{
    size_t touching = 0;
    if (m_pieces.find({p.first - 1, p.second + 1}) != m_pieces.end())
        touching++;
    if (m_pieces.find({p.first, p.second + 1}) != m_pieces.end())
        touching++;
    if (m_pieces.find({p.first + 1, p.second + 1}) != m_pieces.end())
        touching++;
    if (m_pieces.find({p.first - 1, p.second}) != m_pieces.end())
        touching++;
    if (m_pieces.find({p.first + 1, p.second}) != m_pieces.end())
        touching++;
    if (m_pieces.find({p.first - 1, p.second - 1}) != m_pieces.end())
        touching++;
    if (m_pieces.find({p.first, p.second - 1}) != m_pieces.end())
        touching++;
    if (m_pieces.find({p.first + 1, p.second - 1}) != m_pieces.end())
        touching++;
    return touching;
};

// Get surrounding values
//  (-1, 1), (0, 1), (1, 1)
//  (-1, 0), (0, 0), (1, 0)
//  (-1, -1), (0, -1), (1, -1)
void GameEngine::Epoch(std::shared_ptr<GameBoard> pieces)
{
    std::unordered_set<Piece, GameEngine::hashFunction> addSet;
    std::unordered_set<Piece, GameEngine::hashFunction> removeSet;

    //check each point neighbor hit
    //add actions to data structure
    //after all computations update the board
    for(auto& p : *pieces){
        size_t touching = CheckNeighbors(p);
        if (touching < 2 || touching > 3){
            removeSet.insert(p);
        }else{
            addSet.insert(p);
        }
    }

    for(auto& r : removeSet){
        m_pieces.erase(r);
    }

    for(auto& a : addSet){
        m_pieces.erase(a);
    }

};

void GameEngine::ReadFiles()
{
    using namespace std::filesystem;
    std::vector<path> configFiles;
    int x = 0;
    std::cout << "Select a file" << std::endl;
    for (const directory_entry &dir_entry : recursive_directory_iterator("../../configs"))
    {
        std::cout << x++ << ". " << dir_entry.path().filename() << std::endl;
        configFiles.push_back(dir_entry);
    }
    std::cout << std::endl;

    size_t choice = 0;
    std::cin >> choice;
    if((choice<0) && (choice>configFiles.size())){
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
        if (!(iss >> x >> y)) { break; }
        m_pieces.insert({x, y});
    }
};