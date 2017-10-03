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
	// デバッグビルド実行時にメモリチェックを有効
	// '出力'ウィンドウには、すべてのリークを（デバッグモード）ダンプ作る。
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
//! @brief D3Dデバイスを作製する直前に呼ばれ、アプリが必要に応じて装置の設定を
//!   修正することをできるようにする
//! @param [in] pDeviceSettings  任意のユーザーコンテキスト      
//! @param [in] pUserContext     任意のユーザーコンテキスト      
//! @return 
//-----------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings(DXUTDeviceSettings* pDeviceSettings, void* pUserContext)
{
	pDeviceSettings->d3d11.sd.BufferUsage |= DXGI_USAGE_UNORDERED_ACCESS;
	return true;
}


//-----------------------------------------------------------------------------------
//! @brief シーンの更新
//!  この関数は 1 フレームにつき 1 回呼び出されますが,OnFrameRender関数は、シーンを
//!  レンダリングする必要があるときに、1 フレーム中に複数回呼び出すことができます。
//! @param [in] fTime         アプリケーションが開始してからの経過時間 (秒単位) です。
//! @param [in] fElapsedTime  最後のフレームからの経過時間 (秒単位) です。     
//! @param [in] pUserContext  任意のユーザーコンテキスト   
//! @return なし
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
//! @brief 許容された任意のD3D11デバイスを却下するかどうか
//! @param [in] pAdapterInfo      アダプター情報
//! @param [in] output            出力
//! @param [in] pDeviceInfo       デバイス情報
//! @param [in] BackBufferFormat  バックバッファのフォーマット 
//! @param [in] isWindowed        trueの場合Windowモード
//! @param [in] pUserContext      任意のユーザーコンテキスト      
//! @return falseを返すことによって、許容されない任意のD3D11デバイスを却下する
//-----------------------------------------------------------------------------------
bool CALLBACK IsD3D11DeviceAcceptable(const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
	DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext)
{
	if (BackBufferFormat == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
		return false;

	return true;
}


//-----------------------------------------------------------------------------------
//! @brief デバイス作成時の処理
//! @param [in] pd3dDevice    新しく作成された ID3D11Device デバイスへのポインタ。
//! @param [in] pBackBufferSurfaceDesc   バック バッファの DXGI_SURFACE_DESC サーフェイス記述へのポインタ。     
//! @param [in] pUserContext  任意のユーザーコンテキスト      
//! @return 通常、エラーが発生しなかった場合は MC_S_OK を返すようにプログラムする。
//!  失敗した場合は HRESULT という失敗を示すコードを返すようにプログラムする。
//!  サンプル フレームワークは、失敗を示す HRESULT コードを受け取ると、アプリケーションを
//!  シャット ダウンする。
//-----------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11CreateDevice(ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc,
	void* pUserContext)
{
	HRESULT hr;
	//---------------------------------
	// ウィンドウスタイルを変更する
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
//! @brief バックバッファに依存するすべてのD3D11のリソースを作成します。
//! @param [in] pd3dDevice    新しく作成された ID3D11Device デバイスへのポインタ。    
//! @param [in] pSwapChain    バック バッファの D3DSURFACE_DESC サーフェイス記述へのポインタ。     
//! @param [in] pBackBufferSurfaceDesc  バック バッファの D3DSURFACE_DESC サーフェイス記述へのポインタ。   
//! @param [in] pUserContext  任意のユーザーコンテキスト     
//! @return 
//-----------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11ResizedSwapChain(ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
	const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	HRESULT hr;


	return S_OK;
}


//-----------------------------------------------------------------------------------
//! @brief シーンの描画
//!  アプリケーションで現在のシーンをレンダリングするには、この関数が適しています。
//!  フレームワークは、シーンをレンダリングつまり描画する必要があるときには常にこの
//!  関数を呼び出するが、レンダリングが一時停止している場合には呼び出しない。
//! @param [in] pd3dDevice            ID3D11Device デバイスへのポインタ。
//! @param [in] pd3dImmediateContext  ID3D11DeviceContext デバイスへのポインタ。    
//! @param [in] fTime                 アプリケーションが開始してからの経過時間 (秒単位) です。
//! @param [in] fElapsedTime          最後のフレームからの経過時間 (秒単位) です。
//! @param [in] pUserContext          任意のユーザーコンテキスト
//! @return なし
//-----------------------------------------------------------------------------------
void CALLBACK OnD3D11FrameRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
	float fElapsedTime, void* pUserContext)
{

}


//-----------------------------------------------------------------------------------
//! @brief OnD3D11CreateDeviceで作成されたすべてのD3D11のリソースを解放
//! @return なし
//-----------------------------------------------------------------------------------
void CALLBACK OnD3D11DestroyDevice(void* pUserContext)
{
}


//-----------------------------------------------------------------------------------
//! @brief VOnResizedSwapChainで作成されたすべてのD3D11のリソースを解放
//! @return なし
//-----------------------------------------------------------------------------------
void CALLBACK OnD3D11ReleasingSwapChain(void* pUserContext)
{
}