#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SYSTEM_LIB)
#  define SYSTEM_EXPORT Q_DECL_EXPORT
# else
#  define SYSTEM_EXPORT Q_DECL_IMPORT
# endif
#else
# define SYSTEM_EXPORT
#endif
