#ifndef OSUTILS_H
#define OSUTILS_H

#include <qglobal.h>

#if defined(Q_OS_WIN)

#include "winutils/WinUtils.h"
#define osUtils static_cast<OSUtilsBase*>(winUtils())

#elif defined(Q_OS_MACOS)

// No macOS implementation yet

#elif defined(Q_OS_UNIX)

// No Linux implementation yet

#endif

#endif // OSUTILS_H
