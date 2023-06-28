#include<iostream>
#include <unistd.h>
#include "Ennemi.h"
#include <cassert> 
 using namespace std;

 Ennemi::Ennemi(){

 }

 Ennemi::Ennemi(int x, int y, int vie, bool direction, int degat) {
    pos_ennemi.setxy(x,y);
    vie_ennemi=vie;
    arme_ennemi= Arme(degat);
    direction_ennemi= direction;

 }

 Ennemi::~Ennemi(){
 }

 int Ennemi::GetPosEnnemi_X() const
 {
    return pos_ennemi.getx();
 }

 int Ennemi::GetPosEnnemi_Y() const
 {
    return pos_ennemi.gety();
 }

 void Ennemi::SetPosEnnemi(int x, int y){
    assert(x > 0);
    assert(y > 0);
    pos_ennemi.setxy(x,y);
 }

int Ennemi::GetVieEnnemi() const{
    return vie_ennemi;
}

void Ennemi::SetVieEnnemi(int a) {

    vie_ennemi=a;
}

bool Ennemi::getDirection() const
{
    return direction_ennemi;
}

void Ennemi::setDirection(bool a)
{
    direction_ennemi=a;
}

Arme& Ennemi::GetArme() {
    return arme_ennemi;
}

void Ennemi::Deplacement_droite(const Terrain &t) {
    SetPosEnnemi(GetPosEnnemi_X()+1,GetPosEnnemi_Y());
    direction_ennemi=1;
}

void Ennemi::Deplacement_gauche(const Terrain &t) {
    SetPosEnnemi(GetPosEnnemi_X()-1,GetPosEnnemi_Y());
    direction_ennemi=0;
}

void Ennemi::gravite(const Terrain& t)
{
    if(t.estPositionPersoValide(pos_ennemi.getx(),pos_ennemi.gety()+1)) {
    pos_ennemi.setxy(pos_ennemi.getx(),pos_ennemi.gety()+1);
    usleep(1);
    }
}


void Ennemi::tir(const Terrain &t)
{

    if (getDirection()==1)
    {
        Projectile pdr(1);
        pdr.InitProj(GetPosEnnemi_X(),GetPosEnnemi_Y(),0,0);
        GetArme().ajouteproj(pdr);
    }
    if (getDirection()==0)
    {
        Projectile pg(0);
        pg.InitProj(GetPosEnnemi_X(),GetPosEnnemi_Y(),0,0);
        GetArme().ajouteproj(pg);
    }

}


void Ennemi::UpdateArme(Arme& a,const Terrain& t)
{
    a.UpdateProj(t);
}

void Ennemi::testRegressionEnnemi(){
    Ennemi e(12,13,100,true,4);
    Arme a = e.GetArme();
    assert(e.GetPosEnnemi_X() == 12);
    assert(e.GetPosEnnemi_Y() == 13);
    assert(e.GetVieEnnemi() == 100);
    assert(e.getDirection() == true);
    assert(a.getDegat() == 4);

    e.SetPosEnnemi(22,3);
    assert(e.GetPosEnnemi_X() == 22 && e.GetPosEnnemi_Y() == 3);

    Terrain ter;
    e.Deplacement_droite(ter);
    assert(e.GetPosEnnemi_X() == 23 && e.getDirection() == true);

    e.Deplacement_gauche(ter);
    assert(e.GetPosEnnemi_X() == 22 && e.getDirection() == false);

    e.gravite(ter);
    assert(e.GetPosEnnemi_Y() == 4);

    cout << "Succes" << endl; 
}