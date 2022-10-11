#include "GameEngine.hpp"
#include <iostream>
#include <future>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <chrono>

void GameEngine::Menu() const
{
    std::cout << "\t================MAIN MENU================\t" << std::endl;
    std::cout << "\t0. End Game" << std::endl;
    std::cout << "\t1. Add pieces" << std::endl;
    std::cout << "\t2. Print pieces" << std::endl;
    std::cout << "\t3. Clear pieces" << std::endl;
    std::cout << "\t4. Run Simulation for 10 Rounds" << std::endl;
    std::cout << "\t5. Read in configuration file" << std::endl;
    std::cout << "\t6. Print the current state to life file" << std::endl;
};

void GameEngine::Input()
{
    int userInput;
    std::cin >> userInput;
    MenuInput input = static_cast<MenuInput>(userInput);

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
    for (size_t x = 0; x < 10; x++)
    {
        GetEpochPieces(m_SpotsToCheck);
        std::cout << m_SpotsToCheck->size() << std::endl;
        Epoch(m_SpotsToCheck);
    }
};

// Get surrounding values
//  (-1, 1), (0, 1), (1, 1)
//  (-1, 0), (0, 0), (1, 0)
//  (-1, -1), (0, -1), (1, -1)
void GameEngine::GetEpochPieces(std::shared_ptr<GameEngine::GameBoard> p) const
{
    p->clear();
    for (const auto &piece : m_pieces)
    {
        for (const auto &n : m_nieghbors)
        {
            p->insert({(piece.first + n.first), (piece.second + n.second)});
        }
        p->insert(piece);
    }
};

const size_t GameEngine::CheckNeighbors(const Piece &p) const
{
    size_t touching = 0;
    for (auto const &n : m_nieghbors)
    {
        touching += m_pieces.contains({(p.first + n.first), (p.second + n.second)});
    }
    return touching;//the game piece is always technically touching itself
};

void GameEngine::Epoch(std::shared_ptr<GameEngine::GameBoard> pieces)
{
    //We dont want to alter the game board as we go
    std::unordered_set<Piece, GameEngine::hashFunction> removeList, addList;

    for (const auto &p : *pieces)
    {
        const size_t touching = CheckNeighbors(p);
        if (m_pieces.contains(p))
        { // If piece is alive
            if (touching != 3 && touching != 2)
            {
                removeList.insert(p);
            }
        }
        else
        {
            if (touching == 3)
            {
                addList.insert(p);
            }
        }
    }
    for(const auto& r : removeList){
        m_pieces.erase(r);
    }
    for(const auto& a : addList){
        m_pieces.insert(a);
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
        m_pieces.insert({x, y});
    }
};

void GameEngine::PrintState()
{
    std::ofstream outputFile;
    auto now = std::chrono::system_clock::now();
    std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
    std::string path = "./GML_OUTPUT_" + std::to_string(int{ymd.year()}) + "_" + std::to_string(unsigned{ymd.month()}) + "_" + std::to_string(unsigned{ymd.day()}) + "_" + std::to_string(now.time_since_epoch().count()) + ".life";
    outputFile.open(path);
    if (!outputFile.is_open())
    {
        std::cerr << "Could not output game state!" << std::endl;
        return;
    }

    outputFile << "#Life 1.06\n";

    for (const auto &p : m_pieces)
        outputFile << p.first << "\t" << p.second << "\n";

    outputFile.close();
};