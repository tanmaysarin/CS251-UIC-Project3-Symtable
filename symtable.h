/*symtable.h*/

// 
// << TANMAY SARIN >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #03: symtable
//
// Symbol Table: a symbol table is a stack of scopes, typically used by a
// compiler to keep track of symbols in a program (functions, variables,
// types, etc.).  In most programming languages, you "enter scope" when you 
// see {, and "exit scope" when you see the corresponding }.  Example:
//
// int main()
// {              <-- enterScope()
//    int i;      <-- enter "i" into symbol table as type "int"
//    .
//    .
//    while (true)
//    {              <-- enterScope()
//       char i;     <-- enter "i" into symbol table as type "char"
//
// Notice there are two variables named "i", which is legal because
// they are in different scopes.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>

using namespace std;

template<typename KeyT, typename SymbolT>
class symtable
{
public:
  //
  // A symbol table is a stack of scopes.  Every scope has a name, and 
  // we use a map to hold the symbols in that scope.  You can *add* to
  // this class, but you must use the Name and Symbols as given to store
  // the scope name, and scope symbols, respectively.
  //
  class Scope
  {
  public:
    string              Name;
    map<KeyT, SymbolT>  Symbols;

    // constructors:
    Scope()
    {
      // default empty string and an empty map:
    }

    Scope(string name)
    {
      this->Name = name;
      // empty map created by map's constructor:
    }
  };

private:
  //
  // TODO: implementation details
  //
    deque <Scope> mydeque; //define a deque which stores the "Scope" in it...
    int number; //for size

public:
  enum class ScopeOption
  {
    ALL, 
    CURRENT,
    GLOBAL
  };

  //
  // default constructor:
  //
  // Creates a new, empty symbol table.  No scope is open.
  //
  symtable()
  {
    //
    // TODO: note that member variables will have their default constructor 
    // called automatically, so there may be nothing to do here.
    //
    number = 0;
  }

  //
  // size
  //
  // Returns total # of symbols in the symbol table.
  //
  // Complexity: O(1)
  //
  int size() const
  {
    return number; //Return the number of maps in a Scope...
  }

  //
  // numscopes
  //
  // Returns the # of open scopes.
  //
  // Complexity: O(1)
  //
  int numscopes() const
  {
    return mydeque.size(); //because each deque stores one scope object...
  }

  //
  // enterScope
  //
  // Enters a new, open scope in the symbol table, effectively "pushing" on
  // a new scope.  You must provide a name for the new scope, although
  // the name is currently used only for debugging purposes.
  //
  // NOTE: the first scope you enter is known as the GLOBAL scope, since this
  // is typically where GLOBAL symbols are stored.  
  //
  // Complexity: O(1)
  //
  void enterScope(string name)
  {
    Scope Scope1;
    Scope1.Name = name; //Setting the name of the new scope to the name input given by the user...
    mydeque.push_back(Scope1); //pushing the scope name to the back of the deque ...
  }

  //
  // exitScope
  //
  // Exits the current open scope, discarding all symbols in this scope.
  // This effectively "pops" the symbol table so that it returns to the 
  // previously open scope.  A runtime_error is thrown if no scope is 
  // currently open.  
  //
  // Complexity: O(1)
  //
  void exitScope()
  {
    if(mydeque.size() == 0)
        throw runtime_error("No scope currently open");
    
    number = number - this->curScope().Symbols.size();
    
    mydeque.pop_back(); //Deleting the last added scope from the deque...
  }

  //
  // curScope
  //
  // Returns a copy of the current scope.  A runtime_error is thrown if
  // no scope is currently open.
  //
  // Complexity: O(N) where N is the # of symbols in the current scope
  //
  Scope curScope() const
  {
    
    if(mydeque.size() == 0){
        throw runtime_error("No Scope is currently open");
    }
    
    Scope temp; //Make a temprorary scope
    temp.Name = mydeque.back().Name; //Change the name of the temp scope to that of the current scope..
    
    
    for(auto map : mydeque.back().Symbols){
        temp.Symbols.emplace(map); //Initialize all the scopes in the deque to the temp(current) scope...
    }
    
    return temp; //Returns a copy of the current scope with a copy of the contents of the original current scope.. 
  }

