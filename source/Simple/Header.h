#pragma once

#  pragma warning(disable:4819) // disable 「ファイルは、現在のコード ページ (932) で表示できない文字を含んでいます。データの損失を防ぐために、ファイルを Unicode 形式で保存してください。」
#  pragma region libs
#  pragma comment( lib, "pdh.lib" )
#  pragma comment( lib, "Comctl32.lib" )
#  pragma comment( lib, "windowscodecs.lib" )
#  pragma comment( lib, "Dwrite.lib" )
#  pragma comment( lib, "D2d1.lib" )
#  pragma comment( lib, "d3d11.lib")
#  pragma comment( lib, "DirectXTex.lib" )
#  pragma comment( lib, "DXUT.lib" )
#  pragma comment( lib, "DXUTOpt.lib" )
#  if defined(_DEBUG) || defined(DEBUG)
#    pragma comment( lib, "Effects11d.lib" )
#  else
#    pragma comment( lib, "Effects11.lib" )
#  endif
#  pragma endregion libs
