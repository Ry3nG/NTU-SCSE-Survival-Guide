package lab4_3_2;

public class Rectangle extends Shape{
    double length;
    double width;
    public Rectangle(double length, double width) {
        super("Rectangle");
        this.length = length;
        this.width = width;
    }
    public double getArea() {
        return length * width;
    }
    public double getPerimeter() {
        return 2 * (length + width);
    }
    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Perimeter: " + getPerimeter();
    }
}