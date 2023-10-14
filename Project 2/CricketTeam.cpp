//
//  CricketTeam.cpp



#include "CricketTeam.h"


CricketTeam::CricketTeam()
{
    head = nullptr;
    tail = nullptr;
}


//go through linked list and delete each node
CricketTeam::~CricketTeam()
{
    Node *p = head;
    
    while(p != nullptr){
        Node *n = p->next;
        delete p; //this deletes only the node not p 
        p = n;
    }
    
    head = nullptr;
    tail = nullptr;
}

//copy constructor When a brand new CricketTeam is created as a copy of an existing CricketTeam, a deep copy should be made.
CricketTeam::CricketTeam(const CricketTeam& rhs)
{
    if(rhs.head == nullptr)// if old list is empty set to nullptr
    {
        tail = nullptr;
        head = nullptr;
    }
    
    Node *r = rhs.head;
    
    // set head and tail to first node and nullptr the previous node since its the last node
    Node *p = new Node;
    tail = head = p;
    head->prev = nullptr;
    
    // insert values
    p->m_lastName = r->m_lastName;
    p->m_value = r->m_value;
    p->m_firstName = r->m_firstName;
    
    r = r->next;
    
    // if theres one node
    if (r == nullptr)
    {
        p->next = nullptr;
    }
    
    else
    {
        Node *c = head; // copy traverse
        
        while(r != nullptr)// loop through rhs
        {
            // create node and connect
            c->next = new Node;
            c->next->prev = c;
            c = c->next;
            
            c->m_lastName = r->m_lastName;
            c->m_value = r->m_value;
            c->m_firstName = r->m_firstName;
            
            r = r->next;
        }
        
        c->next = nullptr;
        tail = c;
    }
    
}

//assignment operator
const CricketTeam& CricketTeam::operator=(const CricketTeam& rhs)
{
    if(&rhs == this)
    {
        return *this;
    }
    
    
    if(head != nullptr && tail != nullptr)// make sure old list is not empty before deleting
    {
        Node *p = head;
        
        while(p != nullptr){
            Node *n = p->next;
            delete p; //this deletes only the node not p
            p = n;
        }
        
        head = nullptr;
        tail = nullptr;
    }
    
    if(rhs.head == nullptr)// don't copy if rhs has no nodes
    {
        tail = nullptr;
        head = nullptr;
    }
    
    // copy for first node
    Node *r = rhs.head;
    
    Node *p = new Node;
    tail = head = p;
    head->prev = nullptr;
    
    p->m_lastName = r->m_lastName;
    p->m_value = r->m_value;
    p->m_firstName = r->m_firstName;
    
    r = r->next;
    
    // if only one node
    if (r == nullptr)
    {
        p->next = nullptr;
    }
    
    else
    {
        Node *c = head;
        
        while(r != nullptr)// copying the rest of the nodes
        {
            c->next = new Node;
            c->next->prev = c;
            c = c->next;
            
            c->m_lastName = r->m_lastName;
            c->m_value = r->m_value;
            c->m_firstName = r->m_firstName;
            
            r = r->next;
        }
        
        c->next = nullptr;
        tail = c;
    }
    
    return *this;
}


bool CricketTeam::noTeam() const
{
    if(head == nullptr && tail == nullptr)
    {
        return true;
    }
    
    return false;
}


int CricketTeam::cricketerCount() const
{
    int length = 0;
    Node *p = head;
    
    while (p != nullptr)
    {
        length++;
        p = p->next;
    }
    return length; //returning amount of players/nodes
}


// add cricketer players
bool CricketTeam::addCricketer(const std::string& firstName, const std::string& lastName, const CricketType& value)
{
    // make new node for every player entry
    
    Node *p = new Node;
    p->m_firstName = firstName;
    p->m_lastName = lastName;
    p->m_value = value;

    // if no nodes yet, set head and tail to first node
    
    if (head == nullptr)
    {
        head = p;
        tail = p;
        return true;
    }

   // traverse through existing list
    
    Node* j = head;
    
    while (j != nullptr)
    {
        // checks if the new player is in the list already
        
        if (j->m_firstName == firstName && j->m_lastName == lastName)
        {
            // makes sure that there are not multiple attempts to enter the same name
            
            if (tail == j)
            {
                delete p;
                return false;
            }
            
            else
            {
                delete j;
                break;
            }
        }
        
        j = j->next;
    }

    
    j = head; // reset j at head
    
    // traverse to find the elements that are below the current name entry in the alphabet
    while (j != nullptr)
    {
        if (j->m_lastName > lastName || (j->m_lastName == lastName && j->m_firstName > firstName))
        {
            break;
        }
            
        j = j->next;
    }

    
    if (j == head) // if the node that is less than the entry is the first, or there is only one other node in the list
    {
        p->next = head;
        head->prev = p;
        head = p;
    }
    
    else if (j == nullptr) // if there are no nodes that are smaller than the entry, make current node the last node
    {
        p->prev = tail;
        tail->next = p;
        tail = p;
    }
    
    else // insert node in the middle
    {
        p->next = j;
        p->prev = j->prev;
        j->prev->next = p;
        j->prev = p;
    }

    return true;
}




bool CricketTeam::substituteCricketer(const std::string& firstName, const std::string& lastName, const CricketType & value)
{
    //if it meets conditions of first name and last name found, then store value in node
    Node *p = head;
    
    while (p != nullptr)
    {
        if(p->m_lastName == lastName)
        {
            if(p->m_firstName == firstName)
            {
                p->m_value = value;
                return true;
            }
        }
        
        p = p->next;
    }
    return false;
}

