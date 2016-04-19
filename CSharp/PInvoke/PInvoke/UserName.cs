using System;
using System.Text;
using System.Runtime.InteropServices;

namespace PInvoke
{
	class UserName
	{
		[DllImport("Advapi32.dll", CharSet=CharSet.Auto)]
		static extern bool GetUserName(StringBuilder lpBuffer, ref int nSize);

		[DllImport("user32.dll", CharSet=CharSet.Auto)]
		public static extern int MessageBox(IntPtr hWnd, String text, String caption, int options);

		public static void test()
		{
			int nSize=64;
			StringBuilder Buffer = new StringBuilder(nSize);
			GetUserName(Buffer, ref nSize);
			MessageBox(IntPtr.Zero, Buffer.ToString(), "UserName", 0);
		}
	}
}
