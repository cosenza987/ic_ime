#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <bitset>
#include <utility>
#include <algorithm>
#include <random>
#include <memory>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, INT_MAX);
std::uniform_real_distribution<> ddistrib(0, 1);

class Soldado {
    std::string name;
    double health, power, block, avoid, cattack;
public:
    Soldado(std::string name_, double health_, double power_, double block_, double avoid_, double cattack_) : name(name_), health(health_), power(power_), block(block_), avoid(avoid_), cattack(cattack_) {}
    Soldado(const Soldado &a) {
        *this = a;
    }
    double getCounterAttack() {
        return cattack;
    }
    double getBlock() {
        return block;
    }
    double getAvoid() {
        return avoid;
    }
    double getHealth() {
        return health;
    }
    double attackPower() {
        return power;
    }
    std::string getName() {
        return name;
    }
    virtual void defend(Soldado &a, double mul = 1) {
        double attackPower = a.attackPower() * ddistrib(gen);
        double random = ddistrib(gen);
        double percent = 1.0 - random * block;
        random = ddistrib(gen);
        if(random <= avoid) {
            std::cout << this->getName() << " avoided the attack from " << a.getName() << "\n";
            return;
        }
        random = ddistrib(gen);
        this->health -= mul * attackPower * percent;
        std::cout << a.getName() << " attacked " << this->getName() << ", dealing " << attackPower << " points of health. Now, " << this->getName() << " has " << std::max(0.0, this->getHealth()) << " health points.\n";
        if(random <= cattack and this->health > 0) {
            std::cout << this->getName() << " counter-attacked!\n";
            a.defend(*this);
        }
    }
    virtual void attack(Soldado &a) {
        a.defend(*this);
    }
    virtual std::string getType() {
        return "Soldado";
    }
    bool died() {
        return health <= 0;
    }
};

// new definition of blocking, rnd * block = percent that is not taken

// 5% block stat, 15% chance of avoiding, 10% chance of counter-attacking
class Elf : public Soldado {
public:
    Elf(std::string name_, double health_, double power_, double block_ = 0.05, double avoid_ = 0.15, double cattack_ = 0.1) : Soldado(name_, health_, power_ + 1, block_, avoid_, cattack_) {}
    Elf(const Elf &a) : Soldado(a) {}
    void defend(Soldado &a) {
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        a.defend(*this);
    }
    std::string getType() {
        return "Elf";
    }
};

// 5% block stat, 23% chance of avoiding, 7% chance of counter-attacking
class Dwarf : public Soldado {
public:
    Dwarf(std::string name_, double health_, double power_, double block_ = 0.05, double avoid_ = 0.23, double cattack_ = 0.07) : Soldado(name_, health_, power_ + 20, block_, avoid_, cattack_) {}
    Dwarf(const Dwarf &a) : Soldado(a) {}
    void defend(Soldado &a) {
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        int x = distrib(gen) % 10;
        if(x < 4) {
            std::cout << this->getName() << " missed the attack on " << a.getName() << "!\n";
            return;
        } else {
            a.defend(*this);
        }
    }
    std::string getType() {
        return "Dwarf";
    }
};

// 15% block stat, 5% chance of avoiding, 15% chance of counter-attacking
class Human : public Soldado {
public:
    Human(std::string name_, double health_, double power_, double block_ = 0.15, double avoid_ = 0.05, double cattack_ = 0.15) : Soldado(name_, health_, power_, block_, avoid_, cattack_) {}
    Human(const Human &a) : Soldado(a) {}
    void defend(Soldado &a) {
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        int x = distrib(gen) % 10;
        a.defend(*this);
        if(x == 0) {
            std::cout << "Double attack!\n";
            a.defend(*this);
        }
    }
    std::string getType() {
        return "Human";
    }
};

// 5% block stat, 15% chance of avoiding, 15% chance of counter-attacking
class Hobbit : public Soldado {
public:
    Hobbit(std::string name_, double health_, double power_, double block_ = 0.05, double avoid_ = 0.15, double cattack_ = 0.15) : Soldado(name_, health_, power_, block_, avoid_, cattack_) {}
    Hobbit(const Hobbit &a) : Soldado(a) {}
    void defend(Soldado &a) {
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        a.defend(*this);
    }
    std::string getType() {
        return "Hobbit";
    }
};

// 20% block stat, 20% chance of avoiding, 20% chance of counter-attacking
class Sauron : public Soldado {
public:
    Sauron(std::string name_, double health_, double power_, double block_ = 0.2, double avoid_ = 0.2, double cattack_ = 0.2) : Soldado(name_, 10 * health_, power_, block_, avoid_, cattack_) {}
    Sauron(const Sauron &a) : Soldado(a) {}
    void defend(Soldado &a) {
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        int x = distrib(gen) % 10;
        a.defend(*this, (x < 3) ? 2 : 1);
    }
    std::string getType() {
        return "Sauron";
    }
};

