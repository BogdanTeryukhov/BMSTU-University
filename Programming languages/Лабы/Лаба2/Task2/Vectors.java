package com.company;

public class Vectors {
    private double[] vectorsCoords;

    public Vectors(double ... vectorsCoords){
        setVectorsCoords(vectorsCoords);
    }

    public double[] getVectorsCoords() {
        return vectorsCoords;
    }

    public void setVectorsCoords(double[] vectorsCoords) {
        this.vectorsCoords = vectorsCoords;
    }

    public static double getSkaMultiplication(Vectors n1, Vectors n2){
        double[] arr1 = n1.getVectorsCoords();
        double[] arr2 = n2.getVectorsCoords();

        int sum = 0;
        for (int i = 0; i < arr1.length; i++){
            sum += arr1[i] * arr2[i];
        }
        return sum;
    }
}
