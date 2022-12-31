package org.cory7666.lab3;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;

import com.opencsv.bean.CsvToBeanBuilder;

public class App
{
	public static void main (String[] args) throws IllegalAccessException
	{
		try
		{
			var params = new CommandArguments(args).parse();
			List<Disc> initialData = readInitialDataFrom(params.input);
			new FirstTask(initialData).execute();
			new SecondTask(initialData).execute().saveTo(params.output);;
			new ThirdTask(initialData).execute();
		}
		catch (IllegalArgumentException | IllegalAccessException e)
		{
			System.err.println(e.getMessage());
		}
		catch (IOException e)
		{
			System.err.println("[ОШИБКА] Ошибка ввода-вывода.");
		}
	}

	private static List<Disc> readInitialDataFrom (File file) throws IOException
	{
		try (var bufReader = Files.newBufferedReader(file.toPath()))
		{
			return new CsvToBeanBuilder<Disc>(bufReader).withSeparator(';').withType(Disc.class).build().parse();
		}
	}
}
