#ifndef IMAGE_CPP_
#define IMAGE_CPP_

#include "Image.h"
using namespace std;


//---------------------------------------------------------------------------
//Formation d'une image avec un fond uni PVect color en param�tre
Image::Image(const int rx, const int ry,PVect color)
{
	m_rezX=rx;
	m_rezY=ry;
	m_img = new PVect[m_rezY*m_rezX];

	for (int i=0; i<m_rezX*m_rezY; i++)
	{
			m_img[i].x = color.x;
			m_img[i].y = color.y;
			m_img[i].z = color.z;
	}
}
//---------------------------------------------------------------------------
//sauvegarde du fichier image
void Image::save(string filename)
{
	fstream fileHandle;
	fileHandle.open(filename.c_str(), fstream::out | ios::binary);

	fileHandle << "P3" << endl;
	fileHandle << m_rezY << " " << m_rezX << endl;
	fileHandle << "255" << endl;
	for (int i=0; i<m_rezX*m_rezY; i++)
	{
		fileHandle << (int)m_img[i].x << " " << (int)m_img[i].y << " " << (int)m_img[i].z << " " ;
	}

	fileHandle.close();
}
//---------------------------------------------------------------------------
//chargement d'une image pr�-�xistante
void Image::load(string filename)
{
	fstream fileHandle;
	fileHandle.open(filename.c_str(), fstream::in |ios::binary);

	for (int i=0; i<m_rezX*m_rezY; i++)
	{
		fileHandle >> m_img[i].x >> m_img[i].y >> m_img[i].z;
	}

	fileHandle.close();
}
//---------------------------------------------------------------------------
//attribut les couleur PVect de p au pixel en x,y
void Image::setPixel(int x, int y, PVect p)
{
	m_img[m_rezY*y+x]=p;
}
//---------------------------------------------------------------------------
//retourne un PVect des couleur du pixel en x,y de l'image courante
PVect Image::getPixel(int x, int y)
{
	return m_img[m_rezY*y+x];
}
//---------------------------------------------------------------------------
//retourne la taille en X de l'image(nombre de colonnes)
int Image::getRezX()
{
	return m_rezX;
}
//---------------------------------------------------------------------------
//retourne la taille en Z de l'image(nombre de lignes)
int Image::getRezY()
{
	return m_rezY;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void Image::takePicture(float f, float dx, float dz, PVect p0, PVect origin, Scene myScene)
{
	vector<Source> source;
	source.push_back(Source(PVect(10.0,0.0,10.0),PVect(1.0,1.0,1.0)));
	source.push_back(Source(PVect(-10.0,0.0,-10.0),PVect(1.0,1.0,1.0)));
	//Brdf brdf= Brdf(source);

	PVect v,vR;
	v.y = f;
	for (int i=0; i<getRezY(); i++)
	{
		v.z = p0.z-i*dz;
		for (int j=0; j<getRezX(); j++)
		{
			v.x = p0.x+j*dx;
			vR= v;
			vR.normalize();

			Rayon r = Rayon(origin, vR);
			Sphere s = myScene.lanceRayon(r);

			if (r.m_hit)
			{
				//img->setPixel(i,j,s.getColor());
				//brdf.ModeleLambert(img,s,r,i,j);
				//img->ModelePhong(source,s,PVect(1.0,1.0,1.0),512,r,i,j);
				//img->imageMiroir(source,r,s,i,j);
			}
	    }
	}
}
//---------------------------------------------------------------------------
//Envoie le rayon Vm rayon miroir de "rayon" et attribut la couleur trouv�e au point de contact I de la sphere
void Image::imageMiroir(Source source,Rayon rayon,Sphere sphere,int i,int j){
//calcul du teta
	PVect Ps = source.getPosition();
	//calcul point d'impact
	PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

	//calcul de la normale
	PVect N=I-sphere.getCentre();
	N.normalize();

	//calcul du rayon miroir
	PVect Vm=rayon.m_v-2.0*(N*rayon.m_v)*N;
	this->setPixel(i,j,this->getPixel((int)Vm.x,(int)Vm.z));
}
#endif /* IMAGE_CPP_ */
