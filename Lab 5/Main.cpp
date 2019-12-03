/* 
 * File:   main.cpp
 * Author: narwalbi
 *
 * Created on November 16, 2019, 1:04 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <ostream>

#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

using namespace std;

int main(){
    string line, command;
    TreeDB site;
    
    // Need active bool variable to pass to functions
    bool activity;
    
    string name, status;
    unsigned int IPAddress;

    cout << "> ";
    getline(cin, line);
    
    while(!cin.eof()){
        
        stringstream linestream(line);
        linestream >> command;
        
        if(command == "insert"){

            linestream >> name;
            linestream >> IPAddress;
            linestream >> status;
            
            if(status == "active"){
                activity = true;
            } else {
                activity = false; 
            }
            
            // Make new object called entry
            DBentry *entry = new DBentry(name, IPAddress, activity);

            // Insert the entry, pass to insert function which will return true or false 
            if(site.insert(entry)){
                cout << "Success" << endl;
            } else {
                cout << "Error: entry already exists" << endl;
            }    
            
        } else if(command == "find"){
            linestream >> name;
            
            DBentry *entry = site.find(name);
            
            // if entry is NULL, nothing is there therefore DNE
            if(entry == NULL){
                cout << "Error: entry does not exist" << endl;
            } else {
                cout << *entry ;
            }

        } else if(command == "remove"){
            linestream >> name;
            
            // The remove function will take care of NULLs for us 
            if(site.remove(name) == true){
                cout << "Success" << endl;
            } else {
                // If NULL or DNE:
                cout << "Error: entry does not exist" << endl;
            }

        } else if(command == "printall"){
            cout << site;
            
        } else if(command == "printprobes"){
            string name;
            linestream >> name;
            
            // Non-existant name will result in error
            if(site.find(name) == NULL){
                cout << "Error: Entry does not exist" << endl;
            } else {
                // Otherwise print
                site.printProbes();
            }
            
        } else if(command == "removeall"){
            // Removes everything 
            site.clear();
            cout << "Success" << endl;

        } else if(command == "countactive"){
            // Counts all the actives in the BST
            site.countActive();
            
        } else if(command == "updatestatus"){
            bool activity;
            
            linestream >> name;
            linestream >> status;
            
            if(status == "active"){
                activity = true;
            } else {
                activity = false; 
            }
            
            // First check for validity to see if name exists
            if(site.find(name) == NULL){
                cout << "Error: Entry does not exist" << endl;
            } else {
                // Find name and set to active 
                DBentry *entry = site.find(name);
                entry->setActive(activity);
                cout << "Success" << endl;
            }
                  
        }
        
        // Next iteration until you do not reach end of file
        cout << "> ";
        getline(cin, line);
    }
    // End of file reached 
    return 0;
}
