package org.cory7666.lab4;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.border.EmptyBorder;

public class MainWindow extends JFrame
{
	private static final long serialVersionUID = -26268648356920251L;

	private final AutoTableModel tableModel = new AutoTableModel();

	private final JPanel rootPane = new JPanel();
	private final JPanel panelWithButtons = new JPanel();
	private final JPanel panelWithFields = new JPanel();
	private final JTable dataTable = new JTable(tableModel);
	private final JScrollPane scrollPane = new JScrollPane(dataTable);

	private final JButton addRecordButton = new JButton("Добавить запись"),
		updateRecordButton = new JButton("Изменить запись"), deleteRecordButton = new JButton("Удалить выделенное"),
		chooseInputFileButton = new JButton("Загрузить данные"),
		chooseOutputFileButton = new JButton("Выгрузить данные");

	private final JLabel brandFieldLabel = new JLabel("Марка"), yearFieldLabel = new JLabel("Год выпуска"),
		engineVolumeFieldLabel = new JLabel("Объём двигателя"),
		maxSpeedFieldLabel = new JLabel("Максимальная скорость");
	private final TextFieldGroup textFieldGroup = new TextFieldGroup();

	private final MainWindowController controller = new MainWindowController(dataTable, textFieldGroup);

	/**
	 * Launch the application.
	 */
	public static void main (String[] args)
	{
		EventQueue.invokeLater(new Runnable() {
			public void run ()
			{
				try
				{
					MainWindow frame = new MainWindow();
					frame.setVisible(true);
					frame.pack();
				}
				catch (Exception e)
				{
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public MainWindow ()
	{
		/* Окно приложения */
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Автомобили Ltd.");
		setBounds(100, 100, 450, 300);

		/* Корневая панель */
		rootPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		rootPane.setLayout(new BorderLayout(0, 0));
		setContentPane(rootPane);

		/* Прокручеваемая панель */
		rootPane.add(scrollPane, BorderLayout.CENTER);

		/* Панель с кнопками */
		rootPane.add(panelWithButtons, BorderLayout.EAST);
		panelWithButtons.setLayout(new BoxLayout(panelWithButtons, BoxLayout.Y_AXIS));
		panelWithButtons.add(addRecordButton);
		panelWithButtons.add(updateRecordButton);
		panelWithButtons.add(deleteRecordButton);
		panelWithButtons.add(chooseInputFileButton);
		panelWithButtons.add(chooseOutputFileButton);

		/* Панель с полями ввода */
		GridLayout gridLayout = new GridLayout(0, 2);
		panelWithFields.setLayout(gridLayout);
		rootPane.add(panelWithFields, BorderLayout.NORTH);

		panelWithFields.add(brandFieldLabel);
		panelWithFields.add(textFieldGroup.brandField);
		panelWithFields.add(yearFieldLabel);
		panelWithFields.add(textFieldGroup.yearField);
		panelWithFields.add(engineVolumeFieldLabel);
		panelWithFields.add(textFieldGroup.engineVolumeField);
		panelWithFields.add(maxSpeedFieldLabel);
		panelWithFields.add(textFieldGroup.maxSpeedField);

		/* Таблица */
		dataTable.getSelectionModel().setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		setHandlers();
	}

	private void setHandlers ()
	{
		addRecordButton.addActionListener(controller::onAddRecord);
		updateRecordButton.addActionListener(controller::onUpdateRecord);
		deleteRecordButton.addActionListener(controller::onDeleteRecord);
		chooseInputFileButton.addActionListener(controller::onLoadDataFromFileAction);
		chooseOutputFileButton.addActionListener(controller::onSaveDataAction);
		dataTable.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked (MouseEvent event)
			{
				controller.onRowSelectedAction(event);
			}
		});
	}
}
