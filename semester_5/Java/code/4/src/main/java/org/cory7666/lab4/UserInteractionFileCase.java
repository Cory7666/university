package org.cory7666.lab4;

import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

public class UserInteractionFileCase
{
	private final JFileChooser chooser;

	public UserInteractionFileCase ()
	{
		chooser = new JFileChooser();
		chooser.setFileFilter(new FileNameExtensionFilter("Файл CSV", "csv"));
	}

	public File getReadableFileLocation ()
	{
		chooser.setDialogTitle("Открыть файл");
		chooser.showOpenDialog(null);
		return chooser.getSelectedFile();
	}

	public File getSaveFileLocation ()
	{
		chooser.setDialogTitle("Сохранить");
		chooser.showSaveDialog(null);
		return chooser.getSelectedFile();
	}
}
