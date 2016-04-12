using System;

namespace CSharpBasics
{
	public class Grid<T>
	{
		private T[][] data;
		public T[] this[int i]
		{
			get {
				return data [i];
			}
			set {
				data [i] = value;
			}
		}

		public T this[int i, int j]
		{
			get {
				return data [i] [j];
			}
			set {
				data [i] [j] = value;
			}
		}

		int LengthX
		{
			get {
				return data.Length;
			}
		}

		int LengthY
		{
			get {
				if (LengthX > 0) {
					return data [0].Length;
				} else {
					return 0;
				}
			}
		}

		public Grid (int i, int j)
		{
			data = new T[i][];
			for (int k = 0; k < i; k++) {
				data [k] = new T[j];	
			}
		}
	}
}

