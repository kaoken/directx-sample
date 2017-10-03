#include "Header.h"
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

	DXUTInit(true, true, nullptr);
	DXUTSetCursorSettings(true, true);
	DXUTCreateWindow(L"Simple");

	DXUTCreateDevice(D3D_FEATURE_LEVEL_11_0, true, 800, 600);

	DXUTMainLoop();

	return DXUTGetExitCode();
}

