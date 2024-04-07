#ifndef WIDGETCAD_GLOBAL_H
#define WIDGETCAD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WIDGETCAD_LIBRARY)
#define WIDGETCAD_EXPORT Q_DECL_EXPORT
#else
#define WIDGETCAD_EXPORT Q_DECL_IMPORT
#endif

#endif // WIDGETCAD_GLOBAL_H
