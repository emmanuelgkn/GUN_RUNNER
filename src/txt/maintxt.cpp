#include "winTxt.h"
#include "../core/Personnage.h"
#include "../core/Jeu.h"
#include "../core/Arme.h"
#include<iostream>
#include <cassert>
#include <unistd.h>

using namespace std;

void affichertxt(WinTXT win,Jeu & jeu)
{	
    Terrain& ter = jeu.getTerrain();
    Personnage& pers = jeu.getPersonnage();
	const vector<Projectile>& proj_list = pers.GetArme().GetProj();
	vector<Ennemi> en_liste = jeu.getEnnemis();
	vector<Projectile> ennemi_proj_list;
	for (Ennemi& ennemi : en_liste)
	{
		vector<Projectile> ennemi_proj = ennemi.GetArme().GetProj();
		ennemi_proj_list.insert(ennemi_proj_list.end(), ennemi_proj.begin(), ennemi_proj.end());
	}

	//if (!proj_list.empty()) win.print(proj_list[0].GetPosX());

	int winwidth = ter.getdimx()/2;
	int winheight = ter.getdimy();
	int winposx = max(0, min(pers.GetPosX() - winwidth/2, ter.getdimx() - winwidth ));
	//int winposy = max(0, min(pers.GetPosY() - winheight/2, ter.getdimx() - winheight ));
	//cout << winposx << winposy ;
   
    win.clear();

    for(int x = winposx ;x < winposx + winwidth ; ++x)
		for(int y = 0 ;y < winheight ; ++y)
		{
			
			win.print( x - winposx, y, ter.avoirchar(x,y));
		}
			

    // Affichage de Personnage
	win.print(pers.GetPosX() - winposx,pers.GetPosY(),'P');
	
	for (const Projectile& proj : proj_list) {
    // On affiche seulement les projectiles qui sont tires par le personnage
    if (proj.GetPosX() >= winposx && proj.GetPosX() < winposx + winwidth) {
        win.print(proj.GetPosX() - winposx, proj.GetPosY(), '*');
    }
	}

	//les projectiles des ennemis
	for (Projectile& proj : ennemi_proj_list)
	{
		if (proj.GetPosX() >= winposx && proj.GetPosX() < winposx + winwidth)
			win.print(proj.GetPosX() - winposx, proj.GetPosY(), '*');
	}

	for (Ennemi& ennemi : en_liste)
	{
		win.print(ennemi.GetPosEnnemi_X()- winposx,ennemi.GetPosEnnemi_Y(),'E');
	}
	win.draw();
}

void afficherboucle(Jeu& jeu)
{
    // Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)

    WinTXT win (jeu.getTerrain().getdimx(),jeu.getTerrain().getdimy());
	bool ok = true;
	char c;
 
	do {
	    affichertxt(win,jeu);
        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // WIN32
		c = win.getCh();
		jeu.gravite(c);
		jeu.UpdateArmePerso_Ennemi();
		jeu.Collisions_proj_ennemi();
        jeu.Collisions_proj_personnage();
		jeu.Tir_Automatique();
		switch (c) {
			case 'q':
				jeu.ActionClavier('q');
				break;
			case 'd':
				jeu.ActionClavier('d');
				break;
            case 'z':
				jeu.ActionClavier('z');
				break; 
			case 'x':
				ok = false;
				break;
			case 'r' :
				jeu.ActionClavier('r');
				break;
		}
	} while (ok);

} 

int main(int argc, char** argv )
{
    termClear();
	Jeu jeu;
	afficherboucle(jeu);
    termClear();
    return 0;
}

