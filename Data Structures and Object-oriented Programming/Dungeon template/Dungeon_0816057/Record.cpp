#include "Record.h"

Record::Record(){

}

void Record::savePlayer(Player *player, ofstream &outstream_player){
    if(player == NULL){
       cout << "save fail QAQ" << endl;
       return;
    }
    outstream_player.open("player.txt");
    outstream_player << "-----Player:-----" << endl
    << "Name: " << player->getName() << endl
    << "MaxHealth: " << player->getMaxHealth() << endl
    << "CurretHealth: " << player->getCurrentHealth() << endl
    << "Attack: " << player->getAttack() << endl
    << "Defense: " << player->getDefense() << endl
    << "CurrentRoom: room " << player->getCurrentRoom()->getIndex() << endl
    << "PreviousRoom: room " << player->getPreviousRoom()->getIndex() << endl
    << "Inventory: " << endl;

    vector<Item>::iterator begin = player-> getInventory().begin();
    vector<Item>::iterator end = player-> getInventory().end();
    vector<Item>::iterator it;
    for(it = begin ; it != end ; it++){
        outstream_player << "Name: " << it->getName()
        << ", Tag: " << it->getTag()
        << ", Health: " << it->getHealth()
        << ", Attack: " << it->getAttack()
        << ", Defense: " << it->getDefense();
    }
    outstream_player.close();
}

void Record::saveRooms(vector<Room> &rooms, ofstream &outstream_room){

    outstream_room.open("room.txt");
    vector<Room>::iterator begin = rooms.begin();
    vector<Room>::iterator end = rooms.end();
    vector<Room>::iterator it;
    int room_index = 0;
    vector<Object*> objects_in_room;
    for(it = begin ; it != end ; it++){
        outstream_room << "-----Room:-----" << endl;
        outstream_room << "The rooms around room " << room_index << endl;
        if(it->getIsExit()) outstream_room << "Room " << room_index << " is the exit." << endl;
        if(it->getUpRoom() != NULL) outstream_room << "Up: " << it->getUpRoom()->getIndex() << endl;
        else if(it->getDownRoom() != NULL) outstream_room << "Down: " << it->getDownRoom()->getIndex() << endl;
        else if(it->getLeftRoom() != NULL) outstream_room << "Left: " << it->getLeftRoom()->getIndex() << endl;
        else if(it->getRightRoom() != NULL) outstream_room << "Right: " << it->getRightRoom()->getIndex() << endl;
        room_index++;
        objects_in_room = it->getObjects();
        int size_of_objects = objects_in_room.size();
        outstream_room << "Objects in this room: " << endl;
        if(size_of_objects == 0){
            outstream_room << "No objects in this room." << endl;
        }
        else{
            for(int i = 0; i < size_of_objects; i++){
                outstream_room << "Name: " << objects_in_room[i]->getName() << endl
                << "Tag: " << objects_in_room[i]->getTag() << endl;
                if(NPC *npc = dynamic_cast<NPC*> (objects_in_room[i])){
                    outstream_room << "NPC's script: " << npc->getScript() <<endl;
                    vector<Item> commodity = npc->getCommodity();
                    outstream_room << "NPC's commodity: " << endl;
                    vector<Item>::iterator begin = commodity.begin();
                    vector<Item>::iterator end = commodity.end();
                    vector<Item>::iterator it;
                    for(it = begin ; it != end ; it++){
                        outstream_room << "Name: " << it->getName() << endl
                        << "Health: " << it->getHealth() << endl
                        << "Attack: " << it->getAttack() << endl
                        << "Defense: " << it->getDefense() << endl;
                    }
                }
                else if(Monster *monster = dynamic_cast<Monster*> (objects_in_room[i])){
                    outstream_room << "Health: " << monster->getMaxHealth() << endl
                    << "Attack: " << monster->getAttack() << endl
                    << "Defense: " << monster->getDefense() << endl;
                }
            }
        }
    }
    outstream_room.close();
}

void Record::loadPlayer(Player*, ifstream&){

}

void Record::loadRooms(vector<Room>&, ifstream&){

}

void Record::saveToFile(Player *player, vector<Room> &room){
    ofstream outstream_player("player.txt", ios::trunc);
    ofstream outstream_room("room.txt", ios::trunc);
    savePlayer(player, outstream_player);
    saveRooms(room, outstream_room);
}
void Record::loadFromFile(Player *player, vector<Room> &room){
    ifstream instream;
    //instream.open("");
    //instream.close();
}
