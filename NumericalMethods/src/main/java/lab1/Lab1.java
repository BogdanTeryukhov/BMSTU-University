package lab1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Lab1 {

    private static final int MATRIXSIZE = 4;

    public static void main(String[] args) {
        Matrix matrix = new Matrix();

        List<Double> alpha = new ArrayList<>();
        List<Double> beta = new ArrayList<>();
        List<Double> Y = new ArrayList<>();

        Y.add(matrix.getMainDiag().get(0));
        alpha.add(-(matrix.getUpperDiag().get(0) / Y.get(0)));
        beta.add(matrix.getResult().get(0) / Y.get(0));

        for(int i = 1; i < MATRIXSIZE - 1; ++i) {
            Y.add(matrix.getMainDiag().get(i) + (matrix.getLowerDiag().get(i)*alpha.get(i - 1)));
            alpha.add(-(matrix.getUpperDiag().get(i) / Y.get(i)));
            beta.add((matrix.getResult().get(i) - (matrix.getLowerDiag().get(i) * beta.get(i - 1))) / Y.get(i));
        }

        Y.add(MATRIXSIZE - 1, matrix.getMainDiag().get(MATRIXSIZE - 1)
                + matrix.getLowerDiag().get(MATRIXSIZE - 1) * alpha.get(MATRIXSIZE - 2));
        beta.add(MATRIXSIZE - 1, (matrix.getResult().get(MATRIXSIZE - 1) -
                (matrix.getLowerDiag().get(MATRIXSIZE - 1) * beta.get(MATRIXSIZE - 2))) / Y.get(MATRIXSIZE - 1));

        double[] resultX = new double[MATRIXSIZE];
        resultX[MATRIXSIZE - 1] = beta.get(MATRIXSIZE - 1);

        for(int i = MATRIXSIZE - 1; i > 0; --i) {
            resultX[i - 1] = (alpha.get(i - 1) * resultX[i]) + beta.get(i - 1);
        }
        System.out.println("Obtained result: " + Arrays.toString(resultX));

        //Error Calculation
        double[] errorCalculation = new double[MATRIXSIZE];
        for (int i = 0; i < MATRIXSIZE; i++) {
            errorCalculation[i] = Math.abs(resultX[i] - matrix.getAnswerX().get(i));
        }
        System.out.println("Error calculation: " + Arrays.toString(errorCalculation));
    }

    static class Matrix {
        private List<Double> upperDiag;
        private List<Double> mainDiag;
        private List<Double> lowerDiag;
        private List<Double> answerX;
        private List<Double> result;

        public Matrix() {
            upperDiag = new ArrayList<>();
            mainDiag = new ArrayList<>();
            lowerDiag = new ArrayList<>();
            result = new ArrayList<>();
            answerX = new ArrayList<>();

            setUpperDiag();
            setMainDiag();
            setLowerDiag();
            setResult();
            setAnswerX();
        }

        public List<Double> getAnswerX() {
            return answerX;
        }

        public void setAnswerX() {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Answer");
            for (int i = 0; i < MATRIXSIZE; i++) {
                answerX.add(scanner.nextDouble() / 3);
            }
        }

        public void setUpperDiag() {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Upper Diag");
            for (int i = 0; i < MATRIXSIZE; i++) {
                upperDiag.add(scanner.nextDouble() / 3);
            }
        }

        public void setMainDiag() {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Main Diag");
            for (int i = 0; i < MATRIXSIZE; i++) {
                mainDiag.add(scanner.nextDouble() / 3);
            }
        }

        public void setLowerDiag() {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Lower Diag");
            for (int i = 0; i < MATRIXSIZE; i++) {
                lowerDiag.add(scanner.nextDouble() / 3);
            }
        }

        public void setResult() {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Result Diag");
            for (int i = 0; i < MATRIXSIZE; i++) {
                result.add(scanner.nextDouble() / 3);
            }
        }

        public List<Double> getResult() {
            return this.result;
        }

        public List<Double> getUpperDiag() {
            return this.upperDiag;
        }

        public List<Double> getMainDiag() {
            return this.mainDiag;
        }

        public List<Double> getLowerDiag() {
            return this.lowerDiag;
        }

        public String toString() {
            return "Matrix{upperDiag=" + this.upperDiag + ", mainDiag=" + this.mainDiag + ", lowerDiag=" + this.lowerDiag + ", result=" + this.result + "}";
        }
    }
}
