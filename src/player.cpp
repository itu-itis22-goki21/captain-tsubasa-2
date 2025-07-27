#include "Player.h"

Player::Player(){}
Player::Player(string name, Team *team, int x, int y): name(name), team(team), x(x), y(y)
{
}
Player::~Player(){}

Player ***pitch = new Player**[10];



void addPlayer(vector<Player> &usteam, vector<Player> &enteam){
    for (int i = 0; i < 10; ++i) {
        pitch[i] = new Player*[10];
        for (int j = 0; j < 10; ++j) {
            pitch[i][j] = nullptr; // Initially empty
        }
    }
    // Place user team players
    for (int i = 0; i < usteam.size(); i++) {
        int x = usteam[i].x;
        int y = usteam[i].y;
        pitch[x][y] = &usteam[i];
        //std::cout << pitch[x][y]->name << std::endl;
    }

    // Place enemy team players
    for (int i = 0; i < enteam.size(); i++) {
        int x = enteam[i].x;
        int y = enteam[i].y;
        pitch[x][y] = &enteam[i];
        //std::cout << pitch[x][y]->name << std::endl;
    }
}

int magnitude(int x1, int y1, int x2, int y2){
    x2 -=x1;
    y2 -=y1;
    return (x2+y2)/2;
}

void freeball() {
    for (int i = ball.x - ball.velocity / 2; i < ball.x + ball.velocity; i++) {
        for (int j = ball.y - ball.velocity / 2; j < ball.y + ball.velocity; j++) {

            // Prevent out-of-bounds access
            if (i < 0 || i >= 10 || j < 0 || j >= 10 || pitch[i][j] == nullptr)
                continue;

            if (pitch[i][j]->x == i && pitch[i][j]->y == j) {
                pitch[i][j]->hasball = 1;
                pitch[i][j]->x = ball.x;
                pitch[i][j]->y = ball.y;
                //std::cout << pitch[i][j]->name << std::endl;
                return;
            }
        }
    }
}

void pushaway(Player &enemy){
    srand(time(NULL));
    int centerX = (enemy.x);
    int centerY = (enemy.y);

    int offsetX = (rand() % 5) - 2; // -2, -1, 0, 1, 2
    int offsetY = (rand() % 5) - 2;

    ball.x = centerX + offsetX;
    ball.y = centerY + offsetY;
    
    cout << "ball is loose" << endl;

    freeball();
    
    return;
}

void Player::dribble(Player &us, Player &enemy){
    srand(time(NULL));
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
            pushaway(enemy);
            return;
        }
    }
}

vector<Player> lineDrawing(vector<Player> &enplayers, Player &passer, Player &target){
    vector<Player> intercepting_players;
    int dx = target.x - passer.x;
    int dy = target.y - passer.y;
    int m = dy/dx;
    int y;
    //draws a line and pushes the players into the stack players that able to cut the pass
    if(passer.x < target.x){//forward pass
        for(int i = passer.x; i < target.x; i++){
            y = m * (i - passer.x) + passer.y;
            for(int j = 0; j < 10;j++){
                
                if(enplayers[j].x == i && enplayers[j].y ==y){
                    intercepting_players.push_back(enplayers[j]);
                }
            }
        }
        return intercepting_players;
    }else{// else condition is passing backward
        for(int i = passer.x; i > target.x; i--){
            y = m * (i - passer.x) + target.y;
            for(int j = 0; j < 10;j++){
                if(enplayers[j].x == i && enplayers[j].y ==y){
                    intercepting_players.push_back(enplayers[j]);
                }
            }
        }
        return intercepting_players;
    }
    
}

bool passcut(Player &interceptor, Player &passer){
    cout << interceptor.name << " has jumped" << endl;
    
    if(passer.passPower > interceptor.passcut){
        cout << interceptor.name << " could not cut" << endl;
        return 0;
        
    }else if(passer.passPower == interceptor.passcut){
        ball.x = interceptor.x;
        ball.y = interceptor.y;
        pushaway(interceptor);
        
        return 1;
    }
    else{
        cout<< interceptor.name << " has taken out the ball";
        ball.x = interceptor.x;
        ball.y = interceptor.y;
        interceptor.hasball = 1;
        return 1;
    }
    
}

bool interception(vector<Player> &enplayers, Player &passer, Player &target){
    vector<Player> interPlayers;
    interPlayers = lineDrawing(enplayers, passer, target);//intercepting players in this vector
    for(int i = 0; i< interPlayers.size();i++){
        if(passcut(interPlayers[i], passer)){
            
            return 0;
        }else{
            continue;
        }
    }return 1;

}

void drawGrid(Player &passer, vector<Player> &players, vector<Player> &enplayers) {
    const int gridSize = 10;
    int cursorX = passer.x;
    int cursorY = passer.y;

    while (true) {
        system("cls");

        // Draw grid
        for (int y = 0; y <=  gridSize ; y++) {
            for (int x = 0; x <= gridSize ; x++) {
                if(x == cursorX && y == cursorY && x == players[1].x && y == players[1].y){
                    printf("[%d]", players[1].team->jersey.number);
                }
                else if (x == cursorX && y == cursorY)
                    cout << "[ ]";
                else if (x == passer.x && y == passer.y)
                    cout << " P "; 
                else if(x == players[1].x && y == players[1].y){
                    
                    printf(" %d ", players[1].team->jersey.number);
                }else if(x == enplayers[0].x && y == enplayers[0].y){
                    printf("\033[31;1;1m %d \033[0m", enplayers[0].team->jersey.number);
                }else if(x == enplayers[1].x && y == enplayers[1].y){
                    printf("\033[31;1;1m %d \033[0m", enplayers[1].team->jersey.number);
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
                    ball.velocity = magnitude(passer.x, passer.y, target.x, target.y);
                    if(interception(enplayers, passer, target)){
                        //pass succeed if intercept return 1
                        passer.hasball = false;
                        target.hasball = true;
                        ball.x = target.x;
                        ball.y = target.y;
                        cout << "A";
                        return;
                    }
                    else {
                        passer.hasball = false;
                        
                        return;
                    }
                    
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
    return;
}

