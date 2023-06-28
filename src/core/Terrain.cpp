#include "Terrain.h"
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

Terrain::Terrain()
{
	ChargeTerrain("./data/Terrain1.txt");
}

int Terrain::getdimx() const { 
	return dimx; 
}

int Terrain::getdimy() const { return dimy; }

void Terrain::setdimx(int dx)
{	
	assert(dx >= 0);
	dimx = dx;
}

void Terrain::setdimy(int dy)
{
	assert(dy >= 0);
	dimy = dy;
}

void Terrain::ChargeTerrain(const string& filename)
{
	ifstream fichier(filename);
	if(!fichier.is_open())
	{
		cerr << "Le fichier ne peut etre chargé" << filename << endl;
		return;
	}
	int hauteur, longueur;
	fichier >> hauteur >> longueur;

	setdimx(min(longueur,X));
	setdimy(min(hauteur,Y));

	for(int i=0;i<getdimy();i++)
	{
		for(int j=0;j<getdimx();j++)
		{
			fichier >> ter[j][i];
		}
	}
	fichier.close();
}

bool Terrain::estPositionPersoValide(const int x, const int y) const
{
    return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y]=='.'));

}

unsigned char Terrain::avoirchar(int x, int y) const
{
	assert(x>=0);
	assert(y>=0);
	assert(x<dimx);
	assert(y<dimy);
	return ter[x][y];
}

void Terrain::testRegressionTer(){
	Terrain Ter;
	Ter.setdimx(40);
	Ter.setdimy(9);
	assert(Ter.getdimx() == 40);
	assert(Ter.getdimy() == 9);
	assert(Ter.avoirchar(3,3) == ter[3][3]);
	cout << "Succes" << endl;

}