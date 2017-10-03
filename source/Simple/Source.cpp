#include "Header.h"
#if defined(_DEBUG)
#  include <crtdbg.h>
#  define _CRTDBG_MAP_ALLOC
#endif

#include <directx/DXUT.h>
#include <directx/DXUTgui.h>
using namespace DirectX;

bool CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext);
void CALLBACK OnFrameMove(double fTime, float fElapsedTime, void* pUserContext);
LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
	void* pUserContext);

bool CALLBACK IsD3D11DeviceAcceptable(const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
	DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext);
HRESULT CALLBACK OnD3D11CreateDevice(ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc,
	void* pUserContext);
HRESULT CALLBACK OnD3D11ResizedSwapChain(ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
	const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
void CALLBACK OnD3D11ReleasingSwapChain(void* pUserContext);
void CALLBACK OnD3D11DestroyDevice(void* pUserContext);
void CALLBACK OnD3D11FrameRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
	float fElapsedTime, void* pUserContext);


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
#if defined(_DEBUG)
	// �f�o�b�O�r���h���s���Ƀ������`�F�b�N��L��
	// '�o��'�E�B���h�E�ɂ́A���ׂẴ��[�N���i�f�o�b�O���[�h�j�_���v���B
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_crtBreakAlloc = 35906;
#endif

	DXUTSetIsInGammaCorrectMode(false);

	DXUTSetCallbackDeviceChanging(ModifyDeviceSettings);
	DXUTSetCallbackMsgProc(MsgProc);
	DXUTSetCallbackFrameMove(OnFrameMove);

	DXUTSetCallbackD3D11DeviceAcceptable(IsD3D11DeviceAcceptable);
	DXUTSetCallbackD3D11DeviceCreated(OnD3D11CreateDevice);
	DXUTSetCallbackD3D11SwapChainResized(OnD3D11ResizedSwapChain);
	DXUTSetCallbackD3D11FrameRender(OnD3D11FrameRender);
	DXUTSetCallbackD3D11SwapChainReleasing(OnD3D11ReleasingSwapChain);
	DXUTSetCallbackD3D11DeviceDestroyed(OnD3D11DestroyDevice);

	DXUTInit(false, true, nullptr);
	DXUTSetCursorSettings(true, true);
	DXUTCreateWindow(L"Simple");

	DXUTCreateDevice(D3D_FEATURE_LEVEL_11_0, true, 800, 600);

	DXUTMainLoop();

	return DXUTGetExitCode();
}

//-----------------------------------------------------------------------------------
//! @brief D3D�f�o�C�X���쐻���钼�O�ɌĂ΂�A�A�v�����K�v�ɉ����đ��u�̐ݒ��
//!   �C�����邱�Ƃ��ł���悤�ɂ���
//! @param [in] pDeviceSettings  �C�ӂ̃��[�U�[�R���e�L�X�g      
//! @param [in] pUserContext     �C�ӂ̃��[�U�[�R���e�L�X�g      
//! @return 
//-----------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext)
{
	pDeviceSettings->d3d11.sd.BufferUsage |= DXGI_USAGE_UNORDERED_ACCESS;
	return true;
}


//-----------------------------------------------------------------------------------
//! @brief �V�[���̍X�V
//!  ���̊֐��� 1 �t���[���ɂ� 1 ��Ăяo����܂���,OnFrameRender�֐��́A�V�[����
//!  �����_�����O����K�v������Ƃ��ɁA1 �t���[�����ɕ�����Ăяo�����Ƃ��ł��܂��B
//! @param [in] fTime         �A�v���P�[�V�������J�n���Ă���̌o�ߎ��� (�b�P��) �ł��B
//! @param [in] fElapsedTime  �Ō�̃t���[������̌o�ߎ��� (�b�P��) �ł��B     
//! @param [in] pUserContext  �C�ӂ̃��[�U�[�R���e�L�X�g   
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void CALLBACK OnFrameMove(double fTime, float fElapsedTime, void* pUserContext)
{
}




//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
	void* pUserContext)
{

	return 0;
}



