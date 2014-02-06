/*
 * Matrice.h
 *
 *  Created on: 4 f�vr. 2014
 *      Author: Tanguy
 */

#ifndef MATRICE_H_
#define MATRICE_H_

#include "PVect.h"

class Matrice {

private :
	//premi�re ligne de la matrice
	PVect m_m0;

	//deuxi�me ligne de la matrice
	PVect m_m1;

	//troisi�me ligne de la matrice
	PVect m_m2;


public:
	//constructeur de matrice
	Matrice(PVect a,PVect b,PVect c);

	//op�rator * pour deux matrice
	friend Matrice operator*(Matrice const& a, Matrice const& b);

};

#endif /* MATRICE_H_ */
