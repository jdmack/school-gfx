#ifndef CSE167_TIMER_H_ 
#define CSE167_TIMER_H_

class Timer
{
    private:
        unsigned long start_ticks_;
        unsigned long paused_ticks_;
        bool paused_;
        bool started_;

    public:
        Timer();

        void start();
        void stop();
        void pause();
        void unpause();
        int get_ticks();

        // accessors
        bool started() const { return started_; }
        bool paused() const { return paused_; }
};

#endif