  //
  // insert
  //
  // Inserts the (key, symbol) pair in the *current* scope.  If the key
  // already exists in the current scope, the associated symbol is replaced
  // by this new symbol.
  //
  // Complexity: O(lgN) where N is the # of symbols in current scope
  //
  void insert(KeyT key, SymbolT symbol)
  {
    if(mydeque.size() == 0){
        return;
    }
      
    if(mydeque.back().Symbols.count(key)==0){
        mydeque.back().Symbols.emplace(key, symbol); //Add the elements to a map in the front scope if the elements are different
        number++; //Increase the number of elements added to the symtable
    }
    else{
        mydeque.back().Symbols.at(key) = symbol; //Change the symbol of the key if another key with the same name is present...
    }
  }

  //
  // lookup
  //
  // Searches the symbol table for the first (key, symbol) pair that 
  // matches the given key.  The search starts in the current scope, and 
  // proceeds "outward" to the GLOBAL scope.  If a matching (key, symbol)
  // pair is found, true is returned along with a copy of the symbol (via 
  // "symbol" reference parameter).  If not found, false is returned and
  // the "symbol" parameter is left unchanged.
  //
  // NOTE: the search can be controlled by the "option" parameter.  By 
  // default, the entire symbol table is searched as described above.
  // However, the search can also be limited to just the current scope, 
  // or just the GLOBAL scope, via the "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   string                   symbol;
  //   bool                     found;
  //   ...
  //   found = table.lookup("i", 
  //                        symbol, 
  //                        symtable<string,string>::ScopeOption::CURRENT);
  //
  // Complexity: O(SlgN) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  bool lookup(KeyT key, 
              SymbolT& symbol, 
              ScopeOption option = ScopeOption::ALL) const
  {
    if(option == ScopeOption::CURRENT){
        if(mydeque.back().Symbols.count(key) == 1){ //The required key is present in the CURRENT scope
            symbol = mydeque.back().Symbols.at(key); //Return the sumbol of the found key
            return true;
        }
    }else if(option == ScopeOption::ALL){
        for(int i = mydeque.size()-1; i >= 0; i--){
            if(mydeque[i].Symbols.count(key) == 1){ //The required key is present in the ALL scope
                symbol = mydeque[i].Symbols.at(key); //Return the sumbol of the found key
                return true;
            }
        }
    }else if(option == ScopeOption::GLOBAL){   
        if(mydeque.front().Symbols.count(key) == 1){  //The required key is present in the GLOBAL scope
            symbol = mydeque.front().Symbols.at(key); //Return the sumbol of the found key
            return true;
        }
    }
    return false; //If the lookup failed
  }

  //
  // dump
  // 
  // Dumps the contents of the symbol table to the output stream, 
  // starting with the current scope and working "outward" to the GLOBAL
  // scope.  You can dump the entire symbol table (the default), or dump
  // just the current scope or global scope; this is controlled by the 
  // "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   ...
  //   table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
  //
  // Complexity: O(S*N) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  void dump(ostream& output, ScopeOption option = ScopeOption::ALL) const
  {
    output << "**************************************************" << endl;
    


    if (option == ScopeOption::ALL)
    {
        output << "*************** SYMBOL TABLE (ALL) ***************" << endl;
        output << "** # of scopes: " << this->numscopes() << endl;
        output << "** # of symbols: " << this->size() << endl;
        for(int i = mydeque.size() - 1; i >= 0; i--) //Loop through all the elements of the deque
        {
            output << "** " << mydeque[i].Name << " **" << endl;
            for(auto map: mydeque[i].Symbols) //Loop throuh all the maps in an element
            {
                output << map.first << ": " << map.second << endl;
            }
        }
    }
    
    else if (option == ScopeOption::CURRENT)
    {
        output << "*************** SYMBOL TABLE (CUR) ***************" << endl;
        output << "** # of scopes: " << this->numscopes() << endl;
        output << "** # of symbols: " << this->size() << endl;
        output << "** " << mydeque.back().Name << " **" << endl;
        for(auto map : mydeque.back().Symbols) //Loop through the current scope...
        {
            output << map.first << ": " << map.second << endl;
        }
    }
      
    else // global:
    {
        output << "*************** SYMBOL TABLE (GBL) ***************" << endl;
        output << "** # of scopes: " << this->numscopes() << endl;
        output << "** # of symbols: " << this->size() << endl;
        output << "** " << mydeque.front().Name << " **" << endl;
        for(auto map : mydeque.front().Symbols) //Loop though the global(first) scope...
        {
            output << map.first << ": " << map.second << endl;
        }
    }

    
    //
    // output format per scope:
    //
    // ** scopename **
    // key: symbol
    // key: symbol
    // ...
    //

    output << "**************************************************" << endl;
  }

};
