//
        /**
            @author Created by Virgile Broillet P2103804 on 20/11/2024
            @file Image1D.cpp
            @brief
        
            @copyright Copyright © 2024 Virgile Broillet P2103804. All rights reserved for studying or personal use.
        */

#include "../hpp/Image1D.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include "fstream"

#define BLACK_PIXEL 0
#define INT_MAX __INT_MAX__

using namespace std;

/**
 @brief procedure loadPGM: verifie que le fichier est ouvert et que c'est un pgm, copie de toutes les valeurs du filename dans file
 @param filename: string du chemin du fichier
*/

void Image1D::loadPGM(const string& filename) {
    ifstream file(filename);
    /** @details verification de l'ouverture du dossier
    */
    if (!file.is_open()) throw runtime_error("Impossible d'ouvrir le fichier.");

    /** @details verification du format de filename
    */
    string header;
    file >> header;
    if (header != "P2") throw runtime_error("Format PGM non valide.");

    /** @details copie des donnees length, width, maxIntensity dans file
            redimension du vector data pour prendre tous les pixels de filename
    */
    file >> length >> width >> maxIntensity;
    data.resize(length * width);

    for (int i = 0; i < length * width; ++i) {
        file >> data[i];
    }

    file.close();
}

/**
 @brief procedure savePGM: verifie que le fichier est ouvert et enregistre l'image filename dans file
 @param filename: string
*/

void Image1D::savePGM(const string& filename) const {
    ofstream file(filename);
    /** @details verification de l'ouverture du dossier
    */
    if (!file.is_open()) throw runtime_error("Impossible de sauvegarder le fichier.");

    /** @details ecrit dans le file les donnees du filename
    */
    file << "P2\n" << length << " " << width << "\n" << maxIntensity << "\n";

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < length; ++j) {
            file << getPixel(i, j) << " ";
        }
        file << "\n";
    }

    file.close();
}

/**
 @brief fonction getPixel qui prend en parametre les coordonnees d'un pixel et renvoi l'intensité de ce pixel
 @param i, j: des entiers
 @return un entier
*/

int Image1D::getPixel(int i, int j) const {
    /**
     @details data est un vector contenant l'intensité de chaque pixel
    */
    return data[index1D(i, j)];
}

void Image1D::setPixel(int i, int j, int value) {
    data[index1D(i, j)] = value;
}

/**
 @brief fonction index1D qui prends en parametre les coordonnees d'un pixel et retourne l'indice de ce pixel
 @param i, j: des entiers 
 @return un entier
*/

int Image1D::index1D(int i, int j) const {
    return ((i * length) + j);
}

//get pixel ouest du global:
int Image1D::getPixelW(int i, int j) const{
    //verifier si le voisin existe
    if(i==0){
        return -1;
    }
    return data[index1D(i, j-1)];
}

//get pixel Sud Ouest
int Image1D::getPixelSW(int i, int j)const{
    //verifier si le voisin existe
    if(i==0 || j==0){
        return -1;
    }
    return data[index1D(i-1, j-1)];
}

//get pixel Sud
int Image1D::getPixelS(int i, int j) const{
    //verifier si le voisin existe
    if(j==0){
        return -1;
    }
    return data[index1D(i-1, j)];
}

//get pixel Sud Est
int Image1D::getPixelSE(int i, int j) const{
    //verifier si le voisin existe
    if(i==length || j==0){

    }
    return data[index1D(i-1, j+1)];
}

//get pixel Est
int Image1D::getPixelE(int i, int j) const{
    //verifier si le voisin existe
    if(i==length){
        return -1;
    }
    return data[index1D(i-1, j-1)];
}

//get pixel Nord Est
int Image1D::getPixelNE(int i, int j) const{
    //verifier si le voisin existe
    if(i==length || j==width){
        return -1;
    }
    return data[index1D(i, j+1)];
}

//get pixel Nord
int Image1D::getPixelN(int i, int j) const{
    //verifier si le voisin existe
    if(j==width){
        return -1;
    }
    return data[index1D(i+1, j)];
}
    
//get pixel Nord Ouest
int Image1D::getPixelNW(int i, int j) const{
    //verifier si le voisin existe
    if(i==0 || j==width){
        return -1;
    }
    return data[index1D(i+1, j-1)];
}

/**
 @brief fonction qui renvoie la longueur de l'image 
 @return un entier: la longueur
*/
int Image1D::getLength() const
{
    return this->length;
}

/**
 @brief fonction qui renvoie la largeur de l'image 
 @return un entier: la largeur
*/
int Image1D::getWidth() const
{
    return this->width;
}

