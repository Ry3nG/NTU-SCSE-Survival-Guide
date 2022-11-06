package lab4_3_2;

public class Pyramid extends Shape {
    double length;
    double width;
    double height;

    public Pyramid(double length, double width, double height) {
        super("Pyramid");
        this.length = length;
        this.width = width;
        this.height = height;
    }

    public double getArea() {
        return length * width + length * Math.sqrt(Math.pow(width / 2, 2) + Math.pow(height, 2))
                + width * Math.sqrt(Math.pow(length / 2, 2) + Math.pow(height, 2));
    }

    public double getPerimeter() {
        return 4 * Math.sqrt(Math.pow(length / 2, 2) + Math.pow(height, 2));
    }

    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Perimeter: " + getPerimeter();
    }

}
