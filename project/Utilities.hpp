//
//  Utilities.hpp
//  HashTables
//
//  Created by Sunil on 4/28/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#ifndef Utilities_hpp
#define Utilities_hpp

#include "PlayerInfo.hpp"

class Utilities {
public:
    static PlayerInfo ConstructFrom(string line);
    static string MakeKey(string firstName, string lastName);
    static string MakeKey(PlayerInfo& player);
};

#endif /* Utilities_hpp */
