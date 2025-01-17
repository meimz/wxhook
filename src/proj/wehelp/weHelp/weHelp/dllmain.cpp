// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <string>
#define WxSendMessage 0x2EB4E0				//发送消息的call
#define WM_Login 0
#define WM_ShowQrPicture 1
#define WM_Logout 2
#define WM_GetFriendList 3
#define WM_ShowChatRecord 4
#define WM_SendTextMessage 5
#define WM_SendFileMessage 6
#define WM_GetInformation 7
#define WM_SendImageMessage 8
#define WM_SetRoomAnnouncement 9
#define WM_DeleteUser 10
#define WM_QuitChatRoom 11
#define WM_AddGroupMember 12
#define WM_SendXmlCard 13
#define WM_ShowChatRoomMembers 14
#define WM_ShowChatRoomMembersDone 15
#define WM_DecryptDatabase 16
#define WM_AddUser 17
#define WM_SetRoomName 18
#define WM_AutoChat 19
#define WM_CancleAutoChat 20
#define WM_AlreadyLogin 21
#define WM_SendAtMsg 22
#define WM_DelRoomMember 23

//接收的文本消息结构体
struct MessageStruct
{
	wchar_t wxid[40];
	wchar_t content[MAX_PATH];
};

//用于调用微信发送消息call的结构体
struct wxMsg
{
	wchar_t* pMsg;		//微信ID
	int msgLen;			//ID长度
	int buffLen;		//缓冲区长度
	int fill1 = 0;
	int fill2 = 0;
};


struct VMDATA
{
	 char sender[0x120];
	 char cont[0x1000];
	 int msgType;
};


void RegisterWindow(HMODULE hModule);
void SendTextMessage(wchar_t* wxid, wchar_t* msg);
wchar_t * char2wchar(const char* cchar);

LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RegisterWindow, hModule, 0, NULL);//新建一个线程 处理通信
		MessageBoxA(NULL, "已注入", "已注入", MB_OK); //提示下已注入
		break;
	}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


void RegisterWindow(HMODULE hModule)
{
	//1  设计一个窗口类
	WNDCLASS wnd;
	wnd.style = CS_VREDRAW | CS_HREDRAW;//风格
	wnd.lpfnWndProc = WndProc;//窗口回调函数指针.
	wnd.cbClsExtra = NULL;
	wnd.cbWndExtra = NULL;
	wnd.hInstance = hModule;
	wnd.hIcon = NULL;
	wnd.hCursor = NULL;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = TEXT("WeChatHelper");
	//2  注册窗口类
	RegisterClass(&wnd);
	//3  创建窗口
	HWND hWnd = CreateWindow(
		TEXT("WeChatHelper"),  //窗口类名
		TEXT("WeChatHelper"),//窗口名
		WS_OVERLAPPEDWINDOW,//窗口风格
		10, 10, 500, 300, //窗口位置
		NULL,             //父窗口句柄
		NULL,             //菜单句柄
		hModule,        //实例句柄
		NULL              //传递WM_CREATE消息时的附加参数
	);
	//4  更新显示窗口
	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);
	//5  消息循环（消息泵）
	MSG  msg = {};
	//   5.1获取消息
	while (GetMessage(&msg, 0, 0, 0))
	{
		//   5.2翻译消息
		TranslateMessage(&msg);
		//   5.3转发到消息回调函数
		DispatchMessage(&msg);
	}
}

//************************************************************
// 函数名称: WndProc
// 函数说明: 回调函数 用于和控制端通信 
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam
// 返 回 值: LRESULT 
//************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_COPYDATA)
	{


		//MessageBoxA(NULL, "收到消息"+pCopyData->dwData, "收到消息", MB_OK);
		COPYDATASTRUCT *pCopyData = (COPYDATASTRUCT*)lParam;
		switch (pCopyData->dwData)
		{
			//发送文本
		case 5:
		{
			//VMDATA data = *(VMDATA *)pCopyData->lpData;
			//wchar_t *s = char2wchar((char *)pCopyData->lpData);
			char szBuffer[300];

			memset(szBuffer, 0, sizeof(szBuffer));
			sprintf_s(szBuffer, "dwData:%d cbData:%d\r\nlpData:0x%08x = %s\r\n\r\n",
				pCopyData->dwData, pCopyData->cbData,
				(PVOID)pCopyData->lpData, (char*)pCopyData->lpData);
	


			SendTextMessage((wchar_t *)L"gh_d6e111dfce3c", char2wchar(szBuffer));
			
			MessageBoxA(NULL, (LPCSTR)char2wchar(szBuffer), "收到消息", MB_OK);
		}
		break;

		}

		

	}
	return DefWindowProc(hWnd, Message, wParam, lParam);
}
wchar_t * char2wchar(const char* cchar)
{
	wchar_t *m_wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}

//wchar_t* string2wchart(std::string szSrc) {
//	wchar_t   *   wc = new  wchar_t[szSrc.size()];
//	swprintf(wc, L"%S ", szSrc.c_str());//注意大写S。。 
//	return wc;
//}
//************************************************************
// 函数名称: SendTextMessage
// 函数说明: 发送文本消息
// 作    者: GuiShou
// 时    间: 2019/7/4
// 参    数: wxid 微信ID msg消息内容
// 返 回 值: void 
//************************************************************
void SendTextMessage(wchar_t* wxid, wchar_t* msg)
{
	//拿到发送消息的call的地址
	DWORD dwSendCallAddr = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll")) + WxSendMessage;
	//MessageBoxA(NULL, "调用消息体", "调用消息体", MB_OK);
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

//wchar_t * char2wchar(const char* cchar)
//{
//	wchar_t *m_wchar;
//	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
//	m_wchar = new wchar_t[len + 1];
//	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
//	m_wchar[len] = '\0';
//	return m_wchar;
//}
