#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

// Error printing functions: 
void invalidCommand();
void invalidArgument();
void invalidShapeName();
void shapeNameExists(string name);
void shapeNameNotFound(string name);
void invalidShapeType();
void invalidValue();
void tooManyArguments();
void tooFewArguments();
void shapeArrayIsFull();

// Helper functions 
void maxShapes(stringstream &input);
void create(stringstream &input);
void move(stringstream &input);
void rotate(stringstream &input);
void draw(stringstream &input);
void deleteList(stringstream &input);
bool validNameOfShape(string word);
bool validShapeType(string word);
bool fewORInvalidArguments(stringstream &input);
bool inBounds(int num);
int shapeFound(string shapeName);
bool angleInBounds(int angle);
bool additionalArgument(stringstream &input);
bool preExisting(string nameOfShape);

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        // Check which command user wants
        if (command == keyWordsList[1]) {
            maxShapes(lineStream);
        } else if (command == keyWordsList[2]) { 
            create(lineStream);
        } else if (command == keyWordsList[3]) {
            move(lineStream);
        } else if (command == keyWordsList[4]) {
            rotate(lineStream);
        } else if (command == keyWordsList[5]) {
            draw(lineStream);
        } else if (command == keyWordsList[6]) {
            deleteList(lineStream);
        } else {
            invalidCommand();
        }

        // Once the command has been processed, prompt for the
        // next commands
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

void invalidCommand(){
    cout << "Error: invalid command" << endl;
} 

void invalidArgument(){
    cout << "Error: invalid argument" << endl; 
}

void invalidShapeName(){
    cout << "Error: invalid shape name" << endl;
}

void shapeNameExists(string name){ 
    cout << "Error: shape " << name << " exists" << endl;
}

void shapeNameNotFound(string name){
    cout << "Error: shape " << name << " not found" << endl;
}

void invalidShapeType(){
    cout << "Error: too many arguments" << endl;
}

void invalidValue(){
    cout << "Error: invalid value" << endl;
}

void tooManyArguments(){
    cout << "Error: too many arguments" << endl;
}

void tooFewArguments(){
    cout << "Error: too few arguments" << endl;
}

void shapeArrayIsFull(){
    cout << "Error: shape array is full" << endl;
}
 
// Sets up the array 
void maxShapes(stringstream &input){
    // Reads in a max shapes number
    // We are assuming user is entering the information correctly for this
    input >> max_shapes;
    // Allocates (max_shapes) amount of space in the array
    shapesArray = new shape* [max_shapes];
    // Setting each index to NULL
    for(int i= 0; i < max_shapes; i++) {
        shapesArray[i] = NULL;
    }
    cout << "New database: max shapes is " << max_shapes << endl;
}

// Creates the shape
void create(stringstream &input){
    string nameOfShape, typeOfShape;
    int xLocation, yLocation, xSize, ySize;
    
    input >> nameOfShape;
    
    // Here, we know that the shape name is valid 
    // Now lets check for pre-existing shapes with same names in the array 
    if(preExisting(nameOfShape) == true) {
        return;
    }
    
    // Now lets inspect the type of shape 
    input >> typeOfShape;
    
    // Check few arguments
    if(fewORInvalidArguments(input) == false) {
        return;
    }
    // Now we know the string is not empty and the user has typed something 
    // Now lets check if that type is even valid 
    if(!validShapeType(typeOfShape)){
        // Exit function since user did not enter valid shape type (one from the
        // array)
        return;
    }
    
    // Here, we know that the shape type is valid 
    // Now time to the get the x location, y location, x size, and y size
    
    // ----- Check x location ------
    input >> xLocation;
    
    if(!fewORInvalidArguments(input)) {
        return;
    }
    
    if(!inBounds(xLocation)) {
        return;
    }
    
    // ----- Check y location ------
    input >> yLocation;
    
    if(!fewORInvalidArguments(input)) {
        return;
    }
    
    if(!inBounds(yLocation)) {
        return;
    }
    
    // ----- Check x size ------
    input >> xSize;
    
    if(!fewORInvalidArguments(input)) {
        return;
    }
    
    if(!inBounds(xSize)) {
        return;
    }
    
    // ----- Check y size ------
    input >> ySize;
    
    if(!fewORInvalidArguments(input)) {
        return;
    }
    
    if(!inBounds(ySize)) {
        return;
    }
    
    // Checking for additional input 
    if (additionalArgument(input) == true) {
        return;
    }
    
    // After all values are good, let's check if array is full because the 
    // create function will make a new shape everytime it is called
    if((shapeCount >= max_shapes)) {
        shapeArrayIsFull();
        return;
    }
    
    // Let's create a new object by invoking the constructor we made 
    shapesArray[shapeCount] = new shape(nameOfShape, typeOfShape, xLocation, yLocation, xSize, ySize);
    cout << "Created " << nameOfShape << ": " << typeOfShape << " " << xLocation << " " << yLocation << " " << xSize << " " << ySize << endl; 

    // One more shape in the database
    shapeCount++;
} 

