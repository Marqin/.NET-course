using System;
using System.Reflection;
using System.Reflection.Emit;

namespace CSharpBasics
{

	public class Algorithm
	{
		private int num;

		private int[] digits;

		private bool digitsOK;
		private bool sumOK;

		public Algorithm (int n)
		{
			this.num = n;

			if (this.num == 0) {
				digitsOK = false;
				sumOK = false;
				return;
			}

			int len = Convert.ToInt32 (Math.Floor (Math.Log10 (this.num))) + 1;
			this.digits = new int[len];
			int tmp = this.num;
			for (int i = 0; i < len; i++) {
				this.digits [i] = tmp % 10;
				tmp /= 10;
			}
			Array.Reverse (this.digits);

			if (Array.IndexOf (this.digits, 0) >= 0) {
				digitsOK = false;
			} else {
				CheckDigits ();
			}
			CheckSum ();
		}

		private void CheckDigits ()
		{
			for (int i = 0; i < this.digits.Length; i++) {
				if (this.num % this.digits[i] != 0) {
					digitsOK = false;
					break;
				}
			}
			digitsOK = true;
		}

		private void CheckSum ()
		{
			int sum = 0;
			for (int i = 0; i < this.digits.Length; i++) {
				sum += this.digits [i];
			}
			sumOK = (this.num % sum == 0);
		}

		public bool isOK ()
		{
			return digitsOK && sumOK;
		}


		// for reflection task:

		public int value_pub ()
		{
			return this.num;
		}

		[Oznakowane]
		private int value_priv1 ()
		{
			return this.num;
		}

		private int value_priv2 ()
		{
			return this.num;
		}

		private int value_arg (int x)
		{
			return this.num;
		}
	}
}

