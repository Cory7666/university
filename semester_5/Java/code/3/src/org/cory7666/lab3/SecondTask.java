package org.cory7666.lab3;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Collection;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class SecondTask
{
	private final List<Disc> data;

	public SecondTask (Collection<Disc> data)
	{
		this.data = new LinkedList<>(data);
	}

	public SecondTask execute ()
	{
		System.out.println("=== Выполнение работы с " + data.getClass().getName() + " ===");

		System.out.println("Вывод содержимого (до сортировки):");
		data.forEach(this::printElement);

		System.out.println();
		System.out.println("Вывод содержимого (после сортировки):");
		Collections.sort(data);
		data.forEach(this::printElement);

		System.out.println("=== Окончание работы с " + data.getClass().getName() + " ===");

		return this;
	}

	public void saveTo (File file) throws IOException
	{
		System.out.println("=== Сохранение данных " + data.getClass().getName() + " в \"" + file.getPath() + "\" ===");
		try (var writer = Files.newBufferedWriter(file.toPath()))
		{
			data.forEach(x -> {
				try
				{
					writer.write(x.toString());
					writer.newLine();
				}
				catch (IOException e)
				{
					e.printStackTrace();
				}
			});
		}
	}

	private void printElement (Disc disc)
	{
		System.out.println("* " + disc);
	}
}
