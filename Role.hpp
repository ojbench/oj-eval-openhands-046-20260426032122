#include <string>
#include <iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{

    class Fighter;
    class Protector;
    class Caster;

    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        // WARNING: NO OTHER MEMBER VARIABLE IS ALLOWED TO BE ADDED HERE.
        std::string name;
        int health, attack;
        bool alive, defensive;
        // special member variable to represent current alive count
        inline static int aliveNumber = 0;
    public:
        // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        // WARNING: THIS CLASS(Base) CAN NOT BE INSTANTIATED.
        // the function you need to implement or define is as follows.
        // (1) getAliveNumber
        // (2) Constructor
        // (3) launch_attack
        // (4) defend
        static int getAliveNumber(){ return aliveNumber; }

        bool isAlive(){ return alive; }
        bool isDefensive(){ return defensive; }

        virtual void launch_attack(Base* target) = 0;
        virtual void defend(bool flag) = 0;

        virtual ~Base(){ if (alive) --aliveNumber; }
    protected:
        Base(const std::string& n, const int h, const int a)
            : name(n), health(h), attack(a), alive(true), defensive(false) { ++aliveNumber; }
    };

    class Fighter:public Base{
    public:
        // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = true;
                health += 3;
                attack += 2;
            } else {
                defensive = false;
            }
        }
    };

    class Protector:public Base{
    public:
        // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = true;
                health += 7;
                attack += 1;
            } else {
                defensive = false;
            }
        }
    };

    class Caster:public Base{
    public:
        // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = true;
                health += 5;
            } else {
                defensive = false;
            }
        }
    };

    void Fighter::launch_attack(Base *target) {
        int mult = (dynamic_cast<Caster*>(target) != nullptr) ? 2 : 1;
        int raw = attack * mult;
        if (!target->defensive) {
            target->health -= raw;
        } else {
            int dmg = raw - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            // reflect damage to attacker (Fighter takes reflect)
            health -= target->attack;
        }
        if (target->alive && target->health <= 0) {
            target->alive = false;
            --aliveNumber;
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed\n";
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed\n";
            } else {
                std::cout << "Caster " << target->name << " is killed\n";
            }
        }
        if (alive && health <= 0) {
            alive = false;
            --aliveNumber;
            // when both die, target is printed first already
            std::cout << "Fighter " << name << " is killed\n";
        }
    }

    void Protector::launch_attack(Base *target) {
        int mult = (dynamic_cast<Fighter*>(target) != nullptr) ? 2 : 1;
        int raw = attack * mult;
        if (!target->defensive) {
            target->health -= raw;
        } else {
            int dmg = raw - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            // reflect damage to attacker (Protector takes reflect)
            health -= target->attack;
        }
        if (target->alive && target->health <= 0) {
            target->alive = false;
            --aliveNumber;
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed\n";
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed\n";
            } else {
                std::cout << "Caster " << target->name << " is killed\n";
            }
        }
        if (alive && health <= 0) {
            alive = false;
            --aliveNumber;
            std::cout << "Protector " << name << " is killed\n";
        }
    }

    void Caster::launch_attack(Base *target) {
        int mult = (dynamic_cast<Protector*>(target) != nullptr) ? 2 : 1;
        int raw = attack * mult;
        if (!target->defensive) {
            target->health -= raw;
        } else {
            int dmg = raw - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            // Caster does not take reflect damage
        }
        if (target->alive && target->health <= 0) {
            target->alive = false;
            --aliveNumber;
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed\n";
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed\n";
            } else {
                std::cout << "Caster " << target->name << " is killed\n";
            }
        }
        if (alive && health <= 0) {
            alive = false;
            --aliveNumber;
            std::cout << "Caster " << name << " is killed\n";
        }
    }
}
#endif //ROLE_HPP
