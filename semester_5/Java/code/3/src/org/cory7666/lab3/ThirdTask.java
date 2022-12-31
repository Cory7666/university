package org.cory7666.lab3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class ThirdTask
{
	private final Map<String, Disc> data;

	public ThirdTask (Collection<Disc> data)
	{
		this.data = new HashMap<>();
		data.forEach(disc -> this.data.put(disc.albumTitle, disc));
	}

	public void execute ()
	{
		System.out.println("=== Выполнение работы с " + data.getClass().getName() + " ===");

		System.out.println("Вывод содержимого:");
		data.forEach(this::printRecord);

		try
		{
			System.out.println("Найдено: " + data.get(readKey(System.in)).toString());
		}
		catch (IOException | NullPointerException e)
		{
			System.out.println("Указанный элемент не найден.");
		}

		System.out.println("=== Окончание работы с " + data.getClass().getName() + " ===");
	}

	private void printRecord (String key, Disc disc)
	{
		System.out.println("* " + key + " -> " + disc);
	}

	private String readKey (InputStream stream) throws IOException
	{
		var buffReader = new BufferedReader(new InputStreamReader(stream));
		System.out.print("Введите ключ для проверки: ");
		return buffReader.readLine();
	}
}
