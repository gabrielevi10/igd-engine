#include "TileSet.h"

TileSet::TileSet(const int& tw, const int& th, const std::string& file) : tileSet(tileSetGo, file), tileWidth(tw), tileHeight(th) {
    rows = tileSet.GetHeight()/tileHeight;
    columns = tileSet.GetWidth()/tileWidth;
}

void TileSet::RenderTile(uint32_t index, float x, float y) {
    if (index >= 0 && index < columns*rows - 1) {
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth() const {
    return tileWidth;
}

int TileSet::GetTileHeight() const {
    return tileHeight;
}