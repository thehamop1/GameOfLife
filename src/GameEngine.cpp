#include "GameEngine.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>


void GameEngine::PrintPieces()
{
    std::cout << "\tCurrent Game Pieces" << std::endl;
    std::cout << "\t==========================================" << std::endl;

    for (auto &p : m_pieces) std::cout << "\tx: " << p.first << "\t" << "y: " << p.second << std::endl;
}

void GameEngine::InputPiece(const Piece& p)
{
    m_pieces.insert(p);
};

void GameEngine::ClearPiece(const Piece& p)
{
    m_pieces.erase(p);
};

void GameEngine::ClearPieces()
{
    m_pieces.clear();
};

void GameEngine::PrintBoard(){
    for(int y=11;y>-11;y--){
        for(int x=-11;x<11;x++){
            if(m_pieces.contains({x, y})){
                std::cout << "x" << " ";
            }else{
                std::cout << "-" << " ";
            }
        }
        std::cout << std::endl;
    }
};

void GameEngine::RunSim()
{
    // for (size_t x = 0; x < 10000000; x++)//This is how i profiled
    for (size_t x = 0; x < 10; x++)
    {
        GetEpochPieces(m_SpotsToCheck);
        Epoch(m_SpotsToCheck);
    }
};

// Get surrounding values
//  (-1, 1), (0, 1), (1, 1)
//  (-1, 0), (0,0), (1, 0)
//  (-1, -1), (0, -1), (1, -1)
void GameEngine::GetEpochPieces(GameEngine::GameBoard& p) const
{
    p.clear();
    for (const auto &piece : m_pieces)
    {
        for (const auto &n : m_nieghbors)
        {
            p.insert({(piece.first + n.first), (piece.second + n.second)});
        }
        p.insert(piece);
    }
};

// Get surrounding values
//  (-1, 1), (0, 1), (1, 1)
//  (-1, 0), (NOT_ME), (1, 0)
//  (-1, -1), (0, -1), (1, -1)
const size_t GameEngine::CheckNeighbors(const Piece &p) const
{
    size_t touching = 0;
    for (auto const &n : m_nieghbors)
    {
        touching += m_pieces.contains({(p.first + n.first), (p.second + n.second)});
    }
    return touching;
};

void GameEngine::Epoch(GameEngine::GameBoard& pieces)
{
    //We dont want to alter the game board as we go
    std::unordered_set<Piece, GameEngine::hashFunction> removeList, addList;

    for (const auto &p : pieces)
    {
        const size_t touching = CheckNeighbors(p);
        if (m_pieces.contains(p))
        { // If piece is alive
            if (touching != 3 && touching != 2) removeList.insert(p);
        }
        else
        {
            if (touching == 3) addList.insert(p);
        }
    }

    for(const auto& r : removeList) m_pieces.erase(r);

    for(const auto& a : addList) m_pieces.insert(a);
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