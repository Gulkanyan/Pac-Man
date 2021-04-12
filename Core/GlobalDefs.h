#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H
#include <QtDebug>

#endif // GLOBALDEFS_H

// For enabling/disabling debug mode (For disable comment the definition of DEBUG_UTILS
#define DEBUG_UTILS

#ifdef DEBUG_UTILS
    #define DEBUG_LOG qDebug() << __func__ << " " << __LINE__;
#endif
