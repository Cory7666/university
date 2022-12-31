import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.stream.Collectors;

public class MyBuffer extends AbstractBuffer
	implements IBufferComputable, IBufferPrintable, IBufferSortable, IBufferStorable
{
	protected final Double[] data;

	public MyBuffer (int size)
	{
		super(size);
		this.data = new Double[this.size];
		generate();
	}

	@Override
	protected void generate ()
	{
		for (int i = 0; i < size; ++i)
			data[i] = generator.nextDouble();
	}

	@Override
	public void saveOneLine (File file) throws IOException
	{
		try (var writer = Files.newBufferedWriter(file.toPath()))
		{
			for (var element : data)
			{
				writer.write(element.toString());
				writer.write(" ");
			}
		}
	}

	@Override
	public void saveSeparateLines (File file) throws IOException
	{
		try (var writer = Files.newBufferedWriter(file.toPath()))
		{
			for (var element : data)
			{
				writer.write(element.toString());
				writer.newLine();
			}
		}
	}

	@Override
	public void sort ()
	{
		int i, j;
		for (int gap = data.length / 2; gap > 0; gap /= 2)
		{
			for (i = gap; i < data.length; i++)
			{
				Double tmp = data[i];
				for (j = i; j >= gap && tmp.compareTo(data[j - gap]) < 0; j -= gap)
				{
					data[j] = data[j - gap];
				}
				data[j] = tmp;
			}
		}
	}

	@Override
	public void printInfo ()
	{
		System.out.println(this.toString());
	}

	@Override
	public void printAll ()
	{
		System.out
			.println(
				"Содержимое буфера: "
					+ Arrays.stream(data).map(x -> x.toString()).collect(Collectors.joining("; ", "{", "}")) + ".");
	}

	@Override
	public void printFirstN (int n)
	{
		System.out
			.println(
				"Первые " + n + " элементов: "
					+ Arrays
						.stream(Arrays.copyOfRange(data, 0, n))
						.map(x -> x.toString())
						.collect(Collectors.joining("; ", "{", "}"))
					+ ".");
	}

	@Override
	public void printLastN (int n)
	{
		System.out
			.println(
				"Последние " + n + " элементов: "
					+ Arrays
						.stream(Arrays.copyOfRange(data, size - n, size))
						.map(x -> x.toString())
						.collect(Collectors.joining("; ", "{", "}"))
					+ ".");
	}

	@Override
	public void max ()
	{
		System.out.println("Максимальное значение в буфере: " + getMaxValue() + ".");
	}

	private Double getMaxValue ()
	{
		Double max = data[0];
		for (int i = 1; i < size; ++i)
		{
			if (data[i] > max)
			{
				max = data[i];
			}
		}
		return max;
	}

	@Override
	public void min ()
	{
		System.out.println("Минимально значение в буфере: " + getMinValue() + ".");
	}

	private Double getMinValue ()
	{
		Double min = data[0];
		for (int i = 1; i < size; ++i)
		{
			if (data[i] < min)
			{
				min = data[i];
			}
		}
		return min;
	}

	@Override
	public void sum ()
	{
		double sum = 0.0;
		for (var element : data)
		{
			sum += element;
		}

		System.out.println("Сумма: " + sum + ".");
	}

	@Override
	public String toString ()
	{
		return String.format("ID: %d. Тип: %s. Размер: %d.", id, data[0].getClass().getName(), size);
	}
}
