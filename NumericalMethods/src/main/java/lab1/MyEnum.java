package lab1;

public enum MyEnum {
    X,Y;

    private void func(){
        System.out.println(X==X);
        System.out.println(X.ordinal() == Y.ordinal());
        System.out.println(X == Y);
        System.out.println(X.compareTo(Y));
        System.out.println(X.equals(Y));
    }
}
