#include "Arme.h"
#include <iostream>
#include<string.h>
#include <cassert>

using namespace std;

Arme::Arme()
{
    degat_par_balle = 0;
}

Arme::Arme(int x)
{
    assert(x > 0);
    degat_par_balle = x;
    if (degat_par_balle>=4)
    {
        settype("fusil");
    }
    else settype("pistolet");

}

void Arme::settype(string t){
    type = t;
}

int Arme::getDegat()
{
    return degat_par_balle;
}

void Arme::setDegat(int a)
{
    assert(a > 0);
    degat_par_balle = a;
}

string Arme::getType()
{
    return type;
}

const vector<Projectile>& Arme::GetProj () const
{
    return tabproj;
}

void Arme::ajouteproj(Projectile &a)
{
    tabproj.push_back(a);
}

void Arme::UpdateProj(const Terrain& t)
{

    for (auto it = tabproj.begin(); it != tabproj.end(); )
    {
        Projectile& proj = *it;
        if (!t.estPositionPersoValide(proj.GetPosX() + 1, proj.GetPosY()))
        {
            it = tabproj.erase(it); // supprimer le projectile du vecteur
        }
      /* if (!t.estPositionPersoValide(proj.GetPosX() - 1, proj.GetPosY()))
        {
            it = tabproj.erase(it);
        }*/
        else
        {
            if(proj.direction == 1)
                proj.SetPos(proj.GetPosX() + 1, proj.GetPosY());
            else
                proj.SetPos(proj.GetPosX() - 1, proj.GetPosY());
            ++it;
        }
    }
}

void Arme::UpdateProj_Fusil(const Terrain &t)
{
    for (auto it = tabproj.begin(); it != tabproj.end(); )
        {
            Projectile& proj = *it;
            if (proj.GetDistance()>4)
            {
                it = tabproj.erase(it); // supprimer le projectile du vecteur
            }
            else
            {
                if(proj.direction == 1)
                    proj.SetPos(proj.GetPosX() + 1, proj.GetPosY());
                else
                    proj.SetPos(proj.GetPosX() - 1, proj.GetPosY());
                ++it;
            }
            proj.IncrementeDistance();
        }
}

bool Arme::SupprProj_si_col(int x, int y)
{
    for (auto it = tabproj.begin(); it != tabproj.end(); ++it)
    {
        Projectile& proj = *it;
        if (proj.GetPosX() == x && proj.GetPosY() == y)
        {
            it = tabproj.erase(it);
            return true;
        }
    }
    return false;
}
 //voila c'est tout normalement

void Arme::testRegressionArme(){
    Arme a;
    assert(a.getDegat() == 0);

    Arme ar(18);
    assert(ar.getDegat() == 18);

    ar.setDegat(4);
    assert(ar.getDegat() == 4);
    assert(ar.getType() == "fusil");

   
    Projectile Proj;
    ar.ajouteproj(Proj);
    vector<Projectile> tableauProj = ar.GetProj();
    assert(tableauProj[0].GetDistance() == Proj.GetDistance());

    cout << "Succes" << endl;
}