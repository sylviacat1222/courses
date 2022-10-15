#include "GameCharacter.h"

GameCharacter::GameCharacter(){

}

GameCharacter::GameCharacter(string name, string tag, int maxHealth, int attack, int defense):Object(name, tag){
    this->maxHealth = maxHealth;
    this->currentHealth = maxHealth;
    this->attack = attack;
    this->defense = defense;
}

bool GameCharacter::checkIsDead(){
    if(getCurrentHealth() > 0){
        return 0;
    }
    else return 1;
}

int GameCharacter::takeDamage(int damage){
    setCurrentHealth(currentHealth - damage);
}

void GameCharacter::setMaxHealth(int maxHealth){
    this->maxHealth = maxHealth;
}

void GameCharacter::setCurrentHealth(int currentHealth){
    this->currentHealth = currentHealth;
}

void GameCharacter::setAttack(int attack){
    this->attack = attack;
}

void GameCharacter::setDefense(int defense){
    this->defense = defense;
}

int GameCharacter::getMaxHealth(){
    return this->maxHealth;
}

int GameCharacter::getCurrentHealth(){
    return this->currentHealth;
}

int GameCharacter::getAttack(){
    return this->attack;
}

int GameCharacter::getDefense(){
    return this->defense;
}
