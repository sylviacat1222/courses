#include "Player.h"

Player::Player(){

}

Player::Player(string name, int maxHealth, int attack, int defense):GameCharacter(name, "player", maxHealth, attack, defense){

}

void Player::addItem(Item item){
    this->inventory.push_back(item);
}

void Player::increaseStates(int health, int attack, int defense){
    setMaxHealth(getMaxHealth() + health);
    setAttack(getAttack() + attack);
    setDefense(getDefense() + defense);
}

void Player::changeRoom(Room *room){
    setPreviousRoom(getCurrentRoom());
    setCurrentRoom(room);
}

bool Player::triggerEvent(Object* object){
    if (Player *playerptr = dynamic_cast<Player*>(object)){
        cout << "Name:" << playerptr->getName() << endl;
        cout << "Health:" << playerptr->getCurrentHealth() << " / " << playerptr->getMaxHealth() << endl;
        cout << "Attack:" << playerptr->getAttack() << endl;
        cout << "Defense:" << playerptr->getDefense() << endl;
    }
    return 1;
}


void Player::setCurrentRoom(Room *room){
    this->currentRoom = room;
}

void Player::setPreviousRoom(Room *room){
    this->previousRoom = room;
}

void Player::setInventory(vector<Item> inventory){
    this->inventory = inventory;
}

Room* Player::getCurrentRoom(){
    return currentRoom;
}

Room* Player::getPreviousRoom(){
    return previousRoom;
}

vector<Item> Player::getInventory(){
    return inventory;
}
