
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "character.h"
using namespace std;

class Undead {
public:
    virtual string name() const = 0;
    virtual int power() const = 0;
    virtual int agility() const = 0;
    virtual int endurance() const = 0;
    virtual ~Undead() {}
};

class Zombie : public Undead {
public:
    string name() const override { return "Zombie"; }
    int power() const override { return 15; }
    int agility() const override { return 5; }
    int endurance() const override { return 20; }
};

class Skeleton : public Undead {
public:
    string name() const override { return "Skeleton"; }
    int power() const override { return 10; }
    int agility() const override { return 15; }
    int endurance() const override { return 10; }
};

class Lich : public Undead {
public:
    string name() const override { return "Lich"; }
    int power() const override { return 25; }
    int agility() const override { return 12; }
    int endurance() const override { return 18; }
};

// Adapter: Undead → Character
class UndeadAdapter : public Character {
    shared_ptr<Undead> undead;
public:
    UndeadAdapter(shared_ptr<Undead> u) {  // 생성자 , shared_ptr<Undead> u는 외부에서 전달받은 포인터
        /* TODO */
        undead = u; // 멤버 변수에 저장, 그러면 shared_ptr가 복사되어 참조 카운트 증가, undead 객체는 계속 유지됨., 만약 u가 nullptr이면 undead도 nullptr이다.
        
        if (!undead) {
            description = "Unknown Undead";
            type = CharacterType::Unknown;
        } else {
            description = undead->name();
            const string n = description;
            if (n == "Zombie")      type = CharacterType::Zombie;
            else if (n == "Skeleton") type = CharacterType::Skeleton;
            else if (n == "Lich")     type = CharacterType::Lich;
            else                      type = CharacterType::Unknown;
        }
    }
    int getAttack() const override { return undead->power(); }
    int getSpeed() const override { return undead->agility(); }
    int getDefense() const override { return undead->endurance(); }
};


// .(도트) : 직접객체 obj.member // 객체의 멤버 직접 접근
// -> : 포인터 ptr->member // 포인터가 가리키는 객체의 멤버 접근 ( *ptr).member 와 동일
// shared_ptr<T> : 스마트 포인터, 참조 카운팅 방식으로 메모리 관리
// ::( scope) : 네임스페이스 or 클래스 : std::cout, Class::Ffunc() // 범위/ 정적 멤버 지정