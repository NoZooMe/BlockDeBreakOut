#include "Error.h"
#include <string>
#include <DxLib.h>
#include "Define.h"

using namespace std;

void Error::finish(const char* errorMessage, LPCTSTR lpszFuncName, int lineN)
{
	char funcName[1024];
	sprintf_s(funcName, "%s", lpszFuncName);
	printfDx("異常が発生しました。\n%s\n%s(&d)"
		, errorMessage
		, funcName
		, lineN
	);
	while (!ProcessMessage()) {
		ClearDrawScreen();
		ScreenFlip();
	}
	DxLib_End();
	exit(99);
}