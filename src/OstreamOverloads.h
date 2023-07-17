#pragma once

#include <ostream>

#include <SFML/Graphics.hpp>

template <typename T>
std::ostream &operator<<(std::ostream &os, const sf::Vector2<T> &obj)
{
    os << "[" << obj.x << "," << obj.y << "]";
    return os;
}

template <typename T>
std::string ToString(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}