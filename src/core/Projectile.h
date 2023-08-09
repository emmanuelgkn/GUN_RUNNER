#ifndef _Projectile
#define _Projectile
#include "Vec2.h"
#include "Terrain.h"

class Projectile {
    private:
        ///@brief Postiton du projectile
        Vec2 pos;
        ///@brief Vitesse du projectile
        Vec2 vitesse;
        ///@brief distance parcourue par le projectile
        int distance_parcourue;
        public:
        ///@brief direction du projectile
        bool direction;
        ///@brief constructeur de la classe projectile
        Projectile();
        ///@brief constructeur de la classe projectile avec d prescisant la direction 
        Projectile(int d);
        ///@brief recupere la donnée x du vecteur position du projectile
        int GetPosX() const;
        ///@brief recupere la donnée y du vecteur position du projectile
        int GetPosY() const;
        ///@brief change les données x et y du vecteur position du projectile
        void SetPos(int x, int y);
        ///@brief recupere la distance parcourue par le projectile
        int GetDistance() const;
        ///@brief fais augmenter la distance parcourue du projectile
        void IncrementeDistance();
        ///@brief recupere la vitesse du projectile
        Vec2 GetVit();
        ///@brief change la vitesse du projectile
        void SetVit(int x, int y);
        /**
         *@brief initialise la position du projectile
         *@param posx position x du projectile 
         *@param posy position y du projectile
         *@param vx composante x de la vitesse du projectile
         *@param vy composante y de la vitesse du projectile
         */
        void InitProj(int posx, int posy, int vx, int vy);
        ///@brief gere les collitions des projectiles
        bool Collisions(Terrain &t);
        ///@brief fais le test de regression
        void testRegressionProj();
};


#endif
