package assign1_pkg;
import java.util.*;


class MergeSortNonRecursive {

    static Stack<ProgramFrame> callStack;

    // this implement the merge algorithm seen in class. Feel free to call it.
    public static void merge(int A[], int start, int mid, int stop) 
    {
 int index1=start;
 int index2=mid+1;
 int tmp[]=new int[A.length];
 int indexTmp=start;
 
 while (indexTmp<=stop) {
     if (index1<=mid && (index2>stop || A[index1]<=A[index2])) {
  tmp[indexTmp]=A[index1];
  index1++;
     }
     else {
  if (index2<=stop && (index1>mid || A[index2]<=A[index1])) {
      tmp[indexTmp]=A[index2];
      index2++;
  }
     }
     indexTmp++;
 }
 for (int i=start;i<=stop;i++) A[i]=tmp[i];
    }
    
    //--------------------------------------------------------------
    //------EASY TO SPOT WHEN SCROLLING THROUGH CODE----------------
    //--------------------------------------------------------------
    static void mergeSort(int A[]) {
     int front, end, mid;
     front = 0;
     end = A.length-1;
     callStack = new Stack<ProgramFrame>();
     ProgramFrame current = new ProgramFrame(front, end, 1);
     callStack.push(current);
     while (!callStack.empty()){
      mid = ((callStack.peek().start)+(callStack.peek().stop))/2;
      if(callStack.peek().PC == 1){
          if(callStack.peek().stop <= callStack.peek().start){
           callStack.pop();
           if(callStack.empty()){
            break;
           }
           callStack.peek().PC++;
          }
          else {
           callStack.peek().PC++;
          }
          continue;
         }
      if(callStack.peek().PC == 2){
       current = new ProgramFrame(callStack.peek().start, mid, 1);
       callStack.push(current);
       continue;
      }
      if(callStack.peek().PC == 3){
       current = new ProgramFrame(mid+1, callStack.peek().stop, 1);
       callStack.push(current);
       continue;
      }
      if(callStack.peek().PC == 4){
       merge(A, callStack.peek().start, mid, callStack.peek().stop);
       callStack.pop();
       if(!callStack.empty()){
        callStack.peek().PC++;
        continue;
       }
      }
     }
    }
    

    
    public static void main (String args[]) throws Exception {
 
 // just for testing purposes
 int myArray[] = {8,2,10,6};
 mergeSort(myArray);
 System.out.println("Sorted array is:\n");
 for (int i=0;i<myArray.length;i++) {
     System.out.print(myArray[i]+" ");
 }
 System.out.println();
    }
}
class ProgramFrame {
    int start;
    int stop;
    int PC;
    
    public ProgramFrame(int myStart, int myStop, int myPC) {
 start=myStart;
 stop=myStop;
 PC=myPC;
    }

    // returns a String describing the content of the object
    public String toString() {
 return "ProgramFrame: start = " + start + " stop = " + stop + " PC = " + PC;
    }
}