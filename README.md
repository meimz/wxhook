# 萌新学hook  
本人环境 vs2017 微信版本 2.6.8.52 src 里面有  
  
参考资料 加密与解密 第四版  
WeChat2.exe 是一个已经处理过的微信启动器注入了 MsgDll.dll 后面我们只需要替换这个dll 就行  
微信安装目录 这里默认为 C:\Program Files (x86)\Tencent\WeChat  
MsgDll.dll 项目在 src 的 proj 里面  
  
hook QQ 学习交流群  859564146  
## hook 学习DAY1  
  
第一步 将 WeChat2.exe 放到微信安装目录  
第二步 MsgDll.dll     也放到微信安装目录   
第三步 启动微信 WeChat2.exe 将会发现 微信安装目录 多了一个文件 info.log 里面记录了你的手机号那么 hook就成功了  
![效果图](https://github.com/meimz/wxhook/blob/master/static/img/1.png)


第四步 自由修改项目 MsgDll    
  
## hook 学习DAY2  

DAY2 研究方向 将微信收到的消息 保存到  微信安装目录 的 chat.log 文件  