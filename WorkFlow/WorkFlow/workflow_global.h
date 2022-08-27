#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(WORKFLOW_LIB)
#  define WORKFLOW_EXPORT Q_DECL_EXPORT
# else
#  define WORKFLOW_EXPORT Q_DECL_IMPORT
# endif
#else
# define WORKFLOW_EXPORT
#endif
