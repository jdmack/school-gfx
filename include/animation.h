#ifndef CSE167_ANIMATION_H_
#define CSE167_ANIMATION_H_

class Sword;

class Animation
{
    protected:
        Sword * sword_; 
        bool stop_;
        bool pause_;

    public:
        Animation();
        Animation(Sword * sword);

        void toggle_pause();

        virtual bool update(int ticks);
        virtual void stop();


};

#endif
