#pragma once

#include "Actor.h"

namespace GE
{
    class QuadActor : public Actor
    {
    public:
        QuadActor();
        ~QuadActor() = default;

        virtual void Tick(float deltaTime) override;
    };
}