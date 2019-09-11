using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace wssocket2
{
    class WechatApi
    {
        public const int WM_Login = 0;
        public const int WM_ShowQrPicture = 1;
        public const int WM_Logout = 2;
        public const int WM_GetFriendList = 3;
        public const int WM_ShowChatRecord = 4;
        public const int WM_SendTextMessage = 5;
        public const int WM_SendFileMessage = 6;
        public const int WM_GetInformation = 7;
        public const int WM_SendImageMessage = 8;
        public const int WM_SetRoomAnnouncement = 9;
        public const int WM_DeleteUser = 10;
        public const int WM_QuitChatRoom = 11;
        public const int WM_AddGroupMember = 12;
        public const int WM_SendXmlCard = 13;
        public const int WM_ShowChatRoomMembers = 14;
        public const int WM_ShowChatRoomMembersDone = 15;
        public const int WM_DecryptDatabase = 16;
        public const int WM_AddUser = 17;
        public const int WM_SetRoomName = 18;
        public const int WM_AutoChat = 19;
        public const int WM_CancleAutoChat = 20;
        public const int WM_AlreadyLogin = 21;
        public const int WM_SendAtMsg = 22;
        public const int WM_DelRoomMember = 23;

        public const string helperWindows = "WeChatHelper";

        //发送底层函数
        private static void sendToWeChatHelper(ImportFromDLL.MessageStruct msg, int msgtype)
        {
            int cbSize = Marshal.SizeOf(msg);
            IntPtr StructPtr = Marshal.AllocHGlobal(cbSize);
            Marshal.StructureToPtr(msg, StructPtr, true);

            var c = new ImportFromDLL.COPYDATASTRUCT();
            c.dwData = msgtype;
            c.cbData = cbSize;
            c.lpData = StructPtr;

            IntPtr wechatWindowHandler = ImportFromDLL.FindWindow(helperWindows, null);

            var t = ImportFromDLL.SendMessage(wechatWindowHandler, ImportFromDLL.WM_COPYDATA, (IntPtr)5, ref c);
            Marshal.FreeHGlobal(StructPtr);

        }

        //发送文本信息
        public static void sendTextMsg(string wxid,string content)
        {
            var msg = new ImportFromDLL.MessageStruct();
            msg.wxid = wxid;
            msg.content = content;
            sendToWeChatHelper(msg, WM_SendTextMessage);
        }
    }
}
