//IF5 - Octobre 2005
//Raphaelle Chaine

#include <iostream> 
#include <cstdio>
#include <fstream> //ifstream, ofstream
#include <cstdlib> //exit
#include "hpp/Image1D.hpp"

#define MAX __INT_MAX__

void afficherMenu() {
    cout << "==== Menu ====" << endl;
    cout << "1. Charger une forme depuis un fichier PGM" << endl;
    cout << "2. Sauvegarder une forme dans un fichier PGM" << endl;
    cout << "3. Construire l'image de distance d'une forme" << endl;
    cout << "4. Sauvegarder l'image de distance dans un fichier PGM" << endl;
    cout << "5. Projection d'un pixel sur une forme" << endl;
    cout << "6. Construire l'image de distance de l'union de deux formes" << endl;
    cout << "7. Projection d'un point sur l'union de deux formes" << endl;
    cout << "8. Quitter" << endl;
}


int main() {
    Image1D image1, image2;
    vector<int> distances, predecessors;
    vector<int> distancesUnion, predecessorsUnion;
    string filename1, filename2, filename3;

    int choix;
    bool quitter = false;

    while (!quitter) {
        afficherMenu();
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "Nom de Fichier : ";
                cin >> filename1;
                cout << filename1;
                image1.loadPGM(filename1);
                break;
            case 2:
                cout << "Nom de Fichier : ";
                cin >> filename2;
                image1.savePGM(filename2);
                break;
            case 3:
                image1.multiSourceDijkstra(image1, distances, predecessors);
                break;
            case 4:
                cout << "Nom de Fichier : ";
                cin >> filename3;
                image1.saveDistancesPGM(filename3, distances);
                break;
            case 5:
                image1.projectionPixel(distances, predecessors);
                break;
            case 6:
                cout << "Charger la première forme : " << endl;
                cout << "Nom de Fichier : ";
                cin >> filename1;
                image1.loadPGM(filename1);
                cout << "Charger la deuxième forme : " << endl;
                cout << "Nom de Fichier : ";
                cin >> filename2;
                image2.loadPGM(filename2);
                image1.createImageUnion(image2, distancesUnion, predecessorsUnion);
                break;
            case 7:
                cout << "Au revoir !" << endl;
                quitter = true;
                break;
            default:
                cout << "Choix invalide !" << endl;
                break;
        }
    }

    return 0;
}
