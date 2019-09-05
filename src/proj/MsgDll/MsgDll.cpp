/*-----------------------------------------------------------------------
第12章  注入技术
《加密与解密（第四版）》
(c)  看雪学院 www.kanxue.com 2000-2018
-----------------------------------------------------------------------*/

// MsgDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
#define ReciveMessage 0x315E98			//接收消息
#define ReciveMessageParam 0x126D7F8		//接收消息的参数偏移
#define LoginSign_Offset 0x126D860		//登陆标志位
//消息结构体
struct Message
{
	wchar_t type[10];		//消息类型
	wchar_t source[20];		//消息来源
	wchar_t wxid[40];		//微信ID/群ID
	wchar_t msgSender[40];	//消息发送者
	wchar_t content[200];	//消息内容
};



typedef unsigned long       DWORD;

VOID Msg();

void GetInformation();
void InitWindow(HMODULE hModule);
void WriteLog(char *info,char *logfilename);

BOOL APIENTRY DllMain(HMODULE hModule,
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)InitWindow, hModule,0,NULL);
	}
    return TRUE;
}

//************************************************************
// 函数名称: RegisterWindow
// 函数说明: 注册窗口
// 作    者: GuiShou
// 时    间: 2019/6/30
// 参    数: HMODULE hModule 窗口句柄
// 返 回 值: void 
//************************************************************
void InitWindow(HMODULE hModule)
{
	
		Sleep(5000);
		//获取WeChatWin的基址
		DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle("WeChatWin.dll");

		//检测微信是否登陆
		DWORD dwIsLogin = dwWeChatWinAddr + LoginSign_Offset + 0x194;
		if (*(DWORD*)dwIsLogin == 0)	//等于0说明微信未登录
		{
			
			GetInformation();
			
			
		}
	
	

}


void WriteLog(char *info,char *logfilename)
{
	HANDLE	hFile;
	static char	tmp[100];
	DWORD	dwwritten=0;
	static SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf(tmp,"%04dd-%02d-%02d %02d:%02d:%02d  ",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);
	hFile=CreateFile(logfilename,GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(INVALID_HANDLE_VALUE!=hFile) 
	{
		SetFilePointer(hFile,0,0,SEEK_END);
		WriteFile(hFile,tmp,lstrlen(tmp),&dwwritten,NULL);
		WriteFile(hFile,info,lstrlen(info),&dwwritten,NULL);
		WriteFile(hFile,"\r\n",2,&dwwritten,NULL);
		CloseHandle(hFile);
	}
}


void GetInformation()
{	
	//昵称：WeChatWin.dll + 126D91C
	//微信账号：WeChatWin.dll + 126DA80
	//手机号：WeChatWin.dll + 126d950
	//登陆设备：WeChatWin.dll + 126DD48
	//国籍：WeChatWin.dll + 126DAF8
	//省份：WeChatWin.dll + 126DA08
	//城市：WeChatWin.dll + 126DA20
	//头像指针：WeChatWin.dll + 126DBE4
	//微信ID指针：WeChatWin.dll + 126D8A4
	//性别：WeChatWin.dll+126DA04

	//获取WeChatWin的基址
	DWORD dwWeChatWinAddr = (DWORD)GetModuleHandle("WeChatWin.dll");

	//微信ID
	//char wxid[0x1000] = { 0 };
	//DWORD pWxid = dwWeChatWinAddr + 0x126D8A4;
	//sprintf_s(wxid, "%s", (char*)(*(DWORD*)pWxid));
	//if (strlen(wxid) < 40)
	//{
	//	WriteLog(wxid, "info.log");
	//}
	//else
	//{
	//	WriteLog(wxid, "info.log");
	//}
	//
	//

	////微信性别
	//char sex[0x1000] = { 0 };
	//memcpy(sex, (void*)(dwWeChatWinAddr + 0x126DA04), 1);

	//if (sex[0] == 1)
	//{
	//	WriteLog("男","info.log");
	//}
	//if (sex[0] == 2)
	//{
	//	WriteLog("女","info.log");
	//}

	////微信昵称
	//char nickname[0x1000] = { 0 };
	//sprintf_s(nickname, "%s", (char*)(dwWeChatWinAddr + 0x126D91C));
	//WriteLog(nickname,"info.log");
	

	//微信账号
	/*char wxcount[0x1000] = { 0 };
	sprintf_s(wxcount, "%s", (char*)(dwWeChatWinAddr + 0x126DA80));
	WriteLog(wxcount,"info.log");*/

	//手机号
	char phone[0x1000] = { 0 };
	sprintf_s(phone, "%s", (char*)(dwWeChatWinAddr + 0x126d950));
	WriteLog(phone, "info.log");

	////登陆设备
	//char device[0x1000] = { 0 };
	//sprintf_s(device, "%s", (char*)(dwWeChatWinAddr + 0x126DD48));
	//WriteLog(device, "info.log");

	////国籍
	//char nation[0x1000] = { 0 };
	//sprintf_s(nation, "%s", (char*)(dwWeChatWinAddr + 0x126DAF8));
	//WriteLog(nation, "info.log");

	////省份
	//char province[0x1000] = { 0 };
	//sprintf_s(province, "%s", (char*)(dwWeChatWinAddr + 0x126DA08));
	//WriteLog(province, "info.log");

	////城市
	//char city[0x1000] = { 0 };
	//sprintf_s(city, "%s", (char*)(dwWeChatWinAddr + 0x126DA20));
	//WriteLog(city, "info.log");


	////头像
	//char header[0x1000] = { 0 };
	//DWORD pHeader = dwWeChatWinAddr + 0x126DBE4;
	//sprintf_s(header, "%s", (char*)(*(DWORD*)pHeader));
	//WriteLog(header, "info.log");

}

//导出函数
VOID Msg()
{

}