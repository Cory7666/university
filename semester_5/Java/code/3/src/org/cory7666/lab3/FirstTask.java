package org.cory7666.lab3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

public class FirstTask
{
	private final Set<Disc> data;

	public FirstTask (Collection<Disc> data)
	{
		this.data = new HashSet<>(data);
	}

	public void execute ()
	{
		System.out.println("=== Выполнение работы с " + data.getClass().getName() + " ===");

		System.out.println("Вывод содержимого:");
		for (var e : data)
		{
			System.out.println("* " + e);
		}

		try
		{
			var key = readKey(System.in);
			Disc foundedElement = null;
			for (var element : data)
			{
				if (element.albumTitle.equals(key))
				{
					foundedElement = element;
					break;
				}
			}
			System.out.println("Найдено: " + foundedElement.toString());
		}
		catch (IOException | NullPointerException e)
		{
			System.out.println("Указанный элемент не найден.");
		}

		System.out.println("=== Окончание работы с " + data.getClass().getName() + " ===");
	}

	private String readKey (InputStream stream) throws IOException
	{
		var buffReader = new BufferedReader(new InputStreamReader(stream));
		System.out.print("Введите ключ для проверки: ");
		return buffReader.readLine();
	}
}
