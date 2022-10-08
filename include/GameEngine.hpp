#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <utility>
#include <functional>
#include <cstddef>
#include <memory>
#include <iostream>

class GameEngine
{
public:
    void Menu() const;
    void Input();
    inline bool IsOver()const{ return m_end; };

private:
    enum class MenuInput{
        End = 0,
        InputPiece = 1,
        PrintPieces = 2,
        ClearPieces = 3,
        RunSim = 4,
        ReadConfig = 5,
    };
    // Hash function 
    struct hashFunction
    {
        size_t operator()(const std::pair<int64_t, int64_t> &x) const
        {
            return x.first ^ x.second;
        }
    };
    using Piece = std::pair<int64_t, int64_t>;
    using GameBoard = std::unordered_set<Piece, hashFunction>;

    size_t CheckNeighbors(const Piece& p)const;
    void ReadFiles();
    void Epoch(std::shared_ptr<GameBoard> pieces);
    void InputPiece();
    void PrintPieces();
    void ClearPieces();
    void RunSim();
    std::shared_ptr<GameBoard> GetEpochPieces();
    int m_userInput;
    bool m_end = false;
    GameBoard m_pieces;

    constexpr static std::array<std::pair<int64_t, int64_t>, 9> m_nieghbors = {{
        {-1, 1},
        {0, 1},
        {1, 1},
        {-1, 0},
        {0, 0},
        {1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    }};

    std::unordered_map<MenuInput, std::function<void()>> m_menuOptions{
        {MenuInput::InputPiece, [&](){InputPiece();}},
        {MenuInput::PrintPieces, [&](){PrintPieces();}},
        {MenuInput::ClearPieces, [&](){ClearPieces();}},
        {MenuInput::RunSim, [&](){RunSim();}},
        {MenuInput::End, [&](){m_end = true;}},
        {MenuInput::ReadConfig, [&](){ReadFiles();}}
    };
};
