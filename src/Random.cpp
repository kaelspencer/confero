#include "Random.h"

Random * Random::m_instance = 0;

Random * Random::Instance()
{
    if(m_instance == 0)
    {
        m_instance = new Random();
    }

    return m_instance;
}

Random::Random()
{
    srand((unsigned)time(0));
}

unsigned int Random::GetNumber() const
{
    return rand() * rand();
}
