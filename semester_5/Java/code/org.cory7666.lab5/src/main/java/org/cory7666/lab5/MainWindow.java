package org.cory7666.lab5;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TabPane;
import javafx.stage.Stage;

public class MainWindow extends Application
{
	private final String layout = "layout/MainWindow.fxml";
	
	@Override
	public void start (Stage primaryStage) throws Exception
	{
		primaryStage.setScene(new Scene((TabPane) FXMLLoader.load(getClass().getClassLoader().getResource(layout))));
		primaryStage.setMinHeight(400.0);
		primaryStage.setTitle("Автомобили");
		primaryStage.centerOnScreen();
		primaryStage.show();
		
		Logger.debug(getClass(), "Окно создано.");
	}
}
