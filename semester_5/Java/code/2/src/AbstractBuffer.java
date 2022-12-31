import java.util.Random;

public abstract class AbstractBuffer
{
	private static int count = 0;
	protected static final Random generator = new Random();

	protected final int id;
	protected final int size;

	public AbstractBuffer (int size)
	{
		this.id = ++count;
		this.size = size;
	}

	public final int getId ()
	{ return id; }

	public final int size ()
	{
		return size;
	}

	protected abstract void generate ();
}
