/**
 * \file timer.h
 * \brief a timer class
 */
#ifndef IVL_TIMER_H
#define IVL_TIMER_H

#ifdef WIN32   // Windows system specific
#include <windows.h>
#else          // Unix based system specific
#include <sys/time.h>
#endif

namespace ivllib{

  /** \addtogroup misc */
  /*@{*/
  
  /// A timer.
  class Timer
  {
  public:
    /// default constructor
    Timer();

    /// default destructor
    ~Timer();

    /// start timer
    void start();

    /// stop the timer
    void stop();

    /// get elapsed time in seconds
    double getElapsedTime();

    /// get elapsed time in second (same as getElapsedTime)
    double getElapsedTimeInSec();

    /// get elapsed time in milli-second
    double getElapsedTimeInMilliSec();

    /// get elapsed time in micro-second
    double getElapsedTimeInMicroSec();

  private:
    double startTimeInMicroSec;                 // starting time in micro-second
    double endTimeInMicroSec;                   // ending time in micro-second
    int    stopped;                             // stop flag
#ifdef WIN32
    LARGE_INTEGER frequency;                    // ticks per second
    LARGE_INTEGER startCount;                   //
    LARGE_INTEGER endCount;                     //
#else
    timeval startCount;                         //
    timeval endCount;                           //
#endif
  };  // class Timer
  /*@}*/

}  // namespace ivllib

#endif // IVL_TIMER_H
