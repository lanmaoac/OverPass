#define WINDOW_WIDTH  932           
#define WINDOW_HEIGHT 700           
#define WINDOW_TITLE  _T("3D Engine") 



#include <conio.h>



#include <windows.h>
#include <string.h>
#include<atlstr.h>  
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h> 
#include "TerrainClass.h"
#include "CameraClass.h"
#include "DirectInputClass.h"
#include "WaterClass.h"
#include "SkyBoxClass.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "dinput8.lib")    
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "winmm.lib") 

LRESULT CALLBACK    WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

TerrainClass*               g_pTerrain = NULL;
DInputClass*                g_pDInput = NULL;
CameraClass*                  g_pCamera = NULL;
CameraClass*                                g_pLightCamera = NULL;
WaterClass*                                 g_pWater = NULL;
SkyBoxClass*                                g_pSkyBox = NULL;
D3DLIGHT9                   g_Light;
D3DXMATRIX              g_matWorld;

LPDIRECT3DDEVICE9         Device = NULL;


D3DXMATRIX ProjMatrix;


D3DXHANDLE WorldViewProjHandle = 0;

ID3DXEffect* ToonEffect = 0;

IDirect3DTexture9*           DepthScene = NULL;

ID3DXMesh *meshP;
ID3DXMesh *meshT;
D3DXMATRIX  PreView;

HRESULT Direct3D_Init(HWND hwnd, HINSTANCE hInstance)
{


	LPDIRECT3D9  pD3D = NULL;
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DCAPS9 caps; int vp = 0;
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 2;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, vp, &d3dpp, &Device)))
		return E_FAIL;

	pD3D->Release();
	return S_OK;
}
void Direct3D_CleanUp()
{
	Device->Release();
}

