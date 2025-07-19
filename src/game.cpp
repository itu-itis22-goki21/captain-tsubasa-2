#include "Player.h"

Ball ball;

int main(){
    Jersey Tsu(10, 0);
    Team Japan("Japan", Tsu);
    
    Jersey San(9,1);
    Team Brazil("Brazil", San);


    vector <Player> usteam= {{"Tsubasa", &Japan, 5, 5},{"Misaki", &Japan, 7, 5}};
    vector <Player> enteam= {{"Santana", &Brazil,  3, 8},{"Coimbra", &Brazil, 6, 6}};
    usteam[0].pass(usteam[0], usteam, enteam);
}
