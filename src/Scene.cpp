/*
 * Scene.cpp
 *
 *  Created on: 4 f�vr. 2014
 *      Author: Altarrys
 */


#include "Sphere.h"

//mise en place des spheres dans une sc�ne.
Scene::Scene()
{


}
//--------------------------------------------------------------------------------
//destructeur de la sc�ne...
Scene::~Scene()
{

}
//--------------------------------------------------------------------------------
//Lance un rayon r et retourne la sphere avec un intersect retournant le plus petit des m_t.
//On ne modifie le rayon que si intersect retourne un m_hit=true et un plus petit m_t que le courant
Sphere Scene::lanceRayon(Rayon& r)
{
	Rayon rInt=r;
	Sphere Cs;
	for (unsigned int i=0; i<m_objectsList.size(); i++)
	{
		m_objectsList[i].intersect(rInt);
		if (rInt.m_hit && rInt.m_t < r.m_t)
		{
			r=rInt;
			Cs=m_objectsList[i];
		}
	}

	return Cs;
}
//--------------------------------------------------------------------------------
Sphere Scene::lanceRayonAARand(Rayon& r, int nbR, float dx, float dz)
{
	Sphere Cs;
	for (int i=0 ; i < nbR ; i++)
	{
		Rayon rInt=r;
		float dxRand = rand()%dx - dx/2;
		float dzRand = rand()%dz - dz/2;

		rInt.m_o.x = rInt.m_o.x + dxRand;
		rInt.m_o.z = rInt.m_o.z + dzRand;
		for (unsigned int i=0; i<m_objectsList.size(); i++)
		{
			m_objectsList[i].intersect(rInt);
			if (rInt.m_hit && rInt.m_t < r.m_t)
			{
				r=rInt;
				Cs=m_objectsList[i];
			}
		}
	}


	return Cs;
}
//--------------------------------------------------------------------------------
void Scene::imageCarre()
{
	for (int i = 0 ; i< 11 ; i++)
	{
		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0), 0.2, PVect(0.0,0.0,255.0)));
		m_objectsList.push_back(Sphere(PVect(-1.0,6.0,1.0-(float(i)/5.0)), 0.2, PVect(0.0,0.0,255.0)));

		m_objectsList.push_back(Sphere(PVect(1.0,6.0,-1.0+(float(i)/5.0)), 0.2, PVect(0.0,0.0,255.0)));
		m_objectsList.push_back(Sphere(PVect(1.0-(float(i)/5.0),6.0,-1.0), 0.2, PVect(0.0,0.0,255.0)));

		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0-(float(i)/5.0)), 0.2, PVect(0.0,0.0,255.0)));
		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,-1.0+(float(i)/5.0)), 0.2, PVect(0.0,0.0,255.0)));

	}
}
