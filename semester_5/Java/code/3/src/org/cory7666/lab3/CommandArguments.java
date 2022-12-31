package org.cory7666.lab3;

import java.io.File;
import java.io.IOException;

public class CommandArguments
{
	private final String[] args;

	public CommandArguments (String[] args)
	{
		this.args = args;
	}

	public Params parse () throws IllegalAccessException, IOException
	{
		int i = 0;
		try
		{
			File input = null, output = File.createTempFile("lab3-", "-output");

			for (; i < args.length; ++i)
			{
				if (args[i].startsWith("-"))
				{
					switch (args[i])
					{
					case "-i", "--input":
						input = new File(args[++i]);
						break;
					case "-o", "--output":
						output = new File(args[++i]);
						break;
					}
				}
			}
			if (input == null)
				throw new IllegalAccessException("Expected input file, no such given.");
			else
				return new Params(input, output);
		}
		catch (IndexOutOfBoundsException e)
		{
			throw new IllegalArgumentException("After parametr " + i + " expected value.");
		}
	}
}
