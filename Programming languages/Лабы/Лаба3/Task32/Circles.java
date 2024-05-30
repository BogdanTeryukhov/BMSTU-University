package com.company;
import java.lang.Math;

public class Circles implements Comparable<Circles>{
    private double x1, x2;
    private double y1, y2;
    private double r1, r2;

    public Circles(double x1, double y1, double r1,double x2, double y2, double r2) {
        set_X_and_R_and_Y(x1,y1,r1,x2,y2,r2);
    }


    public double getY1() {
        return y1;
    }
    public double getX1() {
        return x1;
    }
    public double getR1() {
        return r1;
    }
    public double getY2() {
        return y2;
    }
    public double getX2() {
        return x2;
    }
    public double getR2() {
        return r2;
    }


    public void set_X_and_R_and_Y(double x1, double y1, double r1,double x2, double y2, double r2) {
        this.x1 = x1;
        this.y1 = y1;
        this.r1 = r1;
        this.x2 = x2;
        this.y2 = y2;
        this.r2 = r2;
    }

    //Ошибка в алгоритме
    public double getS_from_circles(){
        double d = Math.sqrt(Math.pow(x2 - x1,2) + Math.pow(y2 - y1,2));
        double b =  (Math.pow(r1,2) - Math.pow(r2,2) + Math.pow(d,2)) / (2 * d);

        double x_help = x1 + ((b * (x2 - x1 )) /d);
        double y_help = y1 + ((b * (y2 - y1 )) / d);

        double h = Math.sqrt(Math.pow(r1,2) - Math.pow(d - b,2));

        double x3 = x_help + ((h * (x2 - x1)) / d);
        double y3 = y_help + ((h * (y2 - y1)) / d);

        double x4 = x_help - ((h * (x2 - x1)) / d);
        double y4 = y_help - ((h * (y2 - y1)) / d);

        double our_s = Math.sqrt(Math.pow(x3 - x4,2) + Math.pow(y3 - y4,2));
        //System.out.println(our_s);
        return our_s;
    }

    @Override
    public String toString() {
        return "Circles{" + "x1=" + x1 + ", y1=" + y1 + ", r1=" + r1 + ", x2=" + x2 + ", y2=" + y2 + ", r2=" + r2 + '}';
    }

    @Override
    public int compareTo(Circles o) {
        return Double.compare(getS_from_circles(), o.getS_from_circles());
    }
}
