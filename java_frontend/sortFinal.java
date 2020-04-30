import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class sortFinal {
	ArrayList<ArrayList<Integer>> sort (ArrayList<ArrayList<Integer>> docs){
	
		Collections.sort(docs, new Comparator<ArrayList<Integer>>() {    
	        @Override
	        public int compare(ArrayList<Integer> o1, ArrayList<Integer> o2) {
	            return o2.get(1).compareTo(o1.get(1));
	        }               
	});
		
		return docs;
	}
}
