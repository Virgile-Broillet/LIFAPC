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

void Image1D::loadPGM(const string& filename) {
    ifstream file(filename);
    //fichier ouvert?
    if (!file.is_open()) throw runtime_error("Impossible d'ouvrir le fichier.");

    //fichier pgm?
    string header;
    file >> header;
    if (header != "P2") throw runtime_error("Format PGM non valide.");

    file >> length >> width >> maxIntensity;
    data.resize(length * width);

    for (int i = 0; i < length * width; ++i) {
        file >> data[i];
    }

    file.close();
}

void Image1D::savePGM(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossible de sauvegarder le fichier.");

    file << "P2\n" << length << " " << width << "\n" << maxIntensity << "\n";

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < length; ++j) {
            file << getPixel(i, j) << " ";
        }
        file << "\n";
    }

    file.close();
}

int Image1D::getPixel(int i, int j) const {
    return data[index1D(i, j)];
}

void Image1D::setPixel(int i, int j, int value) {
    data[index1D(i, j)] = value;
}

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

int Image1D::getLength() const
{
    return this->length;
}

int Image1D::getWidth() const
{
    return this->width;
}

/**
 @name multiSourceDijkstra(const Image1D& image, vector<int>& distances, vector<int>& predecessors)
 @brief Effectue l'algorithme de Dijkstra sur une image 1D pour calculer les distances minimal et mettre a l'échelle pour pouvoir faire un dégradé chromatiqu .
 @param image , reference constante vers l'image source de type Image1D.
 @param distances , vecteur de sortie contenant les distances minimals pour chaques pixels. normalisée entre 0 et 255
 @param predecessors , vecteur de sortie contenant les prédécésseurs de chaque pixels. -1 veut dire aucun prédécesseurs
 */
void Image1D::multiSourceDijkstra(const Image1D& image, vector<int>& distances, vector<int>& predecessors) {
    int n = image.length * image.width;
    const int INF = INT_MAX;
    
    /**
     @details
     - initialisations des données (disatnce à infini) et prédécesseur à -1)
     - priority_queue représentation d'une file de prioritée : chaque elemt sera un paire de deux entiers, avec greater on change l'ordre de priorité de décroissant à croissant. pq est le nom de la file de priorité
     */
    distances.assign(n, INF);
    predecessors.assign(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    /**
     @details
     - Initialisations des sources (pixels noirs)
     - Ici BLACK_PIXEL est un constante défini plus haut représentant les pixels noirs initialisés à 0
     */
    for (int i = 0; i < n; ++i) {
        if (image.data[i] == BLACK_PIXEL) {
            distances[i] = 0;
            pq.push(make_pair(0, i));
        }
    }

    /**
     @details
     -  On initialise les directions pour les voisins (horizontal, vertical et diagonal)
     */
    vector<pair<int, int> > directions;
    directions.push_back(make_pair(0, 1));
    directions.push_back(make_pair(0, -1));
    directions.push_back(make_pair(1, 0));
    directions.push_back(make_pair(-1, 0));
    directions.push_back(make_pair(1, 1));
    directions.push_back(make_pair(1, -1));
    directions.push_back(make_pair(-1, 1));
    directions.push_back(make_pair(-1, -1));

    
    /**
     @details
     - On effectue le théorème de Dijkstra
     */
    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        if (visited[current]) continue;
        visited[current] = true;

        int x = current / image.width;
        int y = current % image.width;

        /**
         @details parcours des voisins
         */
        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < image.length && ny >= 0 && ny < image.width) {
                int neighbor = nx * image.width + ny;
                if (visited[neighbor]) continue;

                /**
                 @details calcul du cout pour passer d'un noeud a un autre
                 - Déplacement diagonal : coût de complixité 3
                 - Déplacement horizontaux ou vertical : coût de compléxité 2
                 */
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
    
    /**
     @details
     - On normalise les elements pour pouvoir avoir un dégradé chromatique noir profond étant le pixel noir lui même.
     -  Plus on s'éloigne du Pixel noir, plus les pixels sont claire, jusqu'a atteindre le blanc profond.
     */
    int maxDistance = *max_element(distances.begin(), distances.end());
        if (maxDistance == INF) maxDistance = 0; /** @details on évite la diviison par 0 */

        /**
         @details
         - On normalise les distance en 0 et 255.
         */
        for (int i = 0; i < n; ++i) {
            if (distances[i] == INF) {
                distances[i] = 255; /** @details Pixel inateignable, on le normalise à blanc pûre (255) )*/
            } else {
                distances[i] = (distances[i] * 255) / maxDistance;
            }
        }
}


/**
 @name saveDistancesPGM(const string& filename, const vector<int>& distances)
 @brief Sauvegarde d'une image PGM représentant les distances calculées
 @param filename , nom du fichier dans lequel l'image sera sauvegardée
 @param distances , vecteur contenant les distances a sauvegardées chaque valeur représentant une intensité de gris (entre 0 et 255) d'un pixel.
 */
void Image1D::saveDistancesPGM(const string& filename, const vector<int>& distances) const {
    ofstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossible de sauvegarder le fichier.");

    /**
     @details
     - On remplis les premieres lignes du fichiers avec les informations de bases, P2 pour le format PGM, la lngueur et la hauteur ainsi que le maxIntensity
     */
    file << "P2\n" << length << " " << width << "\n" << maxIntensity << "\n";

    /**
     @details
     - On copie toutes les informations du vector data dans notre file.
     */
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            file << distances[index1D(i, j)] << " ";
        }
        file << "\n";
    }

    file.close();
}

