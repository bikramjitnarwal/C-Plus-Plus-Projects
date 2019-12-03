#include "DBentry.h"
#include <iostream>
#include <string>

using namespace std;

DBentry::DBentry(){
    name = "";
    IPaddress = 0;
    active = false;
}

DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active){
    this->name = _name;
    this->IPaddress = _IPaddress;
    this->active = _active;
}

DBentry::~DBentry(){}

void DBentry::setName(string _name){
    this->name = _name;
}

void DBentry::setIPaddress(unsigned int _IPaddress){
    this->IPaddress = _IPaddress;
}

void DBentry::setActive(bool _active){
    this->active = _active;
}

string DBentry::getName() const{
    return this->name;
}

unsigned int DBentry::getIPaddress() const{
    return this->IPaddress;
}

bool DBentry::getActive() const{
    return this->active;
}

// prints the entry in the format 
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs){
    if(rhs.getActive() == true){
        out << rhs.getName() << " : " << rhs.getIPaddress() << " : active" << endl;
    } else {
        cout << rhs.getName() << " : " << rhs.getIPaddress() << " : inactive" << endl;
    }
    return out;
}