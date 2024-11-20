//
        /**
            @author Created by Virgile Broillet P2103804 on 20/11/2024
            @file Image1D.hpp
            @brief
        
            @copyright Copyright © 2024 - 2024+1 Virgile Broillet P2103804. All rights reserved for studying or personal use.
        */
        


#include <iostream>
#include <vector>

using namespace std;

class Image1D {
    unsigned int lenght;
    unsigned int width;
    
    vector<int> data;
    
public:
    // Constructeurs
    Image1D(int lenght, int width);
    ~Image1D();
    
    bool loadPGM(const string& filename); // Charger une image PGM
    bool savePGM(const string& filename) const; // Sauvegarder en PGM

};
