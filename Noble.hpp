// Author: Thu Vu
// Noble.hpp

#ifndef Noble_hpp
#define Noble_hpp

#include <string>
#include <vector>

namespace WarriorCraft {

// Forward declaration
class Protector;

// ================================
// class Noble is an abstract class
class Noble {
    friend std::ostream& operator<<(std::ostream& os, const Noble& nob);
public:
    // Constructor
    Noble(const std::string& name, double strength = 0);
    
    // Virtual methods
    virtual void fight() const = 0;
    virtual void die();
    virtual void wonAgainst(Noble& nob);
    virtual void display() const;

    // Getters
    bool isDead() const;
    const std::string& getName() const;
    double getStrength() const;
    
    // Setters
    void addStrength(double val);
    
    // Other methods
    void bothDie(Noble& nob);
    void battle(Noble& nob);

// Noble private fields: name(string), strength(double), dead(bool)
private:
    std::string name;
    double strength;
    bool dead;
};

// ========================
// Derived classes of Noble

// Class Lord inherits from Noble
class Lord : public Noble {
public:
    // Using Noble constructor
    using Noble::Noble;
    
    // Helper
    bool removeProt(Protector& prot);
    
    // Getters
    size_t getProtInd(const Protector& prot) const;
    bool hasProt(const Protector& prot) const;

    
    // Hire and fire
    bool hires(Protector& prot);
    bool fires(Protector& prot);
    
    // Override methods
    void wonAgainst(Noble& nob) override;
    void die() override;
    void display() const override;

    
    // Define abstract method
    void fight() const override;
    
// Lord private field: a vector of pointers to Protectors
private:
    std::vector<Protector*> army;
};

// Class PersonWithStrengthToFight inherits from Noble
class PersonWithStrengthToFight : public Noble {
public:
    // Using Noble constructor
    using Noble::Noble;
    
    // Define abstract method
    void fight() const override;
};
}

#endif
