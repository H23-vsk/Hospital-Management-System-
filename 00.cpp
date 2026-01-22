#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

/* ================== Hospital Class ================== */
class Hospital {
private:
    string name;
    string address;
    string bloodGroup;

public:
    Hospital() : name(""), address(""), bloodGroup("") {}

    void setName(const string& n) {
        name = n;
    }

    void setAddress(const string& a) {
        address = a;
    }

    void setBloodGroup(const string& bg) {
        bloodGroup = bg;
    }

    string getName() const {
        return name;
    }

    string getAddress() const {
        return address;
    }

    string getBloodGroup() const {
        return bloodGroup;
    }
};

/* ================== Admit Patient ================== */
void admitPatient(Hospital& patient) {
    system("cls");

    string name, address, group;

    cout << "\tEnter Name Of Patient: ";
    cin >> name;

    cout << "\tEnter Address Of Patient: ";
    cin >> address;

    cout << "\tEnter Blood Group Of Patient: ";
    cin >> group;

    patient.setName(name);
    patient.setAddress(address);
    patient.setBloodGroup(group);

    ofstream outfile("D:/Hospital.txt", ios::app);

    if (!outfile) {
        cout << "\tError: File can't open!" << endl;
    } else {
        outfile << patient.getName() << " "
                << patient.getAddress() << " "
                << patient.getBloodGroup() << endl;

        cout << "\n\tPatient Admitted Successfully!" << endl;
    }

    outfile.close();
    Sleep(3000);
}

/* ================== Discharge Patient ================== */
void dischargePatient() {
    system("cls");

    string name;
    cout << "\tEnter Name of Patient to Discharge: ";
    cin >> name;

    ifstream infile("D:/Hospital.txt");
    ofstream outfile("D:/HospitalTemp.txt");

    if (!infile || !outfile) {
        cout << "\tError: File can't open!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        string patientName;
        ss >> patientName;

        if (patientName == name) {
            found = true;
            cout << "\n\tPatient Discharged Successfully!" << endl;
        } else {
            outfile << line << endl;
        }
    }

    if (!found) {
        cout << "\n\tPatient Not Found!" << endl;
    }

    infile.close();
    outfile.close();

    remove("D:/Hospital.txt");
    rename("D:/HospitalTemp.txt", "D:/Hospital.txt");

    Sleep(3000);
}

/* ================== Main Function ================== */
int main() {
    Hospital patient;
    bool exitProgram = false;

    while (!exitProgram) {
        system("cls");

        int choice;
        cout << "\n\tHospital Management System";
        cout << "\n\t**************************";
        cout << "\n\t1. Admit Patient";
        cout << "\n\t2. Discharge Patient";
        cout << "\n\t3. Exit";
        cout << "\n\n\tEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            admitPatient(patient);
            break;

        case 2:
            dischargePatient();
            break;

        case 3:
            system("cls");
            cout << "\n\tGood Luck!" << endl;
            exitProgram = true;
            Sleep(2000);
            break;

        default:
            cout << "\n\tInvalid Choice!" << endl;
            Sleep(2000);
        }
    }

    return 0;
}
