import java.io.FileNotFoundException;
import java.io.IOException;

class App
{
	public static void main (String[] args) throws IOException
	{
		try
		{
			new UserInteraction(
				new CommandStringArguments(args).parse(),
				"Введите коэффициенты квадратного уравнения",
				"Ответ").readNumbers().writeOutput();
		}
		catch (NumberFormatException e)
		{
			System.out.println("Ошибка форматирования числа.");
		}
		catch (IllegalArgumentException | FileNotFoundException e)
		{
			System.out.println(e.getMessage());
		}
		catch (IOException e)
		{
			System.err.println("IO Error.");
		}
	}
}
