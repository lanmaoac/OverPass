#pragma once
#include "OverPassDX9RenderSystem.h"
#include <d3d9.h>
#include <d3dx9.h>

namespace OverPass
{
	DX9RenderSystem::DX9RenderSystem(LPDIRECT3DDEVICE9  device, ID3DXEffect* effect)
	{
		mDevice = device;
		mEffect = effect;
		D3DXCreateTeapot(mDevice, &meshTeapot, 0);
		D3DXCreateBox(mDevice, 100.0f, 100.0f, 100.0f, &meshBox, 0);
	}
	DX9RenderSystem::~DX9RenderSystem() {}

	void DX9RenderSystem::_setWorldMatrix(const Matrix4 &m)
	{
		mWorldMatrix = D3DXMATRIX(
			m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
			m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
			m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
			m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
	}
	void DX9RenderSystem::_setViewMatrix(const Matrix4 &m)
	{
		mViewMatrix = D3DXMATRIX(
			m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
			m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
			m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
			m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
	}
	void DX9RenderSystem::_setProjectionMatrix(const Matrix4 &m)
	{
		mProjMatrix = D3DXMATRIX(
			m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
			m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
			m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
			m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
	}
	void DX9RenderSystem::_setWorldMatrix(Vector3 pos)
	{
		D3DXMatrixTranslation(&mWorldMatrix, pos.x, pos.y, pos.z);
	}


	void DX9RenderSystem::_beginFrame()
	{
		mDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(100, 255, 255), 1.0f, 0);

		mDevice->BeginScene();
	}
	void DX9RenderSystem::_endFrame()
	{
		mDevice->EndScene();

		mDevice->Present(NULL, NULL, NULL, NULL);
	}

	void DX9RenderSystem::_render(const RenderOperation& op)
	{

		printf("fuckyou\n");
		IDirect3DSurface9* pd3dBackBufferSurface;
		D3DXMATRIX mTrans;
		D3DXMatrixScaling(&mTrans, 10.0f, 10.0f, 10.0f);
		mDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pd3dBackBufferSurface);
		mDevice->SetRenderTarget(0, pd3dBackBufferSurface);
		mDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 120, 1.0f, 0);
		//mEffect->SetTexture("ShaderTexture", DepthScene);
		mEffect->SetTechnique("Common");
		UINT numPasses = 0;
		mEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			mEffect->BeginPass(i);
			D3DXMATRIX now = mTrans* mWorldMatrix *mViewMatrix * mProjMatrix;
			mEffect->SetMatrix("WorldViewProjMatrix", &now);
			if (op.mMeshType == 1)
				meshBox->DrawSubset(0);
			else
				meshTeapot->DrawSubset(0);
			mEffect->EndPass();
		}
		mEffect->End();
	}


}