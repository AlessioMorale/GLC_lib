/****************************************************************************

 This file is part of the GLC-lib library.
 Copyright (C) 2005-2008 Laurent Ribon (laumaya@users.sourceforge.net)
 Version 0.9.9, packaged on May, 2008.

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

//! \file glc_geomtools.h declaration of geometry tools functions

#ifndef GLC_GEOMTOOLS_H_
#define GLC_GEOMTOOLS_H_

#include <QVector>
#include <QList>

#include "glc_mesh2.h"

namespace glc
{

//////////////////////////////////////////////////////////////////////
/*! \name Tools Functions*/
//@{
//////////////////////////////////////////////////////////////////////
	//! test if a polygon of mesh is convex
	/*! The polygon must have mare than 3 vertexs */
	bool polygonIsConvex(const GLC_Mesh2*, const QVector<int>&);
	
	//! find intersection between two 2D segments
	/*! Return the intersection as QVector of GLC_Vector2d
	 *  - Empty QVector if there is no intersection
	 *  - Qvector size 1 if there is a unique intersection
	 *  - Qvector size 2 if the segement overlap*/
	QVector<GLC_Vector2d> findIntersection(const GLC_Vector2d&, const GLC_Vector2d&, const GLC_Vector2d&, const GLC_Vector2d&);
	
	//! return true if there is an intersection between 2 segments
	bool isIntersected(const GLC_Vector2d&, const GLC_Vector2d&, const GLC_Vector2d&, const GLC_Vector2d&);

	//! return true if there is an intersection between a ray and a segment
	bool isIntersectedRaySegment(const GLC_Vector2d&, const GLC_Vector2d&, const GLC_Vector2d&, const GLC_Vector2d&);

	//! find intersection of two intervals [u0, u1] and [v0, v1]
	/*! Return the intersection as QVector of GLC_Vector2d
	 *  - Empty QVector if there is no intersection
	 *  - Qvector size 1 if there is a unique intersection
	 *  - Qvector size 2 if the segement overlap*/
	QVector<double> findIntersection(const double&, const double&, const double&, const double&);
	
	//! return true if the segment is in polygon cone
	bool segmentInCone(const GLC_Vector2d&, const GLC_Vector2d&, const GLC_Vector2d&, const GLC_Vector2d&);
	
	//! Return true if the segment is a polygon diagonal
	bool isDiagonal(const QList<GLC_Vector2d>&, const int, const int);
	
	//! Triangulate a polygon
	void triangulate(QList<GLC_Vector2d>&, QList<int>&, QList<int>&);
	
	//! Triangulate polygon wich vertices are in a mesh
	QVector<int> triangulateMeshPoly(const GLC_Mesh2*, QVector<int>);
	
	//! return true if the polygon is couterclockwise ordered
	bool isCounterclockwiseOrdered(const QList<GLC_Vector2d>&);

//@}
	
};

#endif /*GLC_GEOMTOOLS_H_*/