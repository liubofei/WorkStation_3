#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(XMESSAGEBOX_LIB)
#  define XMESSAGEBOX_EXPORT Q_DECL_EXPORT
# else
#  define XMESSAGEBOX_EXPORT Q_DECL_IMPORT
# endif
#else
# define XMESSAGEBOX_EXPORT
#endif
