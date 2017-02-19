#pragma once

#include "OverPassPrerequisites.h"
#include "OverPassRenderSystem.h"
#include <d3d9.h>
#include <d3dx9.h>
namespace OverPass
{
	class DX9RenderSystem:public RenderSystem
	{
	public:
		LPDIRECT3DDEVICE9 mDevice;
		ID3DXEffect* mEffect;

		D3DXMATRIX mProjMatrix;
		D3DXMATRIX mViewMatrix;
		D3DXMATRIX mWorldMatrix;

		ID3DXMesh *meshBox;
		ID3DXMesh *meshTeapot;
		DX9RenderSystem(LPDIRECT3DDEVICE9  device, ID3DXEffect* effect);
		virtual ~DX9RenderSystem();
		void _setWorldMatrix(const Matrix4 &m) ;
		void _setViewMatrix(const Matrix4 &m) ;
		void _setProjectionMatrix(const Matrix4 &m);
		void _setWorldMatrix(Vector3 pos);

		void _beginFrame(void);
		void _endFrame(void);
		 void _render(const RenderOperation& op);
		 void _beginGeometryCount(void) {}
		 void _setProjectionMatrix(void) {}
		 void shutdown(void) {}
	};
}