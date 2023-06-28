#include "Jeu.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

int Jeu::compteur_niveau = 1;

using namespace std;
Jeu::Jeu(): pers(), ter(), tab_en(6) // Initialise le tableau avec un ennemi pour commencer
{
    int vie= 5;
    tab_en[0] = Ennemi(5,5,vie,true,2);
    tab_en[1] = Ennemi(8,5,vie,false,2);
    tab_en[2] = Ennemi(12,1,vie,false,2);
    tab_en[3] = Ennemi(17,1,vie,false,2);
    tab_en[4] = Ennemi(19,1,vie,false,2);
    tab_en[5] = Ennemi(35,1,vie,false,2);
    Arme a = Arme(6);
    ter.ChargeTerrain("./data/Terrain1.txt");
    niveauDeuxDebloque=false;
    niveauTroisDebloque=false;
    finDebloque = false;
}

void Jeu::CreerNouveauJeu(int nombreEnnemis,int degats)
{
    Jeu nouveauJeu;
    int vie = 5;
    nouveauJeu.tab_en.clear();
    for (int i = 0; i < nombreEnnemis; i++)
    {
        int x = (rand() % 38) + 1;
        int y = (rand() % 7) + 1;
        bool a = rand() % 2;
        nouveauJeu.tab_en.push_back(Ennemi(x, y, vie, a, 4)); // Ajouter les nouveaux ennemis au tableau
    }
        Arme nouvelleArme(8);
        nouveauJeu.pers.GetArme() = nouvelleArme;

        if (compteur_niveau==2)
        {
          nouveauJeu.ter.ChargeTerrain("./data/Terrain2.txt");
        }
        else if (compteur_niveau==3)
        {
            nouveauJeu.ter.ChargeTerrain("./data/Terrain3.txt");
        }


    *this = nouveauJeu;
}

void Jeu::ActionClavier(const char ch)
{
    switch(ch)
    {
    case 'd':
        pers.DeplDroite(ter);
        break;
    case 'q':
        pers.DeplGauche(ter);
        break;
    case 'z':
        pers.saut(ter);
        break;
    case 'r' :
        pers.tir(ter);
        break;
    }
}

void Jeu::gravite(const char ch)
{
    pers.gravite(ter);
    for (Ennemi& ennemi : tab_en)   // Parcours tous les ennemis du tableau
    {
        ennemi.gravite(ter);
    }
    if(pers.GetPosY()<5)
    {
        if(ch == 'q') pers.DeplGauche(ter);
        if(ch == 'd') pers.DeplDroite(ter);
    }
}

void Jeu::afficher_Terraintxt(const string& filename)
{
    ter.ChargeTerrain(filename);
}

Terrain& Jeu::getTerrain()
{
    return ter;
}

Personnage& Jeu::getPersonnage()
{
    return pers;
}

vector<Ennemi> Jeu::getEnnemis() const
{
    return tab_en;
}

void Jeu::UpdateArmePerso_Ennemi()
{
    pers.UpdateArme(pers.GetArme(),ter);

     for (Ennemi& ennemi : tab_en)
        {
            ennemi.UpdateArme(ennemi.GetArme(),ter);
        }
}

void Jeu::Collisions_proj_ennemi()
{
    Arme& a = pers.GetArme();
    for (std::size_t i = 0; i < tab_en.size(); i++)
    {
        Ennemi& ennemi = tab_en[i];
        if (a.SupprProj_si_col(ennemi.GetPosEnnemi_X(), ennemi.GetPosEnnemi_Y()))
        {
            ennemi.SetVieEnnemi(ennemi.GetVieEnnemi() - a.getDegat());
            if (ennemi.GetVieEnnemi() <= 0)
            {
                tab_en.erase(tab_en.begin() + i);
                i--; // Décrémenter i pour compenser la suppression de l'ennemi
            }
        }
    }
    if (tab_en.empty())
    {
        if (compteur_niveau == 1)
            niveauDeuxDebloque=true;
        else if (compteur_niveau == 2)
            niveauTroisDebloque=true;
        else if (compteur_niveau == 3)
            finDebloque = true;
    }
}


void Jeu::Collisions_proj_personnage()
{

    vector<Projectile> projectiles;
    for (Ennemi& ennemi : tab_en)
    {
        const vector<Projectile>& proj_ennemi = ennemi.GetArme().GetProj();
        projectiles.insert(projectiles.end(), proj_ennemi.begin(), proj_ennemi.end());
    }
    for (auto it = projectiles.begin(); it != projectiles.end(); )
    {
        bool touche = false;
        for (Ennemi& ennemi : tab_en) {

            if (ennemi.GetArme().SupprProj_si_col(pers.GetPosX(), pers.GetPosY()))
            {

                 if (pers.GetVie() <= 0)
            {
                GAME_OVER=true;
            }
                pers.SetVie(pers.GetVie() - ennemi.GetArme().getDegat());
                touche = true;
                break;
            }
        }
        if (touche)
        {
            it = projectiles.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void Jeu::Tir_Automatique()
{

    for (int i = 0; i < tab_en.size(); i++)
    {
        Ennemi& ennemi = tab_en[i];
        if ((ennemi.GetPosEnnemi_Y()==pers.GetPosY())&& !GAME_OVER&&(abs(ennemi.GetPosEnnemi_X()-pers.GetPosX())<18))
        {
            if (ennemi.GetPosEnnemi_X()-pers.GetPosX()<0)
            {
                if (ennemi.getDirection()==1&&pers.getDirection()==1)
                {
                   ennemi.tir(ter);
                } else {ennemi.setDirection(1); ennemi.tir(ter);}

            } else if (ennemi.getDirection()==0&&pers.getDirection()==0){
                ennemi.tir(ter);
            } else {
            ennemi.setDirection(0);
            ennemi.tir(ter);

            }
        }
   }

}

void Jeu::Niveau_Suivant(int niveau)
{
    compteur_niveau++;
    int nombreEnnemis;
    int degat_ennemis;

    if (niveau == 2)
    {
        nombreEnnemis = 13; 
        degat_ennemis = 2;
    }
    else if (niveau == 3)
    {
        nombreEnnemis = 2;
        degat_ennemis = 4;
    }
    CreerNouveauJeu(nombreEnnemis, degat_ennemis);
}

bool Jeu::DeuxiemeNiveauDebloque() const {
    return niveauDeuxDebloque;
}
bool Jeu::TroisiemeNiveauDebloque() const {
    return niveauTroisDebloque;
}

bool Jeu::FinDebloque() const {
    return finDebloque;
}

void Jeu::testRegressionJeu(){
    Jeu j;
    vector<Ennemi> Ennemis = j.getEnnemis();
    assert(Ennemis.size() == 6);
    assert(j.GAME_OVER == false);

    cout << "Succes" << endl;  
}







