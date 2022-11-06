package lab4_3_2;

public class Cone extends Circle {
    double height;
    public Cone(double radius, double height) {
        super(radius);
        this.name = "Cone";
        this.height = height;
    }
    public double getArea() {
        return Math.PI * radius * (radius + Math.sqrt(height * height + radius * radius));
    }
    public double getVolume() {
        return Math.PI * radius * radius * height / 3;
    }
    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Volume: " + getVolume();
    }
    
}
