#include <stdexcept>
#include <fstream>
#include <iostream>
// Platz für Includes

#include "sokoban.h"

Sokoban::Sokoban(sf::RenderWindow &_window) : window(_window)
{
    if (!texture.loadFromFile("../data/Sokoban.png"))
        throw std::runtime_error("Could not load resource file");

    sprite_wall.setTexture(texture);
    sprite_wall.setTextureRect(sf::IntRect(128, 0, 64, 64));
    sprite_box.setTexture(texture);
    sprite_box.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite_target.setTexture(texture);
    sprite_target.setTextureRect(sf::IntRect(64, 64, 64, 64));
    sprite_floor.setTexture(texture);
    sprite_floor.setTextureRect(sf::IntRect(0, 64, 64, 64));
    sprite_goal.setTexture(texture);
    sprite_goal.setTextureRect(sf::IntRect(64, 0, 64, 64));
    sprite_player[Direction::LEFT].setTexture(texture);
    sprite_player[Direction::LEFT].setTextureRect(sf::IntRect(64, 192, 64, 64));
    sprite_player[Direction::RIGHT].setTexture(texture);
    sprite_player[Direction::RIGHT].setTextureRect(sf::IntRect(0, 128, 64, 64));
    sprite_player[Direction::UP].setTexture(texture);
    sprite_player[Direction::UP].setTextureRect(sf::IntRect(0, 192, 64, 64));
    sprite_player[Direction::DOWN].setTexture(texture);
    sprite_player[Direction::DOWN].setTextureRect(sf::IntRect(64, 128, 64, 64));

    if (!font.loadFromFile("../data/GistLight.otf"))
        throw std::runtime_error("Could not load font file");

    text.setFont(font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(30);
}

void Sokoban::draw_block(Block &b)
{
    sf::Sprite block;
    switch (b.type)
    {
    case Block_Type::BOX:
        block = sprite_box;
        break;
    case Block_Type::WALL:
        block = sprite_wall;
        break;
    case Block_Type::TARGET:
        block = sprite_target;
        break;
    case Block_Type::FLOOR:
        block = sprite_floor;
        break;
    case Block_Type::GOAL:
        block = sprite_goal;
        break;
    case Block_Type::PLAYER:
        block = sprite_player[player_dir];
        break;
    }
    int pos_x = b.x * 64 - (player.x > 8 ? (player.x - 9) * 64 : -64);
    int pos_y = b.y * 64 - (player.y > 6 ? (player.y - 7) * 64 : -64);
    if(pos_y > 0 && pos_x > 0)
    {
        block.setPosition(pos_x, pos_y);
        window.draw(block);
    }
}

void Sokoban::key_pressed(sf::Keyboard::Key k)
{
    switch (k)
    {
    case sf::Keyboard::Left:

        break;
    case sf::Keyboard::Right:

        break;
    case sf::Keyboard::Up:

        break;
    case sf::Keyboard::Down:

        break;
    }
}

void Sokoban::key_released(sf::Keyboard::Key k)
{
    if(is_level_finished())
    {
        load_level();
        return;
    }
    switch (k)
    {
    case sf::Keyboard::Left:
        move_player(Direction::LEFT);
        break;
    case sf::Keyboard::Right:
        move_player(Direction::RIGHT);
        break;
    case sf::Keyboard::Up:
        move_player(Direction::UP);
        break;
    case sf::Keyboard::Down:
        move_player(Direction::DOWN);
        break;
    }
}

void Sokoban::move_player(Direction dir)
{
    int new_x = player.x;
    int new_y = player.y;
    switch (dir)
    {
    case Direction::LEFT:
        new_x--;
        break;
    case Direction::RIGHT:
        new_x++;
        break;
    case Direction::DOWN:
        new_y++;
        break;
    case Direction::UP:
        new_y--;
        break;
    }
    if (can_move(new_x, new_y) || (is_box(new_x, new_y) && move_box(new_x, new_y, dir)))
    {
        player.x = new_x;
        player.y = new_y;
        player_dir = dir;
    }
}

bool Sokoban::move_box(int x, int y, Direction dir)
{
    //Falls die Box in diese Richtung verschiebbar ist, die Box verschieben und true zurück geben
    
    return false;
}

bool Sokoban::is_box(int x, int y)
{
    //Prüfen ob an dieser Position eine Box ist

    return false;
}

bool Sokoban::has_target(int x, int y)
{
    //Prüfen ob an dieser Position eine Target ist

    return false;
}

bool Sokoban::can_move(int x, int y)
{
    //Prüfen ob diese Position betretbar ist (Kein Wall und keine Box)

    return true;
}

void Sokoban::draw()
{
    window.clear();

    text.setString("Title: " + title);
    text.setPosition(50, 10);
    window.draw(text);
    text.setString("Level: " + std::to_string(current_level));
    text.setPosition(400, 10);
    window.draw(text);

    //Alle Blöcke durchgehen und alle Wall, Target und Floor Blöcke mit draw_block anzeigen

    //Alle Boxen anzeigen, wenn an der Stelle der Box auch ein Target ist, dann ein Goal anzeigen

    draw_block(player);

    window.display();
}

void Sokoban::start()
{
    //Den Titel und die Levels aus der Datei ../data/Boxxle1.slc wie in der Angabe beschrieben laden


    load_level();
}

size_t Sokoban::find_first_xml_tag(std::string xml, std::string tag, size_t offset, bool after_tag)
{
    //Beschreibung der Funktion in der Angabe

    return std::string::npos;
}

void Sokoban::load_level()
{
    current_level++;
    
    //Das nächste Level laden
}

bool Sokoban::is_level_finished()
{
    //Prüfen ob an der Position jedes Targets eine Box ist

    return false;
}