package com.company;
import java.util.Arrays;

public class NVector implements Comparable<NVector>{
    private double[] coords;

    public NVector(double ... coords){
        setCoords(coords);
    }

    public double[] getCoords() {
        return coords;
    }

    public void setCoords(double[] coords) {
        this.coords = coords;
    }

    public double vectorLength(){
        int sum = 0;
        for (int i = 0; i < coords.length; i++){
            sum += Math.pow(coords[i], 2);
        }
        return Math.sqrt(sum);
    }

    @Override
    public String toString() {
        return "NVector{" +
                "coords=" + Arrays.toString(coords) +
                '}';
    }

    @Override
    public int compareTo(NVector o) {
        return Double.compare(vectorLength(),o.vectorLength());
    }
}
