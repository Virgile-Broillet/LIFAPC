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

void Image1D::loadPGM(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Impossible d'ouvrir le fichier.");

    std::string header;
    file >> header;
    if (header != "P2") throw std::runtime_error("Format PGM non valide.");

    file >> length >> width >> maxIntensity;
    data.resize(length * width);

    for (int i = 0; i < length * width; ++i) {
        file >> data[i];
    }

    file.close();
}

void Image1D::savePGM(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Impossible de sauvegarder le fichier.");

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
    return i * length + j;
}


bool readPGM(const string&filename){
    ifstream file(filename);
    //verifie si le fichier est ouvert
    if (!file.is_open()) {
            cerr << "Error: Fichier pas ouvert: " << filename << endl;
            return false;
        }
    // Vérification du format
    char lettre[3];
    file.get(lettre, 3); // Lit les deux premiers caractères
    if (lettre[0] != 'P' || lettre[1] != '2') {
        cerr << "Error : Format non PGM." << endl;
        return false;
    }


    file.close();
    return true;
}


void pgm_to_vector(const string&filename){


}