// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#define WxSendMessage 0x2EB4E0				//发送消息的call


void SendTextMessage(wchar_t* wxid, wchar_t* msg);
//用于调用微信发送消息call的结构体
struct wxMsg
{
	wchar_t* pMsg;		//微信ID
	int msgLen;			//ID长度
	int buffLen;		//缓冲区长度
	int fill1 = 0;
	int fill2 = 0;
};
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH: {

		SendTextMessage((wchar_t *)L"gh_d6e111dfce3c", (wchar_t *)L"hello");
	}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void SendTextMessage(wchar_t* wxid, wchar_t* msg)
{
	//拿到发送消息的call的地址
	DWORD dwSendCallAddr = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll")) + WxSendMessage;

	//组装微信ID/群ID的结构体
	wxMsg id = { 0 };
	id.pMsg = wxid;
	id.msgLen = wcslen(wxid);
	id.buffLen = wcslen(wxid) * 2;

	//消息内容
	wxMsg text = { 0 };
	text.pMsg = msg;
	text.msgLen = wcslen(msg);
	text.buffLen = wcslen(msg) * 2;

	//取出微信ID和消息的地址
	char* pWxid = (char*)&id.pMsg;
	char* pWxmsg = (char*)&text.pMsg;

	char buff[0x81C] = { 0 };

	//调用微信发送消息call
	__asm {
		mov edx, pWxid;
		push 0x1;
		push 0;
		mov ebx, pWxmsg;
		push ebx;
		lea ecx, buff;
		call dwSendCallAddr;
		add esp, 0xC;
	}
}