// Moves a desired shape from one x,y to another x,y
void move(stringstream &input) {
    string nameOfShape;
    int locationX, locationY, returnedLocation;
    
    returnedLocation = shapeFound(nameOfShape);
    
    if(returnedLocation == -1) {
        // Get out out here if the name you want is not in the array (user did 
        // not previously make the shape with the desired name)
        shapeNameNotFound(nameOfShape);
        return;
    }
    
    // Now we know that the shape name is in the array
    // Now check x location and y location 
    
    // ---- x location ----
    input >> locationX;
    
    if(fewORInvalidArguments(input) == false) {
        return;
    }
    
    if(inBounds(locationX) == false) {
        return;
    }
    
    // ---- y location ----
    input >> locationY;
    
    if(fewORInvalidArguments(input) == false) {
        return;
    }
    
    if(inBounds(locationY) == false) {
        return;
    }
    
    // Checking for additional input 
    if (additionalArgument(input) == true) {
        return;
    }
    
    shapesArray[returnedLocation]->setXlocation(locationX);
    shapesArray[returnedLocation]->setYlocation(locationY);
    
    cout << "Moved " << nameOfShape << " to " << locationX << " " << locationY << endl;
}

// Rotates the desired shape
void rotate(stringstream &input) {
    string nameOfShape;
    int angle, returnedLocation;
    
    input >> nameOfShape;
    
    // Check name is even valid to begin with
    if(validNameOfShape(nameOfShape) == false){
        invalidShapeName();
        return;
    }
    
    // Let's check that the shape the user wants to move is in the array 
    
    returnedLocation = shapeFound(nameOfShape);
    
    if(returnedLocation == -1) {
        // Get out out here if the name you want is not in the array (user did 
        // not previously make the shape with the desired name)
        shapeNameNotFound(nameOfShape);
        return;
    }
    
    // Now we know that the shape name is in the array
    // Now check the angle
    
    input >> angle;
    
    if(fewORInvalidArguments(input) == false) {
        return;
    }
    
    if(angleInBounds(angle) == false) {
        invalidValue();
        return;
    }
    
    // Checking for additional input 
    if (additionalArgument(input) == true) {
        return;
    }
    
    // Changes to angle of rotation of that object at index "returnedLocation"
    shapesArray[returnedLocation]->setRotate(angle);
    cout << "Rotated " << nameOfShape << " by " << angle << "degrees" << endl;
    
}

