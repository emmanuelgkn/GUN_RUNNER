#ifndef _Personnage
#define _Personnage
#include<iostream>
#include "Arme.h"
#include "Terrain.h"

class Personnage
{
    public:
        ///@brief constructeur de la classe personnage
        Personnage() ;
        ///@brief destructeur de la classe personnage
        ~Personnage();
        ///@brief recupere la donnee x de la position du personnage
        int GetPosX() const;  // v�rifi�
        ///@brief recupere la donnee y de la position du personnage
        int GetPosY() const;  // v�rifi�
        ///@brief change les donnes x et y de la position du personnage
        void SetPos(int x, int y);  //v�rifi�
        ///@brief recupere les points de vie du personnage
        int GetVie();
        ///@brief change les points de vie du personnage
        void SetVie(int v);
        ///@brief recupere l'arme du personage
        Arme& GetArme();
        ///@brief recupere la direction du personnage
        bool getDirection() const;
        ///@brief change la direction du personnage 0 pour gauche et 1 pour droite 
        void setDirection(bool a);
        ///@brief gere le saut du personnage
        void saut(const Terrain& t);
        ///@brief permet le deplacement vers la  gauche du personnage
        void DeplGauche(const Terrain& t) ;
        ///@brief permet le deplacement vers la droite du personnage
        void DeplDroite(const Terrain& t) ;
        ///@brief permet de faire tomber le personnage au sol s'il n'est pas sur une plateforme
        void gravite(const Terrain& t);
        ///@brief gere la capacité de tir du personnage
        void tir(const Terrain& t);
        ///@brief met a jour l'arme du personnage en mettant a jour ses projectiles en fonction du type de l'arme
        void UpdateArme(Arme& a, const Terrain& t);
        ///@brief fais le test de regression
        void testRegressionPers();

    private:
        ///@brief position du personnage
        Vec2 pos;
        ///@brief niveau de vie du personnage
        int niveau_vie;
        ///@brief arme posédée par le personnage
        Arme Arme_poss;
        ///@brief direction du personnage pendant le saut
        bool direction,en_saut; //0 pour gauche, 1 pour droite


};

#endif
