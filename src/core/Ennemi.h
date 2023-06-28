#ifndef ENNEMI_H_INCLUDED
#define ENNEMI_H_INCLUDED
#include <iostream>
#include "Vec2.h"
#include "Terrain.h"
#include "Arme.h"

class Ennemi {
    public:
        ///@brief constructeur de la classe ennemi
         Ennemi();
         /**
          *@brief constructeur de la classe ennemi avec les positions la direction de l'ennemis et les dégats qu'il inflige
          *@param x coordonnée x de la position de l'ennemi
          *@param y coordonnée y de la position de l'ennemi
          *@param vie points de vie de l'ennemi
          *@param direction direction dans laquelle l'ennemi est
          *@param degat degats qu'inlfige l'ennemi*/
         Ennemi(int x, int y, int vie, bool direction, int degat);
         ///@brief destructeur de la classe ennemi
        ~Ennemi();
        ///@brief recupere la position x de l'ennemi
         int GetPosEnnemi_X() const;  
        ///@brief recupere la position y de l'ennemi
         int GetPosEnnemi_Y() const; 
         /**
          * @brief change les composantes x et y de la position de l'ennemi
          * @param x coordonnée x de la position de l'ennemi
          * @param y coordonnée y de la position de l'ennemi
          * */
         void SetPosEnnemi(int x, int y);  
         ///@brief recupere les points de vie de l'ennemi
         int GetVieEnnemi()const ;
         /**
          * @brief change les points de vie de l'ennemi
          * @param v points de vie de l'ennemi
         */
         void SetVieEnnemi(int v);
         ///@brief recupere l'arme que l'ennemi possède
         Arme& GetArme();
         ///@brief recupere la direction de l'ennemi
         bool getDirection() const;
         /**
          * @brief change la direction de l'ennemi
          * @param a direction dans laquelle on veut que l'ennemi se tourne
          * */
         void setDirection(bool a);
         /**
          * @brief deplace l'ennemi vers la droite
          * @param t terrain dans lequel l'ennemi se déplace
          * */
         void Deplacement_droite(const Terrain &t);
         /**
          * @brief deplace l'ennemi vers la gauche
          * @param t terrain dans lequel l'ennemi se déplace
          * */
         void Deplacement_gauche(const Terrain &t);
         /**
          * @brief ramene l'ennemi vers le sol s'il n'est pas sur une plateforme
          * @param t terrain dans lequel l'ennemi se déplace
          * */
         void gravite(const Terrain& t);
         /**
          * @brief fais tirer l'ennemi
          * @param t terrain dans lequel les projectiles de l'arme se déplace
          * */
         void tir(const Terrain& t);
         /**
          * @brief met tout les projectiles de l'arme a jour
          * @param a arme de l'ennemi
          * @param t terrain ou se trouve l'ennemi
          * */
         void UpdateArme(Arme& a, const Terrain& t);
         ///@brief fais le test de regression
         void testRegressionEnnemi();

    private :
    ///@brief position de l'ennemi
    Vec2 pos_ennemi;
    ///@brief points de vie de l'ennemi
    int vie_ennemi;
    ///@brief direction vers laquelle se tourne l'ennemi
    bool direction_ennemi;
    ///@brief l'arme que possède l'ennemi
    Arme arme_ennemi;
};





#endif // ENNEMI_H_INCLUDED


