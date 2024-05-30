package com.company;
import java.lang.Math;

public class Quadrangles implements Comparable<Quadrangles> {
    private double d1, d2;

    public Quadrangles(double d1, double d2){
        setDiag(d1, d2);
    }

    public double getD1() {
        return d1;
    }

    public double getD2() {
        return d2;
    }

    public void setDiag(double d1, double d2){
        this.d1 = d1;
        this.d2 = d2;
    }

    public double findDiagonals(){
        return Math.max(d1,d2);
    }

    @Override
    public String toString() {
        return "Quadrangles{" +
                "d1=" + d1 +
                ", d2=" + d2 +
                '}';
    }

    @Override
    public int compareTo(Quadrangles o) {
        return Double.compare(findDiagonals(),o.findDiagonals());
    }
}
