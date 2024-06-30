import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

class CommandStringArguments
{
	private final String[] args;

	public CommandStringArguments (String[] args)
	{
		this.args = args;
	}

	public Params parse () throws IllegalArgumentException, FileNotFoundException
	{
		InputStream inStream = System.in;
		OutputStream outStream = System.out;
		boolean interactiveInput = true, interactiveOutput = true;
		int i = 0;

		try
		{
			for (; i < args.length; ++i)
			{
				switch (args[i])
				{
				case "-i", "--input":
					++i;
					inStream = new FileInputStream(new File(args[i]));
					interactiveInput = false;
					break;
				case "-o", "--output":
					++i;
					outStream = new FileOutputStream(new File(args[i]));
					interactiveOutput = false;
					break;
				default:
					throw new IllegalArgumentException(String.format("[ERROR] Parametr %s is unknown.", args[i]));
				}
			}
		}
		catch (IndexOutOfBoundsException e)
		{
			throw new IllegalArgumentException(String.format("Expected filename after %s param.", args[i - 1]));
		}

		return new Params(
			new BufferedReader(new InputStreamReader(inStream)),
			new BufferedWriter(new OutputStreamWriter(outStream)),
			interactiveInput,
			interactiveOutput);
	}
}
