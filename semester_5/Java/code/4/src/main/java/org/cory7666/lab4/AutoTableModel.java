package org.cory7666.lab4;

import java.util.Arrays;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Set;

import javax.swing.table.AbstractTableModel;

public class AutoTableModel extends AbstractTableModel
{
	private static final long serialVersionUID = 6181788579049573897L;
	private final Set<Auto> data = new HashSet<>();
	private final String[] header = { "Марка", "Год выпуска", "Объём двигателя", "Максимальная скорость" };

	@Override
	public int getRowCount ()
	{ return data.size(); }

	@Override
	public int getColumnCount ()
	{ return 4; }

	@Override
	public Object getValueAt (int rowIndex, int columnIndex)
	{
		try
		{
			Auto element = getRow(rowIndex);
			return switch (columnIndex)
			{
			case 0 -> element.brand;
			case 1 -> element.year;
			case 2 -> element.engineVolume;
			case 3 -> element.maxSpeed;
			default -> "";
			};
		}
		catch (Exception e)
		{
			return "";
		}
	}

	@Override
	public String getColumnName (int column)
	{
		try
		{
			return header[column];
		}
		catch (Exception ex)
		{
			return "";
		}
	}

	public Auto getRow (int index)
	{
		int counter = 0;
		for (var t : data)
		{
			if (counter++ == index)
			{
				return t;
			}
		}
		throw new NoSuchElementException("Строки с запрошенным индексом не существует");
	}

	public Iterator<Auto> getStorableDataIter ()
	{ return data.iterator(); }

	public void addRows (Collection<Auto> rows)
	{
		rows.forEach(data::add);
		fireTableDataChanged();
	}

	public void addRows (Auto... rows)
	{
		addRows(Arrays.asList(rows));
	}

	public void deleteRow (int row)
	{
		int counter = 0;
		for (var iter = data.iterator(); iter.hasNext();)
		{
			iter.next();
			if (counter++ == row)
			{
				iter.remove();
				fireTableDataChanged();
				break;
			}
		}
	}

	public void deleteAllRows ()
	{
		data.clear();
		fireTableDataChanged();
	}

	public void replaceDataWithIfPresent (Collection<Auto> rows)
	{
		if (rows.size() > 0)
		{
			deleteAllRows();
			addRows(rows);
		}
	}

	public void replaceDataWithIfPresent (Auto... rows)
	{
		replaceDataWithIfPresent(Arrays.asList(rows));
	}
}
