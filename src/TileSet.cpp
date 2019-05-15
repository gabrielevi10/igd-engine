#include "TileSet.h"

#include <iostream>

TileSet::TileSet(uint32_t tileWidth, uint32_t tileHeight, const std::string& file) : 
    tileSet(tileSetGo, file), 
    tileWidth(tileWidth), 
    tileHeight(tileHeight) {
    
    rows = tileSet.GetHeight()/tileHeight;
    columns = tileSet.GetWidth()/tileWidth;
}

void TileSet::RenderTile(uint32_t index, double x, double y) {
    int cx, cy;
    if (index < columns*rows - 1) {
        cx = index % columns;
        cy = index / columns;
        tileSet.SetClip(cx * tileWidth, cy * tileHeight, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

uint32_t TileSet::GetTileWidth() const {
    return tileWidth;
}

uint32_t TileSet::GetTileHeight() const {
    return tileHeight;
}