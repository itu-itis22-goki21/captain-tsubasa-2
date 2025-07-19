#include "Player.h"



vector<vector<Jersey>> pitch;

void addPlayers(vector<Player> &usteam, vector<Player> &enteam){
    for(int i = 0;i< usteam.size(); i++){
        pitch[usteam[i].x][usteam[i].y] = usteam[i].team->jersey; 
    }
}

Player::Player(string name, Team *team, int x, int y): name(name), team(team), x(x), y(y)
{
}
Player::~Player(){}



void freeball(){}
void pushaway(Player &us, Player &enemy){
    int centerX = (us.x + enemy.x);
    int centerY = (us.y + enemy.y);

    int offsetX = (rand() % 5) - 2; // -2, -1, 0, 1, 2
    int offsetY = (rand() % 5) - 2;

    ball.x = centerX + offsetX;
    ball.y = centerY + offsetY;

    cout << "ball is loose" << endl;

    freeball();
}

void Player::dribble(Player &us, Player &enemy){
    int dice1, dice2 = 0;
    dice1 = rand()%6;
    dice2 = rand()%6;
    us.stamina - DRIB;
    enemy.stamina - TACKLE;

    int uslvl = us.dribPower+dice1;
    int enemylvl =enemy.dribPower+dice2;
    int diff = uslvl-enemylvl;
    if(diff > 0){
        cout << us.name << " has dribbled"<<endl;
        return;
    }
    else {
        if(diff <-3){
            if(enemy.aggression == true){
                cout << enemy.name << " has killed" << us.name << endl;
            }
            cout << enemy.name << " has tackled" << endl;
            enemy.hasball = 1;
            return;
        }
        else{
            cout << enemy.name << " has pushed away" << endl;
            pushaway(us, enemy);
            return;
        }
    }
}
void interception(vector<Player> &enplayers){
    //bfs();

}

void drawGrid(Player &passer, vector<Player> &players, vector<Player> &enplayers) {
    const int gridSize = 10;
    int cursorX = passer.x;
    int cursorY = passer.y;

    while (true) {
        system("cls");

        // Draw grid
        for (int y = passer.y - gridSize / 2; y <= passer.y + gridSize / 2; y++) {
            for (int x = passer.x - gridSize / 2; x <= passer.x + gridSize / 2; x++) {
                if(x == cursorX && y == cursorY && x == players[1].x && y == players[1].y){
                    printf("[%d]", players[1].team->jersey.number);
                }
                else if (x == cursorX && y == cursorY)
                    cout << "[ ]";
                else if (x == passer.x && y == passer.y)
                    cout << " P "; 
                else if(x == players[1].x && y == players[1].y){
                    printf(" %d ", players[1].team->jersey.number);
                }
                else
                    cout << "   ";
            }
            cout << "\n";
        }

        cout << "Use arrow keys to move, Enter to pass\n";

        int key = getch();
        if (key == 224) { // arrow keys prefix
            key = getch();
            switch (key) {
                case 72: cursorY--; break; // up
                case 80: cursorY++; break; // down
                case 75: cursorX--; break; // left
                case 77: cursorX++; break; // right
            }
        } else if (key == 13) { // Enter
            // Check if a player is at the cursor position
            for (auto &target : players) {
                if (target.x == cursorX && target.y == cursorY) {
                    cout << passer.name << " passes the ball to " << target.name << "!\n";
                    interception(enplayers);
                    passer.hasball = false;
                    target.hasball = true;
                    ball.x = target.x;
                    ball.y = target.y;
                    return;
                }
            }
            cout << "No player at selected position!\n";
            sleep(1);
        }

        // Clamp cursor within field
        cursorX = max(0, min(cursorX, 20 - 1));
        cursorY = max(0, min(cursorY, 10- 1));
    }
}


void Player::pass(Player &us1, vector<Player> &usplayers, vector<Player> &enplayers){
    drawGrid(us1, usplayers, enplayers);
}

