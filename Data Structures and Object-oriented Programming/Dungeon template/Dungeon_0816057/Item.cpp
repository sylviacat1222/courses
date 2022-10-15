#include "Item.h"

Item::Item():Object(){

}

Item::Item(string name, int health, int attack, int defense):Object(name, "Item"){
    this->health = health;
    this->attack = attack;
    this->defense = defense;
}

void Item::setHealth(int health){
    this->health = health;
}

void Item::setAttack(int attack){
    this->attack = attack;
}

void Item::setDefense(int defense){
    this->defense = defense;
}

int Item::getHealth(){
    return this->health;
}

int Item::getAttack(){
    return this->attack;
}

int Item::getDefense(){
    return this->defense;
}

bool Item::triggerEvent(Object *object){
    if (Player *playerptr = dynamic_cast<Player*>(object)){
        playerptr->increaseStates(this->getHealth(), this->getAttack(), this->getDefense());
    }
    return 1;
}
