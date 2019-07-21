#ifndef TIMER_H
#define TIMER_H

#include<thread>
#include<chrono>

class Timer
{
    std::thread Thread; //thread for asynchronous execution without blocking the main thread
    bool Alive = false; //to check the state of the timer
    long CallNumber = -1L; //determines how many times we would like to call a certain function
    long repeat_count = -1L; //tells how many times a certain function has already been called
    std::chrono::milliseconds interval = std::chrono::milliseconds(0); //interval between function calls
    std::function<void(void)> funct = nullptr; //similar to pointer to a fxn , accepts a function that takes nothing and returns nothing

    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval); //block the thread for certain time interval
        if(Alive)
            Function()(); //second () calls the function that this fxn returns

    }

    void ThreadFunc()
    {
        if(CallNumber == Infinite)
            while(Alive)
                SleepAndRun();
        else
            while(repeat_count--)
                SleepAndRun();
    }

public:
    static const long Infinite = -1L; //state that the fxn will be called infinte no of times so the timer would work until we stop it in a manual fashion.

    Timer() {}

    Timer(const std::function<void(void)> &f) : funct (f) {}

    Timer(const std::function<void(void)> &f,
          const unsigned long &i,
          const long repeat = Timer::Infinite) : funct(f),
                                                 interval(std::chrono::milliseconds(i)),
                                                 CallNumber(repeat) {}
    //for starting the timer
    void Start(bool Async = true)
    {
        if(IsAlive())
            return;
        Alive = true;
        repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc, this);
        else
            this->ThreadFunc(); //to block the main thread
    }

    void Stop()
    {
        Alive = false;
        Thread.join();  //joins the threads,no concurrent execution only main thread


    }

    void SetFunction(const std::function<void(void)> &f)
    {
        funct = f;
    }

    bool IsAlive() const {return Alive;}

    void RepeatCount(const long r)
    {
        if(Alive)
            return;
        CallNumber = r;
    }

    long GetLeftCount() const {return repeat_count;}

    long RepeatCount() const {return CallNumber;}

    void SetInterval(const unsigned long &i)
    {
        if(Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }

    unsigned long Interval() const {return interval.count();}

    const std::function<void(void)> &Function() const
    {
        return funct;
    }

};


#endif // TIMER_H
