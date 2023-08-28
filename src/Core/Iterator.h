#pragma once

template <typename ContainerType>
class Iterator
{
private:
    typename ContainerType::iterator current;

public:
    Iterator(typename ContainerType::iterator iter) : current(iter) {}

    auto &operator*()
    {
        return *current;
    }

    Iterator &operator++()
    {
        ++current;
        return *this;
    }

    bool operator!=(const Iterator &other) const
    {
        return current != other.current;
    }
};