bool CricketTeam::addOrSubstitute(const std::string& firstName, const std::string& lastName, const CricketType& value)
{
    if(substituteCricketer(firstName, lastName, value) == false)
    {
        addCricketer(firstName, lastName, value);
        return true;
    }
    
    return true;
}


bool CricketTeam::releaseCricketer(const std::string& firstName, const std::string& lastName)
{
    if(head == nullptr && tail == nullptr)// if empty
    {
        return false;
    }
    
    //deleting first node
    else if( tail != nullptr && tail ->m_firstName == firstName && tail->m_lastName == lastName )
    {
        Node *p = tail;
        tail = p->prev;
        tail->next = nullptr;
        delete p;
        p = nullptr;
        return true;
    }
    
    //deleting last node
    else if(head->m_lastName == lastName && head != nullptr && head->m_firstName == firstName)
    {
        Node *p = head;
        head = p->next;
        head->prev = nullptr;
        delete p;
        p = nullptr;
        return true;
    }
    
    
    else// make sure everythings deleted
    {
        Node *j = head;
        
        while(j != nullptr)
        {
            if(lastName == j->m_lastName)
            {
                if(firstName == j->m_firstName)
                {
                    j->prev->next = j->next;
                    j->next->prev = j->prev;
                    delete j;
                    j = nullptr;
                    return true;
                }
            }
            
            j = j->next;
        }
        
        return false;
    }
}

// if both first and last name at current node are found, return true
bool CricketTeam::rosteredOnCricketTeam(const std::string& firstName, const std::string& lastName) const
{
    Node *p = head;
    
    while(p != nullptr)
    {
        if(p->m_lastName == lastName)
        {
            if( p->m_firstName == firstName)
            {
                return true;
            }
        }
        p = p->next;
    }
    return false;
}


bool CricketTeam::searchForCricketer(const std::string& firstName, const std::string& lastName, CricketType& value) const
{
    
    Node *p = head;
    
    while( p != nullptr)
    {
        if(p->m_lastName == lastName)
        {
            if( p->m_firstName == firstName)
            {
                value = p->m_value;// inserted value to current nodes value
                return true;
            }
        }
        p = p->next;
    }
    return false;
}


bool CricketTeam::checkTeamForCricketer(int i, std::string& firstName,std::string& lastName, CricketType & value) const
{
    if (i < 0 || i >= cricketerCount()) // if no nodes or entry for i is less than size of list
    {
        return false;
    }
    
    int count = -1; // starting at 0
    
    if (tail == nullptr && head == nullptr) // if no nodes
    {
        return false;
    }
    
    Node *c = head;
    
    while (c != nullptr) // traverse to find position of element i
    {
        count++;
        
        if(count == i) // if count is the same node as i
        {
            break;
        }
        
        c = c->next;
    }
    
    if(count == i && c != nullptr) // makes sure that element i is found
    {
        value = c->m_value;
        firstName = c->m_firstName;
        lastName = c->m_lastName;
        return true;
    }
    
    return false;
}

// swap head and tail
void CricketTeam::tradeCricketTeams(CricketTeam& other)
{
    Node *p = nullptr;
    p = this->head;
    this->head = other.head;
    other.head = p;
    
    Node *j = nullptr;
    j = this->tail;
    this->tail = other.tail;
    other.tail = j;
}




bool mergeCricketers(const CricketTeam & odOne,const CricketTeam & odTwo,CricketTeam & odJoined)
{
    bool nr = true;
    
    if(odOne.noTeam()) // test for if odOne is empty
    {
        odJoined = odTwo;
    }
    
    else if(odTwo.noTeam())// test for if odTwo is empty
    {
        odJoined = odOne;
    }
    
    else
    {
        odJoined = odOne;
        // traverse through each node and find duplicates
        for( int i = 0; i < odTwo.cricketerCount(); i++)
        {

            CricketType c, val;
            std::string fName, lName;
            
            odTwo.checkTeamForCricketer( i, fName, lName, val);
            
            if(odJoined.rosteredOnCricketTeam(fName, lName) == true)
            {
                odJoined.searchForCricketer(fName, lName, c);
                
                    if(val == c)
                    {
                        odJoined.substituteCricketer(fName, lName, c);
                    }
                
                    else
                    {
                        odJoined.releaseCricketer(fName, lName); // release the cricketer
                        nr = false;
                    }
            }
            else
            {
                odJoined.addCricketer(fName, lName, val);
            }
        }
    }
    return nr;
}

void checkCricketers(const std::string& fsearch,const std::string& lsearch,const CricketTeam& odOne,CricketTeam& odResult)
{
    CricketTeam p; // store values
    
    if(fsearch == "*" && lsearch == "*") // copy list
    {
        p = odOne;
    }
    
    else if(fsearch == "*")// search last name
    {
        for (int i = 0; i < odOne.cricketerCount(); i++)
        {
            
            std::string fName, lName;
            CricketType val;
            odOne.checkTeamForCricketer(i, fName, lName, val);
            
            if(lsearch == lName)// store in copy
            {
                p.addCricketer(fName, lName, val);
            }
        }
    }
    
    else if(lsearch == "*")// search first name
    {
        for (int i = 0; i < odOne.cricketerCount(); i++)
        {
            
            std::string fName, lName;
            CricketType val;
            odOne.checkTeamForCricketer(i, fName, lName, val);
            
            if(fName == fsearch)
            {
                p.addCricketer(fName, lName, val);
            }
        }
    }
    
    else if( lsearch != "*" && fsearch != "*")// search both
    {
        CricketType val;
        odOne.searchForCricketer(fsearch, lsearch, val);
        p.addCricketer(fsearch, lsearch, val);
    }
    
    odResult = p;
}

