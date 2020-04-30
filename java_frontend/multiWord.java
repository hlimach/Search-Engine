import java.util.ArrayList;

public class multiWord{
	
	ArrayList<ArrayList<Integer>> multiWordSearching(ArrayList<ArrayList<Integer>> docsFinal,ArrayList<ArrayList<Integer>> docs){
		//loop to combine the two ArrayLists into one final that contains documents that are common
		//return list of docIds and hits
		
		ArrayList<Integer> temp = new ArrayList<Integer>();
		ArrayList<Integer> temp2 = new ArrayList<Integer>();
		ArrayList<ArrayList<Integer>> combined = new ArrayList<ArrayList<Integer>>();
		
				for(int x = 0; x < docs.size(); x++) {
					temp = docs.get(x); //takes the docs
					for(int y = 0; y < docsFinal.size(); y++) {
						temp2 = docsFinal.get(y); //takes all values of docsFinal one by one
						if( temp.get(0).equals(temp2.get(0))) { //locates common ones
							temp.set(1, temp.get(1)+temp2.get(1));
							combined.add(temp); //adds the fancy hit to final vector
							break;
						}
					}
				}

		return combined;
	}

}
