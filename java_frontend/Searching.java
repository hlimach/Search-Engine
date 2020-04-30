import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Searching {
	
	public static ArrayList<ArrayList<Integer>> singlewordSearch(Integer wordID, HashMap<Integer, ArrayList<ArrayList<Integer>>> smallInvertedIndex, HashMap<Integer, ArrayList<ArrayList<Integer>>> invertedIndex) {
	   
		ArrayList<ArrayList<Integer>> docIDs = new ArrayList<ArrayList<Integer>>(); // to store the matching DocIDs with frequency
		ArrayList<ArrayList<Integer>> plaindocIDs = new ArrayList<ArrayList<Integer>>(); // to store docIDs of larger barrel
		
		if(smallInvertedIndex.containsKey(wordID))
			docIDs = smallInvertedIndex.get(wordID);
		
		plaindocIDs = invertedIndex.get(wordID);
		
		//combining the two docID lists to make one
		ArrayList<Integer> temp = new ArrayList<Integer>();
		ArrayList<Integer> temp2 = new ArrayList<Integer>();
		ArrayList<ArrayList<Integer>> finaldocs = new ArrayList<ArrayList<Integer>>();
		
		
		//loop to remove the repeating values from the plaindocIDs 
		for(int x = 0; x < docIDs.size(); x++) {
			int flag = 0;
			temp = docIDs.get(x); //takes the fancy hit
			for(int y = 0; y < plaindocIDs.size(); y++) {
				temp2 = plaindocIDs.get(y); //takes all plain hits one by one
				if( temp.get(0).equals(temp2.get(0))) { //locates the plain hit same as fancy
					temp.set(1, 10000);
					plaindocIDs.remove(y);  //removes that hit from plaindocIDs
					finaldocs.add(temp); //adds the fancy hit to final vector
					
					flag = 1;
					break;
				}
			}
		}
		
		//method to sort plaindocIds based on their frequencies
		sortFinal s = new sortFinal();
		plaindocIDs = s.sort(plaindocIDs);
		
		//adding the plain hits to the final document ids 
		for(int x = 0 ;x <plaindocIDs.size();x++) {
			temp2 = plaindocIDs.get(x); //takes all plain hits one by one
			finaldocs.add(temp2);
		}
		
	    return finaldocs;
	}
}
