#include "TileSet.h"

#include <iostream>

TileSet::TileSet(const int tileWidth, const int tileHeight, const std::string& file) : tileSet(tileSetGo, file), tileWidth(tileWidth), tileHeight(tileHeight) {
    rows = tileSet.GetHeight()/tileHeight;
    columns = tileSet.GetWidth()/tileWidth;
}

void TileSet::RenderTile(uint32_t index, float x, float y) {
    int cx, cy;
    if (index >= 0 && index < columns*rows - 1) {
        cx = index % columns;
        cy = index / columns;
        tileSet.SetClip(cx * tileWidth, cy * tileHeight, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth() const {
    return tileWidth;
}

int TileSet::GetTileHeight() const {
    return tileHeight;
}