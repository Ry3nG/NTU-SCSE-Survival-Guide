package lab4_3_2;

public class Sphere extends Shape{
    double radius;
    public Sphere(double radius) {
        super("Sphere");
        this.radius = radius;
    }
    public double getArea() {
        return 4 * Math.PI * radius * radius;
    }
    public double getPerimeter() {
        return 2 * Math.PI * radius;
    }
    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Perimeter: " + getPerimeter();
    }
}
