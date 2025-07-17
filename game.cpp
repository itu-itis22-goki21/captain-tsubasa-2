#include "Player.h"

Ball ball;

int main(){
    Team Japan("Japan");
    Jersey Tsu(10, 0);
    
    Team Brazil("Brazil");

    vector <Player> usteam= {{"Tsubasa", &Japan, &Tsu, 5, 5},{"Misaki", &Japan, 8, 7, 5}};
    vector <Player> enteam= {{"Santana", &Brazil, 9, 3, 8},{"Coimbra", &Brazil, 10, 6, 6}};
    usteam[0].pass(usteam[0], usteam, enteam);
}
