#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "piece/piece.hh"

//Begining of a fun adventure
int main(int argc, char** argv) {
    if (argc != 1 || argv[1]) {
        std::cerr << "Usage: ./tetris \n";
        return 1;            
    }
    //create a small rectangle
    sf::RectangleShape test(sf::Vector2f(50.0f, 50.0f));
    //color it blue
    test.setFillColor(sf::Color::Red);
    test.setPosition(5.0f, 0.0f);
    //small try of window creation
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                std::cout << "Window closed\n";
            }
        }
        window.clear();
        window.draw(test);
        window.display();
    }

    return 0;
}