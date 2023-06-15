// Author: Thu Vu
// Protector.cpp

#include "Protector.hpp"
#include "Noble.hpp"
#include <iostream>
using namespace std;

namespace WarriorCraft {

// PROTECTOR METHOD DEFINITIONS
// -----------------------------
// Constructor: takes in a name(string) and strength(double) - initialize name
// and strength, initialize lord to nullptr
Protector::Protector(const string& name, double strength) : name(name),
strength(strength), lord(nullptr) {}

// -------
// Getters
// -------

// getName: takes in nothing - return name
const string& Protector::getName() const { return name; }

// getLordName: takes in nothing - return name of Lord
const string& Protector::getLordName() const { return lord->getName(); }

// getStrength: takes in nothing - return strength
double Protector::getStrength() const { return strength; }

// isDead: takes in nothing - return true if strength = 0 - else return false
bool Protector::isDead() const { return strength == 0; }

// isHired: takes in nothing - return true if lord is not nullptr - else false
bool Protector::isHired() const { return lord; }

// -------------
// Other methods
// -------------

// setLord: takes in a pointer to Lord - set lord to that pointer
// - return nothing
void Protector::setLord(Lord* lordPtr) { lord = lordPtr; }

// reduceStrengthBy: takes in a double ratio - reduce strength by that ratio
// return nothing
void Protector::reduceStrengthBy(double ratio) { strength *= 1 - ratio; }

// runaway: takes in nothing - if is hired, remove Protector from army, set
// lord to nullptr, print result and return true - else print error message
// and return false
bool Protector::runaway() {
    if (isHired()) {
        cout << name << " flees in terror, abandoning his lord, "
        << getLordName() << endl;
        lord->removeProt(*this);
        lord = nullptr;
        return true;
    }
    cerr << name << " cannot runaway because he is not hired!" << endl;
    return false;
}

// ===================
// OVERRIDING DEFEND()
// -----------------------------------
// Wizard override version of defend()
// -----------------------------------
// defend: takes in nothing - print defend line if Wizard is not dead
// - return nothing
void Wizard::defend() const {
    if (!isDead()) {
        cout << "POOF!" << endl;
    }
}

// ------------------------------------
// Warrior override version of defend()
// ------------------------------------
// defend: takes in nothing - print common defend line for all Warriors if not
// dead - return nothing
void Warrior::defend() const {
    cout << getName() << " says: Take that in the name of my lord, "
    << getLordName() << endl;
}

// -----------------------------------
// Archer override version of defend()
// -----------------------------------
// defend: takes in nothing - print Archer defend line before Warrior line
// - return nothing
void Archer::defend() const {
    if (!isDead()) {
        cout << "TWANG!\t";
        Warrior::defend();
    }
}

// --------------------------------------
// Swordsman override version of defend()
// ---------------------------------------
// defend: takes in nothing - print Swordsman defend line before Warrior
// line - return nothing
void Swordsman::defend() const {
    if (!isDead()) {
        cout << "CLANG!\t";
        Warrior::defend();
    }
}

// ===============
// Output operator
ostream& operator<<(ostream& os, const Protector& prot) {
    cout << prot.name << ": " << prot.strength;
    return os;
}
}
