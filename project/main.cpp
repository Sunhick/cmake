//
//  main.cpp
//  HashTables
//
//  Created by Sunil on 4/28/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "HashTable.hpp"
#include "Utilities.hpp"

using namespace std;

void die(string message) {
    cout << message << endl;
    exit(0);
}

void PopulateHashTable(string filename, HashTable* map) {
    ifstream file(filename);
    
    // non-existant or corrupted file
    if(file.fail()) {
        die("Could not open file");
    }
    
    string line;
    
    string ignoreHeader;
    std::getline(file, ignoreHeader);
    cout << ignoreHeader << endl;
    std::setiosflags(ios::fixed);
    
    while(std::getline(file, line)) {
        // Format of the line:
        // yearID       : int
        // teamID       : string
        // leagueID     : string
        // playerID     : string
        // salary       : long
        // firstName    : string
        // lastName     : string
        // birthYear    : string
        // birthCountry : string
        // weight       : float
        // height       : float
        // bats         : int
        // throws       : int
        auto playerInfo = Utilities::ConstructFrom(line);
        
        // add playerInfo to the hash table.

        // cout << playerInfo.yearId << "," << playerInfo.teamId << "," << playerInfo.leagueId << ","
        //      << playerInfo.playerId << "," << playerInfo.salary << "," << playerInfo.firstName << ","
        //      << playerInfo.lastName << "," << playerInfo.birthYear << "," << playerInfo.birthCountry << ","
        //      << playerInfo.weight << "," << playerInfo.height << "," << playerInfo.bats << "," << playerInfo.throws
        //      << endl;
    }
}

int main(int argc, const char * argv[]) {
    
    string dmenu =  "1. Query hash table\n"
                    "2. Quit program\n";
    
    string help = "usage: $executable [input file] [hashtable size]\n"
                  "example: $exe PlayerData.txt 5024";
    
    if (argc < 3) {
        cout << "Missing arguments to the program!" << endl;
        die(help);
    }
    
    int choice = 0;
    bool done = false;
    
    string filename {argv[1]};
    int hashSize = stoi(argv[2]);
    
    HashTable* map = new HashTable(hashSize);
    
    // read the file and populate the map
    PopulateHashTable(filename, map);

    do {
        cout << dmenu;
        cin >> choice;
        
        // flush the newlines and other characters
        cin.clear();
        cin.ignore();
        
        switch (choice) {
            case 1:
            {
            }
                
            case 2:
            {
                done = true;
                break;
            }
            
            default:
            {
                // ignore unrecognized input.
                // and let program continue.
            }
        }
        
    } while(!done);
    
    cout << "Goodbye!" << endl;
    delete map;
    return 0;
}
