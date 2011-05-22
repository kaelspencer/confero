#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <ctime>

class Random
{
private:
    static Random * m_instance;

    Random();
    Random(const Random & rhs);
    Random & operator=(const Random & rhs);

public:
    ~Random();
    static Random * Instance();
    unsigned int GetNumber() const;
};

#endif
