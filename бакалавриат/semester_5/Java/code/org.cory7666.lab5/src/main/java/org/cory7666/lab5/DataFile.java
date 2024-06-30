package org.cory7666.lab5;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Iterator;
import java.util.List;

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

	public List<Auto> readAll () throws IOException
	{
		try (var buffReader = Files.newBufferedReader(file.toPath()))
		{
			return new CsvToBeanBuilder<Auto>(buffReader).withSeparator(';').withType(Auto.class).build().parse();
		}
	}

	public void writeAll (Iterator<Auto> collection)
		throws IOException, CsvDataTypeMismatchException, CsvRequiredFieldEmptyException
	{
		try (var writer = Files.newBufferedWriter(file.toPath()))
		{
			new StatefulBeanToCsvBuilder<Auto>(writer).withSeparator(';').build().write(collection);
		}
	}
}
