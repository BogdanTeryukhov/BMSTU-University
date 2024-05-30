package com.company;
import java.lang.Math;

public class MaxCommonDel implements Comparable<MaxCommonDel> {
    private int x;
    private int y;

    public MaxCommonDel(int x, int y){
        setX_and_Y(x, y);
    }
    public int getY() {
        return y;
    }
    public int getX() {
        return x;
    }

    public void setX_and_Y(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int gcd(){
        int f = Math.min(x, y);
        int nod = 0;
        for (int i = 1; i < f + 1; i++){
            if (x % i == 0 && y%i==0){
                nod = i;
            }
        }
        return nod;
    }


    @Override
    public int compareTo(MaxCommonDel o) {
        return Double.compare(gcd(),o.gcd());
    }

    @Override
    public String toString() {
        return "MaxCommonDel{" + "x=" + x + ", y=" + y + '}';
    }
}

