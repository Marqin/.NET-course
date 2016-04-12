using System;

namespace CSharpBasics
{
	public class Program
	{

		public static void benchmark () {
			Algorithm n = new Algorithm (42);

			int tests = 100000;

			// JIT warmup
			for (int i = 0; i < 10; i++) {
				n.GetType ().GetMethod ("value_pub").Invoke (n, null);
			}
			for (int i = 0; i < 10; i++) {
				n.value_pub();
			}
			//

			DateTime Start = DateTime.Now;
			for (int i = 0; i < tests; i++) {
				n.GetType ().GetMethod ("value_pub").Invoke (n, null);
			}
			TimeSpan refl = (Start - DateTime.Now);

			Start = DateTime.Now;
			for (int i = 0; i < tests; i++) {
				n.value_pub();
			}
			TimeSpan norm = (Start - DateTime.Now);

			Console.WriteLine ("normal: {0}, reflection: {1}", norm, refl);
		}


		public static void Main ()
		{
			// alg
			for (int i = 1; i < 10000; i++) {
				Algorithm n = new Algorithm (i);
				if (n.isOK ()) {
					System.Console.WriteLine (i);
				}
			}

			// grid
			Grid<int> G = new Grid<int>(4, 2);
			for (int i = 0; i < 4; i++) {
				G[i] = new int[] {i, 2*i};
			}

			for (int i = 0; i < 4; i++) {
				for (int j=0; j < 2; j++) {
					System.Console.Write("{0} ", G[i,j]);
				}
				System.Console.WriteLine();
			}

			// reflection test
			Algorithm tmp = new Algorithm (42);
			Reflection.getInfo (tmp);

			// reflection benchmark
			benchmark ();
		}
	}
}

