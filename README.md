# 萌新学hook  
本人环境 vs2017 微信版本 2.6.8.52 src 里面有  
  
参考资料 加密与解密 第四版  
[鬼手 大佬的项目 https://github.com/TonyChen56/WeChatRobot ](https://github.com/TonyChen56/WeChatRobot)  

[鬼手 大佬的博客 https://blog.csdn.net/qq_38474570?t=1 ](https://blog.csdn.net/qq_38474570?t=1)  

下面这部分删除线内容有可能环境不同无法使用 请从day5开始

~~WeChat2.exe 是一个已经处理过的微信启动器注入了 MsgDll.dll 后面我们只需要替换这个dll 就行~~ 

~~至于如何注入 MsgDll.dll 请参考 加密与解密 第四版 的第 12 章 注入技术 （如有条件请购买正版）~~

~~微信安装目录 这里默认为 C:\Program Files (x86)\Tencent\WeChat~~  
~~MsgDll.dll 项目在 src 的 proj 里面~~  
  
[hook QQ 学习交流群  859564146](https://jq.qq.com/?_wv=1027&k=5Hm8c9q) 
~~## hook 学习DAY1~~
  
~~第一步 将 src/WeChat2.exe 放到微信安装目录~~  
~~第二步 项目编译好的 MsgDll.dll     也放到微信安装目录~~   
~~第三步 启动微信 WeChat2.exe 将会发现 微信安装目录 多了一个文件 info.log 里面记录了你的手机号那么 hook就成功了~~  
![效果图](https://github.com/meimz/wxhook/blob/master/static/img/1.png)


~~第四步 自由修改项目 具体路径为 src/proj/MsgDll/MsgDll.cpp~~ 
  
~~## hook 学习DAY2~~  

~~DAY2 研究方向 将微信收到的消息 保存到  微信安装目录 的 chat.log 文件~~ 

## hook 学习DAY5  

	proj\sendmsg 里面是一个最小发送信息的代码 修改一下 第25行的 第一个参数 接收者就可以测试 SendTextMessage((wchar_t *)L"gh_d6e111dfce3c", (wchar_t *)L"hello");
	将生成的 dll 用 od 或者其他注入器注入微信就能看到效果
## C# C++ 通信	
	proj\wehelp 注入微信的dll（服务端）  
	proj\wxcc 控制台（客户端）
	
	目前 卡在通信乱码的问题上
	
## websocket
 proj\websocket  一个轻量级的websocket的服务源码 用于做通信
 
 
 
 ##  proj\wssocket2
 
	 proj\wssocket2 是一个调通的 websocket 
	 使用的时候更换下 Program.cs 里面的 35行第一个参数为你的好友ID就行 WechatApi.sendTextMsg("gh_981186a7a5e1", message);
	 启动鬼手的wechatRobot 就能发送消息了
	 
	 
