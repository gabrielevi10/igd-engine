#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "GameObject.h"
#include "TileSet.h"
#include "Component.h"

class TileMap : public Component {
    public:
        TileMap(GameObject& associated, const std::string& file, std::shared_ptr<TileSet> tileSet);

        void Load(const std::string& file);
        void SetTileSet(std::shared_ptr<TileSet> tileSet);
        int& At(int x, int y, int z = 0);
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        int GetWidth() const;
        int GetHeight() const;
        int GetDepth() const;

        void Render();
        void Update(float dt);
        bool Is(const std::string& type) const;

    private:
        std::vector<int> tileMatrix;
        std::shared_ptr<TileSet> tileSet;
        int mapWidth, mapHeight, mapDepth;
};

#endif