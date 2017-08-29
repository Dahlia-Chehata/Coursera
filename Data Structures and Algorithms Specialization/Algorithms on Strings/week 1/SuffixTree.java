
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SuffixTree {
	
	class End{
		int end;
		public End(int end) {
		    this.end=end;
		}	
	}
	
 static class SuffixNode{
		
		private static final int branches = 256;
		SuffixNode children[]=new SuffixNode[branches];
		int start;
		End end;
		int index;
		SuffixNode SuffixLink;
		
		public static SuffixNode createNode(int start,End end) {
			SuffixNode node=new SuffixNode();
			node.start=start;
			node.end=end;
			return node;	
		}
	}
 
 class Active{
	 
	 SuffixNode activeNode; //representing active point
	 int activeLength; // distance to be traveled on active edge
	 int activeEdge; // edge chosen from active point represented by character's index
	 
	 Active(SuffixNode activeNode){
		 this.activeNode=activeNode;
		 activeLength=0; 
		 activeEdge=-1; 
	 }
 }
	 private SuffixNode root;
	 private Active active;
	 private End end;
	 private int remainingCount;
	 private char input[];
	 private static final char EOI ='$';
	 
	 public SuffixTree(char input[]) {
		 this.input= new char[input.length+1];
		 for (int i=0;i<input.length;i++)
			 this.input[i]=input[i];
		 this.input[input.length]=EOI;
	 }
	 public void build () throws Exception {
		 root=SuffixNode.createNode(1, new End(0));
		 root.index=-1;
		 active = new Active (root);
		 this.end=new End(-1);
		 for (int i=0;i<input.length;i++)
			 phase(i);
		 if (remainingCount!=0)
			 throw new Exception("ERROR");
		 setIndex(root,0,input.length);
	 }
	 private void phase(int i) {
		 SuffixNode lastCreatedInternalNode= null;
		 end.end++; //end is incremented in each phase 
		 remainingCount++; //remaining is incremented in each phase
		 while (remainingCount>0) {
			 if (active.activeLength==0) {  //search for path with character i from "ROOT"
				 if (pathFromActiveNodeWithChar(i)!=null) { 
					 //if character already exists ,change active edge with index of character and increment length
					 //and then by rule 3 extension (show stopper)we break,so next phase starts with this active point
					 active.activeEdge=pathFromActiveNodeWithChar(i).start;
					 active.activeLength++;
					 break;
				 } else {
					 root.children[input[i]]=SuffixNode.createNode(i, end);
					 remainingCount--; //decrementing remainingSuffixCount when creating a leaf node
				 }
			 }else { // else meaning implicit suffix tree: the tree is not ending with a leaf since the last
				     //processed character is not unique
				 try {
					 //start processing from active point 
					 //move from active Node in the direction of active edge with length=active length
					 char character =nextCharacter(i);
					 if (character==input[i]) {
						 if (lastCreatedInternalNode!=null)
							 lastCreatedInternalNode.SuffixLink=selectActiveNode();
						 walkdown(i); //update active node
						 break;
					 } else {
						 SuffixNode node =selectActiveNode();
						 int oldStart=node.start;
						 node.start+=active.activeLength;
						 
						 SuffixNode newInternalNode = SuffixNode.createNode
						(oldStart, new End(oldStart + active.activeLength - 1));
						 
						 SuffixNode newLeafNode = SuffixNode.createNode(i,end);
						 
						 newInternalNode.children[input[newInternalNode.start+active.activeLength]]=node;
						 newInternalNode.children[input[i]]=newLeafNode;
						 newInternalNode.index=-1;
						 active.activeNode.children[input[newInternalNode.start]]=newInternalNode;
						 
						 if (lastCreatedInternalNode != null) 
	                            lastCreatedInternalNode.SuffixLink = newInternalNode;
	                     lastCreatedInternalNode = newInternalNode;
	                     newInternalNode.SuffixLink = root;
	                     
	                     if (active.activeNode!=root)
	                    	 active.activeNode=active.activeNode.SuffixLink;
	                     else {
	                    	 active.activeEdge = active.activeEdge  + 1;
	                         active.activeLength--;
	                     }
	                     remainingCount--;
					 }
				 }catch(EndOfPathException e) { //reached end of path so we already have internal node
					 SuffixNode node= selectActiveNode();
					 node.children[input[i]]=SuffixNode.createNode(i, end);
					 if (lastCreatedInternalNode != null) 
                         lastCreatedInternalNode.SuffixLink = node;
					 lastCreatedInternalNode=node;
					 if(active.activeNode != root)
	                        active.activeNode = active.activeNode.SuffixLink;
					 else{
	                        active.activeEdge = active.activeEdge + 1;
	                        active.activeLength--;
	                    }
	                    remainingCount--;
				 }
			 }
		 }
	 }
	 private void walkdown (int i) {
		 SuffixNode node= selectActiveNode();
		 if (range(node)<active.activeLength) {
			 active.activeNode = node;
	         active.activeLength = active.activeLength - range(node);
	         active.activeEdge = node.children[input[i]].start;
		 } else active.activeLength++; //if active length is greater than the node path skip this node
	 }
	 private char nextCharacter(int i) throws EndOfPathException {
		 SuffixNode node= selectActiveNode();
		 if(range(node) >= active.activeLength){
	            return input[node.start + active.activeLength];
	        }
	        if(range(node) + 1 == active.activeLength ){
	            if(node.children[input[i]] != null)
	                return input[i];
	        }
	        else{
	            active.activeNode = node;
	            active.activeLength = active.activeLength - range(node) -1;
	            active.activeEdge = active.activeEdge + range(node)  +1;
	            return nextCharacter(i);
	        }
	        
	        throw new EndOfPathException();
	    }
	 @SuppressWarnings("serial")
	private class EndOfPathException extends Exception{
		 
	 }
	 private SuffixNode selectActiveNode() {
		 return active.activeNode.children[input[active.activeEdge]];
	 }
	 private SuffixNode pathFromActiveNodeWithChar(int i) {
		 return active.activeNode.children[input[i]];
	 }
	 private int range(SuffixNode node) {
		 return node.end.end-node.start;
	 }
	 //to store the index of each suffix
	 private void setIndex(SuffixNode root,int val, int size){
		 if (root==null) return;
		 val+=root.end.end-root.start+1;
		 if (root.index!=-1) {
			 root.index=size-val;
			 return;
		 }
		 for (SuffixNode child:root.children)
			 setIndex(child,val,size);
	 }
	 private void dfsTraversal(SuffixNode root, List<Character> result){
	        if(root == null) return;
	        if(root.index != -1){
	            for(int i=root.start; i <= root.end.end; i++)
	                result.add(input[i]);
	            result.stream().forEach(System.out::print);
	            System.out.println(" " + root.index);
	            for(int i=root.start; i <= root.end.end; i++)
	                result.remove(result.size()-1);
	            return;
	        }
	        
	        for(int i=root.start; i <= root.end.end; i++)
	            result.add(input[i]);
	        for(SuffixNode node : root.children)
	            dfsTraversal(node, result);
	        for(int i=root.start; i <= root.end.end; i++)
	            result.remove(result.size()-1);
	    }
	 
	 public void dfsTraversal(){
	        List<Character> result = new ArrayList<>();
	        for(SuffixNode child : root.children){
	            dfsTraversal(child, result);
	        }
	    }
	
 public static void main(String args[]){
	 Scanner sc = new Scanner(System.in);
	 String input =sc.next();
     SuffixTree tree = new SuffixTree(input.toCharArray());
     try {
		tree.build();
	} catch (Exception e) {
		e.printStackTrace();
	}
     tree.dfsTraversal();
     sc.close();
 }
}
