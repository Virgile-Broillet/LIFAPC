//IF5 - Octobre 2005
//Raphaelle Chaine

#include <iostream> 
#include <cstdio>
#include <fstream> //ifstream, ofstream
#include <cstdlib> //exit
#include "hpp/Image1D.hpp"

/*
void creeFichierEntiers(const char * nomFichier, int nb)
//preconditions : nomFichier chaine de caracteres designant le nom du fichier a creer
//postcondition : le fichier nomFichier contient nb entiers separes par des espaces
{
  std::ofstream ofs;
  ofs.open(nomFichier);
  if(ofs.bad()) 
    {std::cout<<"Impossible d'ouvrir le fichier "<<nomFichier<<" en ecriture \n"; exit(1);}

  for(int i=0;i<nb;i++)
    {
      int temp;
      std::cout << "Entier suivant : ";
      std::cin >> temp; //Ou utilisez la version robuste de saisie d'un int
      ofs << temp <<' ';//Remarquez que l'on separe les int par des espaces
    }
  ofs.close();
}

void litFichierEntiers(const char * nomFichier)
//preconditions : nomFichier chaine de caracteres designant le nom d'un fichier
//                contenant des entiers separes par des caracteres d'espacement
//postcondition : affichage du contenu du fichier sur la sortie standard
{
  std::ifstream ifs;
  ifs.open(nomFichier);
  if(ifs.bad())
    {std::cout<<"Impossible d'ouvrir le fichier "<<nomFichier<<" en lecture \n"; exit(1);}
  int temp;
  while(ifs >> temp)
    std::cout<<"Entier suivant "<<temp<< std::endl;
  ifs.close();
}
*/
int main() {
    try {
        // Création d'une image vide
        Image1D img;
        string filename = "ex1.pgm";

        // Charger une image PGM depuis un fichier
        std::cout << "Chargement de l'image" << filename <<"...\n";
        img.loadPGM(filename);


        // Modifier un pixel pour tester
        int x = 5, y = 5; // Coordonnées arbitraires
        std::cout << "Modification du pixel (" << x << ", " << y << ")...\n";
        img.setPixel(x, y, 100);

        // Sauvegarder l'image modifiée
        std::cout << "Sauvegarde de l'image modifiée dans 'output.pgm'...\n";
        img.savePGM("output.pgm");

        std::cout << "Terminé ! L'image modifiée a été sauvegardée avec succès.\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
    }

    return 0;
}
