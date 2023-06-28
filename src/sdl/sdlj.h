#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../core/Jeu.h"
#include "../core/Arme.h"

//Pour gérer une image avec SDL2
class Image {

private:

    SDL_Surface * m_surface;
    SDL_Texture * m_texture;
    bool m_hasChanged;

public:
    Image () ;
    ~Image();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};


//La classe gerant le jeu avec un affichage SDL
class SDLSimple {

private :

	Jeu jeu;

    SDL_Window * window;
    SDL_Renderer * renderer;
    
    //TTF_Font * font;
    //Image font_im;
    SDL_Color font_color;

    Image im_personnage1;
    Image im_personnage2;
    Image im_mur;
    Image im_plateforme;
    Image im_fond;
    Image im_ennemi1;
    Image im_ennemi2;
    Image im_balle;
    Image im_balle2;
    Image im_intro;
    Image im_start;
    Image im_niv2;
    Image im_niv3;
    Image im_fin;

    bool jeuEnCours;

    enum EtatMenu {
        MenuPrincipal,
        JeuEnCours
    };

    EtatMenu etatMenu;

public :

    SDLSimple ();
    ~SDLSimple ();
    void sdlBoucle ();
    void afficher_barre_de_vie(SDL_Renderer* renderer,int x,int y,int vie,int vie_max, int w, int h, int winPosX);
    bool ClicSurBoutonLancerJeu(int mouseX, int mouseY);
    bool ClicSurProchainNiveau(int mouseX, int mouseY);
    bool ClicSurFin(int mouseX, int mouseY);
    SDL_Texture* chargerTexture(SDL_Renderer* renderer, const char* fichierImage);
    void sdlAff ();

};

#endif