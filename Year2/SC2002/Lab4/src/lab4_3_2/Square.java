package lab4_3_2;

public class Square extends Shape{
    double side;
    public Square(double side) {
        super("Square");
        this.side = side;
    }
    public double getArea() {
        return side * side;
    }
    public double getPerimeter() {
        return 4 * side;
    }
    public String toString() {
        return "Shape: " + name + " Area: " + getArea() + " Perimeter: " + getPerimeter();
    }
}
    
