#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>
using namespace std;
#define kinds 7

class room{

private:
    int room_id;
    int room_exit;
    int room_kinds[kinds];
    int princess;
    int monster;

public:
    room(int id);                               // Constructor for the room class
    void init_kinds();                          // Initialize the kinds of room exits
    void init_check();                          // Check if the room contains a princess or a monster
    int *get_kinds() {return room_kinds;}       // Get the array of room exit kinds
    int get_exit() const {return room_exit;}    // Get the number of room exits
    int get_id() const {return room_id;}        // Get the room id
    int get_princess() const{return princess;}  // Check if the room contains a princess
    int get_monster() const{return monster;}    // Check if the room contains a monster
    void print();                               // Print the room information
};

typedef room* Room;
string exit_kinds[kinds] = {" ","up","left","front","back","right","down"};
// An array representing the kinds of room exits
int order, save, princess_room, monster_room;
int get_order(string go, string exit, Room room);

int main()
{
    srand(time(NULL) + getpid());       // Random seed is using time and PID
    string go, exit;
    int id_cnt = 0;
    bool win = true;
    order = monster_room = princess_room = save = 0;
    vector<Room> rooms;
    vector<int> orders;

    cout << "Welcome to the Adventure!" << endl;
    Room lobby = new room(0);           // Create a new room object for the lobby with ID 0
    lobby->print();
    cin >> go >> exit;
    order = get_order(go, exit, lobby); // Get the order of the chosen exit in the lobby room
    while(order == 0){                  // Repeat until a valid command is entered
        cout << "Illegal command! The exit does not exist." << endl;
        lobby->print();
        cin >> go >> exit;              // Reinput an exit number
        order = get_order(go, exit, lobby);
    }
    rooms.push_back(lobby);
    orders.push_back(order);            // Add the lobby room and its order to the vectors

    while(1){
        Room room_temp = new room(++id_cnt);
        rooms.push_back(room_temp);     // Add the newly created room to the vector of rooms
        if(room_temp->get_princess()){
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "|  Princess: Wow! You have found me!                                        |" << endl;
            cout << "|  Player: Come with me. We have to return to the lobby, or we'll get lost. |" << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            save = 1;                   // Set the flag that the princess has been saved
            break;
        }
        if(room_temp->get_monster()){
            cout << "Sorry, you are beaten." << endl;
            win = false;                // Set the flag that the game is lost
            break;
        }
        room_temp->print();
        cin >> go >> exit;              // Input to choose an exit
        order = get_order(go, exit, room_temp);
        while(order == 0){
            cout << "Illegal command! The exit does not exist." << endl;
            room_temp->print();
            cin >> go >> exit;
            order = get_order(go, exit, room_temp);
        }
        orders.push_back(order);
    }
    while(save){
        Room room_temp = rooms.back();  // Get the last added room
        rooms.pop_back();               // Remove the last added room from the vector of rooms
        if(rooms.empty()) break;
        room_temp->print();
        cin >> go >> exit;              // Input to choose an exit
        order = get_order(go, exit, room_temp);
        while(order == 0){              // Repeat until a valid command is entered
            cout << "Illegal command! The exit does not exist." << endl;
            room_temp->print();
            cin >> go >> exit;
            order = get_order(go, exit, room_temp);
        }
        if(order != kinds - orders.back()){ 
            // Check if the chosen exit is the opposite of the previous exit taken
            cout << "Oh no, You are lost in the castle!" << endl;
            win = false;
            break;
        }
        else{
            orders.pop_back();          // Remove the last added order from the vector
        }
        delete room_temp;
    }
    if(win) cout << "Good! You are win." << endl;
    else cout << "You are lose!" << endl;
    system("PAUSE");
    return 0;

}

room::room(int id){
    room_id = id;
    init_kinds();
    init_check();
}

void room::init_kinds(){
    int kind, flag;
    room_exit = 0;                          // Reset the room exit count
    if(order){                              // The first exit is reverse to the last input
        room_kinds[room_exit++] = kinds - order;
    }
    int i;
    for(i=1; i<kinds; i++){
        kind = (rand() % (kinds - 1)) + 1;  // Generate a random room kind [1-6]
        flag = 0;                           // Haven't encountered this kind of room
        int j;
        for(j=0; j<room_exit; j++){
            if(room_kinds[j] == kind){
                flag = 1;                   // Found this kind of room
                break;
            }
        }
        if(!flag) room_kinds[room_exit++] = kind;
        // If the room kind hasn't been added, add it to the room kinds
    }
}

void room::init_check(){
    if(room_id == 0) return;
    else if(princess_room && monster_room) return;
    // Check if both princess_room and monster_room are already set
    else if(monster_room){
        princess = (rand() % 7)? 0 : 1;     // 1/7 probability
        if(princess) princess_room = 1; 
    } 
    else if(princess_room){
        monster = (rand() % 7)? 0 : 1;      // 1/7 probability
        if(monster) monster_room = 1; 
    }
    // If neither princess_room nor monster_room is set
    else{
        princess = (rand() % 7)? 0 : 1;
        if(princess){
            princess_room = 1;
        }
        else{
            monster = (rand() % 7)? 0 : 1;
            if(monster){
                monster_room = 1;
            }
        }
    }
}

void room::print(){
    int i;
    if(room_id == 0) cout << "Welcome to the lobby. ";
    else cout << "Welcome to Room " << room_id << ". " ;
    cout << "There are " << room_exit << " exits: ";
    for(i=0; i<room_exit; i++){             // Print the all kinds of exits
        if(i == 0) cout << exit_kinds[room_kinds[i]];
        else if(i == room_exit - 1) cout << " and " << exit_kinds[room_kinds[i]];
        else cout << ", " << exit_kinds[room_kinds[i]];
    }
    cout << "." << endl;
    cout << "Choose your direction, please use the form of 'go xxx'!" << endl;
}

int get_order(string go, string exit, Room room){
    int i, exits;
    exits = room->get_exit();
    int *choice = room->get_kinds();        // Get the room's exits' type
    
    if(go == "go"){
        for(i=0; i<exits; i++){             // Check if the exit choice matches the input exit
            if(exit == exit_kinds[choice[i]]) return choice[i];
        }
        if(i == exits) return 0;            // If no matching exit is found, return 0
    }
    return 0;                               // If the input command is not "go", return 0
}
