//
// A symtable unit test based on Catch framework
//
// << Tanmay Sarin >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(3)testing exitScope function")
{
    symtable<string, string> table;
    string symbol;
    
    REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);
    
    REQUIRE_THROWS(table.exitScope());
    
    table.enterScope("global"); //Enter and make a new scope
  
    table.insert("i", "int");
    table.insert("j", "double");
  
    table.enterScope("CURRENT"); //Enter a new scope
    
    table.insert("k", "char"); //Insert values in the scope
  
    REQUIRE(table.size() == 3);
    REQUIRE(table.numscopes() == 2);
    
    table.exitScope(); //Exit the scope
    
    REQUIRE(table.size() == 2);
    REQUIRE(table.numscopes() == 1);
     
}