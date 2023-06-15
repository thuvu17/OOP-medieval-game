// Author: Thu Vu
// hw07.cpp

#include "Protector.hpp"
#include "Noble.hpp"
#include <iostream>
using namespace std;
using namespace WarriorCraft;

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    
    cout << "\n================ Initial Status ===============" << endl;
    cout << sam << endl
    << joe << endl;
    cout << "===============================================\n";
    
    // First battle
    joe.battle(randy);
    joe.battle(sam);
    
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    
    // Result 1
    cout << "\n================ After first battle ===============" << endl;
    cout << sam << endl
     << joe << endl
     << janet << endl
    << barclay << endl;
    cout << "===============================================\n";
    
    // Second battle
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    
    // Result 2
    cout << "\n================ After second battle ===============" << endl;
    cout << sam << endl
     << joe << endl
     << janet << endl
    << barclay << endl;
    cout << "===============================================\n";
    
    // Last battle
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
    
    // Final status
    cout << "\n================ Final Status ===============" << endl;
    cout << sam << endl
     << joe << endl
     << janet << endl
    << barclay << endl;
}
