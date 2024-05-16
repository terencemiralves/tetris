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
        /*
        * @brief runs the main loop of the game
        */
        void run();
        /*
        * @brief checks if there are any lines to delete, if there is updates the board and the pieces
        */
        void check_lines();
        /*
        * @brief add a new player controlled piece
        */
        void add_piece();
        /*
        * @brief draws the pieces
        */
        void draw();
        /*
        * @brief checks if the player collided with the bottom of the window or with another piece
        * @return true if the player collided with the bottom of the window or with another piece
        */
        bool check_collision();
    private:
        std::vector<piece> pieces;
        std::vector<std::vector<int>> board;
        sf::RenderWindow window;
        piece* current_piece;
};