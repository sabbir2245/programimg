#include <iostream>
#include <cstring>

using namespace std;

class Planet
{
    char *name;   // Pointer for the name of the planet
    int distance; // Distance from the sun in millions of kilometers

public:
    Planet()
    {
        name = new char[1];
        name[0] = '\0';
        distance = 0;
    }

    Planet(const char *planetName, int dist)
    {
        name = new char[strlen(planetName) + 1];
        strcpy(name, planetName);
        distance = dist;
    }

    Planet(const Planet &other)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        distance = other.distance;
    }

    ~Planet()
    {
        delete[] name;
    }

    void display()
    {
        cout << "Planet: " << name << ", Distance: " << distance << " million km\n";
    }

    // Method to get the planet name
    const char *getName()
    {
        return name;
    }
    int getdistance()
    {
        return distance;
    }
   friend Planet operator+(int i, Planet &t) 
    {
        Planet temp;                                  // Create a temporary Planet object
        temp.name = new char[strlen(t.name) + 1]; // Allocate memory for name
        strcpy(temp.name, t.name);                // Copy the current planet's name into temp's name
        temp.distance = t.distance + i;                 // Modify the distance
        return temp;                                  // Return the modified temporary object
    }

    Planet operator+(const Planet &n)
    {

        Planet temp;
        temp.name = new char[strlen(n.name) + 1];
        strcpy(temp.name, "Combined");
        temp.distance = this->distance + n.distance;

        return temp;
    }
    Planet &operator=(const Planet &n)
    {
        if (this == &n)
        {
            return *this;
        }
        delete[] name;
        name = new char[strlen(n.name) + 1];
        strcpy(name, n.name);
        distance = n.distance;
        return *this;
    }

    int operator<(const Planet &t)
    {
        if (distance < t.distance)
        {
            return 1;
        }
        return 0;
    }
};

class SolarSystem
{
    Planet planets[10];
    int planetCount;

public:
    SolarSystem()
    {
        planetCount = 0;
    }

    // Add a planet to the solar system
    void addPlanet(const char *name, int distance)
    {
        if (planetCount < 10)
        {
            Planet p(name, distance);
            planets[planetCount] = p;
            planetCount++;
        }
        else
        {
            cout << "Solar system is full. Can't add more planets.\n";
        }
    }

    Planet& operator[](int i)
    {
        return planets[i];
    }

    Planet& operator[](const char *str)
    {
        
        for (int i = 0; i < planetCount; i++)
        {
            /* code */
            if (!strcmp(planets[i].getName(), str))
            {
                return planets[i];
            }
        }

      
       
    }
};

int main()
{
    SolarSystem solarSystem;

    // Add planets to the solar system
    solarSystem.addPlanet("Invalid", -1);
    solarSystem.addPlanet("Sun", 0);
    solarSystem.addPlanet("Earth", 150);
    solarSystem.addPlanet("Mars", 228);

    // Display all planets in the solar system
    solarSystem[1].display();
    solarSystem[2].display();
    solarSystem[3].display();

    solarSystem[3] = 140+ solarSystem[3] ;
    solarSystem[3].display();

    Planet p = solarSystem["Earth"] + solarSystem["Mars"];
    p.display();
    if (solarSystem[2] < solarSystem[3])
    {
        cout << "Earth is closer to the Sun than Mars\n";
    }
    else
    {
        cout << "Mars is closer to the Sun than Earth\n";
    }
 
  p =  solarSystem[1] ;
  p.display();
    return 0;
}