void Image1D::multiSourceDijkstra(const Image1D& image, vector<int>& distances, vector<int>& predecessors) {
    int n = image.length * image.width;
    const int INF = INT_MAX;
    
    // Initialisation des distances et prédécesseurs
    distances.assign(n, INF);
    predecessors.assign(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    // Initialisation des sources (pixels noirs)
    for (int i = 0; i < n; ++i) {
        if (image.data[i] == BLACK_PIXEL) { // BLACK_PIXEL est une constante représentant les pixels noirs initialisé à 0
            distances[i] = 0;
            pq.push(make_pair(0, i));
        }
    }

    // Directions pour les voisins (horizontal, vertical, diagonal)
    vector<pair<int, int> > directions;
    directions.push_back(make_pair(0, 1));
    directions.push_back(make_pair(0, -1));
    directions.push_back(make_pair(1, 0));
    directions.push_back(make_pair(-1, 0));
    directions.push_back(make_pair(1, 1));
    directions.push_back(make_pair(1, -1));
    directions.push_back(make_pair(-1, 1));
    directions.push_back(make_pair(-1, -1));

    
    // Dijkstra
    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        if (visited[current]) continue;
        visited[current] = true;

        int x = current / image.width;
        int y = current % image.width;

        // Parcourir les voisins
        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < image.length && ny >= 0 && ny < image.width) {
                int neighbor = nx * image.width + ny;
                if (visited[neighbor]) continue;

                // Calcul du coût
                int cost = (abs(dx) + abs(dy) == 2) ? 3 : 2;
                int newDist = currentDist + cost;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    predecessors[neighbor] = current;
                    pq.push(make_pair(newDist, neighbor));
                }
            }
        }
    }
    
    int maxDistance = *max_element(distances.begin(), distances.end());
        if (maxDistance == INF) maxDistance = 0; // Évite la division par zéro

        // Étape 2 : Normaliser les distances entre 0 et 255
        for (int i = 0; i < n; ++i) {
            if (distances[i] == INF) {
                distances[i] = 255; // Pixels non atteignables : blanc pur
            } else {
                distances[i] = (distances[i] * 255) / maxDistance;
            }
        }
}


void Image1D::saveDistancesPGM(const string& filename, const vector<int>& distances) const {
    ofstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossible de sauvegarder le fichier.");

    file << "P2\n" << length << " " << width << "\n" << maxIntensity << "\n";

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            file << distances[index1D(i, j)] << " ";
        }
        file << "\n";
    }

    file.close();
}

void Image1D::createImageUnion(Image1D& image2, vector<int>& distancesUnion, vector<int>& predecessorsUnion) {
    // Nous combinons les images de distance des deux formes
    Image1D image1;
    this->length = image1.getLength();
    this->width = image1.getWidth();
    this->data = image1.data;
    this->maxIntensity = image1.maxIntensity;

    vector<int> distances1(length * width);
    vector<int> predecessors1(length * width);
    vector<int> distances2(length * width);
    vector<int> predecessors2(length * width);

    image1.multiSourceDijkstra(image1, distances1, predecessors1);
    image2.multiSourceDijkstra(image2, distances2, predecessors2);

    // Combinaison des deux images de distance
    for (int i = 0; i < length * width; ++i) {
        if (distances1[i] < distances2[i]) {
            distancesUnion[i] = distances1[i];
            predecessorsUnion[i] = predecessors1[i];
        } else {
            distancesUnion[i] = distances2[i];
            predecessorsUnion[i] = predecessors2[i];
        }
    }

    cout << "Image de distance de l'union construite !" << endl;
}

void Image1D::savePredecessors(const string& filename, const vector<int>& predecessors) const {
    ofstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossible de sauvegarder le fichier.");

    for (int pred : predecessors) {
        file << pred << " ";
    }

    file.close();
}

void Image1D::projectionPixel(const vector<int>& distances, const vector<int>& predecessors) {
    int x= 0, y= 0; // Coordonnées du pixel d'intérêt
    int length = this->length;
    int width = this->width;
    
    cout << "Trouvé le Pixel noir le plus proche d'un Pixel :" << endl;
    cout << "X (largeur) : "; cin >> x;
    cout << "Y (hauteur) : "; cin >> y;

    int idx = y * width + x;  // Utiliser y pour la hauteur et x pour la largeur dans le calcul de l'indice

    if (x < 0 || x >= width || y < 0 || y >= length) {  // Vérifier les dimensions avec x en largeur et y en hauteur
        cout << "Coordonnées invalides : x=" << x << ", y=" << y << ", longeur : " << length << ", largeur : " << width <<endl;
        return;
    }

    if (idx < 0 || idx >= distances.size()) {
        if (distances.size() == 0 ){
            cout << "Créer l'image des distances SVP (étape 4)."<< endl;
            return;
        }else{
            cout << "Indice invalide : idx=" << idx << ", taille distances=" << distances.size() << endl;
            return;
        }
    }

    cout << "Distance depuis (" << x << ", " << y << ") : " << distances[idx] << endl;

    // Remonter le chemin
    cout << "Chemin le plus court depuis (" << x << ", " << y << ") :";
    while (idx != -1) {
        cout << " (" << idx % width << ", " << idx / width << ")"; // Afficher les coordonnées avec x en largeur et y en hauteur
        idx = predecessors[idx];
    }
    cout << endl;
}
