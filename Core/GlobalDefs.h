#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H
#include <QtDebug>

// For enabling/disabling debug mode (For disable comment the definition of DEBUG_UTILS
#define DEBUG_UTILS

#ifdef DEBUG_UTILS
    #define DEBUG_LOG qDebug() << __func__ << " " << __LINE__;
#endif

#define DEFAULT_BLOCK_SIZE 25

#define PLAYER_TIMER_DEF_TIMEOUT 100

#define ENEMYS_TIMER_DEF_TIMEOUT 150

#endif // GLOBALDEFS_H
