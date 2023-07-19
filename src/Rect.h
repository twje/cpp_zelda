#pragma once

#include <SFML/Graphics.hpp>

template <typename T>
class Rect
{
public:
    Rect() {}
    Rect(T x, T y, T width, T height)
        : mRect(sf::Vector2<T>(x, y), sf::Vector2<T>(width, height))
    {
    }
    Rect(sf::Vector2<T> position, sf::Vector2<T> size)
        : mRect(position, size)
    {
    }

    std::optional<Rect<T>> FindIntersection(const Rect<T> &rect)
    {
        std::optional<sf::Rect<T>> intersectOpt = mRect.findIntersection(ConvertToSFMLRect(rect));
        if (intersectOpt.has_value())
        {
            sf::Rect<T> intersect = intersectOpt.value();
            return ConvertFromSFMLRect(intersect);
        }
        return std::nullopt;
    }

    Rect Inflate(T x, T y)
    {
        Rect<T> result = *this;
        result.SetLeft(result.GetX() - x / 2);
        result.SetWidth(result.GetWidth() + x);
        result.SetRight(result.GetY() - y / 2);
        result.SetHeight(result.GetHeight() + y);

        return result;
    }

    void MoveHorizontally(T value) { mRect.left += value; }
    void MoveVertically(T value) { mRect.top += value; }

    // Getters
    T GetX() const { return mRect.left; }
    T GetY() const { return mRect.top; }
    T GetWidth() const { return mRect.width; }
    T GetHeight() const { return mRect.height; }
    T GetLeft() const { return mRect.left; }
    T GetTop() const { return mRect.top; }
    T GetRight() const { return mRect.left + mRect.width; }
    T GetBottom() const { return mRect.top + mRect.height; }
    T GetCenterX() const { return mRect.left + mRect.width / 2; }
    T GetCenterY() const { return mRect.top + mRect.height / 2; }

    // Setters
    void SetX(T value) { mRect.left = value; }
    void SetY(T value) { mRect.top = value; }
    void SetPosition(T x, T y) { SetX(x), SetY(y); }
    void SetWidth(T value) { mRect.width = value; }
    void SetHeight(T value) { mRect.height = value; }
    void SetLeft(T value) { mRect.left = value; }
    void SetTop(T value) { mRect.top = value; }
    void SetRight(T value) { mRect.left = value - mRect.width; }
    void SetBottom(T value) { mRect.top = value - mRect.height; }
    void SetCenterX(T value) { mRect.left = value - mRect.width / 2; }
    void SetCenterY(T value) { mRect.top = value - mRect.height / 2; }
    void SetCenter(T x, T y) { SetCenterX(x), SetCenterY(y); }

    static Rect<T> ConvertFromSFMLRect(const sf::Rect<T> &rect)
    {
        return Rect<T>(
            rect.left,
            rect.top,
            rect.width,
            rect.height);
    }

    static sf::Rect<T> ConvertToSFMLRect(const Rect<T> &rect)
    {
        return sf::Rect<T>(
            sf::Vector2<T>(rect.GetLeft(), rect.GetTop()),
            sf::Vector2<T>(rect.GetWidth(), rect.GetHeight()));
    }

private:
    sf::Rect<T> mRect;
};

using FloatRect = Rect<float>;
