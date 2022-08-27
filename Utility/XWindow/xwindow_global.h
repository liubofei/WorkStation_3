#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(XWINDOW_LIB)
#  define XWINDOW_EXPORT Q_DECL_EXPORT
# else
#  define XWINDOW_EXPORT Q_DECL_IMPORT
# endif
#else
# define XWINDOW_EXPORT
#endif
