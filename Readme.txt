GOKANA EMMANUEL P2100037
NECHADI MEHDI P2110129
ID PROJET - 28479
===============================
======== Gun Runner ===========
===============================

======== Description ==========

Gun runner est un jeu de plateforme sur linux et MacOs (avec puce Apple Silicon) codé avec la librairie SDL. 
Le but du jeu est d'éliminer tout les ennemis présent sur la map sans se faire tuer par les nombreux 
obstacles (et les ennemis). 

==== Manuel d'utilisation =====

Voici les principales commandes du jeu:
En mode texte:

q - deplacement à gauche
d - deplacement à droite
z - saut
r - tir
x - pour quitter

En mode graphique:

(Ici les déplacement se font avec les directions du clavier)
DROITE - déplacement à droite
GAUCHE - dépalcement à gauche
HAUT - saut
r - tir
q - pour quitter

Pour compiler les différents exécutables il faut taper les commandes suivantes:


(petite préscision pour les executables avant de les lancer 
dans le répertoire courant faudra bien veiller à faire un
"chmod -R u+x ./bin" car les droits d'execution ne sont pas données directement)
(*oubliez pas de faire un make clean, suivi d'un make avant de lancer les executables)

./bin/sdl - pour lancer le jeu en mode graphique
./bin/texte - pour lancer le jeu en mode texte
./bin/testArme - pour lancer le test de regression de la classe Arme
./bin/testEnn - pour lancer le test de regression de la classe Ennemi
./bin/testPers - pour lancer le test de regression de la classe Personnage
./bin/testJeu - pour lancer le test de regression de la classe Jeu 
./bin/testProj - pour lancer le test de regression de la classe Projectile
./bin/testTer - pour lancer le test de regression de la classe Terrain

==== Organisation de l'archive ====

./bin - repertoire contenant les exécutables 

./data - répertoire contenant les différents assets de notre application notament des images 

./doc - repertoire contenant la documentation du code du Jeu 
./doc/html - repertoire contenant la page web de la documentation

./obj - répertoire contenant les fichier objets du projet 

./src - répertoire contenant les fichiers source du projet (.h/.cpp)
./src/core - répertoire contenant les fichiers sources gérant le coeur du jeu 
./src/sdl - répertoire contenant les ficher sources gérant la partie graphique du jeu
./src/tests - répertoire contenant les différents mains des test de regression
./src/txt - répertoire contenant les fichiers sources gérant la partie texte du jeu
