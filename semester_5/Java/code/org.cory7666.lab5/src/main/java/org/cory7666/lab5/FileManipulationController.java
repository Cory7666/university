package org.cory7666.lab5;

import java.io.File;

import javafx.collections.FXCollections;
import javafx.scene.Node;
import javafx.scene.control.TableView;
import javafx.scene.input.MouseEvent;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;
import javafx.stage.Window;

public class FileManipulationController
{
	private final TableView<Auto> table;
	private final ChartController chartController;

	public FileManipulationController (TableView<Auto> table, ChartController chartController)
	{
		this.table = table;
		this.chartController = chartController;
	}

	public void onLoadFromFileRequest (MouseEvent event)
	{
		try
		{
			Logger.debug(getClass(), "Запрос на загрузку данных из файла. Запрос пути к файлу.");

			Window scene = getSceneFromEvent(event);
			FileChooser chooser = new FileChooser();
			chooser.setTitle("Загрузить из...");
			chooser
				.getExtensionFilters()
				.addAll(new ExtensionFilter("CSV файл", "*.csv"), new ExtensionFilter("Все файлы", "*"));
			File inFile = chooser.showOpenDialog(scene);

			if (inFile == null)
			{
				Logger.debug(getClass(), "Пользователь отменил выбор файла.");
			}
			else
			{
				Logger.debug(getClass(), "Пользователь выбрал файл " + inFile.toString() + ".");
				table.setItems(FXCollections.observableArrayList(new DataFile(inFile).readAll()));
			}

			chartController.updateChart();
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
	}

	public void onSaveToFileRequest (MouseEvent event)
	{
		try
		{
			Logger.debug(getClass(), "Запрос на выгрузку данных из приложения.");

			Window scene = getSceneFromEvent(event);
			FileChooser chooser = new FileChooser();
			chooser.setTitle("Сохранить в...");
			chooser
				.getExtensionFilters()
				.addAll(new ExtensionFilter("CSV файл", "*.csv"), new ExtensionFilter("Все файлы", "*"));

			File outFile = chooser.showSaveDialog(scene);

			if (outFile != null)
			{
				Logger.debug(getClass(), "Выгрузка в " + outFile.toString() + ".");
				new DataFile(outFile).writeAll(table.getItems().iterator());
			}
			else
			{
				Logger.debug(getClass(), "Пользователь отменил операцию выгрузки.");
			}

			chartController.updateChart();
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
	}

	private Window getSceneFromEvent (MouseEvent event)
	{
		return ((Node) event.getSource()).getScene().getWindow();
	}
}
