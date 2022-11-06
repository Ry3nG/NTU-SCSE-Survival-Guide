#include <iostream>
#include <string>
#include "ChildAnimal.h"

using namespace std;

int main()
{
    Mammal *mammalArray[3];
    mammalArray[0] = new Dog("DogName", Green);
    mammalArray[1] = new Cat("CatName", Blue);
    mammalArray[2] = new Lion("LionName", White);
    
    cout << "Select the animal to send to Zoo :\n"
            "(1) Dog (2) Cat (3) Lion (4) Move all animals (5) Quit\n"
         << ends;
    int choice;
    cin >> choice;

    while (choice != 5)
    {
        switch (choice)
        {
        case 1:

            mammalArray[0]->speak();
            mammalArray[0]->move();
            mammalArray[0]->eat();
            break;
        case 2:

            mammalArray[1]->speak();
            mammalArray[1]->move();
            mammalArray[1]->eat();
            break;
        case 3:

            mammalArray[2]->speak();
            mammalArray[2]->move();
            mammalArray[2]->eat();
            break;
        case 4:
            for (int i = 0; i < 3; i++)
            {
                mammalArray[i]->move();
                mammalArray[i]->speak();
                mammalArray[i]->eat();
            }
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }

        cout << "\nSelect the animal to send to Zoo :\n"
                "(1) Dog (2) Cat (3) Lion (4) Move all animals (5) Quit\n"
             << ends;
        cin >> choice;
    }

    for (int i = 0; i < 3; i++)
    {
        delete mammalArray[i];
    }

    return 0;
}