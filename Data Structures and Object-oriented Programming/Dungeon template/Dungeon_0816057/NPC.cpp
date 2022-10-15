#include "NPC.h"

NPC::NPC(){

}

NPC::NPC(string name, string script, vector<Item> commodity):GameCharacter(name, "NPC", 10, 0, 0){
    this->script = script;
    this->commodity = commodity;
}

void NPC::listCommodity(){
    vector<Item>::iterator begin = commodity.begin();
    vector<Item>::iterator end = commodity.end();
    vector<Item>::iterator it;
    int i = 0;
    for(it = begin ; it != end ; it++){
        cout << i << ". " << it->getName()
        << ", Health:" << it->getHealth()
        << ", Attack:" << it->getAttack()
        << ", Defense:" << it->getDefense() << endl;
        i++;
    }
}

bool NPC::triggerEvent(Object *object){
    if (Player *playerptr = dynamic_cast<Player*>(object)){
        cout << this->getScript() << endl;
        this->listCommodity();
        int item_index;
        cin >> item_index;
        Item chosen_item = this->commodity[item_index];
        playerptr->addItem(chosen_item);
        playerptr->increaseStates(chosen_item.getHealth(), chosen_item.getAttack(), chosen_item.getDefense());
        playerptr->setCurrentHealth(playerptr->getMaxHealth());
        cout<< "You become stronger." <<endl;
        playerptr->Player::triggerEvent(playerptr);
        return 1;
    }
    else return 0;
}

void NPC::setScript(string script){
    this->script = script;
}

void NPC::setCommodity(vector<Item> commodity){
    this->commodity = commodity;
}

string NPC::getScript(){
    return script;
}

vector<Item> NPC::getCommodity(){
    return commodity;
}
