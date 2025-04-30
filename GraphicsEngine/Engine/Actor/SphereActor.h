#pragma once

#include "Actor.h"

namespace GE
{
    class SphereActor : public Actor
    {
    public:
        SphereActor();
        ~SphereActor() = default;

        virtual void Tick(float deltaTime) override;
    };
}