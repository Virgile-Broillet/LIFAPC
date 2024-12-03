//
        /**
            @author Created by Virgile Broillet P2103804 & Salma Ahizoune Hiouas P2003590 on 20/11/2024
            @file Image1D.hpp
            @brief
        
            @copyright Copyright © 2024 Virgile Broillet P2103804 & Salma Ahizoune Hiouas P2003590. All rights reserved for studying or personal use.
        */
        


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Image1D {
private:
    unsigned int length; // Longueur de l'image
    unsigned int width; // Largeur de l'image
    int maxIntensity; // Intensité maximale (255)
    
    vector<int> data; // Pixels de l'image en tableau 1D
    
public:
    /**
     @brief constructeur par défaut
     **/
    Image1D() : length(0), width(0), maxIntensity(255), data() {}

    /**
     @brief Constructeur avec initialisation
     */
    Image1D(int length, int width, int maxIntensity = 255)
        : length(length), width(width), maxIntensity(maxIntensity), data(length * width, 255) {}
    
    //      ====== FONCTION DE CHARGEMENT / SAUVGARDE D'IMAGE ======
    
    void loadPGM(const string& filename);
    void savePGM(const string& filename) const;
    
    //      ====== FONCTION D'UTILITÉ ======
    int getPixel(int i, int j) const;
    int index1D(int i, int j) const;
    int getLength() const;
    int getWidth() const;
    
    //      ====== MULTI-SOURCES DIJKSTRA ======
        
    void multiSourceDijkstra(const Image1D& image, vector<int>& distances, vector<int>& predecessors);
    
    //      ====== FONCTION SAVE DISTANCE ET PREDECESSOR  ======

    void saveDistancesPGM(const string& filename, const vector<int>& distances) const;
    void savePredecessors(const string& filename, const vector<int>& predecessors) const;
    
    //      ====== FONCTION UNION  ======
    
    void createImageUnion(Image1D& image2, vector<int>& distancesUnion, vector<int>& predecessorsUnion);

    //      ====== FONCTION DE PROJECTION  ======
    
    void projectionPixel(const vector<int>& distances, const vector<int>& predecessors);

};
