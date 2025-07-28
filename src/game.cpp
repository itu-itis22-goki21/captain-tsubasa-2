#include "Player.h"

Ball ball;

int main(){
    
    Jersey Tsu(10, 0);
    Team Japan("Japan", Tsu);
    
    
    Jersey San(5,1);
    Team Brazil("Brazil", San);
    
    vector <Player> usteam= {{"Tsubasa", &Japan, 0, 5},{"Misaki", &Japan, 9, 5}, {"Wakabayashi", &Japan, 0, 5}};
    vector <Player> enteam= {{"Santana", &Brazil, 3, 5},{"Coimbra", &Brazil, 6, 5}, {"Gertise", &Brazil, 15, 5}};
    usteam[0].hasball = 1;
    addPlayer(usteam, enteam);
    
    usteam[0].shoot(usteam[0], enteam, enteam[2]);
    whoHasBall(usteam, enteam);
}
