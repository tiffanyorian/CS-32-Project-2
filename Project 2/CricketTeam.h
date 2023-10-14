//
//  CricketTeam.h



#ifndef CRICKETTEAM_H
#define CRICKETTEAM_H
#include <iostream>
#include <string>



typedef std::string CricketType;


class CricketTeam;


bool mergeCricketers(const CricketTeam & odOne,const CricketTeam & odTwo,CricketTeam & odJoined);

void checkCricketers(const std::string& fsearch,const std::string& lsearch,const CricketTeam& odOne,CricketTeam& odResult);



class CricketTeam
{
    
private:
    
    struct Node
    {
        Node *next = nullptr;
        
        Node *prev = nullptr;
        
        CricketType m_value;
        
        std::string m_lastName;
        
        std::string m_firstName;
    };
    
    Node *head = nullptr;
    Node *tail = nullptr;
    
public:
    CricketTeam(); // default constructor
    
    ~CricketTeam();// destructor
    
    CricketTeam(const CricketTeam& rhs);// copy constructor
    
    const CricketTeam& operator=(const CricketTeam& rhs);// assignment operator
    
    
    bool noTeam() const;// if no team
    
    int cricketerCount() const;// counts nodes
    
    // add new cricketer
    bool addCricketer(const std::string& firstName, const std::string&
                      lastName, const CricketType& value);
    
    
    bool substituteCricketer(const std::string& firstName, const
                             std::string& lastName, const CricketType & value);
    
  
    bool addOrSubstitute(const std::string& firstName, const
                         std::string& lastName, const CricketType& value);
    
    
    
    bool releaseCricketer(const std::string& firstName, const
                          std::string& lastName);
    
    
    
    bool rosteredOnCricketTeam(const std::string& firstName, const
                               std::string& lastName) const;
    
    
    
    bool searchForCricketer(const std::string& firstName, const
                            std::string& lastName, CricketType& value) const;
    
    
    
    bool checkTeamForCricketer(int i, std::string& firstName,
                               std::string& lastName, CricketType & value) const;
    
    
    void tradeCricketTeams(CricketTeam& other);
    
    
};


#endif /* CricketTeam_h */
