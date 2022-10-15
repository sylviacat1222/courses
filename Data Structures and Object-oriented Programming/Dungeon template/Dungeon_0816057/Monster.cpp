#include "Monster.h"

Monster::Monster(){

}

Monster::Monster(string name, int health, int attack, int defense):GameCharacter(name, "monster", health, attack, defense){

}

bool Monster::triggerEvent(Object *object){
    if (Player *playerptr = dynamic_cast<Player*>(object)){
        cout << "monster's name:" << this->getName() << endl;
        cout << "Attack or retreat? (a/r)" << endl;
        char attack_or_retreat;
        cin >> attack_or_retreat;
        if(attack_or_retreat == 'A' || attack_or_retreat == 'a'){
            while(!(this->checkIsDead()) && !(playerptr->checkIsDead())){
                this->takeDamage(playerptr->getAttack() - this->getDefense());
                cout << "You attack the monster." << endl;
                cout << "Your health:" << playerptr->getCurrentHealth() << endl;
                cout << "Monster's health:" ;
                if(this->getCurrentHealth() > 0) cout << this->getCurrentHealth() << endl << endl;
                else cout << "0" << endl << endl;
                if(this->checkIsDead()){
                    cout << "You defeat this monster!" << endl;
                    playerptr->setCurrentHealth(playerptr->getMaxHealth());
                    return 1;
                }
                playerptr->takeDamage(this->getAttack() - playerptr->getDefense());
                cout << "The monster attack you." << endl;
                cout << "Your health:";
                if(playerptr->getCurrentHealth() > 0) cout << playerptr->getCurrentHealth() << endl << endl;
                else cout << "0" << endl << endl;
                cout << "Monster's health:" << this->getCurrentHealth() << endl << endl;
                if(playerptr->checkIsDead()){
                    cout << "Game Over" << endl;
                    return 1;
                }
            }
        }
        else if(attack_or_retreat == 'R' or attack_or_retreat == 'r'){
            playerptr->setCurrentRoom(playerptr->getPreviousRoom());
            cout << "Go back to room " << playerptr->getCurrentRoom()->getIndex() << endl;
            return 0;
        }
    }
}
