package org.cory7666.lab5;

import java.util.HashMap;

import javafx.collections.FXCollections;
import javafx.scene.chart.PieChart;
import javafx.scene.control.TableView;

public class ChartController
{
	private final TableView<Auto> table;
	private final PieChart chart;

	public ChartController (TableView<Auto> table, PieChart chart)
	{
		this.table = table;
		this.chart = chart;
	}

	public void updateChart ()
	{
		var tableData = table.getItems();
		var counter = new HashMap<Float, Integer>();

		tableData.forEach(x -> {
			var c = counter.get(x.engineVolume);
			if (c == null)
			{
				counter.put(x.engineVolume, 1);
			}
			else
			{
				counter.replace(x.engineVolume, c + 1);
			}
		});

		chart
			.setData(FXCollections
				.observableList(counter
					.entrySet().stream().map(x -> new PieChart.Data(x.getKey().toString() + " попугаев", x.getValue().doubleValue()))
					.toList()));;
	}
}
