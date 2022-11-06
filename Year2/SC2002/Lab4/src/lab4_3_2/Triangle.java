package lab4_3_2;

public class Triangle  extends Shape{
    double base;
    double height;
    public Triangle(double base, double height) {
        super("Triangle");
        this.base = base;
        this.height = height;
    }
    public double getArea() {
        return 0.5 * base * height;
    }
    public double getPerimeter() {
        return 0;
    }
    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Perimeter: " + getPerimeter();
    }
}
