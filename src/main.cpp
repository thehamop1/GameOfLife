#include <iostream>
#include <chrono>
#include <thread>
#include "GameEngine.hpp"

int main()
{
  GameEngine game;

  while(!game.IsOver()){
    game.Menu();
    game.Input();
  }
}