import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;

import java.awt.Color;
import java.awt.Desktop;

import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.Font;
import java.awt.List;
import java.awt.ScrollPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Vector;

import javax.swing.JTable;
import javax.swing.JScrollPane;

public class ResultsPage extends JFrame {

	private JPanel contentPane;
	private JTextField textField;
	private JTable table;

	/**
	 * Create the frame.
	 */
	public ResultsPage(String str) {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 500, 500);
		setTitle("Results");
		contentPane = new JPanel();
		contentPane.setBackground(new Color(220, 227, 232));
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(30, 90, 440, 350);
		contentPane.add(scrollPane);
		
		table = new JTable();
		table.setRowSelectionAllowed(true);
		table.setBackground(new Color(220, 227, 232));
		scrollPane.setViewportView(table);
		DefaultTableModel tableModel = new DefaultTableModel();
		tableModel.addColumn("DocID");
		//parsing the query
		String query = str;
		String[] tokens = query.split(" ");
						  
		ArrayList<ArrayList<Integer>> docsFinal = new ArrayList<ArrayList<Integer>>();

		//creating the searching algorithm
		for(int parwords = 0; parwords < tokens.length ; parwords++) {
			ArrayList<ArrayList<Integer>> docs = new ArrayList<ArrayList<Integer>>();
			if (RunPage.lex.get(tokens[parwords]) != null){
				int wordID = RunPage.lex.get(tokens[parwords]);
				Searching y = new Searching();
				if (wordID % 4 == 0)
					docs = y.singlewordSearch(RunPage.lex.get(tokens[parwords]), RunPage.sii, RunPage.ii4);
				else if (wordID % 3 == 0)
					docs = y.singlewordSearch(RunPage.lex.get(tokens[parwords]), RunPage.sii, RunPage.ii3);
				else if (wordID % 2 == 0)
					docs = y.singlewordSearch(RunPage.lex.get(tokens[parwords]), RunPage.sii, RunPage.ii2);
				else
					docs = y.singlewordSearch(RunPage.lex.get(tokens[parwords]), RunPage.sii, RunPage.ii1);
			}   
		else
		    System.out.println("No matching results found!" );
				 

		//check for multiword query
		if(tokens.length == 1) {
			docsFinal = docs;
		}
					
		//check for the token to see if the token is the first then save it to the final docid list
		//this will tell if the second and onward token is being searched now
		if(parwords == 0) {
			docsFinal = docs;
		}
					
		if(parwords != 0) {
			multiWord mul = new multiWord();
			docsFinal = mul.multiWordSearching(docsFinal, docs);
						
			//method to sort based on their frequencies
			sortFinal s = new sortFinal();
			docsFinal = s.sort(docsFinal);
						
		}	
		}
				
		for(int z = 0; z < docsFinal.size(); z++) {
		    Vector<Vector<Integer>> docIDs = new Vector<Vector<Integer>>();
		    Vector<Integer> temp = new Vector<Integer>();
			temp.add(docsFinal.get(z).get(0));
			docIDs.add(temp);
			tableModel.addRow((docIDs));
		}

		table.setModel(tableModel);
		table.addMouseListener(new java.awt.event.MouseAdapter(){
				public void mouseClicked(java.awt.event.MouseEvent e){
					int row=table.rowAtPoint(e.getPoint());
					int col= table.columnAtPoint(e.getPoint());
					String temp = table.getValueAt(row,col).toString();
					temp = temp.substring(1,temp.length()-1);
					temp += ".txt";
					if (Desktop.isDesktopSupported()) {
					    try {
					        File myFile = new File("/Users/haleema/Desktop/XCode Practice/C++/SearchEngine/data/" + temp);
					        Desktop.getDesktop().open(myFile);
					    } catch (IOException ex) {
					        // no application registered for PDFs
					    }
					}

				}

		});

		
		textField = new JTextField();
		textField.setBounds(20, 20, 370, 30);
		contentPane.add(textField);
		textField.setColumns(10);
		textField.setText(query);
		
		JButton btnNewButton = new JButton("SEARCH");
		btnNewButton.setFont(new Font("Heiti TC", Font.PLAIN, 13));
		btnNewButton.setBounds(387, 21, 100, 29);
		contentPane.add(btnNewButton);
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new ResultsPage(textField.getText()).setVisible(true); 
				setVisible(false);
				dispose();
			}
		});
		
		JLabel lblNewLabel = new JLabel("R  E  S  U  L  T  S");
		lblNewLabel.setFont(new Font(".SF NS Text", Font.PLAIN, 13));
		lblNewLabel.setBounds(30, 62, 150, 16);
		contentPane.add(lblNewLabel);
		
		JButton btnReturnToHomepage = new JButton("RETURN TO HOME");
		btnReturnToHomepage.setFont(new Font("Heiti TC", Font.PLAIN, 13));
		btnReturnToHomepage.setBounds(175, 445, 150, 29);
		contentPane.add(btnReturnToHomepage);
		btnReturnToHomepage.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new SearchPage().setVisible(true); 
				setVisible(false);
				dispose();
			}
		});
	
	}
	
}
