#include <iostream>
#include <cstring>
using namespace std;

class Planet
{
    char *name;
    int distance;

public:
    Planet(const char *planetName = "", int dist = 0) : distance(dist)
    {
        name = new char[strlen(planetName) + 1];
        strcpy(name, planetName);
    }
    Planet(const Planet &other) : distance(other.distance)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    ~Planet() { delete[] name; }

    void display() const
    {
        cout << "Planet: " << name << ", Distance: " << distance << " million km\n";
    }
    const char *getName() const { return name; }
    int getDistance() const { return distance; }

    friend Planet operator+(int i, const Planet &t)
    {
        return Planet(t.name, t.distance + i);
    }
    Planet operator+(const Planet &n) const
    {
        return Planet("Combined", distance + n.distance);
    }
    Planet &operator=(const Planet &n)
    {
        if (this != &n)
        {
            delete[] name;
            name = new char[strlen(n.name) + 1];
            strcpy(name, n.name);
            distance = n.distance;
        }
        return *this;
    }
    bool operator<(const Planet &t) const
    {
        return distance < t.distance;
    }
};

class SolarSystem
{
    Planet planets[10];
    int planetCount;

public:
    SolarSystem() : planetCount(0) {}

    void addPlanet(const char *name, int distance)
    {
        if (planetCount < 10)
            planets[planetCount++] = Planet(name, distance);
    }
    Planet &operator[](int i) { return planets[i]; }

    Planet &operator[](const char *str)
    {
        for (int i = 0; i < planetCount; i++)
        {
            if (!strcmp(planets[i].getName(), str))
                return planets[i];
        }
    }
};

int main()
{
    SolarSystem solarSystem;
    solarSystem.addPlanet("Invalid", -1);
    solarSystem.addPlanet("Sun", 0);
    solarSystem.addPlanet("Earth", 150);
    solarSystem.addPlanet("Mars", 228);

    solarSystem[1].display();
    solarSystem[2].display();
    solarSystem[3].display();

    solarSystem[3] = 140 + solarSystem[3];
    solarSystem[3].display();

    Planet p = solarSystem["Earth"] + solarSystem["Mars"];
    p.display();

    if (solarSystem[2] < solarSystem[3])
        cout << "Earth is closer to the Sun than Mars\n";
    else
        cout << "Mars is closer to the Sun than Earth\n";

    p = solarSystem[1];
    p.display();

    return 0;
}
