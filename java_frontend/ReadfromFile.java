import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;
import java.util.ArrayList; 

public class ReadfromFile {
	
	public static void insertDocs(String start, String end) throws FileNotFoundException {
		int docID = Integer.parseInt(start), lastWordID = RunPage.lex.size()+1, fancy = -1, ending = Integer.parseInt(end);
		
		//running loop for all documents
		while (docID <= ending) {
			
			//opening the file to parse
			String filename = Integer.toString(docID) + ".txt";
			System.out.println(docID);
			File file = new File("/Users/haleema/Desktop/XCode Practice/C++/SearchEngine/data/" + filename); 
			
			Scanner sc = new Scanner(file);
			String str, word;
			int count = 0, plain = 0;

			//loop to the end of the document
	        while(sc.hasNextLine()) {
	            
	        	//taking the first line of the document which is the title
	            str = sc.nextLine();
	            
	            //parsing the string
	            String[] arrOfStr = str.split(" "); 
	            
	            //loop for the entire parsed string
	            for(int i = 0; i < arrOfStr.length; i++) {
	            	
	                int wordID;
	                
	                //checking  if the parsed word exists in the lexicon 
	                if (RunPage.lex.containsKey(arrOfStr[i]))
	                    wordID = RunPage.lex.get(arrOfStr[i]);
	                else { //creating a new word id in the lexicon
	                    wordID = lastWordID + 1;
	                    RunPage.lex.put(arrOfStr[i], wordID);
	                    lastWordID++;
	                }
	                System.out.println("end of lex stuff " +wordID);
	                
	                //checking wordid against the correct barrel
	                if (wordID % 4 == 0) {
	                	System.out.println(arrOfStr[i] + "ii4");
	                	if(RunPage.ii4.containsKey(wordID)) {
	                		boolean contains = false;
	                		for(int index = 0; index < RunPage.ii4.get(wordID).size(); index++) {
	                			
	                			if(RunPage.ii4.get(wordID).get(index).get(0) == docID) {
	                				
	                				if (count == 0 || count == 1 || count == 2 || count == 3)
	                					RunPage.ii4.get(wordID).get(index).add(fancy);
	    	    	                else if (count == 6) {
	    	    	                	RunPage.ii4.get(wordID).get(index).add(plain);
	    	    	                    plain++;
	    	    	                }
	                				
	                				contains = true;
	                				break;
	                				
	                			}
	                			
	                		}
	                		
	                		if(!contains) {
	                			ArrayList<Integer> temp = new ArrayList<Integer>();
	                			temp.add(docID);
	                			RunPage.ii4.get(wordID).add(temp);
	                			
	                			int size = RunPage.ii4.get(wordID).size();
	                			System.out.println("insertion done");
	                			if (count == 0 || count == 1 || count == 2 || count == 3)
                					RunPage.ii4.get(wordID).get(size-1).add(fancy);
    	    	                else if (count == 6) {
    	    	                	RunPage.ii4.get(wordID).get(size-1).add(plain);
    	    	                    plain++;
    	    	                }
	                			
	                		}
	                		
	                	}
	                	else {
	                		System.out.println("doesnt contain wordid");
	                		ArrayList<Integer> temp = new ArrayList<Integer>();
                			temp.add(docID);
                			ArrayList<ArrayList<Integer>> store = new ArrayList<ArrayList<Integer>>();
                			store.add(temp);
	                		RunPage.ii4.put(wordID, store);
	                		if (count == 0 || count == 1 || count == 2 || count == 3)
            					RunPage.ii4.get(wordID).get(0).add(fancy);
	    	                else if (count == 6) {
	    	                	RunPage.ii4.get(wordID).get(0).add(plain);
	    	                    plain++;
	    	                }
	                	}
	                }
	                else if (wordID % 3 == 0) {
	                	System.out.println(arrOfStr[i] + "ii3");
	                	if(RunPage.ii3.containsKey(wordID)) {
	                		boolean contains = false;
	                		for(int index = 0; index < RunPage.ii3.get(wordID).size(); index++) {
	                			
	                			if(RunPage.ii3.get(wordID).get(index).get(0) == docID) {
	                				
	                				if (count == 0 || count == 1 || count == 2 || count == 3)
	                					RunPage.ii3.get(wordID).get(index).add(fancy);
	    	    	                else if (count == 6) {
	    	    	                	RunPage.ii3.get(wordID).get(index).add(plain);
	    	    	                    plain++;
	    	    	                }
	                				
	                				contains = true;
	                				break;
	                				
	                			}
	                			
	                		}
	                		
	                		if(!contains) {
	                			ArrayList<Integer> temp = new ArrayList<Integer>();
	                			temp.add(docID);
	                			RunPage.ii3.get(wordID).add(temp);
	                			
	                			int size = RunPage.ii3.get(wordID).size();
	                			System.out.println("insertion done");
	                			if (count == 0 || count == 1 || count == 2 || count == 3)
                					RunPage.ii3.get(wordID).get(size-1).add(fancy);
    	    	                else if (count == 6) {
    	    	                	RunPage.ii3.get(wordID).get(size-1).add(plain);
    	    	                    plain++;
    	    	                }
	                			
	                		}
	                		
	                	}
	                	else {
	                		System.out.println("doesnt contain wordid");
	                		ArrayList<Integer> temp = new ArrayList<Integer>();
                			temp.add(docID);
                			ArrayList<ArrayList<Integer>> store = new ArrayList<ArrayList<Integer>>();
                			store.add(temp);
	                		RunPage.ii3.put(wordID, store);
	                		if (count == 0 || count == 1 || count == 2 || count == 3)
            					RunPage.ii3.get(wordID).get(0).add(fancy);
	    	                else if (count == 6) {
	    	                	RunPage.ii3.get(wordID).get(0).add(plain);
	    	                    plain++;
	    	                }
	                	}
	                }
	                else if (wordID % 2 == 0) {
	                	System.out.println(arrOfStr[i] + "ii2");
	                	if(RunPage.ii2.containsKey(wordID)) {
	                		boolean contains = false;
	                		for(int index = 0; index < RunPage.ii2.get(wordID).size(); index++) {
	                			
	                			if(RunPage.ii2.get(wordID).get(index).get(0) == docID) {
	                				
	                				if (count == 0 || count == 1 || count == 2 || count == 3)
	                					RunPage.ii2.get(wordID).get(index).add(fancy);
	    	    	                else if (count == 6) {
	    	    	                	RunPage.ii2.get(wordID).get(index).add(plain);
	    	    	                    plain++;
	    	    	                }
	                				
	                				contains = true;
	                				break;
	                				
	                			}
	                			
	                		}
	                		
	                		if(!contains) {
	                			ArrayList<Integer> temp = new ArrayList<Integer>();
	                			temp.add(docID);
	                			RunPage.ii2.get(wordID).add(temp);
	                			
	                			int size = RunPage.ii2.get(wordID).size();
	                			System.out.println("insertion done");
	                			if (count == 0 || count == 1 || count == 2 || count == 3)
                					RunPage.ii2.get(wordID).get(size-1).add(fancy);
    	    	                else if (count == 6) {
    	    	                	RunPage.ii2.get(wordID).get(size-1).add(plain);
    	    	                    plain++;
    	    	                }
	                			
	                		}
	                		
	                	}
	                	else {
	                		System.out.println("doesnt contain wordid");
	                		ArrayList<Integer> temp = new ArrayList<Integer>();
                			temp.add(docID);
                			ArrayList<ArrayList<Integer>> store = new ArrayList<ArrayList<Integer>>();
                			store.add(temp);
	                		RunPage.ii2.put(wordID, store);
	                		if (count == 0 || count == 1 || count == 2 || count == 3)
            					RunPage.ii2.get(wordID).get(0).add(fancy);
	    	                else if (count == 6) {
	    	                	RunPage.ii2.get(wordID).get(0).add(plain);
	    	                    plain++;
	    	                }
	                	}
	                }
	                else {
	                	System.out.println(arrOfStr[i] + "ii1");
	                	if(RunPage.ii1.containsKey(wordID)) {
	                		boolean contains = false;
	                		System.out.println("contains wordid");
	                		for(int index = 0; index < RunPage.ii1.get(wordID).size(); index++) {
	                			
	                			if(RunPage.ii1.get(wordID).get(index).get(0) == docID) {
	                				System.out.println("contains docid");
	                				if (count == 0 || count == 1 || count == 2 || count == 3)
	                					RunPage.ii1.get(wordID).get(index).add(fancy);
	    	    	                else if (count == 6) {
	    	    	                	RunPage.ii1.get(wordID).get(index).add(plain);
	    	    	                    plain++;
	    	    	                }
	                				
	                				contains = true;
	                				break;
	                				
	                			}
	                			
	                		}
	                		
	                		if(!contains) {
	                			System.out.println("does not contain docid");
	                			ArrayList<Integer> temp = new ArrayList<Integer>();
	                			temp.add(docID);
	                			RunPage.ii1.get(wordID).add(temp);
	                			int size = RunPage.ii1.get(wordID).size();
	                			System.out.println("insertion done");
	                			if (count == 0 || count == 1 || count == 2 || count == 3)
                					RunPage.ii1.get(wordID).get(size-1).add(fancy);
    	    	                else if (count == 6) {
    	    	                	RunPage.ii1.get(wordID).get(size-1).add(plain);
    	    	                    plain++;
    	    	                }
	                			System.out.println("hits insertion done");
	                		}
	                		
	                	}
	                	else {
	                		System.out.println("doesnt contain wordid");
	                		ArrayList<Integer> temp = new ArrayList<Integer>();
                			temp.add(docID);
                			ArrayList<ArrayList<Integer>> store = new ArrayList<ArrayList<Integer>>();
                			store.add(temp);
	                		RunPage.ii1.put(wordID, store);
	                		if (count == 0 || count == 1 || count == 2 || count == 3)
            					RunPage.ii1.get(wordID).get(0).add(fancy);
	    	                else if (count == 6) {
	    	                	RunPage.ii1.get(wordID).get(0).add(plain);
	    	                    plain++;
	    	                }
	                	}
	                }
	                
	            }

	            count++;
	        } 
	            
	        docID++;
		}

	}

