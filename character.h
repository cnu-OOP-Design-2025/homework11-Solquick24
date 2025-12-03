
#pragma once
#include <iostream>
#include <string>
using namespace std;


enum class CharacterType {
    Knight,
    Wizard,
    Archer,
    Zombie,
    Skeleton,
    Lich,
    Unknown
};


class Character {
protected:
    string description;
    CharacterType type = CharacterType::Unknown;
public:
    virtual string getDescription() const { return description; }
    virtual int getAttack() const = 0;
    virtual int getSpeed() const = 0;
    virtual int getDefense() const = 0;
    virtual CharacterType getType() const { return type; }
    virtual ~Character() {
        if (this->type != CharacterType::Unknown)
            cout << "Delete Character: " << description << endl;
    }
};

// 기본 캐릭터
class Knight : public Character {
public:
    Knight() { description = "Knight"; type = CharacterType::Knight;}
    int getAttack() const override { return 15; }
    int getSpeed() const override { return 8; }
    int getDefense() const override { return 20; }
};

class Wizard : public Character {
public:
    Wizard() { description = "Wizard"; type = CharacterType::Wizard;}
    int getAttack() const override { return 20; }
    int getSpeed() const override { return 10; }
    int getDefense() const override { return 10; }
};

class Archer : public Character {
public:
    Archer() { description = "Archer"; type = CharacterType::Archer;}
    int getAttack() const override { return 18; }
    int getSpeed() const override { return 15; }
    int getDefense() const override { return 8; }
};

// Decorator 기본 구조
class equip_testmentDecorator : public Character {  // character 클래스 상속받음 
protected:
    shared_ptr<Character> character;
public:
    equip_testmentDecorator(shared_ptr<Character> c) : character(c) {}
    virtual ~equip_testmentDecorator() { }
};

// 장비 클래스
class Armor : public equip_testmentDecorator {
public:
    using equip_testmentDecorator::equip_testmentDecorator;
    string getDescription() const override { return character->getDescription() + " + Armor"; }
    int getAttack() const override { return character->getAttack(); }
    int getSpeed() const override { return character->getSpeed() - 2; }
    int getDefense() const override { return character->getDefense() + 10; }
    CharacterType getType() const override {return character->getType();}
};

class Boots : public equip_testmentDecorator {
public:
    using equip_testmentDecorator::equip_testmentDecorator;
    string getDescription() const override { return character->getDescription() + " + Boots"; }
    int getAttack() const override { return character->getAttack(); }
    int getSpeed() const override { return character->getSpeed() + 5; }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override {return character->getType();}
};

class Staff : public equip_testmentDecorator {
public:
    using equip_testmentDecorator::equip_testmentDecorator;
    string getDescription() const override { return character->getDescription() + " + Staff"; }
    int getAttack() const override { return character->getAttack() + 8; }
    int getSpeed() const override { return character->getSpeed(); }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override {return character->getType();}
};

class Sword : public equip_testmentDecorator {
public:
    using equip_testmentDecorator::equip_testmentDecorator;
    string getDescription() const override { return character->getDescription() + " + Sword"; }
    int getAttack() const override { return character->getAttack() + 10; }
    int getSpeed() const override { return character->getSpeed(); }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override {return character->getType();}
};

class Bow : public equip_testmentDecorator {
public:
    using equip_testmentDecorator::equip_testmentDecorator;
    string getDescription() const override { return character->getDescription() + " + Bow"; }
    int getAttack() const override { return character->getAttack() + 7; }
    int getSpeed() const override { return character->getSpeed() + 2; }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override {return character->getType();}
};
