#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include "Team.h"
#include "ball.h"
#include "goalie.h"
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
    int dribPower = 10;
    int shootPower = 10;
    int passPower = 10;
    int oneTwoPower = 0;

    // Defensive values
    int tacklePower = 0;
    int passcutPower = 0;
    int blockPower = 0;
    int skip = 0;

    // (consider setters/getters)
    int pace = 0;
    bool aggression = false;
    bool hasball = false;
    int stamina = 100; // Starting stamina

    bool isGoalie;
    Goalie goalieSpec;
    Team *team;
    
    Player();
    Player(string name, Team *team, int x, int y);
    ~Player();
    //offensive plays
    Player pass(Player &us1, vector<Player> &usplayers, vector<Player> &enplayers, bool isOneTwo);
    Player dribble(Player &us, Player &enemy, vector<Player> &usplayers, vector<Player> &enplayers);
    int shoot(Player &us, vector<Player> &enplayers, Player &goalie);
    int oneTwo(Player &us1, vector<Player> &usplayers, vector<Player> &enplayers);
    void run(vector<Player> &usplayers, vector<Player> &enplayers);
    //defensive plays
    bool passcut(Player &interceptor, Player &passer);
    bool block(Player &blocker, Player &shooter);
    bool tackle(Player &us, Player &enemy);
};


void addPlayer(vector<Player> &usteam, vector<Player> &enteam);
Player whoHasBall(vector<Player> &usplayers, vector<Player> &enplayers);
string stop(Player enemy, Player us, vector<Player> &enplayers);
string Select(Player &selector);
#endif 