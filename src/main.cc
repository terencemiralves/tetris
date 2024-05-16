#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "game/game.hh"

//Begining of a fun adventure
int main(int argc, char** argv) {
    if (argc != 1 || argv[1]) {
        std::cerr << "Usage: ./tetris \n";
        return 1;            
    }
    auto tetris = game();
    tetris.run();
    return 0;
}