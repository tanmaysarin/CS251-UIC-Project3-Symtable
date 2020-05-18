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


TEST_CASE("(2)testing insert function")
{
    symtable<string, string> table;
    string symbol;
    
    REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);    
    
    table.enterScope("global");
    REQUIRE(!table.lookup("k", symbol)); //Check the case when there is no element
    
    table.insert("i", "int");
    table.insert("j", "double"); //Check if insert is actually inserting
  
    REQUIRE(table.size() == 2);
    REQUIRE(table.numscopes() == 1); //Check the number of elements in the scope and the deque
    
    table.insert("i", "double"); //Test to replace the exisiting variable int i
    
    REQUIRE(table.size() == 2);
    REQUIRE(table.numscopes() == 1); //Check the number of elements in the scope and the deque have not increased
    
    REQUIRE(table.lookup("i", symbol)); //This should return true
    REQUIRE(symbol == "double");
    
    REQUIRE(table.lookup("i", symbol)); //This should return false because int i was replaced with double i
    REQUIRE(symbol != "int");
    
    table.enterScope("CURRENT"); //Enter a new scope
    table.insert("string1", "int");
    REQUIRE(!table.lookup("string1", symbol, symtable<string,string>::ScopeOption::GLOBAL)); //its not in the scope
    
}