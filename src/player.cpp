#include "Player.h"

Player::Player(){}
Player::Player(string name, Team *team, int x, int y): name(name), team(team), x(x), y(y)
{
}
Player::~Player(){}

Player ***pitch = new Player**[10];

Player *GlobaloneTwo = new Player;

void addPlayer(vector<Player> &usteam, vector<Player> &enteam){
    for (int i = 0; i < 11; ++i) {
        pitch[i] = new Player*[11];
        for (int j = 0; j < 11; ++j) {
            pitch[i][j] = nullptr; // Initially empty
        }
    }
    
    // Place user team players
    for (Player &p : usteam) {
    if (p.x >= 0 && p.x < 15 && p.y >= 0 && p.y < 10) {
        pitch[p.x][p.y] = &p;
    }
}

    // Place enemy team players
    for (Player &p : enteam) {
    if (p.x >= 0 && p.x < 15 && p.y >= 0 && p.y < 10) {
        pitch[p.x][p.y] = &p;
    }
}
    cout << "" ;
    return;
}

int magnitude(int x1, int y1, int x2, int y2){
    x2 -=x1;
    y2 -=y1;
    return (x2+y2)/2;
}
string defSelect(Player &selector) {
    int direction = -1;

    cout << "Press arrow key to choose action, then press Enter:\n";
    while (true) {

        int key = getch();
        if (key == 224) { // arrow key prefix
            key = getch();
            system("cls");
            direction = key; // store direction
            switch (key) {
                case 72: cout << "Selected: up (Tackle)\n"; break;
                case 80: cout << "Selected: down (Nothing)\n"; break;
                case 75: cout << "Selected: left (Passcut)\n"; break;
                case 77: cout << "Selected: right (Block)\n"; break;
                default: cout << "Unknown direction\n"; break;
                
            }
        } else if (key == 13 && direction != -1) { // Enter pressed
            switch (direction) {
                case 72: return "tackle";
                case 80: return "nothing";
                case 75: return "passcut";
                case 77: return "block";
                default: return "nothing";
            }
        }
    }
}

string stop(Player enemy, Player us){
    cout << enemy.name << " has stopped " << us.name << endl;
    return defSelect(enemy);

}

Player whoHasBall(vector<Player> &usplayers, vector<Player> &enplayers){
    for(int i = 0; i < usplayers.size(); i++){
        if(usplayers[i].hasball){
            cout << usplayers[i].name <<" has ball at " << usplayers[i].x << " " <<  usplayers[i].y  << endl;
            sleep(1);
            return usplayers[i];
        }
    }
    for(int i = 0; i < enplayers.size(); i++){
        if(enplayers[i].hasball){
            cout << enplayers[i].name <<" has ball at " << enplayers[i].x << " " <<  enplayers[i].y  << endl;
            sleep(1);
            return enplayers[i];
        }
    }
    return *GlobaloneTwo;// there should be an exepction and exit here
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
    sleep(1);

    freeball();
    
    return;
}

