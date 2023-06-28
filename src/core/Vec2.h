#ifndef _Vec2
#define _Vec2

class Vec2 
{
    public:
        ///@brief constructeur de la classe vec2
        Vec2();
        ///@brief constructeur avec coodonées _x et _y
        Vec2(int x_, int y_);
        ///@brief destructeur de la classe vec2
        ~Vec2();
        ///@brief change les coordonnées x et y du vecteur
        void setxy(int x_, int y_);
        ///@brief recupere la donnée x du vecteur
        int getx() const;
        ///@brief recupere la donnée y du vecteur
        int gety() const;
    
    private:
        ///@brief donnees x et y
        int x,y;
};

#endif 