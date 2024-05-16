#pragma once
#include "../piece/piece.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <random>
/*
* @brief Holds all the game logic, the pieces, the board, the score, etc
*/
class game {
    public:
    //Constructors
        game();
        ~game() = default;
    //methods
        void run();
        void check_lines();
        void add_piece();
        void draw();
        bool check_collision();
    private:
        std::vector<piece> pieces;
        std::vector<std::vector<int>> board;
        sf::RenderWindow window;
        piece* current_piece;
};