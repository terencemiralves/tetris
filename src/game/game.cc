#include "game.hh"

game::game() : window(sf::RenderWindow(sf::VideoMode(800, 800), "Tetris")), score(0)
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
    // draw the background
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x, window.getSize().y));
    rectangle.setFillColor(sf::Color(0, 127, 115));
    rectangle.setPosition(0, 0);
    window.draw(rectangle);
    // draw the grid
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

    // draw test saying next piece
    sf::Font font;
    font.loadFromFile("../src/aux/Montserrat-Bold.ttf");
    sf::Text text2;
    text2.setFont(font);
    text2.setString("Next piece");
    text2.setCharacterSize(24);
    text2.setFillColor(sf::Color(255, 199, 0));
    text2.setPosition(775, 0);
    window.draw(text2);
    // Draw the next piece
    for (auto &cube : next_piece.get_cubes())
    {
        sf::RectangleShape rectangle(sf::Vector2f(40, 40));
        // set the color of the piece
        if (next_piece.get_type() == L)
            rectangle.setFillColor(sf::Color(215, 19, 19));
        else if (next_piece.get_type() == Reverse_L)
            rectangle.setFillColor(sf::Color(21, 245, 186));
        else if (next_piece.get_type() == Line)
            rectangle.setFillColor(sf::Color(131, 111, 255));
        else if (next_piece.get_type() == Squigely_left)
            rectangle.setFillColor(sf::Color(246, 233, 178));
        else if (next_piece.get_type() == Squigely_right)
            rectangle.setFillColor(sf::Color(135, 76, 204));
        else if (next_piece.get_type() == T)
            rectangle.setFillColor(sf::Color(255, 234, 227));
        else
            rectangle.setFillColor(sf::Color(242, 123, 189));
        if (next_piece.get_type() == Line)
            rectangle.setPosition(815 + (cube.first - 4) * 50, 50 + cube.second * 50);
        else if (next_piece.get_type() == Cube)
            rectangle.setPosition(790 + (cube.first - 4) * 50, 50 + cube.second * 50);
        else if (next_piece.get_type() == T)
            rectangle.setPosition(815 + (cube.first - 4) * 50, 50 + cube.second * 50);
        else if (next_piece.get_type() == Squigely_left)
            rectangle.setPosition(815 + (cube.first - 4) * 50, 50 + cube.second * 50);
        else if (next_piece.get_type() == Squigely_right)
            rectangle.setPosition(815 + (cube.first - 4) * 50, 50 + cube.second * 50);
        else if (next_piece.get_type() == L)
            rectangle.setPosition(800 + (cube.first - 4) * 50, 50 + cube.second * 50);
        else if (next_piece.get_type() == Reverse_L)
            rectangle.setPosition(800 + (cube.first - 4) * 50, 50 + cube.second * 50);

        window.draw(rectangle);
    }

    // draw the holded piece
    sf::Text text3;
    text3.setFont(font);
    text3.setString("Holded piece");
    text3.setCharacterSize(24);
    text3.setFillColor(sf::Color(255, 199, 0));
    text3.setPosition(25, 150);
    window.draw(text3);
    // holded piece
    for (auto &cube : holded_piece.get_cubes())
    {
        sf::RectangleShape rectangle(sf::Vector2f(40, 40));
        // set the color of the piece
        if (holded_piece.get_type() == L)
            rectangle.setFillColor(sf::Color(215, 19, 19));
        else if (holded_piece.get_type() == Reverse_L)
            rectangle.setFillColor(sf::Color(21, 245, 186));
        else if (holded_piece.get_type() == Line)
            rectangle.setFillColor(sf::Color(131, 111, 255));
        else if (holded_piece.get_type() == Squigely_left)
            rectangle.setFillColor(sf::Color(246, 233, 178));
        else if (holded_piece.get_type() == Squigely_right)
            rectangle.setFillColor(sf::Color(135, 76, 204));
        else if (holded_piece.get_type() == T)
            rectangle.setFillColor(sf::Color(255, 234, 227));
        else
            rectangle.setFillColor(sf::Color(242, 123, 189));
        if (holded_piece.get_type() == Line)
            rectangle.setPosition(50 + (cube.first - 4) * 50, 200 + cube.second * 50);
        else if (holded_piece.get_type() == Cube)
            rectangle.setPosition(25 + (cube.first - 4) * 50, 200 + cube.second * 50);
        else if (holded_piece.get_type() == T)
            rectangle.setPosition(50 + (cube.first - 4) * 50, 200 + cube.second * 50);
        else if (holded_piece.get_type() == Squigely_left)
            rectangle.setPosition(50 + (cube.first - 4) * 50, 200 + cube.second * 50);
        else if (holded_piece.get_type() == Squigely_right)
            rectangle.setPosition(50 + (cube.first - 4) * 50, 200 + cube.second * 50);
        else if (holded_piece.get_type() == L)
            rectangle.setPosition(25 + (cube.first - 4) * 50, 200 + cube.second * 50);
        else if (holded_piece.get_type() == Reverse_L)
            rectangle.setPosition(25 + (cube.first - 4) * 50, 200 + cube.second * 50);

        window.draw(rectangle);
    }

    // draw the score
    sf::Text text;
    text.setFont(font);
    text.setString("Score: " + std::to_string(score));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(255, 199, 0));
    text.setPosition(50, 50);
    window.draw(text);

    // draw the image of the current piece
    for (auto &cube : get_bottom_player_piece())
    {
        sf::RectangleShape rectangle(sf::Vector2f(40, 40));
        // set the color of the piece
        if (current_piece->get_type() == L)
            rectangle.setFillColor(sf::Color(215, 19, 19));
        else if (current_piece->get_type() == Reverse_L)
            rectangle.setFillColor(sf::Color(21, 245, 186));
        else if (current_piece->get_type() == Line)
            rectangle.setFillColor(sf::Color(131, 111, 255));
        else if (current_piece->get_type() == Squigely_left)
            rectangle.setFillColor(sf::Color(246, 233, 178));
        else if (current_piece->get_type() == Squigely_right)
            rectangle.setFillColor(sf::Color(135, 76, 204));
        else if (current_piece->get_type() == T)
            rectangle.setFillColor(sf::Color(255, 234, 227));
        else
            rectangle.setFillColor(sf::Color(242, 123, 189));
        rectangle.setPosition((window.getSize().x / 2) - 245 + cube.first * 50, 10 + cube.second * 50);
        window.draw(rectangle);
    }

    // loop through all the pieces and draw them
    for (auto &piece : pieces)
    {
        for (auto &cube : piece.get_cubes())
        {
            // black background of the cube
            sf::RectangleShape rectangle2(sf::Vector2f(50, 50));
            rectangle2.setFillColor(sf::Color::Black);
            rectangle2.setPosition((window.getSize().x / 2) - 250 + cube.first * 50, 5 + std::round(cube.second) * 50);
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
            else if (current_piece->get_type() == T)
                rectangle.setFillColor(sf::Color(255, 234, 227));
            else
                rectangle.setFillColor(sf::Color(242, 123, 189));
            rectangle.setPosition((window.getSize().x / 2) - 245 + cube.first * 50, 10 + std::round(cube.second) * 50);
            window.draw(rectangle);
        }
    }
}

