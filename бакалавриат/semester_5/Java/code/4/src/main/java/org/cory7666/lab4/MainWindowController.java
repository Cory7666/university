package org.cory7666.lab4;

import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;

import javax.swing.JTable;

public class MainWindowController
{
	private final JTable table;
	private final TextFieldGroup textFieldGroup;

	public MainWindowController (JTable table, TextFieldGroup textFieldGroup)
	{
		this.table = table;
		this.textFieldGroup = textFieldGroup;
	}

	public void onAddRecord (ActionEvent e)
	{
		try
		{
			Auto t = textFieldGroup.constructObjectFromTextFields();
			Logger.debug(getClass(), "Добавление в таблицу " + t + ".");
			((AutoTableModel) table.getModel()).addRows(textFieldGroup.constructObjectFromTextFields());
		}
		catch (NumberFormatException ex)
		{
			Logger.error(getClass(), "Невозможно добавить объект: Одной из полей заполнено неправильно.");
		}
		catch (Exception ex)
		{
			Logger.error(getClass(), "Невозможно добавить объект: " + ex.getMessage() + ".");
		}
	}

	public void onUpdateRecord (ActionEvent e)
	{
		Logger.debug(getClass(), "Запрос на замену записи #" + table.getSelectedRow() + ".");
		try
		{
			try
			{
				if (table.getSelectedRow() >= 0)
				{
					var model = ((AutoTableModel) table.getModel());
					model.deleteRow(table.getSelectedRow());
					model.addRows(textFieldGroup.constructObjectFromTextFields());
				}
				else
				{
					throw new IllegalArgumentException("Нечего менять");
				}
			}
			catch (NumberFormatException ex)
			{
				throw new IllegalArgumentException("Одной из полей заполнено неправильно");
			}
		}
		catch (Exception ex)
		{
			Logger.error(getClass(), "Невозможно изменить запись: " + ex.getMessage() + ".");
		}
	}

	public void onDeleteRecord (ActionEvent e)
	{
		Logger.debug(getClass(), "Запрос на удаление записи #" + table.getSelectedRow() + ".");
		((AutoTableModel) table.getModel()).deleteRow(table.getSelectedRow());
	}

	public void onLoadDataFromFileAction (ActionEvent e)
	{
		Logger.debug(getClass(), "Запрос на загрузку данных из файла.");
		try
		{
			((AutoTableModel) table.getModel())
				.replaceDataWithIfPresent(
					new DataFile(new UserInteractionFileCase().getReadableFileLocation()).readAll());
		}
		catch (NullPointerException ex)
		{}
		catch (Exception ex)
		{
			Logger.error(getClass(), "Ошибка: " + ex.getMessage() + ".");
		}
	}

	public void onSaveDataAction (ActionEvent event)
	{
		Logger.debug(getClass(), "Запрос на сохранение данных в файл.");
		try
		{
			new DataFile(new UserInteractionFileCase().getSaveFileLocation())
				.writeAll(((AutoTableModel) table.getModel()).getStorableDataIter());
		}
		catch (NullPointerException ex)
		{}
		catch (Exception ex)
		{
			Logger.error(getClass(), "Невозможно сохранить данные: " + ex.getMessage() + ",");
		}
	}

	public void onRowSelectedAction (MouseEvent event)
	{
		textFieldGroup.fillTextFieldDataWith(((AutoTableModel) table.getModel()).getRow(table.getSelectedRow()));
	}
}
