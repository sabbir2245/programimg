public class interpolation {
    public static int search(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;

        while (left <= right && target >= arr[left] && target <= arr[right]) {
            // Calculate the position using interpolation formula
            int pos = left + (((target - arr[left]) * (right - left)) / (arr[right] - arr[left]));

            if (arr[pos] == target) {
                return pos; // Element found
            }

            if (arr[pos] < target) {
                left = pos + 1; // Adjust the left boundary
            } else {
                right = pos - 1; // Adjust the right boundary
            }
        }

        return -1; // Element not found
    }

    public static void main(String[] args) {
        int[] arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        int target = 60;

        int result = search(arr, target);

        if (result != -1) {
            System.out.println("Element found at index " + result);
        } else {
            System.out.println("Element not found");
        }
    }
}


    

