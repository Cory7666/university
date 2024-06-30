import java.io.IOException;
import java.util.List;

class UserInteraction
{
	private final Params params;
	private final String inMessage;
	private final String outMessage;
	private List<Double> numbers;

	public UserInteraction (Params params, String inMessage, String outMessage)
	{
		this.params = params;
		this.inMessage = inMessage;
		this.outMessage = outMessage;
	}

	public UserInteraction readNumbers () throws IOException
	{
		if (params.interactiveInput)
		{
			System.out.print(inMessage + ": ");
		}

		this.numbers = List.of(params.in.readLine().split("\\s")).stream().map(x -> Double.parseDouble(x)).toList();

		return this;
	}

	public UserInteraction writeOutput () throws IOException
	{
		try
		{
			params.out
				.write(
					(params.interactiveOutput ? outMessage + ": " : "") + String
						.join(
							"; ",
							new QuadraticEquation(numbers.get(0), numbers.get(1), numbers.get(2))
								.solve()
								.stream()
								.map(x -> x.toString())
								.toList()));
			params.out.newLine();
		}
		catch (ArithmeticException e)
		{
			params.out.write(e.getMessage());
			params.out.newLine();
		}
		catch (IndexOutOfBoundsException e)
		{
			params.out.write("ERROR: Not enought params.");
			params.out.newLine();
		}

		params.out.flush();

		return this;
	}
}