Player Player::dribble(Player &us, Player &enemy, vector<Player> &usplayers, vector<Player> &enplayers){
    string  action = stop(enemy, us);
    
    // Important case:
    //In here if we drib enemy does tackle or passcut or block or nothing
    //So we switch the arguments in the defensive functions
    //switch case would be useful
    if(action == "tackle"){
        cout << enemy.name << " tackling" <<endl;
        if(tackle(us, enemy)){
            return whoHasBall(usplayers, enplayers);
        }
    }else if(action == "passcut"){
        return whoHasBall(usplayers, enplayers);
    }
    return us;
    
}
bool Player::tackle(Player &us, Player &enemy){
    srand(time(NULL));
    int dice1, dice2 = 0;
    dice1 = rand()%6;
    dice2 = rand()%6;
    us.stamina - DRIB;
    enemy.stamina - TACKLE;

    int uslvl = us.dribPower+dice1;
    int enemylvl =enemy.tacklePower+dice2;
    int diff = uslvl-enemylvl;
    if(diff > 0){
        cout << us.name << " has dribbled"<<endl;
        return true;//dribble succeded
    }
    else {
        if(diff <-3){
            if(enemy.aggression == true){
                cout << enemy.name << " has killed" << us.name << endl;
            }
            cout << enemy.name << " has tackled" << endl;
            enemy.hasball = 1;
            return false;
        }
        else{
            cout << enemy.name << " has pushed away" << endl;
            pushaway(enemy);
            return false;
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



bool Player::passcut(Player &interceptor, Player &passer){
    cout << interceptor.name << " has jumped" << endl;
    sleep(1);
    
    if(passer.passPower > interceptor.passcutPower){
        cout << interceptor.name << " could not cut" << endl;
        sleep(1);
        return 0;
        
    }else if(passer.passPower == interceptor.passcutPower){
        ball.x = interceptor.x;
        ball.y = interceptor.y;
        pushaway(*this);
        
        return 1;
    }
    else{
        cout<< interceptor.name << " has taken out the ball";
        sleep(1);
        ball.x = interceptor.x;
        ball.y = interceptor.y;
        interceptor.hasball = 1;
        return 1;
    }
    
}
bool Player::block(Player &blocker, Player &shooter){
    cout << blocker.name << " has jumped" << endl;
    sleep(1);
    
    if(shooter.shootPower > blocker.blockPower){
        cout << blocker.name << " could not blocked" << endl;
        sleep(1);
        return 0;
        
    }else if(shooter.shootPower == blocker.blockPower){
        ball.x = blocker.x;
        ball.y = blocker.y;
        cout << blocker.name << " has blocked" << endl;
        pushaway(*this);
        
        return 1;
    }
    else{
        cout<< blocker.name << " has taken out the ball";
        sleep(1);
        ball.x = blocker.x;
        ball.y = blocker.y;
        blocker.hasball = 1;
        return 1;
    }
}

bool interception(vector<Player> &enplayers, Player &passer, Player &target, bool isPass){
    vector<Player> interPlayers;
    interPlayers = lineDrawing(enplayers, passer, target);//intercepting players in this vector
    if(isPass){
        for(int i = 0; i< interPlayers.size();i++){
            if(interPlayers[i].passcut(interPlayers[i], passer)){
                //pass or shoot cutted
                return 0;
            }else{
                continue;
            }
        //pass or shoot completed    
        }return 1;
    }else{
        for(int i = 0; i< interPlayers.size();i++){
            if(interPlayers[i].block(interPlayers[i], passer)){
                //pass or shoot cutted
                return 0;
            }else{
                continue;
            }
        //pass or shoot completed    
        }return 1;
    }
    
}

Player drawGrid(Player &passer, vector<Player> &players, vector<Player> &enplayers, bool isOneTwo, bool isPass) {
    const int gridSize = 15;
    int cursorX = passer.x;
    int cursorY = passer.y;
    
    if(isOneTwo){
        cout << passer.name << " passes the ball to for one two " << GlobaloneTwo->name << "!\n";
        sleep(1);
        ball.velocity = magnitude(passer.x, passer.y, GlobaloneTwo->x, GlobaloneTwo->y);
        if(interception(enplayers, passer, *GlobaloneTwo, isPass)){
            //pass succeed if intercept return 1
            passer.hasball = false;
            GlobaloneTwo->hasball = true;
            ball.x = GlobaloneTwo->x;
            ball.y = GlobaloneTwo->y;
            
            return *GlobaloneTwo;
        }
        else {
            passer.hasball = false;
            
            return whoHasBall(players, enplayers);
        }
        
    }else{
        
        while (true) {
            system("cls");

            // Draw grid
            for (int y = 0; y <=  gridSize/1.5 ; y++) {
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
                        cout << passer.name << " passes the ball to " << target.name << " in order to pass" << "!\n";
                        sleep(1);
                        ball.velocity = magnitude(passer.x, passer.y, target.x, target.y);
                        if(interception(enplayers, passer, target, isPass)){
                            //pass succeed if intercept return 1
                            passer.hasball = false;
                            target.hasball = true;
                            ball.x = target.x;
                            ball.y = target.y;
                            
                            return target;
                        }
                        else {
                            passer.hasball = false;
                            
                            return whoHasBall(players, enplayers);
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
    
}


Player Player::pass(Player &us1, vector<Player> &usplayers, vector<Player> &enplayers, bool isOneTwo){
    bool isPass = true;
    Player ballOn = drawGrid(us1, usplayers, enplayers, isOneTwo, isPass);
    return ballOn;
}

int Player::oneTwo(Player &us1, vector<Player> &usplayers, vector<Player> &enplayers){
    
    Player ballOn = pass(us1, usplayers, enplayers, false);
    if(ballOn.team->teamname == "Japan"){
        us1.x +=3;// take 3 steps 
        GlobaloneTwo = &us1;
        ballOn = pass(ballOn, usplayers, enplayers, true);
        if(ballOn.team->teamname == "Japan"){
            cout << "One Two succeeded by " << ballOn.name << endl;
            cout << GlobaloneTwo->name << " " << GlobaloneTwo->hasball<< endl;
            return 1; 
        }else return 0;
    }else return 0;

}

int Player::shoot(Player &us, vector<Player> &enplayers, Player &goalie){
    cout << us.name << " has shot into the " << goalie.team->teamname<< " goal" << endl;
    sleep(1);
    bool isPass = false;
    if(interception(enplayers, us, goalie, isPass)){
        
        cout << us.name << "'s shoot going to goal post" << endl;
        sleep(1);
        if(goalie.goalieSpec.catchPower > us.shootPower){
            cout << goalie.goalieSpec.catchPower<< endl;
            
            cout << goalie.name << " had catched the ball" << endl;
            us.hasball = false;
            goalie.hasball = true;
            return 1;
        }else {
            //goal
            cout << us.name<< " 's shot was a goal!" << endl;
            us.hasball = false;
            enplayers[0].hasball = true;
            return 0;
        }
    }else return 0; //shoot cutted

    return -1;
}