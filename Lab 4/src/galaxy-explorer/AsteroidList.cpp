#include <galaxy-explorer/AsteroidList.hpp>

#include "MyAIData.hpp"

// Constructor 
AsteroidListItem::AsteroidListItem() {
    this->next = nullptr;
    this->data = nullptr;
}

// Parameterized Constructor 
AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    this->data = new Asteroid(a);
}

// Destructor 
AsteroidListItem::~AsteroidListItem() {
    if (this->next!=nullptr){
        delete this->data;
    }
}

// Creates an empty list
AsteroidList::AsteroidList() {
    head.setNext(nullptr);
}

// Creates an independent copy of `src`. 
AsteroidList::AsteroidList(const AsteroidList& src)
{
    // The functions in this class are listed in a suggested order of implementation,
    // except for this one and the destructor (because you should put all your constructors together).
   
    // This will be the src 
    const AsteroidListItem *ptr = src.begin();
    // This pointer will allow us to keep track of the last node inserted
    AsteroidListItem* last = nullptr;
    // This pointer will allow us to copy
    AsteroidListItem* nptr = nullptr;
    while(ptr != nullptr) {
        // Copy the node from src
        nptr = new AsteroidListItem(ptr->getData());
        // Inserting last to the end 
        if (last == nullptr) {
            head.setNext(nptr);
        } else {
            // Last item is the new item
            last->setNext(nptr);
        }
        // Go through traversing 
        ptr = ptr->getNext();
        last = nptr;
    }
} 

// Frees all memory associated with this list
AsteroidList::~AsteroidList() {
    // The functions in this class are listed in a suggested order of implementation,
    // except for this one and the copy constructor (because you should put all your constructors together).
    
    // Point will allow us to delete nodes 
    AsteroidListItem *ptr;
    while(head.getNext() != nullptr) {
        ptr = head.getNext();
        head.setNext(ptr->getNext());
        delete ptr; 
    }
}

// Add an asteroid at the beginning of this list
void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem *newAsteroid = new AsteroidListItem(e);
    // Prev first item = newItem's next
    newAsteroid->setNext(head.getNext());    
    // Heads points to new 
    head.setNext(newAsteroid);
}

// Return a reference to the first asteroid
Asteroid& AsteroidList::front() {
    if(head.getNext() != nullptr){
        // Return the data of the first node
        return head.getNext()->getData();
    } else {
        // Else is is empty linked list 
        return *(Asteroid*)nullptr;
    }
}

// Return a reference to the first asteroid
// Same as function above 
const Asteroid& AsteroidList::front() const {
    if(head.getNext() != nullptr){
        return head.getNext()->getData();
    } else {
        return *(Asteroid*)nullptr;
    }
}

// Checks for no entities in the linked list 
bool AsteroidList::isEmpty() const {
    return (head.getNext() == nullptr);
}

// The number of entities in the linked list
int AsteroidList::size() const {
    // Counter variable to keep track of size 
    int size = 0;
    // Pointer to help traverse
    const AsteroidListItem *ptr = beforeBegin();
        
    // Traverse through the linked list and increment size
    while(ptr->hasNext()){
        size = size + 1;
        ptr = ptr->getNext();
    }
    return size;
}

// Return an item corresponding to the position immediately before the first asteroid.
AsteroidListItem* AsteroidList::beforeBegin() {
    return &head;
}

// Return an item corresponding to the position immediately before the first asteroid.
const AsteroidListItem* AsteroidList::beforeBegin() const {
    return &head;
}

// Done
AsteroidListItem* AsteroidList::begin() {
    if(head.getNext() != nullptr){
        // Return first asteroid 
        return head.getNext();
    } else {
        // Return null
    }
}

// Returns an item corresponding to the first asteroid.
const AsteroidListItem* AsteroidList::begin() const {
    if(head.getNext() != nullptr){
        // Return first asteroid 
        return head.getNext();
    } else {
        // Return null
        return nullptr;
    }
}

// Returns an item corresponding to the position of the last asteroid. 
AsteroidListItem* AsteroidList::beforeEnd() {
    // Pointer to traverse linked list 
    AsteroidListItem *ptr = beforeBegin();
    // Traverse until null 
    while(ptr->hasNext()){
        ptr = ptr->getNext();
    }
    return ptr;
}

// Returns an item corresponding to the position of the last asteroid. 
const AsteroidListItem* AsteroidList::beforeEnd() const {
    // Pointer to traverse linked list 
    const AsteroidListItem *ptr = beforeBegin();
    // Traverse until null 
    while(ptr->hasNext()){
        ptr = ptr->getNext();
    }
    return ptr;
}

// Returns an item corresponding to the position immediately after the last asteroid.
AsteroidListItem* AsteroidList::end() {
    return nullptr;
}

// Returns an item corresponding to the position immediately after the last asteroid.
const AsteroidListItem* AsteroidList::end() const {
    return nullptr;
}

// Adds a single asteroid to this list, in the position immediately after `prev`. 
// and returns the item that was inserted
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem *newAsteroid = new AsteroidListItem(e);
    // New items next = prev
    newAsteroid->setNext(prev->getNext());
    prev->setNext(newAsteroid);
    
    return newAsteroid;
}

// Adds independent copies of the entities in `others` to this list, placed 
// immediately after `insertion_point in the same order as `others`.
// Returns the last item that was inserted, or `insertion_point' if `others' is empty
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    // Make a temp and next pointer to help traverse linked list
    AsteroidListItem *temp = prev;
    AsteroidListItem *next = prev->getNext();
    
    const AsteroidListItem *extraHead = others.begin();
    while(extraHead != nullptr) {
        // Copies item
        AsteroidListItem *newAsteroid = new AsteroidListItem(extraHead->getData());
        temp->setNext(newAsteroid);
        temp = temp->getNext();
        extraHead = extraHead->getNext();
    }
    temp->setNext(next);
    
    return temp;
}

// Given a position in this list, delete the following asteroid.
// Returns the list item that followed the erased item, or end() if there wasn't one.
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    // Have to check if we have anything to erase after prev
    if (prev->getNext() == nullptr || prev == nullptr) {
        return prev;
    } else {
        // Delete this item
        AsteroidListItem *ptr = prev->getNext();
        // Prev ptr points to next->next to break the link
        prev->setNext(prev->getNext()->getNext());
        // Maintain memory by deleting what ptr is pointing to 
        delete ptr; 
        
        return prev;
    }
}

// Free all nodes.
void AsteroidList::clear() {
    // Point will allow us to delete nodes 
    AsteroidListItem *ptr;
    while(head.getNext() != nullptr) {
        ptr = head.getNext();
        head.setNext(ptr->getNext());
        delete ptr; 
    }
}

// Makes this list an independent copy of `src`.
AsteroidList& AsteroidList::operator=(const AsteroidList& src) {    
    // Check if src is the same as what is being operated on 
    if(this == &src){
        return (*this);
    }
    // Free all nodes.
    this->clear();
    // Copies all src items to new linked list 
    this->insertAfter(this->beforeBegin(), src);
    
    return *this;
}