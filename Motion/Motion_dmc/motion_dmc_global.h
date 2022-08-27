#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MOTION_DMC_LIB)
#  define MOTION_DMC_EXPORT Q_DECL_EXPORT
# else
#  define MOTION_DMC_EXPORT Q_DECL_IMPORT
# endif
#else
# define MOTION_DMC_EXPORT
#endif
