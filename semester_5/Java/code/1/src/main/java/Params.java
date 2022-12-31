import java.io.BufferedReader;
import java.io.BufferedWriter;

class Params
{
	public final BufferedReader in;
	public final BufferedWriter out;
	public final boolean interactiveInput, interactiveOutput;

	public Params (BufferedReader in, BufferedWriter out, boolean interactiveInput, boolean interactiveOutput)
	{
		this.in = in;
		this.out = out;
		this.interactiveInput = interactiveInput;
		this.interactiveOutput = interactiveOutput;
	}
}
