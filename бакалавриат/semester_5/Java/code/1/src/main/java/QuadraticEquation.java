import java.util.List;

class QuadraticEquation
{
	private final double a, b, c;

	public QuadraticEquation (double a, double b, double c)
	{
		this.a = a;
		this.b = b;
		this.c = c;
	}

	public List<Double> solve () throws ArithmeticException
	{
		final double sqrt_D = Math.sqrt(b * b - 4 * a * c);
		if (sqrt_D == sqrt_D)
		{
			return List.of((-b + sqrt_D) / 2, (-b - sqrt_D) / 2);
		}
		else
		{
			throw new ArithmeticException("The discriminant is less than zero.");
		}
	}
}
