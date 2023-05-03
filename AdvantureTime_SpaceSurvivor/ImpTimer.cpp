#include "ImpTimer.h"
#include "CommonFunc.h"

ImpTimer::ImpTimer()
{
    startTick_ = 0;
    pausedTick_ = 0;
    isPaused_ = false;
    isStarted_ = false;
}

void ImpTimer::Start()
{
    isStarted_ = true;
    isPaused_ = false;
    startTick_ = SDL_GetTicks();
}

void ImpTimer::Stop()
{
    isStarted_ = false;
    isPaused_ = false;
}

void ImpTimer::Pause()
{
    if ((isStarted_ == true) && (isPaused_ == false))
    {
        isPaused_ = true;
        pausedTick_ = SDL_GetTicks() - startTick_;
    }
}

void ImpTimer::Unpause()
{
    if (isPaused_ == true)
    {
        isPaused_ = false;
        //Reset the starting ticks
        startTick_ = SDL_GetTicks() - pausedTick_;
        //Reset the paused ticks
        pausedTick_ = 0;
    }
}

int ImpTimer::GetTicks()
{
    if (isStarted_ == true)
    {
        //If the timer is paused
        if (isPaused_ == true)
        {
            return pausedTick_;
        }
        else
        {
            return SDL_GetTicks() - startTick_;
        }
    }

    //If the timer isn't running
    return 0;
}

bool ImpTimer::IsStarted()
{
    return isStarted_;
}

bool ImpTimer::IsPaused()
{
    return isPaused_;
}