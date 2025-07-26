#include "Player.h"

Ball ball;

int main(){
    Jersey Tsu(10, 0);
    Team Japan("Japan", Tsu);
    
    Jersey San(5,1);
    Team Brazil("Brazil", San);


    vector <Player> usteam= {{"Tsubasa", &Japan, 5, 5},{"Misaki", &Japan, 7, 9}};
    vector <Player> enteam= {{"Santana", &Brazil,  6, 7},{"Coimbra", &Brazil, 6, 6}};
    usteam[0].pass(usteam[0], usteam, enteam);
}