void game::add_piece()
{
    holded = false;
    // add the next piece
    pieces.push_back(next_piece);
    current_piece = &pieces[pieces.size() - 1];
    // set the new next piece
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 6);
    int random_number = dis(gen);
    if (random_number == 0)
        next_piece = piece(L);
    else if (random_number == 1)
        next_piece = piece(Reverse_L);
    else if (random_number == 2)
        next_piece = piece(Line);
    else if (random_number == 3)
        next_piece = piece(Squigely_left);
    else if (random_number == 4)
        next_piece = piece(Squigely_right);
    else if (random_number == 5)
        next_piece = piece(T);
    else
        next_piece = piece(Cube);
    if (check_collision())
    {
        window.close();
        std::cout << "Game Over\n"
                  << "Your score is: " << score << std::endl;
    }
}

void game::check_lines()
{
    int nb_lines = 0;
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
            nb_lines++;
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
    // get the bonus multiplier
    auto bonus = (clock.getElapsedTime().asSeconds() / 60) + 1;
    // update the score
    if (nb_lines == 1)
        score += 40 * bonus;
    else if (nb_lines == 2)
        score += 100 * bonus;
    else if (nb_lines == 3)
        score += 300 * bonus;
    else if (nb_lines == 4)
        score += 1200 * bonus;
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
    // create the first piece
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 6);
    int random_number = dis(gen);
    if (random_number == 0)
        next_piece = piece(L);
    else if (random_number == 1)
        next_piece = piece(Reverse_L);
    else if (random_number == 2)
        next_piece = piece(Line);
    else if (random_number == 3)
        next_piece = piece(Squigely_left);
    else if (random_number == 4)
        next_piece = piece(Squigely_right);
    else if (random_number == 5)
        next_piece = piece(T);
    else
        next_piece = piece(Cube);

    // add the first piece
    add_piece();
    clock.restart();
    sf::Clock clock2;
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
                current_piece->go_right(board);
            }
            // check if the key pressed is the left arrow key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                current_piece->go_left(board);
            }
            // check if the key pressed is the up arrow key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                current_piece->rotate(board);
            }
            // check if the key pressed is the down arrow key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                current_piece->go_down(1);
            }
            // check if the key pressed is the space key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                current_piece->set_cubes(get_bottom_player_piece());
            }
            // check if the player pressed the shift key
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift)
            {
                hold_piece();
            }
        }

        // aplly the gravity
        float deltaT = clock2.restart().asSeconds();
        current_piece->update(deltaT);

        // check the collision
        if (check_collision())
        {
            current_piece->set_in_place(true);
            player_speed = current_piece->get_speed() - 0.1;
            add_piece();
        }

        // check the lines
        check_lines();

        window.clear();
        draw();
        window.display();
    }
}

