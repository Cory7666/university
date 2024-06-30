package org.cory7666.lab4;

import javax.swing.JTextField;

public class TextFieldGroup
{
	public final JTextField brandField = new JTextField();
	public final JTextField yearField = new JTextField();
	public final JTextField engineVolumeField = new JTextField();
	public final JTextField maxSpeedField = new JTextField();

	public Auto constructObjectFromTextFields ()
	{
		var x = new Auto(brandField.getText(), Integer.parseInt(yearField.getText()),
			Float.parseFloat(engineVolumeField.getText()), Integer.parseInt(maxSpeedField.getText()));
		return x;
	}

	public void fillTextFieldDataWith (Auto x)
	{
		brandField.setText(x.brand.toString());
		yearField.setText(x.year.toString());
		engineVolumeField.setText(x.engineVolume.toString());
		maxSpeedField.setText(x.maxSpeed.toString());
	}

	public void clearFields ()
	{
		brandField.setText("");
		yearField.setText("");
		engineVolumeField.setText("");
		maxSpeedField.setText("");
	}
}
