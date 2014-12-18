#include "animation.h"

Animation::Animation()
{
    stop_ = false;
}

Animation::Animation(Sword * sword) : Animation()
{
    sword_ = sword;
}

bool Animation::update(int ticks)
{
    return false;
}

void Animation::stop()
{
    stop_ = true;
}
