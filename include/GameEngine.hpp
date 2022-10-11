#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <utility>
#include <cstddef>

class GameEngine
{
private:
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
    void GetEpochPieces(GameBoard& p) const;
    void Epoch(GameBoard& pieces);

    GameBoard m_pieces;
    GameBoard m_SpotsToCheck;

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
public:
    void PrintBoard();
    void PrintState();
    void PrintPieces();
    void ClearPieces();
    void ClearPiece(const Piece& p);
    void InputPiece(const Piece& p);
    void RunSim();
};