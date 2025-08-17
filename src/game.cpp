#include "Player.h"

Ball ball;

int main(){
    
    Jersey Tsu(10, 0);
    Team Japan("Japan", Tsu);
    
    
    Jersey San(5,1);
    Team Brazil("Brazil", San);
    
    vector <Player> usteam= {{"Tsubasa", &Japan, 1, 10},{"Misaki", &Japan, 9, 5}, {"Wakabayashi", &Japan, 0, 5}};
    vector <Player> enteam= {{"Santana", &Brazil, 3, 5},{"Coimbra", &Brazil, 6, 5}, {"Gertise", &Brazil, 15, 5}};
    usteam[0].hasball = 1;
    addPlayer(usteam, enteam);
    
    //usteam[0].shoot(usteam[0], enteam, enteam[2]);
    //usteam[0].oneTwo(usteam[0], usteam, enteam);
    //usteam[0].pass(usteam[0], usteam, enteam, false);
    //usteam[0].dribble(usteam[0], enteam[0], usteam, enteam);
    usteam[0].run(usteam, enteam);
}
