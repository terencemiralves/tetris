#include <SFML/Graphics.hpp> 
#include <iostream>

//Begining of a fun adventure
int main(int argc, char** argv) {
    if (argc != 1 || argv[1]) {
        std::cerr << "Usage: ./tetris \n";
        return 1;            
    }
    //small try of window creation
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fenêtre SFML");
    return 0;
}