import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.Font;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.awt.event.ActionEvent;
import javax.swing.SwingConstants;

public class SearchPage extends JFrame {

	private JPanel contentPane;
	private JTextField txtSearchNewsArticles;
	
	public SearchPage() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 540, 361);
		setTitle("Search Engine");
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		txtSearchNewsArticles = new JTextField();
		txtSearchNewsArticles.setFont(new Font("Heiti TC", Font.PLAIN, 13));
		txtSearchNewsArticles.setHorizontalAlignment(SwingConstants.CENTER);
		txtSearchNewsArticles.setBounds(70, 140, 400, 30);
		contentPane.add(txtSearchNewsArticles);
		txtSearchNewsArticles.setColumns(10);
		
		JButton btnAddFiles = new JButton("ADD FILES");
		btnAddFiles.setFont(new Font("Heiti TC", Font.PLAIN, 13));
		btnAddFiles.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new AdditionPage().setVisible(true); 
				setVisible(false);
				dispose();
			}
		});
		
		JButton btnSearch = new JButton("SEARCH");
		btnSearch.setFont(new Font("Heiti TC", Font.PLAIN, 13));
		btnSearch.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ResultsPage x = new ResultsPage(txtSearchNewsArticles.getText());
				x.setVisible(true); 
				setVisible(false);
				dispose();
			}
		});
		
		JLabel lblNewLabel = new JLabel("N  E  W  S        S  E  A  R  C  H");
		lblNewLabel.setFont(new Font(".SF NS Text", Font.BOLD, 15));
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setBounds(70, 110, 400, 30);
		contentPane.add(lblNewLabel);
		
		btnSearch.setBounds(300, 175, 117, 29);
		contentPane.add(btnSearch);
		btnAddFiles.setBounds(120, 175, 117, 29);
		contentPane.add(btnAddFiles);
		
		JLabel label = new JLabel("");
		label.setIcon(new ImageIcon(SearchPage.class.getResource("/image/light-lines-540x337.png")));
		label.setBounds(0, 0, 542, 337);
		contentPane.add(label);
		
		
	}
}
