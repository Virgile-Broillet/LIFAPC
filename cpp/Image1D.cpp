//
        /**
            @author Created by Virgile Broillet P2103804 on 20/11/2024
            @file Image1D.cpp
            @brief
        
            @copyright Copyright © 2024 - 2024+1 Virgile Broillet P2103804. All rights reserved for studying or personal use.
        */

#include "../hpp/Image1D.hpp"
#include <iostream>
#include "fstream"

using namespace std;

void Image1D::loadPGM(const string& filename) {
    ifstream file(filename);
    //fichier ouvert?
    if (!file.is_open()) throw runtime_error("Impossible d'ouvrir le fichier.");

    //fichier pgm?
    string header;
    file >> header;
    if (header != "P2") throw runtime_error("Format PGM non valide.");

    //
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
