﻿#pragma once
#include "..\myEngine_API.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
namespace DoMaRe{
	class Renderer;
	class MYENGINE_API Camera{
public:
        Camera();
		bool Init(Renderer* pkRenderer);
        ~Camera();
protected:
        Renderer* m_pkRenderer;
        D3DXVECTOR3 m_Position;
        D3DXVECTOR3 m_LookAt;
        D3DXVECTOR3 m_Right;
        D3DXVECTOR3 m_Up;
        bool m_bChanged;
        float m_RotateAroundUp;
        float m_RotateAroundRight;
        float m_RotateAroundLookAt;
        D3DXMATRIX m_MatView;
public:
        void SetPosition(float fX, float fY, float fZ);
        void MoveForward(float Dist);
        void MoveRight(float Dist);
        void MoveUp(float Dist);
        void MoveInDirection(float Dist, float fDirectionX, float fDirectionY, float fDirectionZ);
        void RotateDown(float Angle);
        void RotateRight(float Angle);
        void Roll(float Angle);
protected:
        void Update();

		friend class Engine;
	};
}