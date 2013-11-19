/*
 * glc_declarativeview.h
 *
 *  Created on: 22/04/2013
 *      Author: laumaya
 */

#ifndef GLC_DECLARATIVEVIEW_H
#define GLC_DECLARATIVEVIEW_H

#include <QQuickView>

class GLC_QuickView : public QQuickView
{
public:
    GLC_QuickView(QWindow* pParent= NULL);
};

#endif // GLC_DECLARATIVEVIEW_H
