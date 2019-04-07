#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include "Sprite.h"
#include "GameObject.h"

class TileSet {
    public:
        TileSet(const int tileWidth, const int tileHeight, const std::string&);

        void RenderTile(uint32_t index, float x, float y);
        int GetTileWidth() const;
        int GetTileHeight() const;
    
    private:
        GameObject tileSetGo;
        Sprite tileSet;
        int rows, columns, tileWidth, tileHeight;
};

#endif