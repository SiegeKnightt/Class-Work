#ifndef PATIENT_H
#define PATIENT_H

class Patient {

    private:
        int days;
        double rate;
        double services;
        double medication;
        char patientType;
        bool validateInput(double);
        bool validateInput(int);
    public:
        Patient() {
            days = 0;
            rate = 0.0;
            services = 0.0;
            medication = 0.0;
            patientType = 'I';
        }
        Patient(char pt, double s, double m) {
            patientType = pt;
            services = s;
            medication = m;
        }
        bool setPatientType(char);
        bool setDays(int);
        bool setRate(double);
        bool setServices(double);
        bool setMedication(double);
        char getPatientType();
        int getDays();
        double getRate();
        double getServices();
        double getMedication();
        double calcTotalCharges(int, double, double, double);
        double calcTotalCharges(double, double);
        double calcTotalCharges();
};

#endif