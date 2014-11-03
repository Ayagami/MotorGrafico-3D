#include "Quad.h"
#include "Entity2D.h"
#include "..\Renderer\Renderer.h"
#include <d3dx9.h>
using namespace DoMaRe;

Quad::Quad():
Entity2D(),
_Vertex( new ColorVertex[4]){

_Vertex[0].x = -0.5f; _Vertex[0].y = 0.5f; _Vertex[0].z = 0.0f;
_Vertex[1].x = 0.5f; _Vertex[1].y = 0.5f; _Vertex[1].z = 0.0f;
_Vertex[2].x = -0.5f; _Vertex[2].y = -0.5f; _Vertex[2].z = 0.0f;
_Vertex[3].x = 0.5f; _Vertex[3].y = -0.5f; _Vertex[3].z = 0.0f;


// Setting the default Color (255,0,0)
_Vertex[0].color = DoMaRe_COLOR_RGB(255,0,0);
_Vertex[1].color = DoMaRe_COLOR_RGB(255,0,0);
_Vertex[2].color = DoMaRe_COLOR_RGB(255,0,0);
_Vertex[3].color = DoMaRe_COLOR_RGB(255,0,0);

updateLocalTransformation();
}

Quad::~Quad(){
	delete[] _Vertex;
	_Vertex = NULL;
}

void Quad::setColor(DWORD c){
	for(int i = 0; i < 4; i++)
		_Vertex[i].color = c;
}

void Quad::setColor(DWORD c, int v){
	if(v >= 0 && v < 4)
		_Vertex[v].color = c;
}

void Quad::draw(Renderer& r) const{
	r.setCurrentTexture(NoTexture);
	r.setMatrix(World, _TrMatrix );
	r.Draw(_Vertex, DoMaRe::TriangleStrip, 4);
}
