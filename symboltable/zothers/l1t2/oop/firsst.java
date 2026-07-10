import java.util.*;

public class firsst {
    public static void main(String[] args) {
        int x = 98;
        long h = 788888888888888L;
        float y = 2.7889f;
        double n = 89.8887;
        char c = 's';
        String name = "Ali akib "; // reference data dypr starts with capital leterr

        Scanner scanner34 = new Scanner(System.in);

        System.out.println("the number is " + h + " " + x + name + y);
        System.out.println("whats your title ?");

        String title = scanner34.nextLine();
        System.out.println("whats your age ?");

        int age;
        age = scanner34.nextInt();
        scanner34.nextLine(); // clearing input buffer, always use after nextInt()

        System.out.println("ehats your fav food");
        String food = scanner34.nextLine();

        System.out.println("you are " + title + ". your age is " + age + ". you eat " + food);

        int friends = 10;
        friends = friends + 1;
        friends++;
        friends--;

        int remna = friends % 3;

        double div = (double) friends / 7;

        int a = 5;
        int b = 12;

        int ca = Math.max(a, b);
        ca = Math.min(a, b);

        double p = Math.sqrt(a*a +b*b);
        System.out.println(p);


        // if,switch is similar to cpp
        //	&& = (AND) both conditions must be true
		// 	|| = (OR) either condition must be true
		//		! = (NOT) reverses boolean value of condition

        Scanner scanner = new Scanner(System.in);
		int rows;
		int columns;
		String symbol = "";
		
		System.out.println("Enter # of rows: ");
		rows = scanner.nextInt();
		System.out.println("Enter # of columns: ");
		columns = scanner.nextInt();
		System.out.println("Enter symbol to use: ");
		symbol = scanner.next();
		
		for(int i=1; i<=rows; i++) {
			System.out.println();
			for(int j=1; j<=columns;j++) {
				System.out.print(symbol);
			}
		}	
        

    // arrays 
    
    String[] cars = {"corvet", "car", "tesla"};
    cars[0] = "mustang" ; 
    int[] nums = {1,  2, 3, 4, 5, 6, 7} ; 
    int size = nums.length;

    String[] cities = new String[5] ; 
    cities[0] = "London" ;
    cities[1] = "Paris" ;
    cities[2] = "Berlin" ;
    cities[3] = "Tokyo" ;
    cities[4] = "New York" ;
    
    // loops
    for(int i=0; i<cities.length; i++) {
        System.out.println(cities[i]);
    }
    
    for(String city : cities) {
        System.out.println(city);
    }
    

    // 2d arrays
    int[][] matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int[][] matrix2 = new int[4][3];
    
    for(int i=0; i<matrix2.length; i++) {
        for(int j=0; j<matrix2[i].length; j++) {
            matrix2[i][j] = (i+1)*(j+1);
        }
    }
    
    for(int i=0; i<matrix.length; i++) {
        for(int j=0; j<matrix[i].length; j++) {
            System.out.print(matrix[i][j] + " ");
        }
        System.out.println();
    }


    String str1 = "cat";
    String str2 = "dog";

    boolean isequal = str1.equals(str2) ;
    int l = str1.length();


    // methods

    int sum = add(5, 10);
    System.out.println(sum);
    
    int result = multiply(5, 3);
    System.out.println(result);
    
    // classes and objects
    Person person = new Person("Ali", 25);
    person.eat();
    person.sleep();
    System.out.println(person.getName());
    System.out.println(person.getAge());
    
    // inheritance
    Animal animal = new Animal("Lion", 5);
    animal.eat();
    animal.sleep();
    System.out.println(animal.getName());
    System.out.println(animal.getAge());
    













    }

  

}
