#pragma once
#include "../Renderer/EMath.h"
#include "../Renderer/RenderTypes.h"
#include "Entity2D.h"
#include "../myEngine_API.h"
namespace DoMaRe{
	class Renderer;
	class Timer;
	//class Entity2D;
	class MYENGINE_API Quad : public Entity2D{
	public:	
		Quad();
		~Quad();
	public:
		void setColor(DWORD c);
		void setColor(DWORD c, int v);
		void Update(Timer& t) { }
	public:
		void draw(Renderer& r) const;
	private:
		ColorVertex* _Vertex;
	};
}