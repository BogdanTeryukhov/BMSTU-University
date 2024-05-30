package lab2;

import java.util.ArrayList;
import java.util.Arrays;

public class Splines {
    private static final int N = 10;

    public static double function(double x) {
        return (x / (Math.pow(x, 2) - 2 * x - 3));
    }

    public static double[] solution(double[] b, double[] a, double[] c, double[] d, int size) {
        ArrayList<Double> alpha = new ArrayList<>();
        ArrayList<Double> beta = new ArrayList<>();

        alpha.add(-c[0] / b[0]);
        beta.add(d[0] / b[0]);
        double y;

        for (int i = 1; i < size - 1; i++) {
            y = a[i - 1] * alpha.get(i - 1) + b[i];
            alpha.add(-c[i] / y);
            beta.add((d[i] - a[i - 1] * beta.get(i - 1)) / y);
        }

        y = a[size - 2] * alpha.get(size - 2) + b[size - 1];
        beta.add((d[size - 1] - a[size - 2] * beta.get(size - 2)) / y);

        ArrayList<Double> result = new ArrayList<>();
        result.addAll(alpha);
        result.addAll(beta);

        double[] x = new double[size];
        x[size - 1] = result.get(size - 1);
        for (int i = size - 2; i >= 0; i--) {
            x[i] = result.get(i) * x[i + 1] + result.get(size + i);
        }
        return x;
    }

    public static void errorCalculation(double l, double h, double[] ys, double[] xs,
                                        double[] coefA, double[] coefB, double[] coefC, double[] coefD) {
        for (int i = 0; i < N; i++) {
            double xIn = l + i * h;
            double xOut = l + (i + 0.5) * h;
            double yIn = function(xIn);
            double yOut = function(xOut);
            double sIn = coefA[i] + coefB[i] * (xIn - xs[i]) + coefC[i] * Math.pow(xIn - xs[i], 2) + coefD[i] * Math.pow(xIn - xs[i], 3);
            double sOut = coefA[i] + coefB[i] * (xOut - xs[i]) + coefC[i] * Math.pow(xOut - xs[i], 2) + coefD[i] * Math.pow(xOut - xs[i], 3);
            System.out.printf("x: %.1f, S(x): %.16f, y(x): %.16f, |S(x)-y(x)|: %.16f%n", xIn, sIn, yIn, Math.abs(yIn - sIn));
            System.out.printf("x: %.1f, S(x): %.16f, y(x): %.16f, |S(x)-y(x)|: %.16f%n", xOut, sOut, yOut, Math.abs(yOut - sOut));
        }
    }

    public static void main(String[] args) {
        double l = -0.5, r = 2.5;
        double h = (r - l) / N;

        //System.out.println("Введите xi: ");
        double[] xs = new double[N + 1];
        for (int i = 0; i <= N; i++) {
            xs[i] = l + i * h;
        }
        //System.out.println(Arrays.toString(xs));

        //System.out.println("Введите yi: ");
        double[] ys = new double[N + 1];
        for (int i = 0; i <= N; i++) {
            ys[i] = function(xs[i]);
        }
        //System.out.println(Arrays.toString(ys));

        //Трехдиагональная матрица
        double[] d = new double[N - 1];
        for (int i = 1; i < N; i++) {
            d[i - 1] = 3 * (ys[i + 1] - 2 * ys[i] + ys[i - 1]) / (h * h);
        }

        double[] b = new double[N - 1];
        Arrays.fill(b, 4);

        double[] a = new double[N - 2];
        Arrays.fill(a, 1);

        double[] c = new double[N - 2];
        Arrays.fill(c, 1);

        double[] coefC = solution(b, a, c, d, N - 1);
        coefC = Arrays.copyOf(coefC, coefC.length + 2);
        System.arraycopy(coefC, 0, coefC, 1, coefC.length - 2);

        coefC[0] = 0;
        coefC[coefC.length - 1] = 0;

        double[] coefA = new double[N];
        for (int i = 1; i <= N; i++) {
            coefA[i - 1] = ys[i - 1];
        }
        //System.out.println("a: " + Arrays.toString(coefA));

        double[] coefB = new double[N];
        for (int i = 1; i <= N; i++) {
            coefB[i - 1] = (ys[i] - ys[i - 1]) / h - (h / 3) * (coefC[i] + 2 * coefC[i - 1]);
        }
        //System.out.println("b: " + Arrays.toString(coefB));

        //System.out.println("c: " + Arrays.toString(coefC));
        double[] coefD = new double[N];
        for (int i = 1; i <= N; i++) {
            coefD[i - 1] = (coefC[i] - coefC[i - 1]) / (3 * h);
        }
        //System.out.println("d: " + Arrays.toString(coefD));

        errorCalculation(l, h, ys, xs, coefA, coefB, coefC, coefD);
    }
}
