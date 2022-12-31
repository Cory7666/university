import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.concurrent.CompletableFuture;
import java.util.stream.Collectors;

public class AbstractApplication
{
	protected static final int ARRAY_SIZE = 10000;
	protected static final int THREAD_COUNT = 3;
	protected static final int PRINT_STEP = 10;
	protected static final int[] THREAD_PRIORITIES = { Thread.MAX_PRIORITY, Thread.NORM_PRIORITY, Thread.MIN_PRIORITY };
	private static final Random gen = new Random();

	public static void main (String... args) throws InterruptedException
	{
		System.out.println("Создание");
		Integer[][] arrays = generateArrays(THREAD_COUNT, ARRAY_SIZE);

		for (int i = 0; i < THREAD_COUNT; ++i)
		{
			var thread = new Thread(new MyTask(arrays[i]));
			thread.setName("Sorter_" + (i + 1));
			thread.setPriority(THREAD_PRIORITIES[i % THREAD_PRIORITIES.length]);
			thread.start();
		}
	}

//	public static void printArray (Class<?> who, Integer[] array)
//	{
//		Logger.toLog(who, Arrays.stream(array).map(x -> x.toString()).collect(Collectors.joining("; ", "{", "}")));
//	}

	public static void printArray (Class<?> who, Integer[] array)
	{
		int i;
		for (i = 0; i + PRINT_STEP < array.length; i += PRINT_STEP + 1)
		{
			Logger
				.toLog(
					who,
					Arrays
						.stream(Arrays.copyOfRange(array, i, i + PRINT_STEP))
						.map(x -> x.toString())
						.collect(Collectors.joining("; ", "* ", " *")));
		}

		Logger
			.toLog(
				who,
				Arrays
					.stream(Arrays.copyOfRange(array, i, array.length))
					.map(x -> x.toString())
					.collect(Collectors.joining("; ", "* ", " *")));
	}

//	public synchronized static void printArray (Class<?> who, Integer[] array)
//	{
//		int i;
//		for (i = 0; i + PRINT_STEP < array.length; i += PRINT_STEP + 1)
//		{
//			Logger
//				.toLog(
//					who,
//					Arrays
//						.stream(Arrays.copyOfRange(array, i, i + PRINT_STEP))
//						.map(x -> x.toString())
//						.collect(Collectors.joining("; ", "* ", " *")));
//		}
//
//		Logger
//			.toLog(
//				who,
//				Arrays
//					.stream(Arrays.copyOfRange(array, i, array.length))
//					.map(x -> x.toString())
//					.collect(Collectors.joining("; ", "* ", " *")));
//	}

	private static Integer[] generateArray (Integer size)
	{
		var ret = new Integer[size];
		for (int i = 0; i < ret.length; ++i)
		{
			ret[i] = gen.nextInt();
		}
		return ret;
	}

	private static Integer[][] generateArrays (int count, int size)
	{
		var ret = new Integer[count][];
		List<CompletableFuture<Integer[]>> futures = new ArrayList<>(count - 1);

		for (int i = 0; i < ret.length - 1; ++i)
		{
			futures.add(CompletableFuture.supplyAsync( () -> generateArray(size)));
		}

		ret[0] = generateArray(size);

		for (int i = 0; i < futures.size(); ++i)
		{
			ret[i + 1] = futures.get(i).join();
		}

		return ret;
	}

	public static Integer[] sort (Integer[] arr)
	{
		for (int left = 0; left < arr.length; left++)
		{
			int value = arr[left];
			int i = left - 1;
			for (; i >= 0; i--)
			{
				if (value < arr[i])
				{
					arr[i + 1] = arr[i];
				}
				else
				{
					break;
				}
			}
			arr[i + 1] = value;
		}
		return arr;
	}
}

class MyTask implements Runnable
{
	private final Integer[] array;

	public MyTask (Integer[] array)
	{
		this.array = array;
	}

	@Override
	public void run ()
	{
		AbstractApplication.printArray(this.getClass(), AbstractApplication.sort(array));
	}
}

class Logger
{
	public static void toLog (Class<?> who, String message)
	{
		System.out.println(String.format("[%s/%s] %s", Thread.currentThread().getName(), who.getName(), message));
	}
}
