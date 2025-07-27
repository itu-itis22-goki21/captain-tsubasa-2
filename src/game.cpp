#include "Player.h"

Ball ball;

void whoHasBall(vector<Player> &usplayers, vector<Player> &enplayers){
    cout << "whohasball entered"<< endl;
    for(int i = 0; i < usplayers.size(); i++){
        if(usplayers[i].hasball){
            cout << usplayers[i].name <<" has ball at " << usplayers[i].x << " " <<  usplayers[i].y  << endl;
        }
    }
    for(int i = 0; i < enplayers.size(); i++){
        if(enplayers[i].hasball){
            cout << enplayers[i].name <<" has ball at " << enplayers[i].x << " " <<  enplayers[i].y  << endl;
        }
    }
    return;
}


int main(){
    Jersey Tsu(10, 0);
    Team Japan("Japan", Tsu);

    
    Jersey San(5,1);
    Team Brazil("Brazil", San);
    
    vector <Player> usteam= {{"Tsubasa", &Japan, 0, 5},{"Misaki", &Japan, 9, 5}};
    vector <Player> enteam= {{"Santana", &Brazil, 3, 5},{"Coimbra", &Brazil, 6, 5}};
    
    usteam[0].hasball = 1;
    addPlayer(usteam, enteam);
    usteam[0].pass(usteam[0], usteam, enteam);
    whoHasBall(usteam, enteam);
}
