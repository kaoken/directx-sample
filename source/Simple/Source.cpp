#include "Header.h"
#include <windows.h>
#include <commctrl.h>
#if defined(_DEBUG)
#  include <crtdbg.h>
#  define _CRTDBG_MAP_ALLOC
#endif

#include <directx/DXUT.h>
#include <directx/DXUTgui.h>
//using namespace DirectX;



INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
#if defined(_DEBUG)
	// デバッグビルド実行時にメモリチェックを有効
	// '出力'ウィンドウには、すべてのリークを（デバッグモード）ダンプ作る。
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_crtBreakAlloc = 35906;
#endif

	//DXUTSetCallbackMsgProc(MsgProc);
	//DXUTSetCallbackKeyboard(OnKeyboard);
	//DXUTSetCallbackFrameMove(OnFrameMove);
	//DXUTSetCallbackDeviceChanging(ModifyDeviceSettings);

	//DXUTSetCallbackD3D11DeviceAcceptable(IsD3D11DeviceAcceptable);
	//DXUTSetCallbackD3D11DeviceCreated(OnD3D11CreateDevice);
	//DXUTSetCallbackD3D11SwapChainResized(OnD3D11ResizedSwapChain);
	//DXUTSetCallbackD3D11SwapChainReleasing(OnD3D11ReleasingSwapChain);
	//DXUTSetCallbackD3D11DeviceDestroyed(OnD3D11DestroyDevice);
	//DXUTSetCallbackD3D11FrameRender(OnD3D11FrameRender);

	DXUTInit(true, true, nullptr); // Parse the command line, show msgboxes on error, no extra command line params
	DXUTSetCursorSettings(true, true);
	DXUTCreateWindow(L"Simple");

	DXUTCreateDevice(D3D_FEATURE_LEVEL_11_0, true, 800, 600);

	DXUTMainLoop();

	return DXUTGetExitCode();
	//return 0;
}

