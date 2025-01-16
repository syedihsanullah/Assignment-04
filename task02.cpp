#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Patient {
    int patientID;
    string name;
    int age;
    string disease;
    int roomNumber;
};

void load_Patients(Patient patients[], int& count);
void save_Patients(Patient patients[], int count);
void add_Patient(Patient patients[], int& count);
void search_Patient(Patient patients[], int count);
void display_Patients(Patient patients[], int count);

const int MAX_PATIENTS = 100; 
int main() {
    Patient patients[MAX_PATIENTS];
    int patient_Count = 0;

    load_Patients(patients, patient_Count);

    int option;
    do {
        cout << "\nHospital Patient Management System\n";
        cout<<"-----------------------------------\n";
        cout << "1. Add New Patient\n";
        cout << "2. Search for a Patient\n";
        cout << "3. Display All Patients\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
        cin >> option;

        if (option == 1) {
            add_Patient(patients, patient_Count);
        } else if (option == 2) {
            search_Patient(patients, patient_Count);
        } else if (option == 3) {
            display_Patients(patients, patient_Count);
        } else if (option == 4) {
            save_Patients(patients, patient_Count);
            cout << "Goodbye! Data saved.\n";
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    } while (option != 4);

    return 0;
}

void load_Patients(Patient patients[], int& count) {
    ifstream file("patients.txt");
    count = 0;
    if (file.is_open()) {
        while (file >> patients[count].patientID) {
            file.ignore(); 
            getline(file, patients[count].name);
            file >> patients[count].age;
            file.ignore(); 
            getline(file, patients[count].disease);
            file >> patients[count].roomNumber;
            file.ignore(); 
            count++;
        }
        file.close();
    } else {
        cout << "No existing patient records found. Starting fresh.\n";
    }
}

void save_Patients(Patient patients[], int count) {
    ofstream file("patients.txt");
    if (file.is_open()) {
        for (int i = 0; i < count; i++) {
            file << patients[i].patientID << "\n";
            file << patients[i].name << "\n";
            file << patients[i].age << "\n";
            file << patients[i].disease << "\n";
            file << patients[i].roomNumber << "\n";
        }
        file.close();
    } else {
        cout << "Error saving data to file.\n";
    }
}

void add_Patient(Patient patients[], int& count) {
    if (count >= MAX_PATIENTS) {
        cout << "Cannot add more patients, hospital is full.\n";
        return;
    }

    cout << "Enter Patient ID: ";
    cin >> patients[count].patientID;
    cin.ignore(); 
    cout << "Enter Name: ";
    getline(cin, patients[count].name);
    cout << "Enter Age: ";
    cin >> patients[count].age;
    cin.ignore(); 
    cout << "Enter Disease: ";
    getline(cin, patients[count].disease);
    cout << "Enter Room Number: ";
    cin >> patients[count].roomNumber;

    count++;
    cout << "Patient added successfully!\n";
}

void search_Patient(Patient patients[], int count) {
    int id;
    cout << "Enter Patient ID to search: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (patients[i].patientID == id) {
            cout << "Patient Found:\n";
            cout << "ID: " << patients[i].patientID << "\n";
            cout << "Name: " << patients[i].name << "\n";
            cout << "Age: " << patients[i].age << "\n";
            cout << "Disease: " << patients[i].disease << "\n";
            cout << "Room Number: " << patients[i].roomNumber << "\n";
            return;
        }
    }
    cout << "Patient not found with ID " << id << ".\n";
}

void display_Patients(Patient patients[], int count) {
    if (count == 0) {
        cout << "No patients admitted currently.\n";
        return;
    }

    cout << "=== List of Admitted Patients ===\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << patients[i].patientID << "\n";
        cout << "Name: " << patients[i].name << "\n";
        cout << "Age: " << patients[i].age << "\n";
        cout << "Disease: " << patients[i].disease << "\n";
        cout << "Room Number: " << patients[i].roomNumber << "\n\n";
    }
}