// 20% block stat, 3% chance of avoiding, 15% chance of counter-attacking
class Orc : public Soldado {
public:
    Orc(std::string name_, double health_, double power_, double block_ = 0.2, double avoid_ = 0.03, double cattack_ = 0.15) : Soldado(name_, health_, power_, block_, avoid_, cattack_) {}
    Orc(const Orc &a) : Soldado(a) {}
    void defend(Soldado &a) {
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        int x = distrib(gen) % 10;
        if(x < 2) {
            a.defend(*this, 2 * 1.1);
        } else {
            a.defend(*this);
        }
    }
    std::string getType() {
        return "Orc";
    }
};

// 10% block stat, 10% chance of avoiding, 5% chance of counter-attacking
// 1.1x more power
class Troll : public Soldado {
public:
    Troll(std::string name_, double health_, double power_, double block_ = 0.1, double avoid_ = 0.1, double cattack_ = 0.05) : Soldado(name_, health_, power_ * 1.1, block_, avoid_, cattack_) {}
    Troll(const Troll &a) : Soldado(a) {}
    void defend(Soldado &a) {
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        a.defend(*this);
    }
    std::string getType() {
        return "Troll";
    }
};

// 5% block stat, 20% chance of avoiding, 5% chance of counter-attacking
class Shadow : public Soldado {
public:
    Shadow(std::string name_, double health_, double power_, double block_ = 0.05, double avoid_ = 0.2, double cattack_ = 0.05) : Soldado(name_, health_, power_, block_, avoid_, cattack_) {}
    Shadow(const Shadow &a) : Soldado(a) {}
    void defend(Soldado &a) {
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        a.defend(*this);
    }
    std::string getType() {
        return "Shadow";
    }
};

// Nosso Wizard tem 30% de chance de ficar invisível e consegue sempre infligir +25%
// 20% block stat, 20% chance of avoiding, 20% chance of counter-attacking
class Wizard : public Soldado {
public:
    Wizard(std::string name_, double health_, double power_, double block_ = 0.2, double avoid_ = 0.2, double cattack_ = 0.2) : Soldado(name_, health_, power_ * 1.25, block_, avoid_, cattack_) {}
    Wizard(const Wizard &a) : Soldado(a) {}
    void defend(Soldado &a) {
        int x = distrib(gen) % 10;
        if(x < 3) {
            std::cout << this->getName() << " became invisible and didn't get attacked by " << a.getName() << "!\n";
            return;
        }
        Soldado::defend(a);
    }
    void attack(Soldado &a) {
        a.defend(*this);
    }
    std::string getType() {
        return "Wizard";
    }
};

void extractFromFile(std::vector<Soldado*> &a, std::vector<Soldado*> &b) {
    std::vector<std::string> names;
    std::ifstream name_extractor("lotrnames.txt");
    while(!name_extractor.eof()) {
        std::string x;
        std::getline(name_extractor, x);
        names.push_back(x);
    }
    std::shuffle(names.begin(), names.end(), gen);
    a.push_back(new Wizard(names.back(), 55, 4));
    names.pop_back();
    b.push_back(new Sauron(names.back(), 10, 2));
    names.pop_back();
    int cura = distrib(gen) % 4, curb = distrib(gen) % 3;
    while((int)names.size() > 1) {
        if(cura == 0) {
            a.push_back(new Elf(names.back(), (distrib(gen) % 10) + 20, (distrib(gen) % 4) + 2));
        } else if(cura == 1) {
            a.push_back(new Dwarf(names.back(), (distrib(gen) % 10) + 15, (distrib(gen) % 3) + 1));
        } else if(cura == 2) {
            a.push_back(new Human(names.back(), (distrib(gen) % 10) + 20, (distrib(gen) % 3) + 2));
        } else {
            a.push_back(new Hobbit(names.back(), (distrib(gen) % 10) + 20, (distrib(gen) % 6) + 2));
        }
        names.pop_back();
        cura = distrib(gen) % 4;
        if(curb == 0) {
            b.push_back(new Orc(names.back(), (distrib(gen) % 10) + 23, (distrib(gen) % 5) + 5));
        } else if(curb == 1) {
            b.push_back(new Troll(names.back(), (distrib(gen) % 10) + 20, (distrib(gen) % 5) + 4));
        } else {
            b.push_back(new Shadow(names.back(), (distrib(gen) % 10) + 25, (distrib(gen) % 4) + 5));
        }
        names.pop_back();
        curb = distrib(gen) % 3;
    }
}

