#ifndef GLDMASK_GLOBAL_H
#define GLDMASK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GLDMASK_LIBRARY)
#  define GLDMASKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GLDMASKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GLDMASK_GLOBAL_H
