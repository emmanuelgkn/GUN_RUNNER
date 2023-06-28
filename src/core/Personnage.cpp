#include<iostream>
#include <unistd.h>
#include "Personnage.h"
#include <cassert>

using namespace std;

Personnage::Personnage()
{
    pos.setxy(1,5);
    Arme_poss=Arme(2);
    niveau_vie=250;
}

Personnage::~Personnage()
{

}

bool Personnage::getDirection() const
{
    return direction;
}

void Personnage::setDirection(bool a)
{
    direction = a;
}

int Personnage::GetPosX() const
{
    return pos.getx();
}

int Personnage::GetPosY() const
{
    return pos.gety();
}

void Personnage::SetPos(int x, int y)
{   
    assert(x>=0);
    assert(y>=0);
    pos.setxy(x,y);
}

int Personnage::GetVie ()
{
    return niveau_vie;
}

Arme& Personnage::GetArme()
{
    return Arme_poss;
}

void Personnage::SetVie(int v)
{
    if (v < 0)
    {
        niveau_vie = 0;
    }
    else
    {
        niveau_vie = v;
    }
}

void Personnage::saut(const Terrain& t)
{
    const int maxDist =5; // distance maximale autorisée entre le personnage et le bloc sur lequel il veut sauter
    int x = pos.getx();
    int y = pos.gety() - maxDist;
    while (!t.estPositionPersoValide(x, y) && y < pos.gety())
    {
        ++y;
    }
    if (t.estPositionPersoValide(x, y) && !en_saut)   // Vérifier que le personnage n'est pas en train de sauter
    {
        pos.setxy(x, y);
        en_saut = true; // Mettre la variable en_saut à true
    }
}

void Personnage::gravite(const Terrain& t)
{
    if(t.estPositionPersoValide(pos.getx(),pos.gety()+1))
    {
        pos.setxy(pos.getx(),pos.gety()+1);
        usleep(1);
    }
    else en_saut=false;
}

void Personnage::DeplDroite(const Terrain& t)   //il faudras qu'elle prenne en compte le terrain pour pouvoir prendre en compte et indiquer les obstacles qui empechent le joueur d'avancer
{
    if(t.estPositionPersoValide(pos.getx()+1,pos.gety()))
    {
        pos.setxy(pos.getx()+1,pos.gety());
        direction=1;
    }
}

void Personnage::DeplGauche(const Terrain& t){
    if(t.estPositionPersoValide(pos.getx()-1,pos.gety()))
    {
        pos.setxy(pos.getx()-1,pos.gety());
        direction= 0;
    }
}


void Personnage::tir(const Terrain &t)
{

    if(GetArme().getType()=="fusil")
    {
        if (getDirection()==1)
        {
            if (t.estPositionPersoValide(GetPosX()-1,GetPosY()))
            {
                SetPos(GetPosX()-1,GetPosY());
            }

        }
        else if (t.estPositionPersoValide(GetPosX()+1,GetPosY()))
        {
            SetPos(GetPosX()+1,GetPosY());
        }
    }

    if (getDirection()==1)
    {
        Projectile pdr(1);
        pdr.InitProj(GetPosX(),GetPosY(),0,0);
        GetArme().ajouteproj(pdr);
    }
    if (getDirection()==0)
    {
        Projectile pg(0);
        pg.InitProj(GetPosX(),GetPosY(),0,0);
        GetArme().ajouteproj(pg);
    }

}

void Personnage::UpdateArme(Arme& a,const Terrain& t)
{
    if (a.getDegat()>=5)
    {
        a.UpdateProj_Fusil(t);
    }
    else
        a.UpdateProj(t);
}

void Personnage::testRegressionPers(){
    Personnage p;
    assert(p.GetPosX() == 1 && p.GetPosY() == 5);
    assert(p.GetArme().getDegat()== 2);
    assert(p.GetVie() == 20);

    p.setDirection(true);
    assert(p.getDirection() == true);

    p.SetPos(12,13);
    assert(p.GetPosX() == 12 && p.GetPosY() == 13);

    Personnage pers;
    Terrain ter;
    pers.saut(ter);
    assert(pers.GetPosY() == 1);

    pers.gravite(ter);
    assert(pers.GetPosY() == 2);

    cout << "succes" << endl;
}