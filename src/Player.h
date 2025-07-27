#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include "Team.h"
#include "ball.h"
#include <conio.h> // for getch() on Windows
#include <unistd.h>
#include <unistd.h>

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
    int shootPower = 0;
    int passPower = 10;
    int oneTwoPower = 0;

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

    
    Team *team;
    
    Player();
    Player(string name, Team *team, int x, int y);
    ~Player();
    Player pass(Player &us1, vector<Player> &usplayers, vector<Player> &enplayers, bool isOneTwo);
    void dribble(Player &us, Player &enemy);
    void shoot(Player &us, vector<Player> &enplayers, Player &goalie);
    int oneTwo(Player &us1, vector<Player> &usplayers, vector<Player> &enplayers);
};

void addPlayer(vector<Player> &usteam, vector<Player> &enteam);
Player whoHasBall(vector<Player> &usplayers, vector<Player> &enplayers);

#endif 