#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include "Team.h"
#include <conio.h> // for getch() on Windows
#include<unistd.h>

#define DRIB 40
#define PASS 20
#define SHOOT 50
#define RUN 5
#define HEAL 1 
#define TACKLE 40

#define MAX_VALUE 255
using namespace std;

class Player
{
public:
    int x, y;
    string name;
    int dribPower = 0;
    int shoot = 0;
    int passPower = 0;
    int oneTwo = 0;

    // Defensive values
    int tackle = 0;
    int passcut = 0;
    int block = 0;
    int skip = 0;

    // (consider setters/getters)
    int pace = 0;
    bool aggression = false;
    bool hasball = false;
    int stamina = 100; // Starting stamina

    int jersey;
    Team *team;

    Player(string name, Team *team, int jersey, int x, int y);
    ~Player();
    void pass(Player &us1, vector<Player> &usplayers, vector<Player> &enplayers);
    void dribble(Player &us, Player &enemy);
};



class Ball{
public:
    int x, y;
};

extern Ball ball;
#endif 