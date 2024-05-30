package lab3;

public class MethodComparison {

    public static final double a = -0.5;
    public static final double b = 2.5;
    public static double epsilon = 0.001;

    public static double function(double x) {
        return (x / (Math.pow(x, 2) - 2 * x - 3));
    }

    public static double richardsonFormula(double Ih, double Ih2, int k) {
        return (Ih - Ih2) / (Math.pow(2, k) - 1);
    }

    public static void printing(int N, double Ih_2, double R) {
        System.out.println("\t\tN: " + N);
        System.out.println("\t\tIh_2: " + Ih_2);
        System.out.println("\t\tR: " + R);
        System.out.println("\t\tIh_2 + R: " + (Ih_2 + R));
    }

    public static double rectanglesMethod(double h, int N) {
        h = h / N;
        double sum = 0;
        for (int i = 1; i < N + 1; i++) {
            sum += function(a + (i - 0.5) * h);
        }
        return h * sum;
    }

    public static void rectanglesMethodResult(double h, int k) {
        int N = 1;
        double R = 100.0;
        int iterations = 0;
        double Ih = 0.0;
        double Ih2 = 0.0;

        while (!(Math.abs(R) < epsilon)) {
            N = N * 2;
            Ih2 = Ih;
            Ih = rectanglesMethod(h, N);
            R = richardsonFormula(Ih, Ih2, k);
            iterations += 1;
        }
        printing(N, Ih2, R);
    }

    public static double trapezoidMethod(double h, int N) {
        h = h / N;
        double sum = 0;
        for (int i = 1; i < N; i++) {
            sum += function(a + i * h);
        }
        return h * (function(a) * function(b) / (2 + sum));
    }

    public static void trapezoidMethodResult(double h, int k) {
        int N = 1;
        double R = 100.0;
        int iterations = 0;
        double Ih = 0.0;
        double Ih2 = 0.0;

        while (!(Math.abs(R) < epsilon)) {
            N = N * 2;
            Ih2 = Ih;
            Ih = trapezoidMethod(h, N);
            R = richardsonFormula(Ih, Ih2, k);
            iterations += 1;
        }
        printing(N, Ih2, R);
    }

    public static double simpsonMethod(double h, int N) {
        h = h / N;
        double sum1 = 0;
        for (int i = 1; i < N; i++) {
            sum1 += function(a + i * h);
        }
        double sum2 = 0;
        for (int i = 1; i < N + 1; i++) {
            sum2 += function(a + (i - 0.5) * h);
        }
        double sum3 = 0;
        for (int i = 1; i < N + 2; i++) {
            sum3 += function(a + (i - 1) * h);
        }
        return h / 6 * (sum1 + 4 * sum2 + sum3);
    }

    public static void simpsonMethodResult(double h, int k) {
        int N = 1;
        double R = 100.0;
        int iterations = 0;
        double Ih = 0.0;
        double Ih2 = 0.0;

        while (!(Math.abs(R) < epsilon)) {
            N = N * 2;
            Ih2 = Ih;
            Ih = simpsonMethod(h, N);
            R = richardsonFormula(Ih, Ih2, k);
            iterations += 1;
        }
        printing(N, Ih2, R);
    }

    public static void main(String[] args) {
        double halfH = b - a;
        System.out.println("Epsilon: " + epsilon);
        System.out.println("\tRectangles Method: ");
        rectanglesMethodResult(halfH, 2);
        System.out.println("\tTrapezoid Method: ");
        trapezoidMethodResult(halfH, 2);
        System.out.println("\tSimpson Method: ");
        simpsonMethodResult(halfH, 4);
        epsilon /= 10;
        System.out.println("\n\n");
    }
}