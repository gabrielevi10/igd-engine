#include <fstream>
#include <iostream>

#include "TileMap.h"
#include "Helpers.h"

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet) : Component(associated), tileSet(tileSet) {
    Load(file);
}

void TileMap::Load(const std::string& file) {
    std::ifstream f(file);
    std::string line;
    std::vector<std::string> splitted_line;
    
    getline(f, line);

    splitted_line = Helpers::Split(line, ',');

    mapWidth = std::stoi(splitted_line[0]);
    mapHeight = std::stoi(splitted_line[1]);
    mapDepth = std::stoi(splitted_line[2]);

    while (getline(f, line)) {
        splitted_line = Helpers::Split(line, ',');
        for (std::string s : splitted_line) {
            if (s.size() != 1) {
                tileMatrix.push_back(std::stoi(s) - 1);
            }
        }
    } 
    f.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[x + mapWidth*y + mapWidth*mapHeight*z];     
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            tileSet->RenderTile(At(i, j, layer), i + 64, j + 64);
        }
    }
}

int TileMap::GetWidth() const {
    return mapWidth;
}

int TileMap::GetHeight() const {
    return mapHeight;
}

int TileMap::GetDepth() const {
    return mapDepth;
}

void TileMap::Render() {
    for (int layer = 0; layer < mapDepth; layer++) {
        RenderLayer(layer);
    }
}

void TileMap::Update(float dt) {}

bool TileMap::Is(const std::string& type) {
    return type == "TileMap";
}