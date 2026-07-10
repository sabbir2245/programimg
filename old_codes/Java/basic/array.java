package Java.basic;

import java.util.Arrays;

public class array {

    public static void main(String[] args) {
        
        // 1. Initializing an array using the `new` keyword with default values
        int[] arr1 = new int[5];  // Array of size 5 with default values (0)
        System.out.println("arr1 (default values): " + Arrays.toString(arr1));
        
        // 2. Initializing an array with specific values
        int[] arr2 = {1, 2, 3, 4, 5};  // Array with values 1, 2, 3, 4, 5
        System.out.println("arr2 (specific values): " + Arrays.toString(arr2));
        
        // 3. Initializing an array using the `new` keyword with values
        int[] arr3 = new int[]{6, 7, 8, 9, 10};  // Array with values 6, 7, 8, 9, 10
        System.out.println("arr3 (new keyword with values): " + Arrays.toString(arr3));
        
        // 4. Initializing an array of strings
        String[] names = {"Alice", "Bob", "Charlie"};
        System.out.println("names (String array): " + Arrays.toString(names));
        
        // 5. Initializing an array with a specific value using Arrays.fill
        int[] arr4 = new int[5];
        Arrays.fill(arr4, 10);  // All elements are set to 10
        System.out.println("arr4 (filled with 10): " + Arrays.toString(arr4));
        
        // 6. Initializing an array using a loop
        int[] arr5 = new int[5];
        for (int i = 0; i < arr5.length; i++) {
            arr5[i] = i * 2;  // Filling with dynamic values
        }
        System.out.println("arr5 (loop-initialized): " + Arrays.toString(arr5));
    
    }
}

     

 class TwoDArrayExample {

    public static void main(String[] args) {
        
        // Define the size of the 2D array (m rows and n columns)
        int m = 3;  // number of rows
        int n = 4;  // number of columns

        // 1. Initialize a 2D array with default values (0)
        int[][] arr1 = new int[m][n];
        System.out.println("arr1 (default values):");
        print2DArray(arr1);

        // 2. Initialize a 2D array with specific values
        int[][] arr2 = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        };
        System.out.println("\narr2 (specific values):");
        print2DArray(arr2);

        // 3. Initialize a 2D array using the `new` keyword and set values dynamically
        int[][] arr3 = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                arr3[i][j] = i * n + j + 1;  // Filling with dynamic values
            }
        }
        System.out.println("\narr3 (dynamically filled):");
        print2DArray(arr3);
        
        // 4. Initialize a 2D array using `Arrays.fill` method
        int[][] arr4 = new int[m][n];
        for (int i = 0; i < m; i++) {
            Arrays.fill(arr4[i], 7);  // Fill each row with the value 7
        }
        System.out.println("\narr4 (filled with 7s):");
        print2DArray(arr4);
    }

    // Helper method to print a 2D array
    public static void print2DArray(int[][] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.println(Arrays.toString(arr[i]));
        }
    }
    
}

 class JaggedArrayExample {

    public static void main(String[] args) {
        
        // Create a jagged array where each row has a different number of columns
        int[][] jaggedArray = new int[3][];  // 3 rows, but columns will be defined individually
        
        // Initialize the rows with different column sizes
        jaggedArray[0] = new int[2];  // Row 0 with 2 columns
        jaggedArray[1] = new int[3];  // Row 1 with 3 columns
        jaggedArray[2] = new int[4];  // Row 2 with 4 columns

        // Fill the jagged array with values
        int value = 1;
        for (int i = 0; i < jaggedArray.length; i++) {
            for (int j = 0; j < jaggedArray[i].length; j++) {
                jaggedArray[i][j] = value++;  // Assigning incremental values to the array
            }
        }

        // Print the jagged array
        System.out.println("Jagged Array:");
        for (int i = 0; i < jaggedArray.length; i++) {
            for (int j = 0; j < jaggedArray[i].length; j++) {
                System.out.print(jaggedArray[i][j] + " ");
            }
            System.out.println();
        }
    }
}

