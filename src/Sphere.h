/*
 * Sphere.h
 *
 *  Created on: 22 janv. 2014
 *      Author: Tanguy
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <iostream>
#include "PVect.h"
#include "Rayon.h"
#include "Brdf.h"

class Sphere {

private :
	//centre de la sph�re
	PVect m_c;
	//rayon de la sph�re
	float m_r;
	//couleur de la sph�re
	PVect m_color;


public :
	//Brdf demand�e
	Brdf *m_brdf;

	//lance un rayon vers la sphere objet et modifie le rayon s'il touche la sph�re
	void intersect(Rayon &R);

	//Constructeur d'une sphere avec c son centre, r son rayon et color sa couleur face � une lumi�re blanche
	Sphere(PVect c, float r,Brdf *b);

	//constructeur vide...
	Sphere();

	//retourne la couleur de la sphere face � une lumi�re blanche
	PVect getColor();

	//retourne le centre de la sphere
	PVect getCentre();


};


#endif /* SPHERE_H_ */
