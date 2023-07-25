#include "Sprite.h"

void Sprite::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    sf::RenderStates statesCopy(states);
    statesCopy.transform *= getTransform();
    target.draw(mSprite, statesCopy);
}
