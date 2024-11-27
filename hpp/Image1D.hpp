//
        /**
            @author Created by Virgile Broillet P2103804 on 20/11/2024
            @file Image1D.hpp
            @brief
        
            @copyright Copyright © 2024 - 2024+1 Virgile Broillet P2103804. All rights reserved for studying or personal use.
        */
        


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Image1D {
private:
    unsigned int length; // Longueur de l'image
    unsigned int width; // Largeur de l'image
    int maxIntensity; // Intensité maximale (255 pour PGM)
    
    vector<int> data; // Pixels de l'image en tableau 1D
    
public:
    // Constructeur par défaut
    Image1D() : length(0), width(0), maxIntensity(255), data() {}

    // Constructeur avec initialisation
    Image1D(int length, int width, int maxIntensity = 255)
        : length(length), width(width), maxIntensity(maxIntensity), data(length * width, 255) {}
    
    void loadPGM(const string& filename); // Charger une image PGM
    void savePGM(const string& filename) const; // Sauvegarder en PGM
    
    // Accès aux pixels
    int getPixel(int i, int j) const;
    void setPixel(int i, int j, int value);

    // Conversion entre index 2D et 1D
    int index1D(int i, int j) const;

    // Verification du fichier
    bool readPGM(const string&filename);

    //procedure qui prend un fichier pgm et "rempli" les donnees de l'image1D
    void pgm_to_vector(const string&filename);

};
