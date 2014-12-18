#ifndef CSE167_ANIMATION_H_
#define CSE167_ANIMATION_H_

class Sword;

class Animation
{
    protected:
        Sword * sword_; 
        bool stop_;

    public:
        Animation();
        Animation(Sword * sword);

        virtual bool update(int ticks);
        virtual void stop();

};

#endif
