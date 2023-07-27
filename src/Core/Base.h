#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args &&...args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

using TexturePtr = Ref<sf::Texture>;
using TextureVector = std::vector<TexturePtr>;
using TextureMap = std::unordered_map<std::string, TextureVector>;