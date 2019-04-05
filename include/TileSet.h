#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include "Sprite.h"
#include "GameObject.h"

class TileSet {
    public:
        TileSet(const int&, const int&, const std::string&);

        void RenderTile(uint32_t, float, float);
        int GetTileWidth() const;
        int GetTileHeight() const;
    
    private:
        GameObject tileSetGo;
        Sprite tileSet;
        int rows, columns, tileWidth, tileHeight;
};

#endif