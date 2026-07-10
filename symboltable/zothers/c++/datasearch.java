public class datasearch{

  public static int interpolationsearch(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;

        while (left <= right && target >= arr[left] && target <= arr[right]) {
            // Calculate the position using interpolation formula
            int pos = left + (((target - arr[left]) * (right - left)) / (arr[right] - arr[left]));

            if (arr[pos] == target) {
                return pos; // Element found
            }

            if (arr[pos] < target) {
                left = pos + 1; 
            } else {
                right = pos - 1; 
        }
    }
        return -1;
    }


    

public static int Binearsearch(int[] arr , int target ){

    int low =0 ; 
    int high = arr.length - 1 ; 
    
     while(low<=high){
        int middle = low +(high - low)/2 ;

        int value = arr[middle];

        if(value == target ){
            return middle ; 
        }
        else if (value<target ){
            low =middle+1;
        }
        else{ 
            high = middle  -1 ; 
        }
     }


   

    return -1;
}
public static void Linearsearch(int[] arr , int target ){
    for (int i = 0 ; i < arr.length ; i ++){
        if (arr[i]==target) {
            System.out.println("element found at index "+i);}

        //else System.out.println("element not found");    

        }
        }


public static void main(String[] args) {
    int[] arr = new int[1000]; 
    for(int i = 0 ; i<1000; i++){
        arr[i]=i ; 
    }
    int target = 114 ;



    long time1 = System.currentTimeMillis();
    int result =Binearsearch( arr,target);

    if (result != -1) {
        System.out.println("Element found at index " + result);
    } else {
        System.out.println("Element not found in the array.");
    }
    long time3 = System.currentTimeMillis();
    System.out.println("time for binary search is " +(time3 - time1)/1000.00 + "s");



    Linearsearch(arr,target);
    long time4 =System.currentTimeMillis();

        System.out.println("time for linear search is " +(time4 - time3)/1000.00 + "s");



int y = interpolationsearch(arr,target) ;
    long time5 =System.currentTimeMillis();
    if (y != -1) {
        System.out.println("Element found at index " +y);
    } else {
        System.out.println("Element not found");
    }
System.out.println("time for interpolation search is " +(time5 - time4)+ "ms");


}
}