// Author: Thu Vu
// Noble.cpp

#include "Noble.hpp"
#include "Protector.hpp"
#include <iostream>
using namespace std;

namespace WarriorCraft {

// ========================
// NOBLE METHOD DEFINITIONS
// Constructor: takes in a name(string), strength(double) - initialize name and
// strength, initialize dead to false
Noble::Noble(const string& name, double strength) : name(name),
strength(strength), dead(false) {}

// ----------------
// Virtual methods
// ----------------
// die: takes in nothing - set strength to 0 and dead to true
// - return nothing
void Noble::die() {
    strength = 0;
    dead = true;
}

// wonAgainst: takes in a Noble nob - decrease the strength by that of nob
// make nob die and print out result - return nothing
void Noble::wonAgainst(Noble& nob) {
    strength -= nob.strength;
    nob.die();
    cout << name << " defeats " << nob.name << endl;
}

// display: takes in nothing - output Noble name and strength - return nothing
void Noble::display() const {
    cout << "Noble " << name << " has a strength of " << strength << endl;
}

// -------
// Getters
// -------
// isDead: takes in nothing - return dead status
bool Noble::isDead() const { return dead; }

// getName: takes in nothing - return the name
const string& Noble::getName() const { return name; }

// getStrength: takes in nothing - return strength
double Noble::getStrength() const { return strength; }

// -------
// Setters
// -------
// addStrength: takes in a double val - add val to strength
// return nothing
void Noble::addStrength(double val) { strength += val; }

// --------------
// Battle methods
// --------------
// bothDie: takes in a Noble nob - make Noble and nob die, print result
// return nothing
void Noble::bothDie(Noble& nob) {
    die();
    nob.die();
    cout << "Mutual Annihilation: " << name << " and " << nob.name <<
    " die at each other's hands" << endl;
}

// battle: takes in a Noble nob - display battle status, if both Nobles are
// dead, print result - else make both Nobles fight
// if one is dead, print result; if same strength, both die
// if one has more strength than the other, whoever has more strength wins
// - return nothing
void Noble::battle(Noble& nob) {
    cout << name << " battles " << nob.name << endl;
    // if both dead - announce result
    if (dead && nob.dead) {
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        // if one is dead - announce result
    } else {
        fight();
        nob.fight();
        if (dead && !nob.dead) {
            cout << "He's dead, " << nob.name << endl;
        } else if (!dead && nob.dead) {
            cout << "He's dead, " << name << endl;
            // if same strength - make they both die and announce result
        } else if (strength == nob.strength) {
            bothDie(nob);
        } else if (strength > nob.strength) {
            wonAgainst(nob);
        } else {
            nob.wonAgainst(*this);
        }
    }
}

// =======================
// LORD METHOD DEFINITIONS
// -------
// Getters
// -------
// getProtInd: takes in a Protector prot - return index of prot in army if
// found - else return the size of the army
size_t Lord::getProtInd(const Protector& prot) const {
    // loop through army, return the index of prot if found
    for (size_t i = 0; i < army.size(); ++i) {
        if (army[i] == &prot) {
            return i;
        }
    }
    return army.size();
}

// hasProt: takes in a Protector prot - return true if prot is found in
// army - else return false
bool Lord::hasProt(const Protector& prot) const {
    if (getProtInd(prot) != army.size()) {
        return true;
    }
    return false;
}

// --------
// Helpers
// --------
// removeProt: takes in a Protector prot - if prot is found in army, remove
// prot from army, decrease strength of prot from army and return true
// - else return false
bool Lord::removeProt(Protector& prot) {
    // if army has prot, decrease strength of army and remove prot
    if (hasProt(prot)) {
        size_t ind = getProtInd(prot);
        addStrength(-prot.getStrength());
        // if prot is not at the end of the army, push it to the end then
        // remove prot
        if (ind != army.size() - 1) {
            for (size_t j = ind; j < army.size() - 1; ++j) {
                army[j] = army[j + 1];
            }
        }
        army.pop_back();
        return true;
    }
    return false;
}

// ----------------
// Hires and fires
// ----------------
// hires: takes in a Protector prot - if Lord is not dead and prot is not
// hired, add prot and his strength to army, set Lord pointer to this
// - return true - else print error message and return false
bool Lord::hires(Protector& prot) {
    if (isDead() || prot.isHired()) {
        cerr << getName() << " failed to hire " << prot.getName() << endl;
        return false;
    } else {
        cout << getName() << " hired " << prot.getName() << endl;
        army.push_back(&prot);
        prot.setLord(this);
        addStrength(prot.getStrength());
        return true;
    }
}

// fires: takes in a Protector prot - if Lord is not dead and prot is in
// army - remove prot from army, print result and return true
// - else print error message and return false
bool Lord::fires(Protector& prot) {
    if (!isDead() && hasProt(prot)) {
        removeProt(prot);
        prot.setLord(this);
        cout << "You don't work for me anymore " << prot.getName()
        << "! -- " << getName() << "." << endl;
        return true;
    }
    cerr << getName() << " failed to fire " << prot.getName() << endl;
    return false;
}

// ----------------
// Override methods
// ----------------
// wonAgainst: takes in a Noble nob - decrease strength of each Protector
// in army by ratio of strength of nob/Lord - call Noble wonAgainst()
// - return nothing
void Lord::wonAgainst(Noble& nob) {
    // loop through the army, reduce strength of each Protector by ratio of
    // nob strength / Lord strength
    for (size_t i = 0; i < army.size(); ++i) {
        army[i]->reduceStrengthBy(nob.getStrength() / getStrength());
    }
    Noble::wonAgainst(nob);
}

// die: takes in nothing - set each Protector strength in the army to 0,
// call Noble die() - return nothing
void Lord::die() {
    // loop through the army, set strength of each Protector to 0
    for (size_t i = 0; i < army.size(); ++i) {
        army[i]->reduceStrengthBy(1);
    }
    Noble::die();
}

// display: takes in nothing - display Lord name and each Protector in army
// - return nothing
void Lord::display() const {
    cout << "Lord " << getName() << " has an army of " << army.size() << endl;
    for (size_t i = 0; i < army.size(); ++i) {
        cout << "\t" << *army[i] << endl;
    }
}

// ===================
// OVERRIDING FIGHT()
// -----------------------------------
// Lord override version of fight()
// -----------------------------------
// fight: takes in nothing - if Lord is not dead, make each Protector in the
// army defend - return nothing
void Lord::fight() const {
    if (!isDead()) {
        // loop through the army, call defend() on each Protector
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->defend();
        }
    }
}

// -----------------------------------------------------
// PersonWithStrengthToFight override version of fight()
// -----------------------------------------------------
// fight: takes in nothing - if Noble is not dead, print out fight line
// - return nothing
void PersonWithStrengthToFight::fight() const {
    if (!isDead()) {
        cout << "Ugh!" << endl;
    }
}

// ===============
// Output operator
ostream& operator<<(ostream&os, const Noble& nob) {
    nob.display();
    return os;
}
}