/**
 @name createImageUnion(Image1D& image2, vector<int>& distancesUnion, vector<int>& predecessorsUnion)
 @brief Créer une image de distance représentant l'union des deux images.
 @param image2 , une deuxieme image de type Image1D utilisé pour calculer les distances
 @param distancesUnion , Vecteur de sortie où seront stocker les distances combinées des deux images
 @param predecessorsUnion , Vecteur de sortie où seront stocker les prédécesseurs combinés des deux images.
 */
void Image1D::createImageUnion(Image1D& image2, vector<int>& distancesUnion, vector<int>& predecessorsUnion) {
    /**
     @details
     - On initialise l'image1 avec l'image importé de la classe
     */
    Image1D image1;
    this->length = image1.getLength();
    this->width = image1.getWidth();
    this->data = image1.data;
    this->maxIntensity = image1.maxIntensity;

    vector<int> distances1(length * width);
    vector<int> predecessors1(length * width);
    vector<int> distances2(length * width);
    vector<int> predecessors2(length * width);

    /**
     @details
     - On fait appel a Dijkstra sur les deux images.
     **/
    image1.multiSourceDijkstra(image1, distances1, predecessors1);
    image2.multiSourceDijkstra(image2, distances2, predecessors2);

    /**
     @details
     - On combine les deux images pour faire leur Union.
     */
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

/**
 @name savePredecessors(const string& filename, const vector<int>& predecessors)
 @brief Sauvegarde le vecteur des prédécesseurs
 @param filename , le chemin complet ou le nom de fichier ou sauvgardé les prédécesseurs
 @param predecessors , le vecteur prédécesseur a sauvgardé
 */
void Image1D::savePredecessors(const string& filename, const vector<int>& predecessors) const {
    ofstream file(filename);
    if (!file.is_open()) throw runtime_error("Impossible de sauvegarder le fichier.");

    /**
     @details
     - on copie toutes les informations du vecteur dans le fichier
     */
    for (int pred : predecessors) {
        file << pred << " ";
    }

    file.close();
}

/**
 @name projectionPixel(const vector<int>& distances, const vector<int>& predecessors)
 @brief Projette un pixel donnée vers le pixel noir le plus proche et affiche le chemin le plus cours pour y acceder en fonction de la compléxité calculer plus haut
 @param distances , Vecteur contenant les distances calculées à partir des pixels noirs.
 @param predecessors , Vecteur contenant les prédécesseurs de chaque pixel dans le chemin le plus court.
 */
void Image1D::projectionPixel(const vector<int>& distances, const vector<int>& predecessors) {
    int x= 0, y= 0; /** @details coordonnées du Pixel d'interêt **/
    int length = this->length;
    int width = this->width;
    
    cout << "Trouvé le Pixel noir le plus proche d'un Pixel :" << endl;
    cout << "X (largeur) : "; cin >> x;
    cout << "Y (hauteur) : "; cin >> y;

    int idx = y * width + x;  /** @details On utilise  y pour la hauteur et x pour la largeur dans le calcul de l'indice */

    if (x < 0 || x >= width || y < 0 || y >= length) {  /** @details On vérifie  les dimensions avec x en largeur et y en hauteur */
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

    cout << "Chemin le plus court depuis (" << x << ", " << y << ") :";
    while (idx != -1) {
        cout << " (" << idx % width << ", " << idx / width << ")"; /** @details On affiche les coordonnées avec x en largeur et y en hauteur */
        idx = predecessors[idx];
    }
    cout << endl;
}
