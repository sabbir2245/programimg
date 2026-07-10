package Java.collections;

public class Player implements Comparable<Player> {
    String name;
    int score;

    Player(String name, int score) {
        this.name = name;
        this.score = score;
    }

    @Override
    public int compareTo(Player other) {
        // Comparing by score in descending order
        return Integer.compare(other.score, this.score);
    }

    @Override
    public String toString() {
        return name + ": " + score;
    }

    public static void main(String[] args) {
        Player player1 = new Player("Alice", 150);
        Player player2 = new Player("Bob", 200);
        Player player3 = new Player("Charlie", 100);

        Player[] players = { player1, player2, player3 };

        System.out.println("Before sorting:");
        for (Player player : players) {
            System.out.println(player);
        }

        java.util.Arrays.sort(players); // Sorting players based on score

        System.out.println("\nAfter sorting:");
        for (Player player : players) {
            System.out.println(player);
        }
    }
}