std::vector<std::pair<float, float>> game::get_bottom_player_piece()
{
    std::vector<std::pair<float, float>> bottom_piece = current_piece->get_cubes();
    // round the position of the cubes
    for (size_t i = 0; i < bottom_piece.size(); i++)
    {
        bottom_piece[i].first = std::round(bottom_piece[i].first);
        bottom_piece[i].second = std::round(bottom_piece[i].second);
    }
    while (true)
    {
        for (auto &cube : bottom_piece)
        {
            cube.second += 1;
        }
        for (auto &cube : bottom_piece)
        {
            // check if the image collided with the bottom of the window
            if (std::round(cube.second) == 19)
            {
                return bottom_piece;
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
                        return bottom_piece;
                    }
                }
            }
        }
    }
    return bottom_piece;
}

void game::print_board()
{
    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[i].size(); j++)
        {
            // print the player piece
            auto pice = false;
            for (auto cube : current_piece->get_cubes())
            {
                if (std::round(cube.first) < 0)
                {
                    std::cout << "ERROR\n";
                }
                if (std::round(cube.first) == j && std::round(cube.second) == i)
                {
                    pice = true;
                    std::cout << "X|";
                }
            }
            if (board[i][j] == 0 && !pice)
                std::cout << " |";
            else if (board[i][j] == 1)
                std::cout << "X|";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------" << std::endl;
}

void game::hold_piece()
{
    if (!holded)
    {
        if (holded_piece.get_cubes().size() == 0)
        {
            holded_piece = piece(current_piece->get_type());
            pieces.pop_back();
            add_piece();
        }
        else
        {
            piece temp = holded_piece;
            holded_piece = piece(current_piece->get_type());
            pieces.pop_back();
            pieces.push_back(temp);
            current_piece = &pieces[pieces.size() - 1];
        }
        holded = true;
    }
}