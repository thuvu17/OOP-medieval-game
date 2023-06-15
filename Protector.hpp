// Author: Thu Vu
// Protector.hpp

#ifndef Protector_hpp
#define Protector_hpp

#include <string>

namespace WarriorCraft {

// Forward declaration
class Lord;

// Class Protector is an abstract class
class Protector {
    friend std::ostream& operator<<(std::ostream& os, const Protector& prot);
public:
    // Constructor
    Protector(const std::string& name, double strength);
    
    // Getters
    const std::string& getName() const;
    const std::string& getLordName() const;
    double getStrength() const;
    bool isDead() const;
    bool isHired() const;

    // Setters
    void setLord(Lord* lordPtr);
    void reduceStrengthBy(double ratio);
    
    // Other method
    bool runaway();
    
    // Abstract method
    virtual void defend() const = 0;
    
// Protector fields: string for name, double for strength, a pointer to a Lord
private:
    std::string name;
    double strength;
    Lord* lord;
};

// ============================
// Derived classes of Protector
// ------------------------------------
// Class Wizard inherits from Protector
class Wizard : public Protector {
public:
    // Using Protector constructor
    using Protector::Protector;
    
    // Define abstract method
    void defend() const override;
};

// ------------------------------------------------------------
// Class Warrior inherits from Protector - is an abstract class
class Warrior : public Protector {
public:
    // Using Protector constructor
    using Protector::Protector;
    
    // Abstract method
    virtual void defend() const = 0;
};

// ==========================
// Derived classes of Warrior
// ----------------------------------
// Class Archer inherits from Warrior
class Archer : public Warrior {
public:
    // Using Warrior constructor
    using Warrior::Warrior;
    
    // Define abstract method
    void defend() const override;
};

// -------------------------------------
// Class Swordsman inherits from Warrior
class Swordsman : public Warrior {
public:
    // Using Warrior constructor
    using Warrior::Warrior;
    
    // Define abstract method
    void defend() const override;
};
}
#endif
