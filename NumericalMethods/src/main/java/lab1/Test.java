package lab1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;



public class Test{
    private void run(){
        try {
            run();
        }catch (Exception e){
            System.out.println("exception,");
        }
        System.out.println("finished,");
    }
    public static void main(String[] args) {
        new Test().run();
        System.out.println("done");
    }
}