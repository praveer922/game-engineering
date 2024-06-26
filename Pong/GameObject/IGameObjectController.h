#pragma once


struct GameObject;

class IGameObjectController {
public:
    virtual ~IGameObjectController() {}

    virtual void update(GameObject& gameObject, float dt) = 0; // Pure virtual function for updating the controller
};