package com.company;


public class AriphmeticProgression implements Comparable<AriphmeticProgression>{
    private int a; //первый член прогрессии
    private int d; //разность прогрессии

    public AriphmeticProgression(int a,int d) {
        setA_D(a,d);
    }

    public int getA() {
        return a;
    }
    public int getD() {
        return d;
    }

    public void setA_D(int a,int d) {
        this.a = a;
        this.d = d;
    }

    public int getInProgression() {
        int count = 1;
        int temp = a;
        while (a+d>=0 && a+d<=100){
            count++;
            a+=d;
        }
        a = temp;
        return count;
    }

    @Override
    public String toString() {
        return "AriphmeticProgression{" + "a=" + a + ", d=" + d + '}';}

    @Override
    public int compareTo(AriphmeticProgression o) {
        return Integer.compare(getInProgression(),o.getInProgression());
    }
}
