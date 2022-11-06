#ifndef ANIMAL
#define ANIMAL
#include <iostream>
#include <string>

enum COLOR
{
    Green,
    Blue,
    White,
    Black,
    Brown
};

class Animal
{
private:
    std::string _name;
    COLOR _color;

public:
    Animal();
    Animal(std::string name, COLOR color);
    virtual ~Animal();

    virtual void speak() const;
    virtual void move() = 0;
};

class Mammal : public Animal
{
public:
    Mammal();
    Mammal(std::string n, COLOR c);
    ~Mammal();

    void move();
    virtual void eat();
};

#endif // _ANIMAL_
