#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(UTILITY_LIB)
#  define UTILITY_EXPORT Q_DECL_EXPORT
# else
#  define UTILITY_EXPORT Q_DECL_IMPORT
# endif
#else
# define UTILITY_EXPORT
#endif
