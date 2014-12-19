#include "animation.h"

Animation::Animation()
{
    stop_ = false;
    pause_ = false;
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

void Animation::toggle_pause()
{
    pause_ = !pause_;
}
