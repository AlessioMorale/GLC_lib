/*
 * glc_declarativeview.h
 *
 *  Created on: 22/04/2013
 *      Author: laumaya
 */

#ifndef GLC_DECLARATIVEVIEW_H
#define GLC_DECLARATIVEVIEW_H

#include <QQuickView>

class GLC_DeclarativeView : public QQuickView
{
public:
    GLC_DeclarativeView(QWindow* pParent= NULL);
};

#endif // GLC_DECLARATIVEVIEW_H
