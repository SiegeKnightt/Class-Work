// Reeves Farrell
#ifndef VISITOR_H
#define VISITOR_H
#include <string>

using namespace std;

class Visitor {
    
    private:
        string name;
        string address;
        string email;
        string duration;
        bool parent;
    public:
        string getName();
        string getAddress();
        string getEmail();
        string getDuration();
        bool getParent();
        void setName(string n);
        void setAddress(string a);
        void setEmail(string e);
        void setDuration(string d);
        void setParent(bool p);
};
#endif