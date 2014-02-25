/*
 * Brdf.h
 *
 *  Created on: 25 f�vr. 2014
 *      Author: Tanguy
 */

#ifndef BRDF_H_
#define BRDF_H_

#include "Source.h"
#include "Sphere.h"
#include "Image.h"
#include "Rayon.h"
#include "vector.h"

class Brdf {
private:
	vector<Source> m_source;
public:
	Brdf(vector<Source> s);
	void ModeleLambert(Image *img,Sphere sphere,Rayon rayon,int i,int j);
};

#endif /* BRDF_H_ */