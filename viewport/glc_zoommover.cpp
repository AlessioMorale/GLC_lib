/****************************************************************************

 This file is part of the GLC-lib library.
 Copyright (C) 2005-2008 Laurent Ribon (laumaya@users.sourceforge.net)
 Version 1.1.0, packaged on March, 2009.

 http://glc-lib.sourceforge.net

 GLC-lib is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 GLC-lib is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with GLC-lib; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

 *****************************************************************************/

#include "glc_zoommover.h"
#include "glc_viewport.h"

// Default constructor
GLC_ZoomMover::GLC_ZoomMover(GLC_Viewport* pViewport, const QList<GLC_RepMover*>& repsList)
: GLC_Mover(pViewport, repsList)
, m_MaxZoomFactor(3.0)
{

}

// Copy constructor
GLC_ZoomMover::GLC_ZoomMover(const GLC_ZoomMover& mover)
: GLC_Mover(mover)
, m_MaxZoomFactor(mover.m_MaxZoomFactor)
{

}

GLC_ZoomMover::~GLC_ZoomMover()
{

}


//////////////////////////////////////////////////////////////////////
// Get Functions
//////////////////////////////////////////////////////////////////////

// Return a clone of the mover
GLC_Mover* GLC_ZoomMover::clone() const
{
	return new GLC_ZoomMover(*this);
}

//////////////////////////////////////////////////////////////////////
// Set Functions
//////////////////////////////////////////////////////////////////////

// Initialized the mover
void GLC_ZoomMover::init(int, int y)
{
	// Change origine (view center) and cover between -1 and 1
	const double vSize= static_cast<double>(m_pViewport->getWinVSize());
	m_PreviousVector.setY((vSize / 2.0 - y) / ( vSize / 2.0));
}

// Move the camera
void GLC_ZoomMover::move(int, int y)
{
	// Change origine (View Center) and cover (from -1 to 1)
	const double vSize= static_cast<double>(m_pViewport->getWinVSize());
	const double Posy= (vSize / 2.0 - y) / ( vSize / 2.0);

	// Compute zoom factor between (1 / MAXZOOMFACTOR) and (MAXZOOMFACTOR)
	double ZoomFactor= Posy - m_PreviousVector.Y();

	if (ZoomFactor > 0)
	{
		ZoomFactor= (m_MaxZoomFactor - 1.0) * ZoomFactor + 1.0;
	}
	else
	{
		ZoomFactor= 1.0 / ( (m_MaxZoomFactor - 1.0) * fabs(ZoomFactor) + 1.0 );
	}

	m_pViewport->cameraHandle()->zoom(ZoomFactor);

	m_PreviousVector.setY(Posy);
}