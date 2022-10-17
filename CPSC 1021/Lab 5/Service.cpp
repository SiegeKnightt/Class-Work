// Alex Gravlee
#include <string>
#include "Service.h"
using namespace std;

    Service::Service(string n, string a, string e, string dpt, int ys) {
        name = n;
        address = a;
        email = e;
        department = dpt;
        yearsService = ys;
    }

    void Service::setName(string n) {
        name = n;
    }
    void Service::setAddress(string a) {
        address = a;
    }
    void Service::setEmail(string e) {
        email = e;
    }
    void Service::setDepartment(string dpt) {
        department = dpt;
    }
    void Service::setYearsService(int ys) {
        yearsService = ys;
    }