//-----------------------------------------------------------------------------------
//! @brief ���e���ꂽ�C�ӂ�D3D11�f�o�C�X���p�����邩�ǂ���
//! @param [in] pAdapterInfo      �A�_�v�^�[���
//! @param [in] output            �o��
//! @param [in] pDeviceInfo       �f�o�C�X���
//! @param [in] BackBufferFormat  �o�b�N�o�b�t�@�̃t�H�[�}�b�g 
//! @param [in] isWindowed        true�̏ꍇWindow���[�h
//! @param [in] pUserContext      �C�ӂ̃��[�U�[�R���e�L�X�g      
//! @return false��Ԃ����Ƃɂ���āA���e����Ȃ��C�ӂ�D3D11�f�o�C�X���p������
//-----------------------------------------------------------------------------------
bool CALLBACK IsD3D11DeviceAcceptable(const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
	DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext)
{
	if (BackBufferFormat == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
		return false;

	return true;
}


//-----------------------------------------------------------------------------------
//! @brief �f�o�C�X�쐬���̏���
//! @param [in] pd3dDevice    �V�����쐬���ꂽ ID3D11Device �f�o�C�X�ւ̃|�C���^�B
//! @param [in] pBackBufferSurfaceDesc   �o�b�N �o�b�t�@�� DXGI_SURFACE_DESC �T�[�t�F�C�X�L�q�ւ̃|�C���^�B     
//! @param [in] pUserContext  �C�ӂ̃��[�U�[�R���e�L�X�g      
//! @return �ʏ�A�G���[���������Ȃ������ꍇ�� MC_S_OK ��Ԃ��悤�Ƀv���O��������B
//!  ���s�����ꍇ�� HRESULT �Ƃ������s�������R�[�h��Ԃ��悤�Ƀv���O��������B
//!  �T���v�� �t���[�����[�N�́A���s������ HRESULT �R�[�h���󂯎��ƁA�A�v���P�[�V������
//!  �V���b�g �_�E������B
//-----------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11CreateDevice(ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc,
	void* pUserContext)
{
	HRESULT hr;
	//---------------------------------
	// �E�B���h�E�X�^�C����ύX����
	//---------------------------------
	HWND hWnd = DXUTGetHWND();
	LONG_PTR winStyle = GetWindowLongPtr(hWnd, GWL_STYLE);

	winStyle &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME);

	//winStyle |= WS_MINIMIZEBOX;
	//winStyle |= WS_MAXIMIZEBOX;
	//winStyle |= WS_THICKFRAME;
	SetWindowLongPtr(hWnd, GWL_STYLE, winStyle);
	return S_OK;
}


//-----------------------------------------------------------------------------------
//! @brief �o�b�N�o�b�t�@�Ɉˑ����邷�ׂĂ�D3D11�̃��\�[�X���쐬���܂��B
//! @param [in] pd3dDevice    �V�����쐬���ꂽ ID3D11Device �f�o�C�X�ւ̃|�C���^�B    
//! @param [in] pSwapChain    �o�b�N �o�b�t�@�� D3DSURFACE_DESC �T�[�t�F�C�X�L�q�ւ̃|�C���^�B     
//! @param [in] pBackBufferSurfaceDesc  �o�b�N �o�b�t�@�� D3DSURFACE_DESC �T�[�t�F�C�X�L�q�ւ̃|�C���^�B   
//! @param [in] pUserContext  �C�ӂ̃��[�U�[�R���e�L�X�g     
//! @return 
//-----------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11ResizedSwapChain(ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
	const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	HRESULT hr;


	return S_OK;
}


//-----------------------------------------------------------------------------------
//! @brief �V�[���̕`��
//!  �A�v���P�[�V�����Ō��݂̃V�[���������_�����O����ɂ́A���̊֐����K���Ă��܂��B
//!  �t���[�����[�N�́A�V�[���������_�����O�܂�`�悷��K�v������Ƃ��ɂ͏�ɂ���
//!  �֐����Ăяo���邪�A�����_�����O���ꎞ��~���Ă���ꍇ�ɂ͌Ăяo���Ȃ��B
//! @param [in] pd3dDevice            ID3D11Device �f�o�C�X�ւ̃|�C���^�B
//! @param [in] pd3dImmediateContext  ID3D11DeviceContext �f�o�C�X�ւ̃|�C���^�B    
//! @param [in] fTime                 �A�v���P�[�V�������J�n���Ă���̌o�ߎ��� (�b�P��) �ł��B
//! @param [in] fElapsedTime          �Ō�̃t���[������̌o�ߎ��� (�b�P��) �ł��B
//! @param [in] pUserContext          �C�ӂ̃��[�U�[�R���e�L�X�g
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void CALLBACK OnD3D11FrameRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
	float fElapsedTime, void* pUserContext)
{

}


//-----------------------------------------------------------------------------------
//! @brief OnD3D11CreateDevice�ō쐬���ꂽ���ׂĂ�D3D11�̃��\�[�X�����
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void CALLBACK OnD3D11DestroyDevice(void* pUserContext)
{
}


//-----------------------------------------------------------------------------------
//! @brief VOnResizedSwapChain�ō쐬���ꂽ���ׂĂ�D3D11�̃��\�[�X�����
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void CALLBACK OnD3D11ReleasingSwapChain(void* pUserContext)
{
}