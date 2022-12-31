package org.cory7666.lab4;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import com.opencsv.bean.CsvToBeanBuilder;
import com.opencsv.bean.StatefulBeanToCsvBuilder;
import com.opencsv.exceptions.CsvDataTypeMismatchException;
import com.opencsv.exceptions.CsvRequiredFieldEmptyException;

public class DataFile
{
	private final File file;

	public DataFile (File file)
	{
		this.file = file;
	}

	public Set<Auto> readAll () throws IOException
	{
		try (var buffReader = Files.newBufferedReader(file.toPath()))
		{
			return new HashSet<>(
				new CsvToBeanBuilder<Auto>(buffReader).withSeparator(';').withType(Auto.class).build().parse());
		}
	}

	public void writeAll (Iterator<Auto> collection) throws IOException
	{
		try (var buffWriter = Files.newBufferedWriter(file.toPath()))
		{
			new StatefulBeanToCsvBuilder<Auto>(buffWriter).withSeparator(';').build().write(collection);;
		}
		catch (CsvDataTypeMismatchException | CsvRequiredFieldEmptyException ex)
		{
			Logger.error(getClass(), ex.getMessage());
		}
	}
}
