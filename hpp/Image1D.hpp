//
        /**
            @author Created by Virgile Broillet P2103804 on 20/11/2024
            @file Image1D.hpp
            @brief
        
            @copyright Copyright © 2024 Virgile Broillet P2103804. All rights reserved for studying or personal use.
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

    //get pixel ouest du global:
    int getPixelW(int i, int j) const;

    //get pixel sud Ouest
    int getPixelSW(int i, int j) const;

    //get pixel Sud
    int getPixelS(int i, int j) const;

    //get pixel Sud Est
    int getPixelSE(int i, int j) const;

    //get pixel Est
    int getPixelE(int i, int j) const;

    //get pixel Nord Est
    int getPixelNE(int i, int j) const;

    //get pixel Nord
    int getPixelN(int i, int j) const;
    
    //get pixel Nord Ouest
    int getPixelNW(int i, int j) const;
    
    int getLength() const;
    
    int getWidth() const;
        
    void multiSourceDijkstra(const Image1D& image, vector<int>& distances, vector<int>& predecessors);
    
    void saveDistancesPGM(const string& filename, const vector<int>& distances) const;

    void createImageUnion(Image1D& image2, vector<int>& distancesUnion, vector<int>& predecessorsUnion);
        
    void savePredecessors(const string& filename, const vector<int>& predecessors) const;

    void projectionPixel(const vector<int>& distances, const vector<int>& predecessors);

};
