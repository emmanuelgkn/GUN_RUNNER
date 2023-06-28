#include <cassert>
#include <time.h>
#include "sdlj.h"
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
using namespace std;

const int TAILLE_SPRITE = 32;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

float temps ()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}

Image::Image () : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false)
{
}

Image::~Image()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer)
{
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr)
    {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr)
        {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr)
    {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (m_texture == NULL)
    {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);
    if (m_texture == nullptr) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?m_surface->w:w;
    r.h = (h<0)?m_surface->h:h;

    if (m_hasChanged)
    {
        ok = SDL_UpdateTexture(m_texture,nullptr,m_surface->pixels,m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(renderer,m_texture,nullptr,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const
{
    return m_texture;
}

void Image::setSurface(SDL_Surface * surf)
{
    m_surface = surf;
}

SDLSimple::SDLSimple () : jeu()
{
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
    cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
    SDL_Quit();
    exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }



    int dimx, dimy;
    dimx = jeu.getTerrain().getdimx();
    dimy = jeu.getTerrain().getdimy();
    dimx = dimx * TAILLE_SPRITE;
    dimy = dimy * TAILLE_SPRITE;

    // Creation de la fenetre
    window = SDL_CreateWindow("Gun_runner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 40*32/2, 9*32, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

   /* // FONTS
    font = TTF_OpenFont("data/arial.ttf",50);
    if (font == nullptr)
        font = TTF_OpenFont("../data/arial.ttf",50);
    if (font == nullptr) {
            cout << "Failed to load arial.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}*/

	/*
    font_color.r = 50;font_color.g = 50;font_color.b = 255;
	font_im.setSurface(TTF_RenderText_Solid(font,"PACJUNIOR",font_color));
	font_im.loadFromCurrentSurface(renderer);
    */


    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_personnage1.loadFromFile("data/personnage1.png",renderer);
    im_mur.loadFromFile("data/mur.png",renderer);
    im_personnage2.loadFromFile("data/personnage2.png",renderer);
    //im_angle1.loadFromFile("data/angle1.png",renderer);
    //im_angle2.loadFromFile("data/angle2.png",renderer);
    im_plateforme.loadFromFile("data/plateforme.png",renderer);
    im_fond.loadFromFile("data/fond.png",renderer);
    im_ennemi1.loadFromFile("data/ennemi1.png",renderer);
    im_ennemi2.loadFromFile("data/ennemi2.png",renderer);
    im_balle.loadFromFile("data/balle3.png",renderer);
    im_balle2.loadFromFile("data/balle2.png",renderer);
    im_intro.loadFromFile("data/intro.jpg",renderer);
    //im_start.loadFromFile("data/start.png",renderer);
    im_niv2.loadFromFile("data/niveau2.jpg",renderer);
    im_niv3.loadFromFile("data/niveau3.jpg",renderer);
    im_fin.loadFromFile("data/fin.jpg",renderer);

}

SDLSimple::~SDLSimple ()
{
    //TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


 void SDLSimple::afficher_barre_de_vie(SDL_Renderer* renderer,const int x,const int y,int vie,int vie_max, int w, int h, int winPosX)
 {
    int x1 = (x - winPosX) * TAILLE_SPRITE;
    int y1 = y * TAILLE_SPRITE;

    int barre_w = 40;
    int barre_h = 5;
    // Position de la barre de vie par rapport à l'ennemi
    int barre_x = x1 + TAILLE_SPRITE/2 - barre_w/2;
    int barre_y = y1 - barre_h - 5;
    // Couleur de la barre de vie
    SDL_Color color = { 0, 255,128 , 255 };
    float vie_pourcentage = (float)vie / vie_max;
    // Dessin de la barre de vie
    SDL_Rect barre_rect = { barre_x, barre_y, (int)(barre_w * vie_pourcentage), barre_h };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &barre_rect);

 }

/*
    int y1 = pers.GetPosY() * TAILLE_SPRITE;

    // Taille de la barre de vie
    int barre_w = 40;
    int barre_h = 5;

    // Position de la barre de vie par rapport à l'ennemi
    int barre_x = x + TAILLE_SPRITE/2 - barre_w/2;
    int barre_y = y1 - barre_h - 5;

    // Couleur de la barre de vie
    SDL_Color color = { 0, 255,128 , 255 };

    float vie_pourcentage = (float)pers.GetVie() / 6.0;

    // Dessin de la barre de vie
    SDL_Rect barre_rect = { barre_x, barre_y, (int)(barre_w * vie_pourcentage), barre_h };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &barre_rect);
    */

bool SDLSimple::ClicSurBoutonLancerJeu(int mouseX, int mouseY)
{
    SDL_Rect boutonRect = { 207, 188, 227, 35};
    return (mouseX >= boutonRect.x && mouseX <= boutonRect.x + boutonRect.w &&
            mouseY >= boutonRect.y && mouseY <= boutonRect.y + boutonRect.h);
}
bool SDLSimple::ClicSurProchainNiveau(int mouseX, int mouseY)
{
    SDL_Rect boutonRect = {148, 48, 336, 39 };
    return (mouseX >= boutonRect.x && mouseX <= boutonRect.x + boutonRect.w &&
            mouseY >= boutonRect.y && mouseY <= boutonRect.y + boutonRect.h);
}

bool SDLSimple::ClicSurFin(int mouseX, int mouseY)
{
    SDL_Rect boutonRect = { 230, 228, 185, 30 };
    return (mouseX >= boutonRect.x && mouseX <= boutonRect.x + boutonRect.w &&
            mouseY >= boutonRect.y && mouseY <= boutonRect.y + boutonRect.h);
}

SDL_Texture* SDLSimple::chargerTexture(SDL_Renderer* renderer, const char* fichierImage) {
    SDL_Surface* surface = IMG_Load(fichierImage);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void SDLSimple::sdlAff()
{
    SDL_RenderClear(renderer);

    if (etatMenu == MenuPrincipal) {
        // Afficher un écran noir pour le menu d'accueil
      //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderClear(renderer);
        //SDL_Texture* fondTexture = chargerTexture(renderer, "data/intro.webp");
       // SDL_Texture* startTexture = chargerTexture(renderer, "data/start.png");
        //SDL_RenderCopy(renderer, fondTexture, NULL, NULL);
        im_intro.draw(renderer, 0, 0, 40*32/2, 9*32);

        // Dessiner le bouton "Lancer le jeu"
       SDL_Rect boutonRect = { 207, 188, 227, 35 };
       /* SDL_SetRenderDrawColor(renderer, 255, 0, 0, 10);
        SDL_RenderFillRect(renderer, &boutonRect);*/
        //SDL_RenderCopy(renderer, startTexture, NULL, &boutonRect);
       // im_start.draw(renderer, 200, 100, 200, 65);

        // Vérifier si un clic a été effectué sur le bouton
        SDL_Point mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);
        if (SDL_PointInRect(&mousePos, &boutonRect)) {
            // Changer l'état du menu si le bouton est cliqué
            if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                etatMenu = JeuEnCours;
            }
        }
    }
    else if (etatMenu == JeuEnCours) {
        im_fond.draw(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        Terrain& ter = jeu.getTerrain();
        Personnage& pers = jeu.getPersonnage();
        vector<Ennemi> en_liste = jeu.getEnnemis();
        vector<Projectile> proj_list = pers.GetArme().GetProj();
        vector<Projectile> ennemi_proj_list;

        const int winWidth = SCREEN_WIDTH / TAILLE_SPRITE;
        const int winHeight = SCREEN_HEIGHT / TAILLE_SPRITE;
        int winPosX = max(0, min(pers.GetPosX() - winWidth / 2, ter.getdimx() - winWidth));
        int winPosY = max(0, min(pers.GetPosY() - winHeight / 2, ter.getdimy() - winHeight));

        for (Ennemi& ennemi : en_liste)
        {
            vector<Projectile> ennemi_proj = ennemi.GetArme().GetProj();
            ennemi_proj_list.insert(ennemi_proj_list.end(), ennemi_proj.begin(), ennemi_proj.end());
        }

        // Afficher les sprites des murs
        for (int x = winPosX; x < winPosX + winWidth; ++x)
        {
            for (int y = winPosY; y < winPosY + winHeight; ++y)
            {
            if (ter.ter[x][y] == '*')
            {
                im_mur.draw(renderer, (x - winPosX) * TAILLE_SPRITE, (y - winPosY) * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            }
            if (ter.ter[x][y] == 'P')
            {
                im_plateforme.draw(renderer, (x - winPosX) * TAILLE_SPRITE, (y - winPosY) * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            }
            for (Projectile& proj : proj_list)
            {
                im_balle.draw(renderer,(proj.GetPosX()-winPosX)*TAILLE_SPRITE*1.05,proj.GetPosY()*TAILLE_SPRITE*1.05,TAILLE_SPRITE/2,TAILLE_SPRITE/2);
            }
            {
            for (Projectile& proj : ennemi_proj_list)
            {
                im_balle2.draw(renderer, (proj.GetPosX() - winPosX) * TAILLE_SPRITE * 1.05, proj.GetPosY() * TAILLE_SPRITE * 1.05, TAILLE_SPRITE / 2, TAILLE_SPRITE / 2);
            }
            }
            if (pers.getDirection()==1)
            {
                im_personnage1.draw(renderer,(pers.GetPosX() - winPosX)*TAILLE_SPRITE,pers.GetPosY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
            }
            else im_personnage2.draw(renderer,(pers.GetPosX() - winPosX)*TAILLE_SPRITE,pers.GetPosY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
            for (Ennemi& ennemi : en_liste)
            {
                if (ennemi.getDirection()==1)
                {
                     im_ennemi1.draw(renderer,(ennemi.GetPosEnnemi_X()- winPosX)* TAILLE_SPRITE,ennemi.GetPosEnnemi_Y()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
                }
               else im_ennemi2.draw(renderer,(ennemi.GetPosEnnemi_X()- winPosX)* TAILLE_SPRITE,ennemi.GetPosEnnemi_Y()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
            }
            for (Ennemi& ennemi : en_liste)
            {
                afficher_barre_de_vie(renderer,ennemi.GetPosEnnemi_X(),ennemi.GetPosEnnemi_Y(),ennemi.GetVieEnnemi(),6,40,5,winPosX);
            }
            afficher_barre_de_vie(renderer,pers.GetPosX(),pers.GetPosY(),pers.GetVie(),250,40,5,winPosX);

        }
    }
    if (jeu.DeuxiemeNiveauDebloque()) {
        im_niv2.draw(renderer, 0, 0, 40*32/2, 9*32);
       /*font_color.r = 255;font_color.g = 255;font_color.b = 255;
        font_im.setSurface(TTF_RenderText_Solid(font,"NIVEAU 2",font_color));
        font_im.loadFromCurrentSurface(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Rect boutonRect = { 148, 48, 336, 39 };
        SDL_SetRenderDrawColor(renderer, 225, 200, 0, 255);
        SDL_RenderFillRect(renderer, &boutonRect);*/
        }
    if (jeu.TroisiemeNiveauDebloque()) {
        im_niv3.draw(renderer, 0, 0, 40*32/2, 9*32);
        /*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Rect boutonRect = { 300, 250, 200, 100 };
        SDL_SetRenderDrawColor(renderer, 255, 40, 240, 255);
        SDL_RenderFillRect(renderer, &boutonRect);*/

    }
    if (jeu.FinDebloque()){
        im_fin.draw(renderer, 0, 0, 40*32/2, 9*32);
        /*SDL_Rect boutonRect = { 230, 228, 185, 30 };
        SDL_SetRenderDrawColor(renderer, 255, 40, 240, 255);
        SDL_RenderFillRect(renderer, &boutonRect);*/
    }
}
}

void SDLSimple::sdlBoucle()
{
    SDL_Event events;
    bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;
    int compteur = 0;

    bool jeuEnCours = false; // Ajout d'une variable pour gérer l'état du jeu

    // tant que ce n'est pas la fin ...
    while (!quit)
    {
        nt = SDL_GetTicks();
        if (nt - t > 75)
        {
            if (jeuEnCours) { // Ajout d'une condition pour exécuter les actions du jeu seulement lorsque le jeu est en cours
                jeu.gravite(events.key.keysym.scancode);
                jeu.UpdateArmePerso_Ennemi();
                jeu.Collisions_proj_ennemi();
                jeu.Collisions_proj_personnage();
                compteur++;
                if (compteur >= 7)
                {
                    jeu.Tir_Automatique();
                    compteur = 0;
                }
            }

            t = nt;
        }

        // tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a cliqué sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN) // Si une touche est enfoncée
            {
                switch (events.key.keysym.scancode)
                {
                    case SDL_SCANCODE_UP:
                        jeu.ActionClavier('z'); // car Y inverse
                        break;
                    case SDL_SCANCODE_LEFT:
                        jeu.ActionClavier('q');
                        break;
                    case SDL_SCANCODE_RIGHT:
                        jeu.ActionClavier('d');
                        break;
                    case SDL_SCANCODE_R:
                        jeu.ActionClavier('r');
                        break;
                    case SDL_SCANCODE_ESCAPE:
                    case SDL_SCANCODE_Q:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
            else if (events.type == SDL_MOUSEBUTTONDOWN) // Si un clic de souris a eu lieu
            {
                int mouseX = events.button.x;
                int mouseY = events.button.y;

                if (etatMenu == MenuPrincipal && ClicSurBoutonLancerJeu(mouseX, mouseY)) // si le bouton pour lancer le premier jeu est cliqué et qu'on est sur le menu principal
                {
                    jeuEnCours = true; // Démarrer le jeu lorsque le bouton est cliqué
                }
                else if (jeu.DeuxiemeNiveauDebloque() && etatMenu == JeuEnCours && ClicSurProchainNiveau(mouseX, mouseY)) // si le bouton pour changer  premier jeu est cliqué et qu'on est sur le menu principal
                {
                    cout<<"deuxieme niveau"<<endl;
                    jeu.Niveau_Suivant(2); // Appeler la fonction pour passer au niveau deux
                }
                else if (jeu.TroisiemeNiveauDebloque() && etatMenu == JeuEnCours && ClicSurProchainNiveau(mouseX, mouseY)) // si le bouton pour changer  premier jeu est cliqué et qu'on est sur le menu principal
                {
                    cout<<"troisieme niveau"<<endl;
                    jeu.Niveau_Suivant(3); // Appeler la fonction pour passer au niveau deux
                }
                else if(jeu.FinDebloque() && etatMenu == JeuEnCours && ClicSurFin(mouseX, mouseY)){
                    quit = true;
                }
            }
        }

        // on affiche le jeu sur le buffer caché
        sdlAff();

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
}