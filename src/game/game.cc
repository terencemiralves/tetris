#include "game.hh"

game::game() : window(sf::RenderWindow(sf::VideoMode(800, 800), "Tetris"))
{
    // initialize the board
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < 10; j++)
        {
            row.push_back(0);
        }
        board.push_back(row);
    }
}

void game::draw()
{
    //draw the background
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x, window.getSize().y));
    rectangle.setFillColor(sf::Color(0, 127, 115));
    rectangle.setPosition(0, 0);
    window.draw(rectangle);
    //draw the grid
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            sf::RectangleShape rectangle(sf::Vector2f(50, 50));
            rectangle.setFillColor(sf::Color::White);
            rectangle.setPosition((window.getSize().x / 2) - 250 + j * 50, 5 + i * 50);
            window.draw(rectangle);
            sf::RectangleShape rectangle2(sf::Vector2f(45, 45));
            rectangle2.setFillColor(sf::Color::Black);
            rectangle2.setPosition((window.getSize().x / 2) - 248 + j * 50, 7 + i * 50);
            window.draw(rectangle2);
        }
    }

    // loop through all the pieces and draw them
    for (auto &piece : pieces)
    {
        for (auto &cube : piece.get_cubes())
        {
            //black background of the cube
            sf::RectangleShape rectangle2(sf::Vector2f(50, 50));
            rectangle2.setFillColor(sf::Color::Black);
            rectangle2.setPosition((window.getSize().x / 2) - 250 + cube.first * 50, 5 + cube.second * 50);
            window.draw(rectangle2);
            sf::RectangleShape rectangle(sf::Vector2f(40, 40));
            // set the color of the piece
            if (piece.get_type() == L)
                rectangle.setFillColor(sf::Color(215, 19, 19));
            else if (piece.get_type() == Reverse_L)
                rectangle.setFillColor(sf::Color(21, 245, 186));
            else if (piece.get_type() == Line)
                rectangle.setFillColor(sf::Color(131, 111, 255));
            else if (piece.get_type() == Squigely_left)
                rectangle.setFillColor(sf::Color(246, 233, 178));
            else if (piece.get_type() == Squigely_right)
                rectangle.setFillColor(sf::Color(135, 76, 204));
            else
                rectangle.setFillColor(sf::Color(242, 123, 189));
            rectangle.setPosition((window.getSize().x / 2) - 245 + cube.first * 50, 10 + cube.second * 50);
            window.draw(rectangle);
        }
    }
}

void game::add_piece()
{
    // add a piece randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 5);
    int random_number = dis(gen);
    if (random_number == 0)
        pieces.push_back(piece(L));
    else if (random_number == 1)
        pieces.push_back(piece(Reverse_L));
    else if (random_number == 2)
        pieces.push_back(piece(Line));
    else if (random_number == 3)
        pieces.push_back(piece(Squigely_left));
    else if (random_number == 4)
        pieces.push_back(piece(Squigely_right));
    else
        pieces.push_back(piece(Cube));
    current_piece = &pieces[pieces.size() - 1];
}

void game::check_lines()
{
    // check if a line is full
    for (size_t i = 0; i < board.size(); i++)
    {
        bool full = true;
        for (size_t j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 0)
            {
                full = false;
                break;
            }
        }
        // if the line is full delete it
        if (full)
        {
            for (size_t j = 0; j < board[i].size(); j++)
            {
                board[i][j] = 0;
            }
            // update the board
            for (size_t k = i; k > 0; k--)
            {
                for (size_t j = 0; j < board[k].size(); j++)
                {
                    board[k][j] = board[k - 1][j];
                }
            }
            // update the pieces
            for (auto &piece : pieces)
                piece.delete_row(i);
        }
    }
}

bool game::check_collision()
{
    // check if the player collided with the bottom of the window or with another piece
    for (auto &cube : current_piece->get_cubes())
    {
        // check if the player collided with the bottom of the window
        if (std::round(cube.second) == 19)
        {
            for (auto &cube : current_piece->get_cubes())
            {
                board[std::round(cube.second)][std::round(cube.first)] = 1;
            }
            return true;
        }
        // check if the player collided with another piece
        for (auto &piece : pieces)
        {
            if (!piece.get_in_place())
                continue;
            for (auto &cube_ : piece.get_cubes())
            {
                if (std::round(cube.first) == std::round(cube_.first) && std::round(cube.second) + 1 == std::round(cube_.second))
                {
                    for (auto &cube : current_piece->get_cubes())
                    {
                        board[std::round(cube.second)][std::round(cube.first)] = 1;
                    }
                    return true;
                }
            }
        }
   }
    return false;
}

void game::run()
{
    // add the first piece
    add_piece();
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                std::cout << "Window closed\n";
            }
            // check if the key pressed is the right arrow key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                current_piece->go_right();
            }
            // check if the key pressed is the left arrow key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                current_piece->go_left();
            }
            // check if the key pressed is the up arrow key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                current_piece->rotate();
            }
            // check if the key pressed is the down arrow key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                current_piece->go_down(1);
            }
        }

        // aplly the gravity
        float deltaT = clock.restart().asSeconds();
        current_piece->update(deltaT);

        // check the collision
        if (check_collision())
        {
            current_piece->set_in_place(true);
            add_piece();
        }

        // check the lines
        check_lines();

        window.clear();
        draw();
        window.display();
    }
}