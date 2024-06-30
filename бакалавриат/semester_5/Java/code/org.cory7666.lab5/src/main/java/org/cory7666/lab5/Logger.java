package org.cory7666.lab5;

import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonType;

public class Logger
{
	public static int logLevel = 0;

	public static void debug (Class<?> who, String message)
	{
		if (logLevel <= 0)
		{
			print("DEBUG", Thread.currentThread().getName(), who, message);
		}
	}

	public static void error (Class<?> who, String message)
	{
		if (logLevel <= 1)
		{
			print("ERROR", Thread.currentThread().getName(), who, message);
			new Alert(AlertType.ERROR, message, ButtonType.CLOSE).showAndWait();
		}
	}

	private static void print (String rock, String threadName, Class<?> who, String message)
	{
		System.out.printf("[%s] [%s/%s] %s\n", rock, threadName, who.getName(), message);
	}
}
