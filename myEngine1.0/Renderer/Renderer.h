#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "../VertexBuffer/VertexBuffer.h"
#include "../myEngine_API.h"
#include "RenderTypes.h"
#include "EMath.h"
#include <d3d9.h>
namespace DoMaRe{/*
class VertexBuffer;
struct ColorVertex;
struct TexCoordVertex;*/
class MYENGINE_API Renderer{
	public:
		Renderer();
		~Renderer();
		bool Init(HWND _HwnD);
		void BeginFrame();
		void EndFrame();
		void setMatrix(MatrixType, const Matrix&);
		void Draw(ColorVertex*, DoMaRe::Primitive, size_t);
		void Draw(TexCoordVertex*, DoMaRe::Primitive, size_t);
		void Clear();
		const Texture loadTexture (const std::string& Fname, int KeyCode);
		void setCurrentTexture (const Texture& r_Texture);
	private:
		IDirect3D9  * d3d;
		IDirect3DDevice9  * d3d_dev;
		DoMaRe::VertexBuffer * p_vb;
		DoMaRe::VertexBuffer * p_vbT;
		std::vector<Texture> r_vTextures;
};
}