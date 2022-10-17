#include <string>
#include <iomanip>
#include "Moped.h"
using namespace std;

    Moped::Moped(string mk, string mdl, int y, string lp, int mp, int cd) {
        make = mk;
        model = mdl;
        year = y;
        licensePlate = lp;
        mopedPower = mp;
        commuteDistance = cd;
    }

    void Moped::setMake(string mk) {
        make = mk;
    }
    void Moped::setModel(string mdl) {
        model = mdl;
    }
    void Moped::setYear(int y) {
        year = y;
    }
    void Moped::setLicensePlate(string lp) {
        licensePlate = lp;
    }
    void Moped::setMopedPower(int mp) {
        mopedPower = mp;
    }
    void Moped::setCommutedistance(int cd) {
        commuteDistance = cd;
    }