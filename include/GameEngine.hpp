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
        PrintState = 6,
    };
    // Hash function 
    struct hashFunction
    {
        template<typename T>
        size_t operator()(const std::pair<T, T> &x) const
        {
            std::size_t hash1 = std::hash<T>()(x.first);
            std::size_t hash2 = std::hash<T>()(x.second);
            return hash1 ^ hash2;
        }
    };
    using Piece = std::pair<int64_t, int64_t>;
    using GameBoard = std::unordered_set<Piece, hashFunction>;

    inline const size_t CheckNeighbors(const Piece& p)const;
    void GetEpochPieces(std::shared_ptr<GameEngine::GameBoard> p) const;
    void ReadFiles();
    void Epoch(std::shared_ptr<GameBoard> pieces);
    void InputPiece();
    void PrintPieces();
    void ClearPieces();
    void PrintState();
    void RunSim();

    bool m_end = false;

    GameBoard m_pieces;

    std::shared_ptr<GameEngine::GameBoard> m_SpotsToCheck = std::make_shared<GameEngine::GameBoard>();

    constexpr static std::array<std::pair<int64_t, int64_t>, 8> m_nieghbors = {{
        {-1, 1},
        {0, 1},
        {1, 1},
        {-1, 0},
        {1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    }};

    const std::unordered_map<MenuInput, std::function<void()>> m_menuOptions{
        {MenuInput::InputPiece, [&](){InputPiece();}},
        {MenuInput::PrintPieces, [&](){PrintPieces();}},
        {MenuInput::ClearPieces, [&](){ClearPieces();}},
        {MenuInput::RunSim, [&](){RunSim();}},
        {MenuInput::End, [&](){m_end = true;}},
        {MenuInput::ReadConfig, [&](){ReadFiles();}},
        {MenuInput::PrintState, [&](){PrintState();}}
    };
};