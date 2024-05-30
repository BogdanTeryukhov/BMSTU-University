package lab6;

public class Lab6 {
    public static double eps = 0.001;

    public static double f(double x, double y) {
        return x + 2 * y + 4 * (Math.pow(1 + x * x + y * y, ((double) 1 / 2)));
    }

    public static void main(String[] args) {
        
    }
}
