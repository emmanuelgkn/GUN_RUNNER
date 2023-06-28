#ifndef _Terrain
#define _Terrain
#include <string>
using namespace std;
const int X = 100;
const int Y = 100;
class Terrain
{
    public:
    ///@brief constructeur de la classe terrain 
    Terrain();
    ///@brief recupere la donnee dimx du terrain
    int getdimx() const;
    ///@brief recupere la donnee dimy du terrain
    int getdimy() const;
    ///@brief test si la postion du personnage, d'un projectile, d'un ennemi est valide
    bool estPositionPersoValide (const int x, const int y) const;
    ///@brief permet de recuperer le carractere present axu coodonnées x et y du tableau
    unsigned char avoirchar(int x, int y) const;
    ///@brief permet de charger un terrain
    void ChargeTerrain(const string& filename);
    ///@brief permet de changer la donnee dimx du terrain
    void setdimx(int dx);
    ///@brief permet de changer la donnee dimy du terrain
    void setdimy(int dy);
    char ter[X][Y];
    ///@brief fais le test de regression
    void testRegressionTer();


    private:
    ///@brief la largeur et la longueur du terrain
    int dimx, dimy;
};

#endif
