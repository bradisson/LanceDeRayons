/*
 * Brdf.cpp
 *
 *  Created on: 25 f�vr. 2014
 *      Author: Tanguy
 */

#include "Brdf.h"




//applique le modele de lambert sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
PVect Lambert::ModeleLambert(Image *img,PVect vo,Source source,Rayon rayon)
{
	PVect Pix=PVect(0.0,0.0,0.0);
		PVect Ps = source.getPosition();
		//calcul point d'impact
		PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

		//calcul de la normale
		PVect N=I-vo;
		N.normalize();


		//calcul du Vi
		PVect Vi=Ps-I;
		Vi.normalize();

		//calcul du teta
		float teta=N*Vi;

		if (teta<0.0){
			teta=0.0;
		}

		//pr�paration du PVect couleur
		Pix.x+=(source.getPuissance().x*m_kd.x)*teta;
		Pix.y=+(source.getPuissance().y*m_kd.y)*teta;
		Pix.z+=(source.getPuissance().z*m_kd.z)*teta;

	return Pix;
}


//applique le modele de phong sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
//avec un coefficient n de sp�cularit� et Ks la composante couleur de la sp�cularit�
PVect Phong::ModelePhong(Source source,Sphere sphere,PVect Ks,float n,Rayon rayon)
{
	//calcul du teta
		PVect Ps = source.getPosition();
		//calcul point d'impact
		PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

		//calcul de la normale
		PVect N=I-sphere.getCentre();
		N.normalize();


		//calcul du Vi
		PVect Vi=Ps-I;
		Vi.normalize();

		//calcul du teta
		float teta=N*Vi;

		if (teta<0.0){
			teta=0.0;
		}

		//calcul alpha
		PVect H=Vi-rayon.m_v;
		H.normalize();
		float alpha=H*N;

		if (alpha<0.0){
			alpha=0.0;
		}

	return(CalcModelePhong(source.getPuissance(),sphere.getColor(),Ks,n,alpha,teta));
}
//---------------------------------------------------------------------------
//renvoie le calcul de phong avec la partie diffuse et la partie sp�culaire
PVect Phong::CalcModelePhong(PVect puissance,PVect Kd,PVect Ks,float n,float alpha,float teta){

		PVect partie_dif;
		PVect partie_spec;
		PVect P;

		//calcul du cosalpha puissance n
	    float value = pow(alpha, n);

	    //calcul de la partie diffuse de Phong
	    partie_dif.x = (1.0/M_PI)*Kd.x;
	    partie_dif.y = (1.0/M_PI)*Kd.y;
	    partie_dif.z = (1.0/M_PI)*Kd.z;

	    //calcul de la partie speculaire de Phong
	    partie_spec.x = ((n+2.0)/(2.0*M_PI))*Ks.x*value;
	    partie_spec.y = ((n+2.0)/(2.0*M_PI))*Ks.y*value;
	    partie_spec.z = ((n+2.0)/(2.0*M_PI))*Ks.z*value;

	    //Application du modele de Phong
	    P.x = puissance.x*(partie_dif.x + partie_spec.x)*teta;
	    P.y = puissance.y*(partie_dif.y + partie_spec.y)*teta;
	    P.z = puissance.z*(partie_dif.z + partie_spec.z)*teta;

	    return P;
}

