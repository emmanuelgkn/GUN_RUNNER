#include<iostream>
#include "Projectile.h"
#include <cassert>

using namespace std;

Projectile::Projectile()
{
    distance_parcourue = 0;
}


Projectile::Projectile(int c)
{
    assert(c == 0 || c == 1);
    distance_parcourue=0;
    if(c == 1)
        direction = 1;
    else
        direction = 0;
}

int Projectile::GetPosX() const
{
    return pos.getx();
}
int Projectile::GetPosY() const
{
    return pos.gety();
}
void Projectile::SetPos(int x, int y)
{
    
    pos.setxy(x,y);
}

Vec2 Projectile::GetVit()
{
    return vitesse;
}

int Projectile::GetDistance() const
{
    return distance_parcourue;
}

void Projectile::IncrementeDistance()
{
    distance_parcourue= distance_parcourue + 1;
}

void Projectile::InitProj(int posx, int posy, int vx, int vy) {
    assert(posx>=0);
    assert(posy>=0);
    SetPos(posx,posy);
}

void Projectile::testRegressionProj(){

    Projectile proj;
    assert(proj.GetDistance() == 0);

    proj.IncrementeDistance();
    assert(proj.GetDistance() == 1);

    Projectile pr (1);
    assert(pr.direction == 1);
    
    pr.SetPos(10,12);
    assert(pr.pos.getx() == 10 && pr.pos.gety() == 12);

    pr.InitProj(12,13,14,15);
    assert(pr.pos.getx() == 12 && pr.pos.gety() == 13);

    cout << "Succes" << endl;
}
