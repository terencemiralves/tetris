#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <cmath>
#include <iostream>

/*
* @brief holds all the types of pieces
*/
enum piece_type {
    L,
    Reverse_L,
    Line,
    Squigely_left,
    Squigely_right,
    Cube
};


/*
* @brief Holds all the info of a piece (all of it's square in a vector, and methods that allows you to aply a move to the piece) 
*/
class piece {
    public:
    //Constructors (take the piece type)
        piece() = default;
        /*
        * @brief piece constructor, takes the type of the created piece
        * @param piece_type enum piece_type, the type of the piece
        */
        piece(piece_type);
        ~piece() = default;

    //getters
        piece_type get_type();
        std::vector<std::pair<float, float>> get_cubes();
        bool get_in_place();
        float get_speed();

    //setter
        void set_in_place(bool in_place_);
        void set_speed(float speed_);
        void set_cubes(std::vector<std::pair<float, float>> cubes_);

    //methods
        /*
        * @brief aplies a shift of the size of a cube to all the cubes on the right
        */
        void go_right();
        /*
        * @brief aplies a shift of the size of a cube to all the cubes on the left
        */
        void go_left();
        /*
        * @brief aplies a shift of the given size to all the cubes to the bottom
        * @param down the amount of the down shift
        */       
        void go_down(float down);
        /*
        * @brief delets all the cubes on a certain row updates all the cubes that were above if they placed
        * @param row the row where the elements have to be deleted
        */
        void delete_row(int row);
        /*
        * @brief rotates the piece
        */
        void rotate();
        /*
        * @brief updates the piece
        * @param dt the time that has passed since the last update
        */
        void update(float dt);

    private:
        std::vector<std::pair<float, float>> cubes;
        piece_type type;
        bool in_place;
        float gravity;
        float speed;
        float min_speed;
};