#ifndef CHILDANIMAL
#define CHILDANIMAL
#include <String>
#include <iostream>

#include "Animal.h"

class Dog : public Mammal
{

public:
    Dog(std::string n, COLOR c);
    ~Dog();
    void speak() const;
    void move();
    void eat();
};

class Cat : public Mammal
{
public:
    Cat(std::string n, COLOR c);
    ~Cat();
    void speak() const;
    void move();
    void eat();
};

class Lion : public Mammal
{
public:
    Lion(std::string n, COLOR c);
    ~Lion();
    void speak() const;
    void move();
    void eat();
};

#endif