	public static HashMap<String,Integer> readLexicon(String filename) throws NumberFormatException, IOException {
		HashMap<String,Integer> lexicon = new HashMap<String,Integer>();
		
		File file = new File("/Users/haleema/Desktop/XCode Practice/C++/SearchEngine/data/" + filename); 
	    BufferedReader br = new BufferedReader(new FileReader(file));
	    while (true) {
	    	
	            String str, word;
	            word = br.readLine();

	            if(word.equals("."))
	            	break;
	            
	            str = br.readLine();
	            lexicon.put(word,Integer.parseInt(str));
	            
	    }
		return lexicon;
	}
	
	public static HashMap<Integer,ArrayList<ArrayList<Integer>>> readInvertedIndex(String filename) throws FileNotFoundException {
		HashMap<Integer,ArrayList<ArrayList<Integer>>> invertedIndex = new HashMap<Integer,ArrayList<ArrayList<Integer>>>();
		
		File file = new File("/Users/haleema/Desktop/XCode Practice/C++/SearchEngine/data/" + filename); 
	    Scanner sc = new Scanner(file); 
	  
	    while (sc.hasNextLine()) {
	    	
	    	ArrayList<ArrayList<Integer>> hits = new ArrayList<ArrayList<Integer>>();
	        String str;
	        str = sc.nextLine();

	        if (str == "") 
	        	break;

	        int wordID = Integer.parseInt(str);

	        while (true) {
	        	str = sc.nextLine();
	        	
	            if (str.equals("_")) 
	            	break;
	            
	            ArrayList<Integer> temp = new ArrayList<Integer>();
	            temp.add(Integer.parseInt(str));
	            
	            Integer count = 0; 
	            while (true) {
	            	str = sc.nextLine();
	            	
	                if (str.equals(".") || str.equals("_")) 
	                	break;
	                
	                count++;
	            }
	            temp.add(count);
	            hits.add(temp);
	        }
	        
	        invertedIndex.put(wordID, hits);
	            
	    }
		return invertedIndex;
		
	}
	
	
	public static HashMap<Integer,ArrayList<ArrayList<Integer>>> readSmallInvertedIndex(String filename) throws FileNotFoundException {
		File file = new File("/Users/haleema/Desktop/XCode Practice/C++/SearchEngine/data/" + filename); 
	    Scanner sc = new Scanner(file); 
	    
	    HashMap<Integer,ArrayList<ArrayList<Integer>>> smallInvertedIndex = new HashMap<Integer,ArrayList<ArrayList<Integer>>>();
	  
	    while (sc.hasNextLine()) {
	    	ArrayList<ArrayList<Integer>> fancyHits = new ArrayList<ArrayList<Integer>>();
	        String str;
	        str = sc.nextLine();

	        if (str == "")
	            break;
	        
	        int wordID = Integer.parseInt(str);
	        while(true) {
	        	ArrayList<Integer> temp = new ArrayList<Integer>();
	            str = sc.nextLine();
	            
	            if(str.equals("_"))
	                break;
	            
	            Integer docID= Integer.parseInt(str);
	            temp.add(docID);
	            
	            str = sc.nextLine();
	            Integer count= Integer.parseInt(str);
	            temp.add(count);
	            fancyHits.add(temp);
	        }
	        smallInvertedIndex.put(wordID, fancyHits);
	    }

		return smallInvertedIndex;
	}
	
	

}
