#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>
#include "GameObject.h"

class State {
    public:
        State();
        virtual ~State();

        virtual void LoadAssets() = 0;
        virtual void Update(double dt) = 0;
        virtual void Render() = 0;

        virtual void Start() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
        virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object) const;

        bool PopRequested() const;
        bool QuitRequested() const;

    protected:
        virtual void StartArray();
        virtual void UpdateArray(double dt);
        virtual void RenderArray();

        bool popRequested, quitRequested, started;
        std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif