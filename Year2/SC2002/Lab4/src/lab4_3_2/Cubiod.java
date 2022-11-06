package lab4_3_2;

public class Cubiod extends Rectangle {
    double height;

    public Cubiod(double length, double width, double height) {
        super(length, width);
        this.name = "Cubiod";
        this.height = height;
    }

    public double getVolume() {
        return getArea() * height;
    }

    public double getSurfaceArea() {
        return 2 * (getArea() + length * height + width * height);
    }

    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Perimeter: " + getPerimeter() + " Volume: " + getVolume()
                + " Surface Area: " + getSurfaceArea();
    }
}
