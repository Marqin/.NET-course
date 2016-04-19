using System;
using System.Text;
using System.Runtime.InteropServices;

delegate int delegat(int x);

namespace PInvoke
{
	class Execute
	{
		[DllImport("ExecuteC.dll", CharSet=CharSet.Auto)]
		static extern int ExecuteC(int x, delegat f);

		[DllImport("isPrimeC.dll", CharSet=CharSet.Auto)]
		static extern int isPrimeC(int n);

		static int fun(int x){
			return 2*x;
		}

		public static void test()
		{
			Console.WriteLine(ExecuteC(7, isPrimeC));
		}
	}
}
