class GameBoard
{
public:
    GameBoard();
    void Menu();
    inline void End(){ m_end = true; }
    inline bool IsOver()const{ return m_end; };

private:
    bool m_end = false;
    bool x = 0;
};
