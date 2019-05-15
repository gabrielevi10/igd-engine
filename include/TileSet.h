#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include "Sprite.h"
#include "GameObject.h"

class TileSet {
    public:
        TileSet(uint32_t tileWidth, uint32_t tileHeight, const std::string&);

        void RenderTile(uint32_t index, double x, double y);
        uint32_t GetTileWidth() const;
        uint32_t GetTileHeight() const;
    
    private:
        GameObject tileSetGo;
        Sprite tileSet;
        uint32_t rows, columns, tileWidth, tileHeight;
};

#endif