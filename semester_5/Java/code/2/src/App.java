import java.io.File;
import java.io.IOException;

public class App
{
	static final int BUFFER_INIT_SIZE = 20, BUFFER_COUNT = 5;

	public static void main (String[] args)
	{
		try
		{
			for (int i = 0; i < BUFFER_COUNT; ++i)
			{
				var buffer = new MyBuffer(BUFFER_INIT_SIZE);
				buffer.printInfo();
				buffer.printFirstN(10);
				buffer.max();
				buffer.min();
				buffer.sort();
				buffer.printLastN(10);

				if (i % 2 == 0)
				{
					buffer.saveOneLine(File.createTempFile("lab2-", "-buffer" + buffer.getId() + "-oneline"));
				}
				else
				{
					buffer.saveSeparateLines(File.createTempFile("lab2-", "-buffer" + buffer.getId() + "-multilines"));
				}
			}
		}
		catch (IOException e)
		{
			System.err.println(e.getMessage());
		}
	}

}
