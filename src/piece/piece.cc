#include "piece.hh"

piece::piece(piece_type type) : type(type), in_place(false) {
    //initialize all the cubes
    cubes = std::vector<sf::Vector2f>();
    auto form = std::vector<std::vector<int>>();
    if (type == Line) {
        form.push_back(std::vector<int>(1, 1, 1, 1));
    }
    else if (type == L) {
        form.push_back(std::vector<int>(1, 0));
        form.push_back(std::vector<int>(1, 0));
        form.push_back(std::vector<int>(1, 1));
    }
    else if (type == Reverse_L) {
        form.push_back(std::vector<int>(0, 1));
        form.push_back(std::vector<int>(0, 1));
        form.push_back(std::vector<int>(1, 1));
    }
    else if (type == Cube) {
        form.push_back(std::vector<int>(1, 1));
        form.push_back(std::vector<int>(1, 1));
    }
    else if (type == Squigely_left) {
        form.push_back(std::vector<int>(1, 1, 0, 0));
        form.push_back(std::vector<int>(0, 0, 1, 1));
    }
}

piece_type piece::get_type() { return type; }

std::vector<sf::Vector2f> piece::get_cubes() { return cubes; }

void piece::set_in_place(bool in_place_) {
    in_place = in_place_;
}

void piece::go_right() {
    for (size_t i = 0; i < cubes.size(); i++) {
        cubes[i].x += 50;
    }
}

void piece::go_left() {
    for (size_t i = 0; i < cubes.size(); i++) {
        cubes[i].x -= 50;
    }
}

void piece::go_down(float down) {
    for (size_t i = 0; i < cubes.size(); i++) {
        cubes[i].y += down;
    }
}

void piece::delete_row(float row) {
    //if not in place then we are playing this cube so we are not deleting it
    if (!in_place)
        return;
    auto new_cubes = std::vector<sf::Vector2f>();
    for (size_t i = 0; i < cubes.size(); i++) {
        if (cubes[i].y != row) {
            //check if he is above of the deleted row
            if (cubes[i].y < row) {
                //if it is then bring it down a notch
                cubes[i].y -= 50.0f;
            }
            new_cubes.push_back(cubes[i]);
        }
    }
    cubes = new_cubes;
}