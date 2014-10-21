#include <chrono>
#include "timer.h"

Timer::Timer()
{
    // Initialize the variables
    start_ticks_ = 0;
    paused_ticks_ = 0;
    paused_ = false;
    started_ = false;
}

void Timer::start()
{
    // Start the timer
    started_ = true;

    // Unpause the timer
    paused_ = false;

    // Get the current clock time
    start_ticks_ = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}

void Timer::stop()
{
    // Stop the timer
    started_ = false;

    // Unpause the timer
    paused_ = false;
}

void Timer::pause()
{
    // If the timer is running and isn't already paused_
    if((started_ == true) && (paused_ == false)) {
        // Pause the timer
        paused_ = true;

        // Calculate the paused_ ticks
        paused_ticks_ = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count() - start_ticks_;

    }
}

void Timer::unpause()
{
    // If the timer is paused_
    if(paused_ == true) {
        // Unpause the timer
        paused_ = false;

        // Reset the starting ticks
        start_ticks_ = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count() - paused_ticks_;

        // Reset the paused_ ticks
        paused_ticks_ = 0;
    }
}

int Timer::get_ticks()
{
    // If the timer is running
    if(started_ == true) {
        // If the timer is paused_
        if(paused_ == true) {
            // Return the number of ticks when the timer was paused_
            return paused_ticks_;
        }
        else {
            // Return the current time minus the start time
            return std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count() - start_ticks_;
        }
    }

    // If the timer isn't running
    return 0;
}