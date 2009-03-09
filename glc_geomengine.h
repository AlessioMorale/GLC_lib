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

//! \file glc_geomengine.h Interface for the GLC_GeomEngine class.

#ifndef GLC_GEOMENGINE_H_
#define GLC_GEOMENGINE_H_

#include "glc_ext.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//////////////////////////////////////////////////////////////////////
//! \class GLC_GeomEngine
/*! \brief GLC_GeomEngine : Parent class for all specialized engine
 */

/*! GLC_GeomEngine is a abstract class. \n \n
 *  Main attributes of GLC_GeomEngine:
 *		- Material : 	GLC_Material
 * 		- Graphic properties
 * 		- Transformation Matrix
 *
 * GLC_GeomEngine provide :
 * 		- Function to create VBO : GLC_GeomEngine::createVbo
 *
 */
//////////////////////////////////////////////////////////////////////
class GLC_GeomEngine
{
public:
	//! Default constructor
	GLC_GeomEngine();

	//! Copy constructor
	GLC_GeomEngine(const GLC_GeomEngine&);

	//! Destructor
	virtual ~GLC_GeomEngine();

//////////////////////////////////////////////////////////////////////
/*! \name OpenGL Functions*/
//@{
//////////////////////////////////////////////////////////////////////
public:
	//! Vbo creation
	virtual void createVBOs()= 0;

	//! Vbo Usage
	virtual void useVBOs(bool)= 0;
//@}

//////////////////////////////////////////////////////////////////////
// Protected members
//////////////////////////////////////////////////////////////////////
protected:
	//! VBO ID
	GLuint m_VboId;

};

#endif /* GLC_GEOMENGINE_H_ */
