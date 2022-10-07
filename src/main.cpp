#include <iostream>
#include <chrono>
#include <thread>
#include "GameBoard.hpp"

int main()
{
  GameBoard game;

  while(!game.IsOver()){
    game.Menu();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}