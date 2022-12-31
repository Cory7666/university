package org.cory7666.lab5;

import javafx.beans.property.SimpleFloatProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.chart.PieChart;
import javafx.scene.control.Button;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;

public class MainWindowController
{
	@FXML private Button loadFromFileButton, saveToFileButton;

	@FXML private TableView<Auto> table;
	@FXML private TableColumn<Auto, String> tableColumn_Brand;
	@FXML private TableColumn<Auto, Number> tableColumn_Year;
	@FXML private TableColumn<Auto, Number> tableColumn_EngineVolume;
	@FXML private TableColumn<Auto, Number> tableColumn_MaxSpeed;

	@FXML private TextField brandTextField, yearTextField, volumeTextField, speedTextField;
	@FXML private Button addRecordButton, editRecordButton, deleteRecordButton;

	@FXML private PieChart chart;

	private FileManipulationController fileManipController;
	private TableManipulationController tableManipController;
	private ChartController chartController;

	public MainWindowController ()
	{}

	@FXML
	public void initialize ()
	{
		Logger.debug(getClass(), "Контроллер создан.");

		table.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
		chartController = new ChartController(table, chart);

		tableColumn_Brand.setCellValueFactory(x -> new SimpleStringProperty(x.getValue().brand));
		tableColumn_Year.setCellValueFactory(x -> new SimpleIntegerProperty(x.getValue().year));
		tableColumn_EngineVolume.setCellValueFactory(x -> new SimpleFloatProperty(x.getValue().engineVolume));
		tableColumn_MaxSpeed.setCellValueFactory(x -> new SimpleIntegerProperty(x.getValue().maxSpeed));

		this.fileManipController = new FileManipulationController(table, chartController);
		loadFromFileButton.setOnMouseClicked(fileManipController::onLoadFromFileRequest);
		saveToFileButton.setOnMouseClicked(fileManipController::onSaveToFileRequest);

		this.tableManipController = new TableManipulationController(table, chartController, brandTextField,
			yearTextField, volumeTextField, speedTextField);
		addRecordButton.setOnMouseClicked(tableManipController::onAddDataRequest);
		editRecordButton.setOnMouseClicked(tableManipController::onEditDataRequest);
		deleteRecordButton.setOnMouseClicked(tableManipController::onDeleteDataRequest);

		table.setItems(FXCollections.observableArrayList());
		table.setOnMouseClicked(tableManipController::onTableRowSelected);
	}
}
