#include "Core/SpriteDataView.h"
#include "Core/SpriteData.h"

const sf::Texture &SpriteDataView::GetTexture() const { return *mData.mTexture; }
const sf::IntRect &SpriteDataView::GetTextureRegion() const { return mData.mTextureRegion; }
const FloatRect &SpriteDataView::GetBoundingBox() const { return mData.mBoundingBox; }
const FloatRect &SpriteDataView::GetHitBox() const { return mData.mHitBox; }