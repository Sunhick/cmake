//
//  Utilities.cpp
//  HashTables
//
//  Created by Sunil on 4/28/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#include "Utilities.hpp"

#include <sstream>

PlayerInfo Utilities::ConstructFrom(string line) {
    stringstream lineStream(line);
    
    // Format of the line:
    // yearID : int
    // teamID : int
    // leagueID : int
    // playerID : int
    // salary : float
    // firstName : string
    // lastName : string
    // birthYear : string
    // birthCountry : string
    // weight : float
    // height : float
    // bats : int
    // throws : int
    
    int yearId;
    char bats, throws;
    float salary, weight, height;
    string teamId, playerId, leagueId, firstName, lastName, birthYear, birthCountry;
    char ignoreComma;
    
    lineStream >> yearId;       lineStream >> ignoreComma;
    // lineStream >> teamId;       lineStream >> ignoreComma;
    std::getline(lineStream, teamId, ',');
    // lineStream >> leagueId;     lineStream >> ignoreComma;
    std::getline(lineStream, leagueId, ',');
    // lineStream >> playerId;     lineStream >> ignoreComma;
    std::getline(lineStream, playerId, ',');
    lineStream >> salary;       lineStream >> ignoreComma;
    // lineStream >> firstName;    lineStream >> ignoreComma;
    std::getline(lineStream, firstName, ',');
    // lineStream >> lastName;     lineStream >> ignoreComma;
    std::getline(lineStream, lastName, ',');
    // lineStream >> birthYear;    lineStream >> ignoreComma;
    std::getline(lineStream, birthYear, ',');
    // lineStream >> birthCountry; lineStream >> ignoreComma;
    std::getline(lineStream, birthCountry, ',');
    lineStream >> weight;       lineStream >> ignoreComma;
    lineStream >> height;       lineStream >> ignoreComma;
    lineStream >> bats;         lineStream >> ignoreComma;
    lineStream >> throws;
    
    return {
        .yearId = yearId,
        .teamId = teamId,
        .leagueId = leagueId,
        .playerId = playerId,
        .salary = salary,
        .firstName = firstName,
        .lastName = lastName,
        .birthYear = birthYear,
        .birthCountry = birthCountry,
        .weight = weight,
        .height = height,
        .bats = bats,
        .throws = throws
    };
}
