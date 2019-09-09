using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;




namespace wxcc
{
    public partial class Form1 : Form
    {

       

        public Form1()
        {
            InitializeComponent();
        }

        private void bt1_Click(object sender, EventArgs e)
        {
            WatchLog_Print(1, textBox1.Text);

        }

        // 消息打印
        public void WatchLog_Print(int logType, string strs)
        {
            int mark = ImportFromDLL.WM_COPYDATA;
            IntPtr wechatWindowHandler = ImportFromDLL.FindWindow("WeChatHelper",null);


            IntPtr init = Marshal.StringToHGlobalAnsi(strs);
            ImportFromDLL.COPYDATASTRUCT msg = new ImportFromDLL.COPYDATASTRUCT
            {
                dwData = 5,
                cbData = Encoding.Default.GetBytes(strs).Length + 1, //长度 注意不要用strText.Length;  
                lpData = init
            };


            var t = ImportFromDLL.SendMessage(wechatWindowHandler, mark, (IntPtr)logType, ref msg);
        }

    }
}