void Objects_Init()
{
	::ZeroMemory(&g_Light, sizeof(g_Light));
	g_Light.Type = D3DLIGHT_POINT;
	g_Light.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	g_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Light.Specular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	//g_Light.Direction = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Device->SetLight(0, &g_Light);
	Device->LightEnable(0, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	g_pCamera = new CameraClass(Device);
	g_pCamera->SetCameraPosition(&D3DXVECTOR3(0.0f, 0.0f, -1000.0f));
	g_pCamera->SetTargetPosition(&D3DXVECTOR3(0.0f, 0.0f, 1200.0f));
	g_pCamera->SetViewMatrix();
	g_pCamera->SetProjMatrix();
	g_pCamera->CalculateViewMatrix(&PreView);

	//g_pTerrain = new TerrainClass(Device);
	//g_pTerrain->LoadTerrainFromFile(L"heighmap.raw", L"terrainstone.jpg");
	//g_pTerrain->InitTerrain(200, 200, 120.0f, 8.0f);

	g_pWater = new WaterClass(Device);
	g_pWater->InitWater(200, 200, 60.0f, 40.0f);

	//g_pSkyBox = new SkyBoxClass(Device);
	//g_pSkyBox->LoadSkyTextureFromFile(L"TropicalSunnyDayFront2048.png", L"TropicalSunnyDayBack2048.png", L"TropicalSunnyDayRight2048.png", L"TropicalSunnyDayLeft2048.png", L"TropicalSunnyDayUp2048.png");
	//g_pSkyBox->InitSkyBox(50000);

	D3DXCreateTeapot(Device, &meshT, 0);
	D3DXCreateBox(Device, 100.0f, 100.0f, 100.0f, &meshP, 0);


}
void Update(HWND hwnd)
{
	g_pDInput->GetInput();

	// ��������������ƶ��ӽ�
	if (g_pDInput->IsKeyDown(DIK_A))  g_pCamera->MoveAlongRightVec(-4.0f);
	if (g_pDInput->IsKeyDown(DIK_D))  g_pCamera->MoveAlongRightVec(4.0f);
	if (g_pDInput->IsKeyDown(DIK_W)) g_pCamera->MoveAlongLookVec(4.0f);
	if (g_pDInput->IsKeyDown(DIK_S))  g_pCamera->MoveAlongLookVec(-4.0f);
	if (g_pDInput->IsKeyDown(DIK_R))  g_pCamera->MoveAlongUpVec(3.0f);
	if (g_pDInput->IsKeyDown(DIK_F))  g_pCamera->MoveAlongUpVec(-3.0f);

	//���������������ת�ӽ�
	if (g_pDInput->IsKeyDown(DIK_LEFT))  g_pCamera->RotationUpVec(-0.003f);
	if (g_pDInput->IsKeyDown(DIK_RIGHT))  g_pCamera->RotationUpVec(0.003f);
	if (g_pDInput->IsKeyDown(DIK_UP))  g_pCamera->RotationRightVec(-0.003f);
	if (g_pDInput->IsKeyDown(DIK_DOWN))  g_pCamera->RotationRightVec(0.003f);
	if (g_pDInput->IsKeyDown(DIK_Q)) g_pCamera->RotationLookVec(0.003f);
	if (g_pDInput->IsKeyDown(DIK_E)) g_pCamera->RotationLookVec(-0.003f);

	//������������������������ת
	g_pCamera->RotationUpVec(g_pDInput->MouseDX()* 0.001f);
	g_pCamera->RotationRightVec(g_pDInput->MouseDY() * 0.001f);

	//�����ֿ��ƹ۲����������
	static FLOAT fPosZ = 0.0f;
	fPosZ += g_pDInput->MouseDZ()*0.03f;

	//���㲢����ȡ���任����
	D3DXMATRIX matView;
	g_pCamera->CalculateViewMatrix(&matView);
	//Device->SetTransform(D3DTS_VIEW, &matView);

	//����ȷ������任����浽g_matWorld��
	D3DXMatrixTranslation(&g_matWorld, 0.0f, 0.0f, fPosZ);

}
void Render(HWND hwnd)
{
	D3DXMatrixTranslation(&g_matWorld, 0.0f, 0.0f, 0.0f);
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(100, 255, 255), 1.0f, 0);

	Device->BeginScene();

	//g_pTerrain->RenderTerrain(&g_matWorld, false);
	//g_pWater->RenderWater(&g_matWorld, false);
	//D3DXMATRIX matSky, matTransSky, matRotSky;
	//D3DXMatrixTranslation(&matTransSky, 0.0f, -12000.0f, 0.0f);
	//D3DXMatrixRotationY(&matRotSky, -0.000005f*timeGetTime());   //��ת�������, ��ģ���Ʋ��˶�Ч��
	//matSky = matTransSky*matRotSky;
	//g_pSkyBox->RenderSkyBox(&matSky, false);


	Device->EndScene();

	Device->Present(NULL, NULL, NULL, NULL);

}
void SetRenderTarget(int iRenderTargetIdx, IDirect3DTexture9* pd3dRenderTargetTexture)
{
	if (pd3dRenderTargetTexture == NULL)
	{
		Device->SetRenderTarget(iRenderTargetIdx, NULL);
	}
	else
	{
		IDirect3DSurface9* pd3dSurface;
		pd3dRenderTargetTexture->GetSurfaceLevel(0, &pd3dSurface);
		Device->SetRenderTarget(iRenderTargetIdx, pd3dSurface);

	}
}
void ClearTexture(IDirect3DTexture9* pd3dTexture, D3DCOLOR xColor)
{
	IDirect3DSurface9* pd3dSurface;
	pd3dTexture->GetSurfaceLevel(0, &pd3dSurface);
	Device->ColorFill(pd3dSurface, NULL, xColor);
	pd3dSurface->Release();
}
bool Setup()
{
	HRESULT hr = 0;
	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFile(
		Device,           // associated device
		L"shadowmap.txt", // effect filename
		0,                // no preprocessor definitions
		0,                // no ID3DXInclude interface
		D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
		0,                // don't share parameters
		&ToonEffect,      // return effect
		&errorBuffer);    // return error messages

	// output any error messages
	if (errorBuffer)
	{
		MessageBox(0, CString((char *)errorBuffer->GetBufferPointer()), 0, 0);
	}

	if (FAILED(hr))
	{
		MessageBox(0, CString((char *)errorBuffer->GetBufferPointer()), 0, 0);
		//MessageBox(0, L"D3DXCreateEffectFromFile() - FAILED", 0, 0);
	}

	D3DXMatrixPerspectiveFovLH(
		&ProjMatrix, D3DX_PI * 0.25f, // 45 - degree
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		1.0f, 30000.0f);

	Device->CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT,
		1, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &DepthScene, NULL);

	WorldViewProjHandle = ToonEffect->GetParameterByName(0, "WorldViewProjMatrix");



	return true;
}
void Display()
{
	if (Device)
	{

		D3DXMATRIX matView;
		g_pCamera->CalculateViewMatrix(&matView);

		D3DXMATRIX g_matWorld1, g_matWorld2;
		D3DXMatrixTranslation(&g_matWorld2, 0.0f, 0.0f, 400.0f);
		D3DXMatrixTranslation(&g_matWorld1, 0.0f, 0.0f, 200.0f);

		D3DXMATRIX mTrans;
		D3DXMatrixScaling(&mTrans, 10.0f, 10.0f, 10.0f);

		UINT numPasses = 0;

		Device->BeginScene();
		SetRenderTarget(0, DepthScene);
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 120, 1.0f, 0);
		ToonEffect->SetTechnique("Normal");
		numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			D3DXMATRIX now = mTrans *  g_matWorld1 *matView * ProjMatrix;
			D3DXMATRIX now2 = mTrans *  g_matWorld1 *PreView * ProjMatrix;
			ToonEffect->SetMatrix("WorldViewProjMatrix", &now);
			ToonEffect->SetMatrix("LightWorldViewProjMatrix", &now2);
			meshP->DrawSubset(0);
			ToonEffect->EndPass();
		}
		ToonEffect->End();

		numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			D3DXMATRIX now = g_matWorld2  * matView   * ProjMatrix;
			D3DXMATRIX now2 = g_matWorld2  * PreView * ProjMatrix;
			ToonEffect->SetMatrix("WorldViewProjMatrix", &now);
			ToonEffect->SetMatrix("LightWorldViewProjMatrix", &now2);
			meshT->DrawSubset(0);
			ToonEffect->EndPass();
		}
		ToonEffect->End();


		IDirect3DSurface9* pd3dBackBufferSurface;
		Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pd3dBackBufferSurface);
		Device->SetRenderTarget(0, pd3dBackBufferSurface);
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 120, 1.0f, 0);
		ToonEffect->SetTexture("ShaderTexture", DepthScene);
		ToonEffect->SetTechnique("Normal_S");
		numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			D3DXMATRIX now = mTrans *  g_matWorld1 *matView * ProjMatrix;
			D3DXMATRIX now2 = mTrans *  g_matWorld1 *PreView * ProjMatrix;
			ToonEffect->SetMatrix("LightWorldViewProjMatrix", &now2);
			ToonEffect->SetMatrix("WorldViewProjMatrix", &now);
			meshP->DrawSubset(0);
			ToonEffect->EndPass();
		}

		numPasses = 0;
		ToonEffect->Begin(&numPasses, 0);
		for (int i = 0; i < numPasses; i++)
		{
			ToonEffect->BeginPass(i);
			D3DXMATRIX now = g_matWorld2  * matView   * ProjMatrix;
			D3DXMATRIX now2 = g_matWorld2  * PreView * ProjMatrix;
			ToonEffect->SetMatrix("LightWorldViewProjMatrix", &now2);
			ToonEffect->SetMatrix("WorldViewProjMatrix", &now);
			meshT->DrawSubset(0);
			ToonEffect->EndPass();
		}
		ToonEffect->End();


		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	//��ʼ���һ�������Ĵ�����
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = (HICON)::LoadImage(NULL, _T("GameMedia\\icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = _T("ForTheDreamOfGameDevelop");

	if (!RegisterClassEx(&wndClass))
		return -1;

	HWND hwnd = CreateWindow(_T("ForTheDreamOfGameDevelop"), WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	Direct3D_Init(hwnd, hInstance);


	MoveWindow(hwnd, 200, 10, WINDOW_WIDTH, WINDOW_HEIGHT, true);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	g_pDInput = new DInputClass();
	g_pDInput->Init(hwnd, hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	Objects_Init();
	Setup();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		static FLOAT fLastTime = (float)::timeGetTime();
		static FLOAT fCurrTime = (float)::timeGetTime();
		static FLOAT fTimeDelta = 0.0f;
		fCurrTime = (float)::timeGetTime();
		fTimeDelta = (fCurrTime - fLastTime) / 1000.0f;
		fLastTime = fCurrTime;

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update(hwnd);
			Display();
			//Render(hwnd);
		}
	}
	UnregisterClass(_T("ForTheDreamOfGameDevelop"), wndClass.hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:           // �ͻ����ػ���Ϣ
		Render(hwnd);          //����Direct3D_Render���������л���Ļ���
		ValidateRect(hwnd, NULL);   // ���¿ͻ�������ʾ
		break;                  //������switch���

	case WM_KEYDOWN:                // ���̰�����Ϣ
		if (wParam == VK_ESCAPE)    // ESC��
			DestroyWindow(hwnd);    // ���ٴ���, ������һ��WM_DESTROY��Ϣ
		break;
	case WM_DESTROY:        //����������Ϣ
		Direct3D_CleanUp();     //����Direct3D_CleanUp����������COM�ӿڶ���
		PostQuitMessage(0);   //��ϵͳ�����и��߳�����ֹ����������ӦWM_DESTROY��Ϣ
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

