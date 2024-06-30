import java.io.File;
import java.io.IOException;

public interface IBufferStorable
{
	public void saveOneLine (File file) throws IOException;

	public void saveSeparateLines (File file) throws IOException;
}
