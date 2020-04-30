import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;

import javax.swing.JTextField;
import javax.swing.SwingConstants;
import java.awt.Color;
import javax.swing.JButton;

public class AdditionPage extends JFrame {

	private JPanel contentPane;
	private JTextField txtStart;
	private JTextField textEnd;

	/**
	 * Create the frame.
	 */
	public AdditionPage() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 500, 300);
		setTitle("Add Files");
		contentPane = new JPanel();
		contentPane.setBackground(new Color(220, 227, 232));
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JButton btnReturn = new JButton("RETURN");
		btnReturn.setFont(new Font("Heiti TC", Font.PLAIN, 13));
		btnReturn.setBounds(20, 235, 100, 29);
		contentPane.add(btnReturn);
		btnReturn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new SearchPage().setVisible(true); 
				setVisible(false);
				dispose();
			}
		});
		
		textEnd = new JTextField();
		textEnd.setHorizontalAlignment(SwingConstants.CENTER);
		textEnd.setColumns(10);
		textEnd.setBounds(255, 145, 80, 26);
		contentPane.add(textEnd);
		textEnd.addKeyListener(new KeyAdapter() {
	         public void keyPressed(KeyEvent ke) {
	            if (ke.getKeyChar() >= '0' && ke.getKeyChar() <= '9') {
	            } else {
	            	textEnd.setText("Error");
	            }
	         }
	      });
		
		txtStart = new JTextField();
		txtStart.setHorizontalAlignment(SwingConstants.CENTER);
		txtStart.setBounds(140, 145, 80, 26);
		contentPane.add(txtStart);
		txtStart.setColumns(10);
		txtStart.addKeyListener(new KeyAdapter() {
	         public void keyPressed(KeyEvent ke) {
	            if (ke.getKeyChar() >= '0' && ke.getKeyChar() <= '9') {
	            } else {
	            	txtStart.setText("Error");
	            }
	         }
	      });
		
		JButton btnNewButton = new JButton("INSERT");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(Integer.parseInt(txtStart.getText()) > Integer.parseInt(textEnd.getText()) || 
						Integer.parseInt(txtStart.getText()) < 50000) {
					JOptionPane.showMessageDialog(null, "Invalid inputs.");
				}
				else {
					try {
						ReadfromFile.insertDocs(txtStart.getText(), textEnd.getText());
					} catch (FileNotFoundException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					JOptionPane.showMessageDialog(null, "Files inserted.");
				}
			}
		});
		btnNewButton.setFont(new Font("Heiti TC", Font.PLAIN, 13));
		btnNewButton.setBounds(340, 144, 80, 29);
		contentPane.add(btnNewButton);
		
		JLabel lblTo = new JLabel("To");
		lblTo.setFont(new Font(".SF NS Text", Font.PLAIN, 13));
		lblTo.setBounds(230, 150, 30, 16);
		contentPane.add(lblTo);
		
		JLabel lblFrom = new JLabel("From");
		lblFrom.setFont(new Font(".SF NS Text", Font.PLAIN, 13));
		lblFrom.setBounds(100, 150, 50, 16);
		contentPane.add(lblFrom);
		
		JLabel lblmustBeAbove = new JLabel("*must be above 50001");
		lblmustBeAbove.setFont(new Font(".SF NS Text", Font.PLAIN, 13));
		lblmustBeAbove.setBounds(274, 112, 206, 16);
		contentPane.add(lblmustBeAbove);
		
		JLabel lblSpecifyDocidsTo = new JLabel("S P E C I F Y   D O C I D s   T O   B E   A D D E D");
		lblSpecifyDocidsTo.setHorizontalAlignment(SwingConstants.CENTER);
		lblSpecifyDocidsTo.setFont(new Font(".SF NS Text", Font.BOLD, 15));
		lblSpecifyDocidsTo.setBounds(50, 80, 400, 40);
		contentPane.add(lblSpecifyDocidsTo);
		
		JLabel label = new JLabel("");
		label.setBackground(Color.WHITE);
		label.setIcon(null);
		label.setBounds(0, 0, 500, 490);
		contentPane.add(label);
	}

}
