#pragma once
#include "../piece/piece.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <random>
/**
* @brief Holds all the game logic, the pieces, the board, the score, etc
*/
class game {
    public:
    //Constructors
        game();
        ~game() = default;
    //methods
        /**
        * @brief runs the main loop of the game
        */
        void run();
        /**
        * @brief checks if there are any lines to delete, if there is updates the board and the pieces
        */
        void check_lines();
        /**
        * @brief add a new player controlled piece
        */
        void add_piece();
        /**
        * @brief draws the pieces
        */
        void draw();
        /**
        * @brief checks if the player collided with the bottom of the window or with another piece
        * @return true if the player collided with the bottom of the window or with another piece
        */
        bool check_collision();
        /**
        * @brief Gives back the coordinate of the player's piece if he was to continue to go down
        * @return the coordinates of the player's piece if he was to continue to go down
        */
        std::vector<std::pair<float, float>> get_bottom_player_piece();
        /**
        * @brief Prints the board with the player piece
        */
        void print_board();
        /**
        * @brief switch the current piece with the holded piece, if there is no holded piece then the current piece is put in hold
        */
        void hold_piece();
    private:
        std::vector<piece> pieces;
        std::vector<std::vector<int>> board;
        sf::RenderWindow window;
        piece* current_piece;
        float player_speed;
        int score;
        sf::Clock clock;
        piece next_piece;
        piece holded_piece;
        bool holded;
};
