using System;
using System.Text;
using System.Runtime.InteropServices;

namespace PInvoke
{
	class isPrime
	{
		[DllImport("isPrimeC.dll", CharSet=CharSet.Auto)]
		static extern int isPrimeC(int n);

		public static void test()
		{
			Console.Write("Integer to test: ");
			int n = Convert.ToInt32(Console.ReadLine());
			Console.WriteLine(isPrimeC(n));
		}
	}
}
