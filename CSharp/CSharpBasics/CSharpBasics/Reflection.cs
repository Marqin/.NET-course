using System;
using System.Reflection;
using System.Linq;

namespace CSharpBasics
{
	public class Reflection
	{
		public static void getInfo(Object o)
		{
			Type myType = o.GetType();
			MethodInfo[] inf = myType.GetMethods(BindingFlags.NonPublic|BindingFlags.Instance|BindingFlags.DeclaredOnly);

			for (int i = 0; i < inf.Length; i++) {
				if (inf [i].ReturnType == typeof(int) && inf [i].GetParameters().Length == 0) {
					if (inf [i].GetCustomAttributes (typeof(Oznakowane)).Any ()) {
						System.Console.WriteLine ("{0}.{1}(): {2}", o.GetType(), inf[i].Name, inf[i].Invoke(o, null));
					}

				}
			}
		}
	}
}

