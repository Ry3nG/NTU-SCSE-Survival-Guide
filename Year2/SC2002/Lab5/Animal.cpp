#include <iostream>
#include <string>
#include "Animal.h"

using namespace std;

Animal::Animal()
{
    _name = "No Name";
    _color = Green;
}

Animal::Animal(string name, COLOR color) : _name(name), _color(color)
{
    cout << "Constructing: " << _color << " " << _name << endl;
}

Animal::~Animal()
{
    cout << "Destructing: " << _color << " " << _name << endl;
}

void Animal::speak() const
{
    cout << "Animal::speak() called" << endl;
}

void Animal::move() {}

 void Mammal::eat() 
{
    cout << "Mammal::eat() called" << endl;
}

Mammal::Mammal() : Animal() {}

Mammal::Mammal(string n, COLOR c) : Animal(n, c) {}

Mammal::~Mammal() {
    cout << "Destructing Mammal objects" << endl;
}

void Mammal::move()
{
    cout << "Mammal::move() called" << endl;
}
