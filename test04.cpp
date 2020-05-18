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

TEST_CASE("(4)testing curScope function and the lookup fucntion")
{
    symtable<string, string> table;
    //symtable<string, string>::Scope scope = table.curScope();
    string symbol;
    
    REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);
    
    table.enterScope("global");
    REQUIRE(table.curScope().Name == "global"); //checks if curScope() is returned correctly

  
    table.insert("i", "int");
    table.insert("j", "double");
    
    REQUIRE(table.lookup("i",symbol, symtable<string,string>::ScopeOption::GLOBAL));
  
    table.enterScope("ABC"); //Enter a new scope
    REQUIRE(table.curScope().Name == "ABC"); //checks if curScope() is returned correctly
    
    table.insert("k", "char");
    table.insert("string1", "string");
    
    REQUIRE(table.lookup("string1",symbol, symtable<string,string>::ScopeOption::CURRENT)); //Look for the key in the specified scope
    
    table.enterScope("A");
    table.insert("a", "float");
    table.insert("b", "double");
    
    table.enterScope("B");
    table.insert("c", "char");
    table.insert("d", "int");
    
    REQUIRE(table.lookup("b",symbol, symtable<string,string>::ScopeOption::ALL)); //Look for the key in the specified scope
}    