void extractStatsFromFile(std::vector<Soldado*> &a, std::vector<Soldado*> &b) {
    std::ifstream stats_extractor("lotrnamesstats.txt");
    while(!stats_extractor.eof()) {
        std::string type;
        stats_extractor >> type;
        if(type.empty()) break;
        double health, power;
        stats_extractor >> health >> power;
        std::string name;
        std::getline(stats_extractor, name);
        name.erase(name.begin());
        if(type == "Wizard") {
            a.push_back(new Wizard(name, health, power));
        } else if(type == "Elf") {
            a.push_back(new Elf(name, health, power));
        } else if(type == "Dwarf") {
            a.push_back(new Dwarf(name, health, power));
        } else if(type == "Human") {
            a.push_back(new Human(name, health, power));
        } else if(type == "Hobbit") {
            a.push_back(new Hobbit(name, health, power));
        } else if(type == "Sauron") {
            b.push_back(new Sauron(name, health, power));
        } else if(type == "Orc") {
            b.push_back(new Orc(name, health, power));
        } else if(type == "Troll") {
            b.push_back(new Troll(name, health, power));
        } else if(type == "Shadow") {
            b.push_back(new Shadow(name, health, power));
        } else {
            std::cout << "Invalid file input!\n";
            exit(1);
        }
    }
}

void extractManually(std::vector<Soldado*> &a, std::vector<Soldado*> &b) {
    std::set<std::string> s = {"Wizard", "Elf", "Dwarf", "Human", "Hobbit", "Sauron", "Orc", "Troll", "Shadow"};
    std::string type;
    std::cout << "What type of character do you want to insert? The following options are avaliable:\n";
    std::cout << "On the good side: Wizard, Elf, Dwarf, Human, Hobbit\n";
    std::cout << "On the bad side: Sauron, Orc, Troll, Shadow\n";
    while(std::cin >> type) {
        if(s.find(type) == s.end()) {
            std::cout << "Invalid type! Please try again\n";
            continue;
        }
        std::cout << "Insert both health and power values associated to the character.\n";
        double health, power;
        std::cin >> health >> power;
        std::cout << "Insert the name of your character\n";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);
        if(type == "Wizard") {
            a.push_back(new Wizard(name, health, power));
        } else if(type == "Elf") {
            a.push_back(new Elf(name, health, power));
        } else if(type == "Dwarf") {
            a.push_back(new Dwarf(name, health, power));
        } else if(type == "Human") {
            a.push_back(new Human(name, health, power));
        } else if(type == "Hobbit") {
            a.push_back(new Hobbit(name, health, power));
        } else if(type == "Sauron") {
            b.push_back(new Sauron(name, health, power));
        } else if(type == "Orc") {
            b.push_back(new Orc(name, health, power));
        } else if(type == "Troll") {
            b.push_back(new Troll(name, health, power));
        } else if(type == "Shadow") {
            b.push_back(new Shadow(name, health, power));
        }
        int choice;
        std::cout << "Do you want to insert another character? 1 - Yes, 0 - No\n";
        while(std::cin >> choice) {
            if(choice == 1) {
                break;
            } else if(choice == 0) {
                return;
            } else {
                std::cout << "Invalid option, please try again.\n";
            }
        }
        std::cout << "What type of character do you want to insert? The following options are avaliable:\n";
        std::cout << "On the good side: Wizard, Elf, Dwarf, Human, Hobbit\n";
        std::cout << "On the bad side: Sauron, Orc, Troll, Shadow\n";
    }
}

void battle(std::vector<Soldado*> a, std::vector<Soldado*> b) {
    int round = 1;
    while(!a.empty() and !b.empty()) {
        std::cout << "Round " << round++ << "!\n";
        std::vector<Soldado*> na, nb;
        while(!a.empty() and !b.empty()) {
            if(distrib(gen) % 2) {
                a.back()->defend(*b.back());
            } else {
                b.back()->defend(*a.back());
            }
            if(!a.back()->died()) {
                na.push_back(a.back());
            } else {
                std::cout << a.back()->getName() << " died!\n";
            }
            a.pop_back();
            if(!b.back()->died()) {
                nb.push_back(b.back());
            } else {
                std::cout << b.back()->getName() << " died!\n";
            }
            b.pop_back();
        }
        std::shuffle(na.begin(), na.end(), gen);
        std::shuffle(nb.begin(), nb.end(), gen);
        std::shuffle(a.begin(), a.end(), gen);
        std::shuffle(b.begin(), b.end(), gen);
        a.insert(a.begin(), na.begin(), na.end());
        b.insert(b.begin(), nb.begin(), nb.end());
    }
    std::cout << (a.empty() ? "The bad side won.\n" : "The good side won.\n");
    std::cout << "The survivors are:\n";
    for(auto e : a) {
        std::cout << e->getType() << "\t " << e->getName() << "\n";
    }
    for(auto e : b) {
        std::cout << e->getType() << "\t " << e->getName() << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::vector<Soldado*> a, b;
    std::cout << "Do you wish to insert the characters manually (option 1) or extract names from file (option 2) or extract names and stats from file (option 3)?\n";
    int op;
    while(std::cin >> op) {
        if(op == 1) {
            extractManually(a, b);
            break;
        } else if(op == 2) {
            extractFromFile(a, b);
            break;
        } else if(op == 3) {
            extractStatsFromFile(a, b);
            break;
        } else {
            std::cout << "Invalid option!\n";
            continue;
        }
    }
    std::cout << "Press Enter to begin the battle.\n";
    std::cin.ignore(); std::cin.ignore();
    battle(a, b);
    return 0;
}