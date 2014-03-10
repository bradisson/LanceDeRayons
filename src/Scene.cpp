/*
 * Scene.cpp
 *
 *  Created on: 4 f�vr. 2014
 *      Author: Altarrys
 */


#include "Scene.h"

//scene

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
Sphere Scene::lanceRayonAARand(vector<Rayon> r , float dx, float dz)
{
	Sphere Cs;
	for (int i=0 ; i < r.size() ; i++)
	{
		Rayon rInt = r[i];
		for (unsigned int i=0; i<m_objectsList.size(); i++)
		{
			m_objectsList[i].intersect(rInt);
			if (rInt.m_hit && rInt.m_t < r[i].m_t)
			{
				r[i]=rInt;
				Cs=m_objectsList[i];
			}
		}
	}


	return Cs;
}
//--------------------------------------------------------------------------------
void Scene::imageCarre()
{
	m_source.push_back(Source(PVect(0.0,0.0,5.0),PVect(1.0,1.0,1.0)));
	m_source.push_back(Source(PVect(5.0,0.0,-5.0),PVect(1.0,1.0,1.0)));
	for (int i = 0 ; i< 11 ; i++)
	{
		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0), 0.1,new Lambert(PVect(255.0,120.0,0.0))));
		m_objectsList.push_back(Sphere(PVect(-1.0,6.0,1.0-(float(i)/5.0)), 0.1,new Lambert(PVect(0.0,0.0,255.0))));

		m_objectsList.push_back(Sphere(PVect(1.0,6.0,-1.0+(float(i)/5.0)), 0.1,new Phong(PVect(125.0,50.0,0.0),PVect(0.0,50.0,125.0),8)));
		m_objectsList.push_back(Sphere(PVect(1.0-(float(i)/5.0),6.0,-1.0), 0.1,new Phong(PVect(125.0,0.0,0.0),PVect(0.0,50.0,125.0),8)));

		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0-(float(i)/5.0)), 0.1,new Lambert(PVect(0.0,0.0,255.0))));
		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,-1.0+(float(i)/5.0)), 0.1,new Phong(PVect(0.0,0.0,125.0),PVect(0.0,0.0,125.0),8)));
	}
}
//--------------------------------------------------------------------------------
void Scene::testAA()
{
	m_source.push_back(Source(PVect(5.0,0.0,0.0),PVect(1.0,1.0,1.0)));
	m_objectsList.push_back(Sphere(PVect(0.0,3.0,0.0), 0.5,new Phong(PVect(125.0,25.0,0.0),PVect(125.0,25.0,0.0),8)));

}
//--------------------------------------------------------------------------------
vector<Source> Scene::getSource()
{
	return m_source;
}

