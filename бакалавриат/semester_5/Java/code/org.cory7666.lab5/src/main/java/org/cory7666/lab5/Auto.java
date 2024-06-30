package org.cory7666.lab5;

import com.opencsv.bean.CsvBindByName;

public class Auto
{
	@CsvBindByName (column = "Brand") public final String brand;
	@CsvBindByName (column = "Year") public final Integer year;
	@CsvBindByName (column = "Max Speed") public final Integer maxSpeed;
	@CsvBindByName (column = "Engine Volume") public final Float engineVolume;

	public Auto (String brand, Integer year, Float engineVolume, Integer maxSpeed)
	{
		if (brand == null)
		{
			throw new IllegalArgumentException("brand не может быть пустым.");
		}

		if (year < 1800)
		{
			throw new IllegalArgumentException("Год должен быть больше 1800.");
		}

		if (engineVolume < 0.0)
		{
			throw new IllegalArgumentException("Объём двигателя не может быть меньше нуля.");
		}

		if (maxSpeed <= 0)
		{
			throw new IllegalArgumentException("Максимальная скорость должна быть больше нуля.");
		}

		this.brand = brand;
		this.year = year;
		this.engineVolume = engineVolume;
		this.maxSpeed = maxSpeed;
	}

	public Auto ()
	{
		brand = "undefined";
		year = 0;
		maxSpeed = 0;
		engineVolume = 0.0f;
	}

	@Override
	public boolean equals (Object o)
	{
		if (o instanceof Auto other)
		{
			return this.brand.equals(other.brand) && this.engineVolume.equals(other.engineVolume)
				&& this.year.equals(other.year) && this.maxSpeed.equals(other.maxSpeed);
		}
		else
		{
			return false;
		}
	}
}
