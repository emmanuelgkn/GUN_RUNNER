#ifndef _Arme
#define _Arme
#include "Projectile.h"
#include "string"
#include "Terrain.h"
#include<vector>
#include <chrono>

using namespace std;
class Arme {
    public:
        ///@brief constructeur de la classe arme
        Arme();
        /**
        *@brief constructeur de la classe arme avec les dégats que l'arme inflige
        *@param degat degats infligés par l'arme
        */
        Arme(int degat);
        ///@brief recupere les dégarts que l'arme inflige
        int getDegat();
        /**
        *@brief change les dégats
        *@param a les degats que l'arme inflige
        */
        void setDegat(int a);
        ///@brief recupere le type de l'arme
        string getType();
        /**
        *@brief ajoute un nouveau projectile a l'arme
        *@param a projectile a ajouter au tableau des projectiles de l'arme
        */
        void ajouteproj(Projectile &a) ;
        ///@brief recupere un projectile de l'arme
        const vector<Projectile>& GetProj () const;
        /**
        *@brief met a jour  le projectile notament sa position et son apparition dans le jeu
        *@param t terrain dans lequel le projetile se déplace
        */
        void UpdateProj(const Terrain& t);
        /**
        *@brief met a jour le projectil (d'un fuisil ici)
        *@param t terrain dans lequel le projectile se déplace
        */
        void UpdateProj_Fusil(const Terrain &t);
        /**
        *@brief supprime le projectile si il touche un obstacle
        *@param x coorodonée x de la position du projectile
        *@param y coordonee y de la position du projectile 
        **/
        bool SupprProj_si_col(int x, int y);
        /**
        *@brief change le type de l'arme
        *@param t chaine de caractere definissant le type de l'arme
        */
        void settype(string t);
        ///@brief fais le test de regression
        void testRegressionArme();

    private:
        ///@brief tableau de projectiles
        vector<Projectile> tabproj;
        ///@brief type de l'arme
        string type;
        ///@brief les degats que l'arme inflige
        int degat_par_balle;
        ///@brief rareté de l'arme
        int rarete;
};
#endif
