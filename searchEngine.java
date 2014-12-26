package mainpkg;

import java.util.*;
import java.io.*;

// This class implements a google-like search engine
public class searchEngine {

    public HashMap<String, LinkedList<String> > wordIndex;                  // this will contain a set of pairs (String, LinkedList of Strings)	
    public directedGraph internet;             // this is our internet graph
    
    
    
    // Constructor initializes everything to empty data structures
    // It also sets the location of the internet files
    searchEngine() {
	// Below is the directory that contains all the internet files
	htmlParsing.internetFilesLocation = "internetFiles";
	wordIndex = new HashMap<String, LinkedList<String> > ();		
	internet = new directedGraph();				
    } // end of constructor2014 <-- lol
    
    
    // Returns a String description of a searchEngine
    public String toString () {
	return "wordIndex:\n" + wordIndex + "\ninternet:\n" + internet;
    }
    
    
    void traverseInternet(String url) throws Exception {
    	/*Start with collecting the words of the webpage we are on, and if they already exist in
    	wordIndex then then just add the current url to the linked list of pages that have that word.
    	If the word isn't in wordIndex, add an entry to wordIndex for that word then add the url to it's linked list
    	*/
    	LinkedList<String> content = new LinkedList<String>();
    	content = htmlParsing.getContent(url);
    	Iterator<String> i = content.iterator();
    	while ( i.hasNext() ) {
    		String s = i.next(); 
    		if(!wordIndex.containsKey(s)){
    			wordIndex.put(s, new LinkedList<String>());
    			wordIndex.get(s).addLast(url);
    		}
    		else {
    			wordIndex.get(s).addLast(url);
    		}
    	}
    	/* find all the links in the current url. Create a vertex for the url, then populate it's neighboors using addEdge
    	 for all the sites in links.
    	 */
    	LinkedList<String> links = new LinkedList<String>();
    	links = htmlParsing.getLinks(url);
    	internet.addVertex(url);
    	//re using old iterator because i'm done with it above
    	i = links.iterator();
    	while ( i.hasNext() ) {
    		String s = i.next(); 
    		internet.addEdge(url, s);
    	}
    	//mark as visited
    	internet.setVisited(url, true);
    	/*
    	 * Now we have to run the DFS recursively
    	 * We want to generate a list of vertices in the current graph, and make sure we don't recurse to a site already on the graph
    	 * Didn't realize addEdge added the vertices as well. this made a problem so i added the else portion to deal with it
    	 */
    	LinkedList<String> currentVertices = internet.getVertices();
    	i = links.iterator();
    	while ( i.hasNext() ) {
    		String s = i.next(); 
    		if(currentVertices.contains(s)){
    			if(internet.getVisited(s)==false){
    				traverseInternet(s);
    			}
    		}
    		else {
    			traverseInternet(s);
    		}
    	}
	
	
    } // end of traverseInternet
    
    
    /* This computes the pageRanks for every vertex in the internet graph.
       It will only be called after the internet graph has been constructed using 
       traverseInternet.
       Use the iterative procedure described in the text of the assignment to
       compute the pageRanks for every vertices in the graph. 
       
       This method will probably fit in about 30 lines.
    */
    void computePageRanks() {
	//First we get the linked list of all vertices and set their PR to 1
    	LinkedList<String> allSites = internet.getVertices();
    	Iterator<String> iter = allSites.iterator();
    	while ( iter.hasNext() ) {
    		String s = iter.next(); 
    		internet.setPageRank(s, 1.0);
    	}
    	//Now we run our iterative loop. Here we must calculate all the new value before overwritting the old.
    	//Here I use an array to store the new values, then overwrite the old ones on the actual linked list. I use a counter to keep track of the indicies
    	double[] newValues = new double[allSites.size()];//array of new values
    	int j = 0;//opted to use a counter and a for loop, rather than test convergence for simplicity since assignment said that was fine
    	for (j=0;j<100;j++){
    		iter = allSites.iterator();
    		int index = 0;//current index of the array associated with the current element of the linked list
    		while (iter.hasNext()){//allSites iteration
        		double tmpValue = 0.5;//keeps track of the current PR value, starts at 0.5 because its the damper
        		String s = iter.next();
        		LinkedList<String> neighbors = internet.getEdgesInto(s);
        		Iterator<String> nIter = neighbors.iterator();
        		while(nIter.hasNext()){//for each neighbor of allSites add it's contribution to the PR
        			String h = nIter.next();
        			tmpValue = tmpValue + (0.5*((internet.getPageRank(h))/internet.getOutDegree(h)));//multiplied by 0.5 cause of damper
        		}
        		newValues[index] = tmpValue;
        		index = index + 1;
        	}
    		iter = allSites.iterator();
    		index = 0;
    		while ( iter.hasNext()){
    			String s = iter.next();
    			internet.setPageRank(s, newValues[index]);
    			index = index + 1;
    		}
    	}
    } // end of computePageRanks
    
	
    /* Returns the URL of the page with the high page-rank containing the query word
       Returns the String "" if no web site contains the query.
       This method can only be called after the computePageRanks method has been executed.
       Start by obtaining the list of URLs containing the query word. Then return the URL 
       with the highest pageRank.
       This method should take about 25 lines of code.
    */
    String getBestURL(String query) {
	    /*
	     * The idea here is to have a variable to store the current best result. By default this is the first site in the linked
	     * list corresponding to the searched word. We then iterate through that list and if a better result comes up, it is the new resultOfSearch
	     * there is an else statement so if the word is not in any of the known sites, a generic message is returned indicating no sites were found
	     */
		if(wordIndex.containsKey(query)){
			Iterator<String> wordIt = wordIndex.get(query).iterator();
			String resultOfSearch = wordIndex.get(query).getFirst();//The current best result that will be returned at the end of the iteration
			while(wordIt.hasNext()){// for each site with the query corresponds to, check if it's better than the current result
				String s = wordIt.next();
				if(internet.getPageRank(s) > internet.getPageRank(resultOfSearch)){
					resultOfSearch = s;
				}
			}
			return resultOfSearch;
		}
		else{
			return "No results matched your search";
		}
    } // end of getBestURL
    
    
	
    public static void main(String args[]) throws Exception{		
	searchEngine mySearchEngine = new searchEngine();
	// to debug your program, start with.
	mySearchEngine.traverseInternet("http://www.cs.mcgill.ca/~blanchem/250/a.html");
	// When your program is working on the small example, move on to
	//mySearchEngine.traverseInternet("http://www.cs.mcgill.ca");
	
	mySearchEngine.computePageRanks();
	
	BufferedReader stndin = new BufferedReader(new InputStreamReader(System.in));
	String query;
	do {
	    System.out.print("Enter query: ");
	    query = stndin.readLine();
	    if ( query != null && query.length() > 0 ) {
		System.out.println("Best site = " + mySearchEngine.getBestURL(query));
	    }
	} while (query!=null && query.length()>0);				
    } // end of main
}