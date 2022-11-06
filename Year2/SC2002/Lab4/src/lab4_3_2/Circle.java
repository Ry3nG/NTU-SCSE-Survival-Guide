package lab4_3_2;

public class Circle extends Shape{
    double radius;
    public Circle(double radius) {
        super("Circle");
        this.radius = radius;
    }
    public double getArea() {
        return Math.PI * radius * radius;
    }
    public double getPerimeter() {
        return 2 * Math.PI * radius;
    }
    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Perimeter: " + getPerimeter();
    }
}

