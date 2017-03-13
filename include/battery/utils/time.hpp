#ifndef __UTILS_TIME_HPP__
#define __UTILS_TIME_HPP__

#include <sys/time.h>
#include <time.h>

namespace battery {

void tic(struct timespec *tic);
float toc(struct timespec *tic);
float mtoc(struct timespec *tic);
double time_now(void);

} // end of battery namespace
#endif
