#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "../myEngine_API.h"

namespace DoMaRe{
	struct MYENGINE_API ColorVertex{
		float x,y,z;
		DWORD color;
	};
	
	extern const DWORD ColorVertexType;

	struct MYENGINE_API TexCoordVertex{
		float x,y,z;
		float u,v;
	}; 

	extern const int TexCoordVertexType;

	typedef IDirect3DTexture9* Texture;
	static const Texture NoTexture = NULL; 

	enum Primitive{
		TriangleList = 0,
        TriangleStrip,
        PointList,
        LineList,
        LineStrip,
        TriangleFan,
        PrimitiveCount
	};

	enum MatrixType{
		View = 0,
		Projection,
		World,
		MatrixTypeCount
	};
#define DoMaRe_COLOR_ARGB(a,r,g,b)  ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define DoMaRe_COLOR_RGB(r,g,b) DoMaRe_COLOR_ARGB(0xff,r,g,b)
}