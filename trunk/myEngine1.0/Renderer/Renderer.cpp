#pragma once
#include "Renderer.h"
using namespace DoMaRe;
Renderer::Renderer():
d3d(NULL),
d3d_dev(NULL),
p_vb(NULL),
p_vbT(NULL)
{
	// Again, Nothing to do.
}

Renderer::~Renderer(){


	if(p_vb){
	delete p_vb;
	p_vb = NULL;
	}

	if(p_vbT){
	delete p_vbT;
	p_vbT = NULL;
	}
	if(d3d_dev){
	d3d_dev->Release();
	d3d_dev = NULL;
	}

	if(d3d){
	d3d->Release();
	d3d = NULL;
	}

	Clear();
}
void Renderer::Clear(){
	
	for(std::vector<Texture>::iterator it = r_vTextures.begin(); it != r_vTextures.end(); it++){
		(*it)->Release();
		(*it) = NULL;
	}

	r_vTextures.clear();

}

bool Renderer::Init(HWND _HwnD){
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = _HwnD;
	if(d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _HwnD, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3d_dev) == D3D_OK){
		d3d_dev->SetRenderState(D3DRS_LIGHTING,FALSE);
		d3d_dev->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
		
		d3d_dev->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		d3d_dev->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		d3d_dev->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		d3d_dev->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

		D3DVIEWPORT9 kViewport;
		d3d_dev->GetViewport(&kViewport);

		float fViewPortWidth = static_cast<float>(kViewport.Width);
		float fViewPortHeight = static_cast<float>(kViewport.Height);
		
		D3DXMATRIX projectionMatrix;
		D3DXMatrixOrthoLH(&projectionMatrix,fViewPortWidth,fViewPortHeight, -1.0f, 1.0f);
		d3d_dev->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

		p_vb = new DoMaRe::VertexBuffer(d3d_dev, sizeof(DoMaRe::ColorVertex), DoMaRe::ColorVertexType);
		p_vbT = new DoMaRe::VertexBuffer(d3d_dev, sizeof(DoMaRe::TexCoordVertex), DoMaRe::TexCoordVertexType);
		return true;
	}
	return false;
}

void Renderer::BeginFrame(){
	d3d_dev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0);
	d3d_dev->BeginScene();
}

void Renderer::EndFrame(){
	p_vb->flush();
	d3d_dev->EndScene();
	d3d_dev->Present(NULL,NULL,NULL,NULL);
}


D3DPRIMITIVETYPE primitiveMap[DoMaRe::PrimitiveCount] = {
        D3DPT_TRIANGLELIST, 
        D3DPT_TRIANGLESTRIP,
        D3DPT_POINTLIST,
        D3DPT_LINELIST,     
        D3DPT_LINESTRIP,
        D3DPT_TRIANGLEFAN
};

D3DTRANSFORMSTATETYPE MatrixTypeMapping[MatrixTypeCount] ={
 D3DTS_VIEW,
 D3DTS_PROJECTION,
 D3DTS_WORLD
};

void Renderer::setMatrix(MatrixType matrixType, const Matrix& matrix){
	d3d_dev->SetTransform(MatrixTypeMapping[matrixType], matrix);
}

const Texture Renderer::loadTexture(const std::string& Fname, int KeyCode){
	IDirect3DTexture9* p_Texture = NULL;
	HRESULT HR = D3DXCreateTextureFromFileEx(d3d_dev,
											Fname.c_str(),
											0,0,0,0,
											D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
											D3DX_FILTER_NONE, D3DX_FILTER_NONE,
											KeyCode,
											NULL,
											NULL,
											&p_Texture);
	if(HR != D3D_OK){
		return NoTexture;
	}
	else{
		r_vTextures.push_back(p_Texture);
		return p_Texture;
	}
}

void Renderer::Draw(ColorVertex* v, DoMaRe::Primitive p, size_t vC){
	p_vb->bind();
	p_vb->draw(v,primitiveMap[p], vC);
}

void Renderer::Draw(TexCoordVertex* v, DoMaRe::Primitive p, size_t vC){
	p_vbT->bind();
	p_vbT->draw(v,primitiveMap[p], vC);
}

void Renderer::setCurrentTexture(const Texture& r_Texture){
	d3d_dev->SetTexture(0,r_Texture);
}