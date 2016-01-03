/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <nyra/sfml/TileMap.h>
#include <nyra/sfml/Graphics.h>

namespace nyra
{
namespace sfml
{
//===========================================================================//
TileMap::TileMap(const Vector2U& numTiles,
                 const Vector2U& tileSize,
                 const std::string& pathname,
                 const uint16_t* tiles) :
    mNumTiles(numTiles),
    mTileSize(tileSize)
{
    // load the tileset texture
    if (!mTexture.loadFromFile(pathname))
    {
        throw std::runtime_error("Unable to load texture: " + pathname);
    }

    // resize the vertex array to fit the level size
    mVertices.setPrimitiveType(sf::Quads);
    mVertices.resize(mNumTiles.product() * 4);

    // populate the vertex array, with one quad per tile
    for (size_t jj = 0; jj < mNumTiles.y; ++jj)
    {
        for (size_t ii = 0; ii < mNumTiles.x; ++ii)
        {
            // get the current tile number
            const size_t tileNumber = tiles[ii + jj * mNumTiles.x];

            // find its position in the tileset texture
            const size_t tu = tileNumber % (mTexture.getSize().x / mTileSize.x);
            const size_t tv = tileNumber / (mTexture.getSize().x / mTileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &mVertices[(ii + jj * mNumTiles.x) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(
                    ii * mTileSize.x, jj * mTileSize.y);
            quad[1].position = sf::Vector2f(
                    (ii + 1) * mTileSize.x, jj * mTileSize.y);
            quad[2].position = sf::Vector2f(
                    (ii + 1) * mTileSize.x, (jj + 1) * mTileSize.y);
            quad[3].position = sf::Vector2f(
                    ii * mTileSize.x, (jj + 1) * mTileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(
                    tu * mTileSize.x, tv * mTileSize.y);
            quad[1].texCoords = sf::Vector2f(
                    (tu + 1) * mTileSize.x, tv * mTileSize.y);
            quad[2].texCoords = sf::Vector2f(
                    (tu + 1) * mTileSize.x, (tv + 1) * mTileSize.y);
            quad[3].texCoords = sf::Vector2f(
                    tu * mTileSize.x, (tv + 1) * mTileSize.y);
        }
    }
}

//===========================================================================//
void TileMap::render(const Matrix& matrix,
                     GraphicsInterface& graphics)
{

    const sf::Transform sfmlMatrix(matrix(0, 0), matrix(0, 1), matrix(0, 2),
                                   matrix(1, 0), matrix(1, 1), matrix(1, 2),
                                   matrix(2, 0), matrix(2, 1), matrix(2, 2));

    // apply the transform
    mRenderState.transform = sfmlMatrix;

    // apply the tileset texture
    mRenderState.texture = &mTexture;

    // draw the vertex array
    Graphics& sfmlGraphics(dynamic_cast<Graphics&>(graphics));
    sfmlGraphics.getRenderTarget().draw(mVertices, mRenderState);
}
}
}