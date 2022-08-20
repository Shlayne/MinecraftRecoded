using System;

namespace eng
{
	public class Main
	{
		public float FloatVar { get; set; }

		public Main()
		{
			Console.WriteLine("Main()");
		}

		public void PrintMessage()
		{
			Console.WriteLine("Hello from C#!");
		}

		public void PrintInt(int i)
		{
			Console.WriteLine($"Int from C++ in C#: {i}");
		}

		public void PrintCustomMessage(string message)
		{
			Console.WriteLine($"Message from C++ in C#: {message}");
		}
	}
}
