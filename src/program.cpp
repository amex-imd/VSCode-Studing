#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include "out.h"

struct monster
{
public:
    char *name;
    int *stats;
    // Можно напрямую менять поля и ломать работу памяти - плохо...

private:
    int __size;

public:
    monster(const char *n, int size) : __size(size)
    {
        this->name = new char[strlen(n) + 1]; // Zero-char
        strcpy(this->name, n);
        stats = new int[size];
        for (int i = 0; i < size; ++i)
            stats[i] = i * 13;
    }

    monster(const monster &other) : __size(other.__size)
    {
        this->name = new char[strlen(other.name) + 1]; // Zero-char
        strcpy(this->name, other.name);
        stats = new int[other.__size];
        for (int i = 0; i < other.__size; ++i)
            stats[i] = other.stats[i];
    }

    monster &operator=(const monster &other)
    {
        if (this != &other)
        {
            this->free();
            this->__size = other.__size;

            this->name = new char[strlen(other.name) + 1]; // Zero-char
            strcpy(this->name, other.name);
            stats = new int[other.__size];
            for (int i = 0; i < other.__size; ++i)
                stats[i] = other.stats[i];
        }
        return *this;
    }

    monster(monster &&other)
    {
        this->name = other.name;
        this->stats = other.stats;
        this->__size = other.__size;

        other.name = NULL;
        other.stats = NULL;
        other.__size = 0;
    }

    monster &operator=(monster &&other)
    {
        if (this != &other)
        {
            this->free();

            this->name = other.name;
            this->stats = other.stats;
            this->__size = other.__size;

            other.name = NULL;
            other.stats = NULL;
            other.__size = 0;
        }
        return *this;
    }

    ~monster()
    {
        this->free();
    }

private:
    void free()
    {
        delete[] this->name;
        delete[] this->stats;

        this->__size = 0;
        this->name = NULL;
        this->stats = NULL;
    }
};

void hack_the_system()
{
    monster m("Ghoul", 4);
    int *raw = m.stats;

    for (int i = 0; i < 4; ++i)
        raw[i] += 100;
    std::cout << m.name << " hacked stats:";
    for (int i = 0; i < 4; ++i)
        std::cout << raw[i] << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<monster> monsters;
    for (int i = 0; i < 3; ++i)
        monsters.push_back(monster("Zombie", 5));
}