package org.cory7666.lab4;

import javax.swing.JOptionPane;

public class Logger
{
	public static int logLevel = 0;

	public static void debug (Class<?> who, String message)
	{
		if (logLevel <= 0)
		{
			postMessage("DEBUG", who, message);
		}
	}

	public static void error (Class<?> who, String message)
	{
		if (logLevel <= 2)
		{
			postMessage("ERROR", who, message);
			JOptionPane.showMessageDialog(null, message);
		}
	}

	private synchronized static void postMessage (String panicLevel, Class<?> who, String message)
	{
		System.out
			.println(
				String.format("[%s] [%s/%s] %s", panicLevel, Thread.currentThread().getName(), who.getName(), message));
	}
}
