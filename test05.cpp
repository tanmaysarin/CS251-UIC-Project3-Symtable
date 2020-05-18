//
// A symtable unit test based on Catch framework
//
// << Tanmay Sarin >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>

#include<string>

#include "symtable.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("(5)dynamic testing")
{
    symtable<int, int> table; // define the table
    
    int j;
    int i;
    
    for(i=0; i < 100; i++){
        table.enterScope(to_string(i)); //enter the scopes
        for(j=0; j< 100; j++){
            table.insert(j, j); //insert value in the scope
        }
        REQUIRE(table.numscopes() == i+1);
        REQUIRE(table.size() == (i+1)*100);
        
        table.exitScope(); //exit the scope and remove it
        table.enterScope(to_string(i)); //enter a new scope
        REQUIRE(table.numscopes() == i+1);
        for(j=0; j< 100; j++){
            table.insert(j, j); //insert values in the scope
        }
        REQUIRE(table.size() == (i+1)*100);
    }
}