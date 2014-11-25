#pragma once
#include "Renderer.h"
using namespace DoMaRe;
Renderer::Renderer():
d3d(NULL),
d3d_dev(NULL),
p_vb(NULL),
p_vbT(NULL),
p_vb3D(NULL),
wireFrameMode(false),
m_pkProjectionMatrix( new D3DXMATRIX() ),
p_ib(NULL)
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

	if(m_pkProjectionMatrix){
	delete m_pkProjectionMatrix;
	m_pkProjectionMatrix = NULL;
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

	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = _HwnD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;  // HAGAMOS 2500 FRAMES, PORQUE PODEMOS.

	if(d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _HwnD, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3d_dev) == D3D_OK){
		d3d_dev->SetRenderState(D3DRS_LIGHTING,FALSE);
		d3d_dev->SetRenderState(D3DRS_ZENABLE, TRUE);

		//d3d_dev->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);

		
		/*d3d_dev->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		d3d_dev->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		d3d_dev->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		d3d_dev->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);*/

		//d3d_dev->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

		D3DVIEWPORT9 kViewport;
		d3d_dev->GetViewport(&kViewport);

		float fViewPortWidth = static_cast<float>(kViewport.Width);
		float fViewPortHeight = static_cast<float>(kViewport.Height);
		
		//D3DXMATRIX projectionMatrix;
		D3DXMatrixPerspectiveFovLH(m_pkProjectionMatrix, D3DXToRadian(90), fViewPortWidth / fViewPortHeight, 1, 3000);

		//D3DXMatrixOrthoLH(&projectionMatrix,fViewPortWidth,fViewPortHeight, -1.0f, 1.0f);
		d3d_dev->SetTransform(D3DTS_PROJECTION, m_pkProjectionMatrix);

		D3DXVECTOR3 kPos(0.0f, 0.0f, -1000.0f);
        D3DXVECTOR3 kLook(0.0f, 0.0f, 1.0f);
        D3DXVECTOR3 kUp(0.0f, 1.0f, 0.0f);

		SetCamera(kPos, kLook, kUp);

	//	p_vb = new DoMaRe::VertexBuffer(d3d_dev, sizeof(DoMaRe::ColorVertex), DoMaRe::ColorVertexType);
	//	p_vbT = new DoMaRe::VertexBuffer(d3d_dev, sizeof(DoMaRe::TexCoordVertex), DoMaRe::TexCoordVertexType);
		return true;
	}
	return false;
}

void Renderer::setWireFrameMode(bool theMode){
	if(theMode == true){
		d3d_dev->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	}else{
		d3d_dev->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	}

	wireFrameMode = theMode;
}
void Renderer::BeginFrame(){
	d3d_dev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	d3d_dev->BeginScene();
}

void Renderer::SetCamera(D3DXVECTOR3 kViewerPos, D3DXVECTOR3 kLookPos, D3DXVECTOR3 kViewerUp){

		D3DXMATRIX kMatrix;

        D3DXMatrixLookAtLH(&kMatrix, &kViewerPos, &kLookPos, &kViewerUp);
        d3d_dev->SetTransform(D3DTS_VIEW, &kMatrix);

}

void Renderer::SetCamera(D3DXMATRIX * matrix){

	d3d_dev->SetTransform(D3DTS_VIEW,matrix);

}

void Renderer::setTransformMatrix(D3DXMATRIX* kMatrix){
	    // set the matrix
        d3d_dev->MultiplyTransform(D3DTS_VIEW, kMatrix);
}


void Renderer::loadIdentity(){
	D3DXMATRIX kTempMatrix;

        // set identity matrix
    D3DXMatrixIdentity(&kTempMatrix);

        // if it is a view matrix, use default values

                
    D3DXVECTOR3 kEyePos(0,0,-1);
    D3DXVECTOR3 kLookPos(0,0,0);
    D3DXVECTOR3 kUpVector(0,1,0);
                
                // generate the view matrix
    D3DXMatrixLookAtLH(&kTempMatrix, &kEyePos, &kLookPos, &kUpVector);
        
        // set the matrix
    d3d_dev->SetTransform(D3DTS_VIEW, &kTempMatrix);
}

void Renderer::EndFrame(){
	//p_vb->flush();
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

const Texture Renderer::loadTexture(const std::string& Fname){
	IDirect3DTexture9* p_Texture = NULL;
	HRESULT HR = D3DXCreateTextureFromFileEx(d3d_dev,
											Fname.c_str(),
											0,0,0,0,
											D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
											D3DX_FILTER_NONE, D3DX_FILTER_NONE,
											0,
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

void Renderer::Draw(DoMaRe::Primitive p){
	int ThePrimitive = 0;
    D3DPRIMITIVETYPE pTipe = primitiveMap[p];

    if(pTipe == D3DPT_POINTLIST){
		ThePrimitive = p_ib->indexCount();
    }
    else if(pTipe == D3DPT_LINELIST){
		ThePrimitive = p_ib->indexCount() / 2;
    }
    else if(pTipe == D3DPT_LINESTRIP){
		ThePrimitive = p_ib->indexCount() - 1;
    }
    else if(pTipe == D3DPT_TRIANGLELIST){
		ThePrimitive = p_ib->indexCount() / 3;
    }
    else if(pTipe == D3DPT_TRIANGLESTRIP){
		ThePrimitive = p_ib->indexCount() - 2;
    }
    else if(pTipe == D3DPT_TRIANGLEFAN){
		ThePrimitive = p_ib->indexCount() - 2;
    }
	d3d_dev->DrawIndexedPrimitive(primitiveMap[p], 0, 0, p_vb3D->vertexCount(), 0, ThePrimitive);
}
void Renderer::setCurrentTexture(const Texture& r_Texture){
	d3d_dev->SetTexture(0,r_Texture);
}

void Renderer::setCurrentVertexBuffer(VertexBuffer3D * c_vb3D){
	p_vb3D = c_vb3D;
}

void Renderer::setCurrentIndexBuffer(IndexBuffer * c_ib){
	p_ib = c_ib;
}

VertexBuffer3D* Renderer::createVB(size_t vSize, unsigned int FVF){
	return new VertexBuffer3D(*this,d3d_dev,vSize,FVF);
}

IndexBuffer* Renderer::createIB(){
	return new IndexBuffer(*this,d3d_dev);
}

const Matrix&	Renderer::projectionMatrix() const{
	return m_pkProjectionMatrix;
}