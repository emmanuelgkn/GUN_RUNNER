#ifndef _Jeu
#define _Jeu
#include "Personnage.h"
#include "Terrain.h"
#include "Ennemi.h"
#include <string>
#include<vector>
#include <unistd.h>
#include <math.h>


class Jeu
{
public:
    ///@brief constructeur de la classe jeu
    Jeu();
    ///@brief permet de creer une nouvelle partie
    void CreerNouveauJeu(int nombreEnnemis,int degats);
    /**
     * @brief gere les actions du personnage en fonctions des différentes touches utilisés
     * @param ch caractere designant l'action que l'on veut réaliser
     * */
    void ActionClavier(const char ch);
    /**
     * @brief fais redescendre le personage si il saute ou si il n'est plus sur une plateforme
     * @param ch caracteres soit g (pour gauche), soit d (pour droite) pour changer de direction lors de la déscente
     * */
    void gravite(const char ch);
    /**
     * @brief permet l'affichage du terrain en mode texte
     * @param filename nom du ficher terrain a charger pour l'affichage
     * */
    void afficher_Terraintxt(const string& filename);
    ///@brief permet de recuperer un terrain 
    Terrain& getTerrain();
    ///@brief permet de recupérer un personnage
    Personnage& getPersonnage();
    ///@brief permet de recuperer le tableau d'ennemis
    vector<Ennemi> getEnnemis() const; // Retourne une référence constante sur le tableau d'ennemis
    ///@brief permet de mettre a jour l'arme du personnage et ceux des ennemis
    void UpdateArmePerso_Ennemi();
    ///@brief permet de gerer les collisions des projectiles qui touchent les ennemis
    void Collisions_proj_ennemi();
    ///@brief permet de gerer les collisions des qui touchent le personnage
    void Collisions_proj_personnage();
    ///@brief gere les tirs des ennemis en fonction de la position du personnage
    void Tir_Automatique();
    ///@brief permet de faire apparaitre un fusil que l'on peut eventuelement récuperer sur la map
    void Niveau_Suivant(int niveau);
    ///@brief fais le test de regression
    void testRegressionJeu();
    ///@brief booleen indiquant si la partie est finie
    bool GAME_OVER;
    ///@brief permet de debloquer le deuxiemme niveau
    bool DeuxiemeNiveauDebloque() const;
    ///@brief permet de debloquer le troisiemme niveau
    bool TroisiemeNiveauDebloque() const;
    ///@brief permet de se situer parmis les niveaux
    static int compteur_niveau;
    ///@brief indique si le niveau est fini
    bool FinDebloque() const;
private:
    ///@brief personnage
    Personnage pers;
    ///@brief terrain ou le personnage ce trouve
    Terrain ter;
    ///@brief Tableau d'ennemis
    vector<Ennemi> tab_en; 
    bool niveauDeuxDebloque;
    bool niveauTroisDebloque;// Tableau d'ennemis
    bool finDebloque;
};
#endif
