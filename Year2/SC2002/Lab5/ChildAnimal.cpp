#include <iostream>
#include <string>
#include "ChildAnimal.h"

using namespace std;

Dog::Dog(string n, COLOR c) : Mammal(n, c) {}

Dog::~Dog()
{
    cout << "Dog Destructor" << endl;
}

void Dog::speak() const
{
    cout << "Woof" << endl;
}

void Dog::move()
{
    cout << "Dog::move() called" << endl;
}
void Dog::eat()
{
    cout << "Dog::eat() called" << endl;
}


Cat::Cat(string n, COLOR c) : Mammal(n, c) {}

Cat::~Cat()
{
    cout << "Cat Destructor" << endl;
}

void Cat::speak() const
{
    cout << "Meow" << endl;
}

void Cat::move()
{
    cout << "Cat::move() called" << endl;
}

void Cat::eat()
{
    cout << "Cat::eat() called" << endl;
}



Lion::Lion(string n, COLOR c) : Mammal(n, c) {}

Lion::~Lion()
{
    cout << "Lion Destructor" << endl;
}

void Lion::speak() const
{
    cout << "Roar" << endl;
}

void Lion::move()
{
    cout << "Lion::move() called" << endl;
}
void Lion::eat()
{
    cout << "Lion::eat() called" << endl;
}

