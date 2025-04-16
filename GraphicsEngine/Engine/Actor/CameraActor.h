#pragma once

#include "Actor.h"
namespace GE
{
    class CameraActor : public Actor
    {
    public:
        CameraActor();

        virtual void Tick(float deltaTime) override;

    private:
        void Move(float deltaTime);
        void Rotate();
        
    };
}

