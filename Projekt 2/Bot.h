#pragma once
#include "Gracz.h"
class Bot :
    public Gracz
{
private:
    int typBota; // ryzykuj¹cy(1), normalny(2) lub zachowawczy(3)
public:
    Bot(Kasyno& _kasyno, int numer, int trybBotow);
    void czyPass();
};
