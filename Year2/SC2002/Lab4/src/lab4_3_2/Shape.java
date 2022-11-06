package lab4_3_2;

public abstract class Shape {
    double area;
    double perimeter;
    String name;

    public abstract double getArea();

    public abstract double getPerimeter();

    public String getName() {
        return name;
    }

    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Perimeter: " + getPerimeter();
    }

}
