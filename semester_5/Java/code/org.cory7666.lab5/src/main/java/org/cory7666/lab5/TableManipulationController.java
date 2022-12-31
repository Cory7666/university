package org.cory7666.lab5;

import javafx.event.Event;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;

public class TableManipulationController
{
	private final TableView<Auto> table;
	private final TextField brandTextField, yearTextField, volumeTextField, speedTextField;
	private final ChartController chartController;

	private Auto previoslySelectedItem = null;

	public TableManipulationController (TableView<Auto> table, ChartController chartController,
		TextField brandTextField, TextField yearTextField, TextField volumeTextField, TextField speedTextField)
	{
		this.table = table;
		this.brandTextField = brandTextField;
		this.yearTextField = yearTextField;
		this.volumeTextField = volumeTextField;
		this.speedTextField = speedTextField;
		this.chartController = chartController;
	}

	public void onAddDataRequest (MouseEvent event)
	{
		Logger.debug(getClass(), "Добавление данных в таблицу.");

		try
		{
			var prevData = table.getItems();
			prevData.add(createObjectFromFields());

			chartController.updateChart();
		}
		catch (NumberFormatException ex)
		{
			Logger.error(getClass(), "Невозможно добавить: Одно из полей не заполнено.");
		}
		catch (Exception e)
		{
			Logger.error(getClass(), "Невозможно добавить: " + e.getMessage() + ".");
		}
	}

	public void onEditDataRequest (MouseEvent event)
	{
		Logger.debug(getClass(), "Изменение данных в таблице.");

		Auto newItemValue = createObjectFromFields();

		var data = table.getItems();
		data.add(data.indexOf(previoslySelectedItem), newItemValue);
		table.setItems(data);

		previoslySelectedItem = newItemValue;

		chartController.updateChart();
	}

	public void onDeleteDataRequest (MouseEvent event)
	{
		Logger.debug(getClass(), "Удаление данных из таблицы.");

		var data = table.getItems();
		data.remove(createObjectFromFields());
		table.setItems(data);

		chartController.updateChart();
	}

	public void onTableRowSelected (Event event)
	{
		previoslySelectedItem = table.getSelectionModel().getSelectedItem();

		if (previoslySelectedItem == null)
		{
			return;
		}

		writeObjectToFields(previoslySelectedItem);

		table.getSelectionModel().clearSelection();
	}

	private Auto createObjectFromFields ()
	{
		return new Auto(brandTextField.getText(), Integer.parseInt(yearTextField.getText()),
			Float.parseFloat(volumeTextField.getText()), Integer.parseInt(speedTextField.getText()));
	}

	private void writeObjectToFields (Auto o)
	{
		brandTextField.setText(o.brand);
		yearTextField.setText(o.year.toString());
		volumeTextField.setText(o.engineVolume.toString());
		speedTextField.setText(o.maxSpeed.toString());
	}
}
