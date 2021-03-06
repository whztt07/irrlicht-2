// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_SOFTWARE_TEXTURE_H_INCLUDED__
#define __C_SOFTWARE_TEXTURE_H_INCLUDED__

#include "ITexture.h"
#include "CImage.h"

namespace irr
{
namespace video
{

/*!
	interface for a Video Driver dependent Texture.
*/
class CSoftwareTexture : public ITexture
{
public:

	//! constructor
	CSoftwareTexture(IImage* surface, const io::path& name,
			bool renderTarget=false, void* mipmapData=0);

	//! destructor
	virtual ~CSoftwareTexture();

	//! lock function
	virtual void* lock(E_TEXTURE_LOCK_MODE mode=ETLM_READ_WRITE, u32 mipmapLevel=0) _IRR_OVERRIDE_;

	//! unlock function
	virtual void unlock() _IRR_OVERRIDE_;

	//! returns unoptimized surface
	virtual CImage* getImage();

	//! returns texture surface
	virtual CImage* getTexture();

	//! Regenerates the mip map levels of the texture. Useful after locking and
	//! modifying the texture
	virtual void regenerateMipMapLevels(void* mipmapData=0) _IRR_OVERRIDE_;

private:
	CImage* Image;
	CImage* Texture;
};


} // end namespace video
} // end namespace irr

#endif

