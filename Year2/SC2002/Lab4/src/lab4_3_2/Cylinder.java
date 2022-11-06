package lab4_3_2;

public class Cylinder extends Circle {
    double height;

    public Cylinder(double radius, double height) {
        super(radius);
        this.name = "Cylinder";
        this.height = height;
    }

    public double getArea() {
        return 2 * Math.PI * radius * (radius + height);
    }

    public double getVolume() {
        return Math.PI * radius * radius * height;
    }

    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Volume: " + getVolume();
    }

}
