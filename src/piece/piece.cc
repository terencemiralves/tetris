#include "piece.hh"

piece::piece(piece_type type) : type(type), in_place(false), gravity(0.1f), speed(1.0f), min_speed(0.1f)
{
    // initialize all the cubes
    switch (type)
    {
    case L:
        cubes.push_back(std::make_pair(4, 0));
        cubes.push_back(std::make_pair(4, 1));
        cubes.push_back(std::make_pair(4, 2));
        cubes.push_back(std::make_pair(5, 2));
        break;
    case Reverse_L:
        cubes.push_back(std::make_pair(5, 0));
        cubes.push_back(std::make_pair(5, 1));
        cubes.push_back(std::make_pair(5, 2));
        cubes.push_back(std::make_pair(4, 2));
        break;
    case Line:
        cubes.push_back(std::make_pair(4, 0));
        cubes.push_back(std::make_pair(4, 1));
        cubes.push_back(std::make_pair(4, 2));
        cubes.push_back(std::make_pair(4, 3));
        break;
    case Squigely_left:
        cubes.push_back(std::make_pair(3, 0));
        cubes.push_back(std::make_pair(4, 0));
        cubes.push_back(std::make_pair(4, 1));
        cubes.push_back(std::make_pair(5, 1));
        break;
    case Squigely_right:
        cubes.push_back(std::make_pair(5, 0));
        cubes.push_back(std::make_pair(4, 0));
        cubes.push_back(std::make_pair(4, 1));
        cubes.push_back(std::make_pair(3, 1));
        break;
    case Cube:
        cubes.push_back(std::make_pair(4, 0));
        cubes.push_back(std::make_pair(5, 1));
        cubes.push_back(std::make_pair(4, 1));
        cubes.push_back(std::make_pair(5, 0));
        break;
    }
}

piece_type piece::get_type() { return type; }

std::vector<std::pair<float, float>> piece::get_cubes() { return cubes; }

void piece::set_in_place(bool in_place_)
{
    in_place = in_place_;
    // round the position of the cubes
    for (size_t i = 0; i < cubes.size(); i++)
    {
        cubes[i].first = std::round(cubes[i].first);
        cubes[i].second = std::round(cubes[i].second);
    }
}

void piece::go_right()
{
    // check if the piece can go right
    for (size_t i = 0; i < cubes.size(); i++)
    {
        if (std::round(cubes[i].first) == 9)
            return;
    }
    for (size_t i = 0; i < cubes.size(); i++)
    {
        cubes[i].first += 1;
    }
}

void piece::go_left()
{
    // check if the piece can go left
    for (size_t i = 0; i < cubes.size(); i++)
    {
        if (std::round(cubes[i].first) == 0)
            return;
    }
    for (size_t i = 0; i < cubes.size(); i++)
    {
        cubes[i].first -= 1;
    }
}

void piece::go_down(float down)
{
    for (size_t i = 0; i < cubes.size(); i++)
    {
        cubes[i].second += down;
    }
}

void piece::delete_row(int row)
{
    // if not in place then we are playing this cube so we are not deleting it
    if (!in_place)
        return;
    auto new_cubes = std::vector<std::pair<float, float>>();
    for (size_t i = 0; i < cubes.size(); i++)
    {
        if (cubes[i].second != row)
        {
            // check if he is above of the deleted row
            if (cubes[i].second < row)
            {
                // if it is then bring it down a notch
                cubes[i].second += 1;
            }
            new_cubes.push_back(cubes[i]);
        }
    }
    cubes = new_cubes;
}

void piece::rotate()
{
    // if the piece is a cube then we don't need to rotate it
    if (type == Cube)
        return;
    // get the center of the piece
    auto center = cubes[1];
    //check if the rotation won't make the piece go out of bounds
    for (size_t i = 0; i < cubes.size(); i++)
    {
        // if the cube is the center then we don't need to check it
        if (cubes[i] == center)
            continue;
        // get the relative position of the cube to the center
        auto relative_position = std::make_pair(cubes[i].first - center.first, cubes[i].second - center.second);
        // check if the cube will go out of bounds
        if (std::round(center.first - relative_position.second) < 0 ||std::round(center.first - relative_position.second) > 9 ||std::round(center.second + relative_position.first) > 19)
            return;
    }
    // rotate the piece
    for (size_t i = 0; i < cubes.size(); i++)
    {
        // if the cube is the center then we don't need to rotate it
        if (cubes[i] == center)
            continue;
        // get the relative position of the cube to the center
        auto relative_position = std::make_pair(cubes[i].first - center.first, cubes[i].second - center.second);
        // rotate the cube
        cubes[i] = std::make_pair(center.first - relative_position.second, center.second + relative_position.first);
    }
}

bool piece::get_in_place()
{
    return in_place;
}

void piece::update(float dt)
{
    // if the piece is in place then we don't need to update it
    speed += gravity * dt; // Increase speed over time
    if (speed < min_speed)
    {
        speed = min_speed; // Clamp speed to minimum value
    }

    // Move the piece down based on speed
    go_down(speed * dt);
}

void piece::set_speed(float speed_)
{
    speed = speed_;
}

float piece::get_speed()
{
    return speed;
}

void piece::set_cubes(std::vector<std::pair<float, float>> cubes_)
{
    cubes = cubes_;
}