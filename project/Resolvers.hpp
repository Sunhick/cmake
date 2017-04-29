//
//  CollisionResolver.hpp
//  HashTables
//
//  Created by Sunil on 4/28/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#ifndef Resolver_hpp
#define Resolver_hpp

#include "HashTable.hpp"
#include "CollisionResolver.hpp"

// open addressing (using linear probing)
class LinearProbingResolver : public CollisionResolver {
public:
    virtual void add(HashEntry**& table, HashEntry* entry, int index) override;
    virtual PlayerInfo* get(HashEntry**& table, string key, int index) override;
    virtual void Delete(HashEntry* entry) override;
    
    virtual ~LinearProbingResolver();
};

// collsion resolution using chaining
class ChainingResolver : public CollisionResolver {
public:
    virtual void add(HashEntry**& table, HashEntry* entry, int index) override;
    virtual PlayerInfo* get(HashEntry**& table, string key, int index) override;
    virtual void Delete(HashEntry* entry) override;
    
    virtual ~ChainingResolver();
};

#endif /* Resolver_hpp */
