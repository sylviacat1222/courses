#include "Dungeon.h"

Dungeon::Dungeon(){

}

/* Create a new player, and give him/her basic status */
void Dungeon::createPlayer(){
    Player *player = new Player("Hero", 50, 10, 10);
    this->player = *player;
}

/* Create a map, which include several different rooms */
void Dungeon::createMap(){
    //create monsters
    Monster *little_monster1 = new Monster("Little_monster1", 10, 11, 8);
    Monster *little_monster2 = new Monster("Little_monster2", 15, 11, 8);
    Monster *little_monster3 = new Monster("Little_monster3", 20, 11, 8);
    Monster *big_monster = new Monster("Big_monster", 30, 12, 8);

    //create NPC
    vector<Item> *commodity = new vector<Item>;
    NPC *npc = new NPC("NPC", "Choose an item you prefer.(Please enter the index)", *commodity);

    //create items
    Item *sword = new Item("Sword", 0, 2, 0);
    Item *shield = new Item("Shield", 0, 0, 2);
    Item *magic_potion = new Item("Magic_potion", 5, 0, 0);
    commodity->push_back(*sword);
    commodity->push_back(*shield);
    commodity->push_back(*magic_potion);
    npc->setCommodity(*commodity);

    //create rooms
    vector<Object*> *objects0 = new vector<Object*>;
    vector<Object*> *objects1 = new vector<Object*>;
    vector<Object*> *objects2 = new vector<Object*>;
    vector<Object*> *objects3 = new vector<Object*>;
    vector<Object*> *objects4 = new vector<Object*>;

    //objects in rooms
    objects0->push_back(npc);
    objects1->push_back(npc);
    objects1->push_back(little_monster1);
    objects2->push_back(npc);
    objects2->push_back(little_monster2);
    objects3->push_back(npc);
    objects3->push_back(little_monster3);
    objects4->push_back(npc);
    objects4->push_back(big_monster);
    Room *room0 = new Room(0, 0, *objects0);
    Room *room1 = new Room(0, 1, *objects1);
    Room *room2 = new Room(0, 2, *objects2);
    Room *room3 = new Room(0, 3, *objects3);
    Room *room4 = new Room(1, 4, *objects4);

    //room0
    room0->setUpRoom(room2);
    room0->setRightRoom(room1);
    //room1
    room1->setLeftRoom(room0);
    //room2
    room2->setUpRoom(room3);
    room2->setDownRoom(room0);
    //room3
    room3->setDownRoom(room2);
    room3->setLeftRoom(room4);
    //room4
    room4->setRightRoom(room3);

    this->rooms.push_back(*room0);
    this->rooms.push_back(*room1);
    this->rooms.push_back(*room2);
    this->rooms.push_back(*room3);
    this->rooms.push_back(*room4);
}

/* Deal with player's moving action */
void Dungeon::handleMovement(){
    if(player.getCurrentRoom()->getIsExit() == 1){
        cout << "This is the last room" << endl;
    }
    else{
        cout << "Now you can move to other rooms.(1:up, 2:down, 3:left, 4:right)" << endl;
        int movement;
        cin >> movement;
        if(movement == 1 && player.getCurrentRoom()->getUpRoom()!=NULL){
            player.changeRoom(player.getCurrentRoom()->getUpRoom());
            cout << "Move to room " << player.getCurrentRoom()->getIndex() << endl;
        }
        else if(movement == 2 && player.getCurrentRoom()->getDownRoom()!=NULL){
            player.changeRoom(player.getCurrentRoom()->getDownRoom());
            cout << "Move to room " << player.getCurrentRoom()->getIndex() << endl;
        }
        else if(movement == 3 && player.getCurrentRoom()->getLeftRoom()!=NULL){
            player.changeRoom(player.getCurrentRoom()->getLeftRoom());
            cout << "Move to room " << player.getCurrentRoom()->getIndex() << endl;
        }
        else if(movement == 4 && player.getCurrentRoom()->getRightRoom()!=NULL){
            player.changeRoom(player.getCurrentRoom()->getRightRoom());
            cout << "Move to room " << player.getCurrentRoom()->getIndex() << endl;
        }
        else{
            cout << "The room does not exist." <<endl;
            cout << "Go back to room " << player.getCurrentRoom()->getIndex() << endl;
        }
    }
}

/* Deal with player's interaction with objects in that room */
void Dungeon::handleEvent(Object *object){
    if (NPC *npcptr = dynamic_cast<NPC*>(object)){
            npcptr->triggerEvent(&player);
            this->player.getCurrentRoom()->popObject(npcptr);
    }
    else if (Monster *monsterptr = dynamic_cast<Monster*>(object)){
            monsterptr->triggerEvent(&player);
            this->player.getCurrentRoom()->popObject(monsterptr);
    }
    else if (Item *itemptr = dynamic_cast<Item*>(object)){
            itemptr->triggerEvent(&player);
            this->player.getCurrentRoom()->popObject(itemptr);
    }
}

/* Deal with all game initial setting       */
/* Including create player, create map etc  */
void Dungeon::startGame(){
    this->createPlayer();
    this->createMap();
    player.setCurrentRoom(&rooms[0]);
    //player.setCurrentHealth(player.getMaxHealth());
}

/* Deal with the player's action     */
/* including showing the action list */
/* that player can do at that room   */
/* and dealing with player's input   */
void Dungeon::chooseAction(vector<Object*> objects){
    cout << "Some things in this room:" << endl;
    for(unsigned int i = 0; i < objects.size(); i++){
        cout << i << ". " << objects[i]->getName() << endl;
    }

    cout << "Choose an action.(enter the index)" << endl;
    unsigned int action_index;
    cin >> action_index;
    if(action_index <= objects.size()){
        this->handleEvent(objects[action_index]);
    }
}

/* Check whether the game should end or not */
/* Including player victory, or he/she dead */
bool Dungeon::checkGameLogic(){
    if(player.checkIsDead()){
        return 1;
    }
    else if(player.getCurrentRoom()->getIsExit()){
        return 1;
    }
    else return 0;
}

/* Deal with the whole game process */
void Dungeon::runDungeon(){
    cout << "Game start" << endl;
    string player_name;
    cout << "Please enter your name." << endl;
    cin >> player_name;
    this->startGame();
    player.setName(player_name);
    Record *record = new Record;
    cout << "You're now at room " << player.getCurrentRoom()->getIndex() << endl;
    while(1){
        if(player.getCurrentRoom()->getObjects().size()!=0) this->chooseAction(player.getCurrentRoom()->getObjects());
        else if(this->checkGameLogic()){
            cout << "The end" << endl;
            break;
        }
        else{
            /*cout << "Do you want to save?(y/n)" <<endl;
            char yesno;
            cin >> yesno;
            if(yesno == 'Y' || yesno == 'y'){
                record->saveToFile(&player, rooms);
            }*/
            this->handleMovement();
        }
    }
    exit(0);
}