// Prints all or one specific shape
void draw(stringstream &input) {
    string argument;
    int returnedLocation;
    
    input >> argument;
 
    // If keyword is "all"
    if (argument == keyWordsList[0]) {
        // Draw all 
        cout << "Drew all shapes" << endl;
        for(int i = 0; i<max_shapes; i++) {
            if(shapesArray[i]!= NULL){
                shapesArray[i]->draw();
            }
        }
    } else {
        // Draw only 1 shape 
        
        // Check name is even valid to begin with
        if(validNameOfShape(argument) == false){
            invalidShapeName();
            return;
        }
        
        // Find shape
        returnedLocation = shapeFound(argument);
        if(returnedLocation == -1) {
            // Get out out here if the name you want is not in the array (user did 
            // not previously make the shape with the desired name)
            shapeNameNotFound(argument);
            return;
        } 
        // Checking for additional input 
        if (additionalArgument(input) == true) {
            return;
        }
        
        shapesArray[returnedLocation]->draw();
        cout << "Drew " << shapesArray[returnedLocation]->getName() << endl;
    }
}

// Deletes the desired shape 
void deleteList(stringstream &input) {
    string argument;
    int returnedLocation;
    
    input >> argument;
    
    // watch out for null 
    if (argument == keyWordsList[0]) {
        // Delete all 
        cout << "Deleted: all shapes" << endl;
        for(int i = 0; i<max_shapes; i++) {
            if(shapesArray[i]!= NULL){
                // delete the ith index of the array 
                delete shapesArray[i];
                shapesArray[i]=NULL;
            }
        }
    } else {
        // Delete only 1 shape 
        
        // Find shape
        returnedLocation = shapeFound(argument);
        if(returnedLocation == -1) {
            // Get out out here if the name you want is not in the array (user did 
            // not previously make the shape with the desired name)
            shapeNameNotFound(argument);
            return;
        } 
        
        // Checking for additional input 
        if (additionalArgument(input) == true) {
            return;
        }
        
        cout << "Deleted shape " << shapesArray[returnedLocation]->getName() << endl;
        if(shapesArray[returnedLocation]!= NULL){
            // delete the ith index of the array 
            delete shapesArray[returnedLocation];
            shapesArray[returnedLocation]=NULL;
        }
    }
}

// Check if the name is an already existing shape type or key word 
bool validNameOfShape(string word) {
    // Checking for key word match
    for(int i = 0; i <= 6; i++) {
        if(word == keyWordsList[i]){
            return false;
        }
    }
    // Checking for already shape  type match 
    for(int j = 0; j <= 2; j++) {
        if(word == shapeTypesList[j]){
            return false;
        }
    }
    // Only returns true if it is not a word identical to the ones in the arrays given to us 
    return true;
}

// Need to check if the shape is one of the allowed types of shapes
bool validShapeType(string word){
    for(int i = 0; i <= 2; i++) {
        if(word == shapeTypesList[i]) {
            return true;
        }
    }
    return false;
}

// Checks if too few arguments or invalid argument 
bool fewORInvalidArguments(stringstream &input){
    if(input.fail()) {
        if(input.eof()) {
            tooFewArguments();
            return false;
        } else {
            invalidArgument();
            return false;
        }
    }
    return true;
}

// Checks value is above 0
bool inBounds(int num){
    if(num > 0){
        return true;
    } else { 
        invalidValue();
        return false;
    }
}

// Mimics a boolean function but returns the index if shape name is found 
int shapeFound(string shapeName) {
    for(int x = 0; x < shapeCount; x++) {
        if((shapesArray[x] != NULL) &&(shapesArray[x]->getName() == shapeName)){
            return x;
        }
    }
    return -1;
}

// Checks if angle is between 0 and 360
bool angleInBounds(int angle){
    if (angle <= 360 && angle >= 0) {
        return true;
    } else {
        return false;
    }
}

// Checks for additional argument from user
bool additionalArgument(stringstream &input){
    if (input.eof() == false) {
        tooManyArguments();
        return true;
    } else {
        return false;
    }
}

bool preExisting(string nameOfShape){
    for(int x = 0; x < shapeCount; x++) {
        if((shapesArray[x] != NULL) && (nameOfShape == shapesArray[x]->getName())) {
            // There is a pre existing name in the array 
            shapeNameExists(nameOfShape);
            return true;
        } else {
            shapesArray[x]->setName(nameOfShape);
            return false;
        }
    }
}
