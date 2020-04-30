import java.awt.EventQueue;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class RunPage {
	
	public static HashMap<String,Integer> lex;
	public static HashMap<Integer,ArrayList<ArrayList<Integer>>> sii;
	public static HashMap<Integer,ArrayList<ArrayList<Integer>>> ii1;
	public static HashMap<Integer,ArrayList<ArrayList<Integer>>> ii2;
	public static HashMap<Integer,ArrayList<ArrayList<Integer>>> ii3;
	public static HashMap<Integer,ArrayList<ArrayList<Integer>>> ii4;

	public static void main(String[] args) throws NumberFormatException, IOException {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
			
		lex = ReadfromFile.readLexicon("lexicon.txt");
		System.out.println(lex.size());
		sii = ReadfromFile.readSmallInvertedIndex("small_inverted_index.txt");
		ii1 = ReadfromFile.readInvertedIndex("inverted_index1.txt");
		ii2 = ReadfromFile.readInvertedIndex("inverted_index2.txt");
		ii3 = ReadfromFile.readInvertedIndex("inverted_index3.txt");
		ii4 = ReadfromFile.readInvertedIndex("inverted_index4.txt");
		
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					SearchPage frame = new SearchPage();
					frame.setTitle("Search Engine");
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
		
		
		
		
		
	}

}
