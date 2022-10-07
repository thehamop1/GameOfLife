#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <utility>
#include <functional>
#include <cstddef>
#include <iostream>


enum class MenuInput{
    End = 0,
    InputPiece = 1,
    PrintPieces = 2,
    ClearPieces = 3,
};

class GameEngine
{
public:
    void Menu() const;
    void Input();
    inline bool IsOver()const{ return m_end; };

private:
    using GameBoard = std::unordered_map<int64_t, int64_t>;

    void InputPiece();
    void PrintPieces();
    void ClearPieces();

    int m_userInput;
    bool m_end = false;
    GameBoard m_pieces;

    std::unordered_map<MenuInput, std::function<void()>> m_menuOptions{
        {MenuInput::InputPiece, [&](){InputPiece();}},
        {MenuInput::PrintPieces, [&](){PrintPieces();}},
        {MenuInput::ClearPieces, [&](){ClearPieces();}},
        {MenuInput::End, [&](){m_end = true;}}
    };
};
