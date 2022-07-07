#include<iostream>
#include<cstring>
#include<iomanip>
#include<stdlib.h>
#include<climits>
#include<algorithm>
using namespace std;

#define MAX_PATIENTS 100
int patients[MAX_PATIENTS]  = {0};
string receptionistName = "";

class node
{
    public:
    string patientName;
    int appId;
    node *next;

    node(string name)       // will appoint a random appointment number
    {
        patientName=name;
        next = NULL;
        appId = rand() % MAX_PATIENTS;
        while(patients[appId] != 0)
        {
            appId = rand()%MAX_PATIENTS;
        }
        patients[appId] = 1;
    }

    node(string name, int aId)  // no need of random appointment
    {
        patientName = name;
        next = NULL;
        appId = aId;
        patients[appId] = 1;
    }
};

node * getNewPatient();

#include"singleLinkedList.h"

void handlingPatient(singleLL *);
void delay();
void conversation();
string validateName(string);


bool onlySpaces(char a, char b)
{
    if(a==b && a==' ')
        return true;
    return false;
}

int main()
{
    cout<<"** WELCOME TO GROUP-5 HOSPITAL **\n";

    while(1)
    {
        cout<<"\nReceptionist Information : ";
        cout<<"\nEnter your name : ";
        getline(cin ,receptionistName);

        receptionistName = validateName(receptionistName);

        if(receptionistName.compare("-1") == 0)
            cout<<"* Please enter a valid name. Try Again! *\n";
        else
            break;
    }

    conversation();
    memset(patients, 0, sizeof(patients));  // Used to assign 0 values to 'patients' array

    singleLL * patientList = new singleLL();

    int option = 0;

    while(option!=5)
    {

        cout<<"\n\n********** MAIN MENU **********\n";
        cout<<"1. Add new patient\n";
        cout<<"2. Arrange already existing patients\n";
        cout<<"3. Display Patients\n";
        cout<<"4. Assign a patient to doctor\n";
        cout<<"5. Done with today's work\n";

        cin>>option;
        cout<<endl;

        switch(option)
        {
            case 1: if(patientList->isFull())
                        cout<<"Sorry! All the slots are already booked. Try again after sometime. \n";
                    else
                        patientList->insertNode(patientList->countPatients()+1);
                    break;

            case 2: patientList->arrangeList();
                    //break;

            case 3: patientList->printList();
                    break;

            case 4: handlingPatient(patientList);       // assigning to doctor
                    break;

            case 5: cout<<"Thankyou "<<receptionistName<<"! For being the receptionist of our Group-5 Hospital.\n";delay();
                    cout<<"Have a nice day :)\n\n";
                    break;

            default:cout<<"Please select a valid option :) Try Again\n";
                    break;
        }
    }
    return 0;
}

void delay()
{
    for(long long int i=0;i<(int)1e8;i++);
}

void conversation()
{
    char rcpName[1000];
    strcpy(rcpName , receptionistName.c_str());

    printf("\n");
    printf("Doctor : Welcome, %s!\n", rcpName);delay();
    printf("         You are the new receptionist of our prestigious hospital.\n");delay();
    printf("         And now its your duty to handle our customers properly.\n");delay();
    printf("         And i hope you will do your job efficiently :)");delay();

    printf("\n\n");delay();
    printf("%s : Sure Doctor! But what i am supposed to do?", rcpName);

    printf("\n\n");delay();
    printf("Doctor : Don't worry about that. You will be provided with a menu.\n");delay();
    printf("         In which you have to select an option depending upon the situation that arises.");delay();

    printf("\n\n");delay();
    printf("%s : Okay Doctor :)\n", rcpName);
    printf("\n");delay();

}

node *getNewPatient()
{
    char rcpName[1000];
    strcpy(rcpName, receptionistName.c_str());

    printf("%s :\n", rcpName);delay();
    printf("    Good Morning Mam/Sir, Welcome to GROUP-5 Hospital.\n");delay();
    printf("    Please provide some details so that we can arrange a meeting for you with the doctor.\n");delay();

    printf("Patient : Sure %s \n\n", rcpName);delay();

    string name;
    printf("%s : What's your name?\n", rcpName);delay();
    printf("Patient : ");delay();
    cin.ignore();
    getline(cin, name);

    name = validateName(name);

    if(name.compare("-1") == 0)
    {
        cout<<"* Please enter a valid name. Try Again! *\n";delay();

        while(1)
        {
            cout<<"\nEnter your name : ";
            getline(cin ,name);

            name = validateName(name);

            if(name.compare("-1") == 0)
                cout<<"* Please enter a valid name. Try Again! *\n";
            else
                break;
        }
    }

    string option="";
    printf("\n");
    printf("%s : Do you have an appointment id ?(Yes/No)?\n", rcpName);delay();

    printf("Patient : ");delay();
    getline(cin, option);

    transform(option.begin(), option.end(), option.begin(), ::tolower);

    int aId;
    printf("\n");delay();
    if(option.compare("y")==0 || option.compare("yes")==0)
    {
        printf("\n%s : Enter your appointment id : \n", rcpName);delay();
        printf("*  Appointment ID must be between 0 and %d  *\n", MAX_PATIENTS-1);delay();
        cin>>aId;

        while(!(aId>=0 && aId<MAX_PATIENTS))
        {
            printf(" * Please enter a valid appointment ID. Try Again!*\n");

            printf("\n%s : Enter your appointment id : \n", rcpName);delay();
            printf("*  Appointment ID must be between 0 and %d  *\n", MAX_PATIENTS-1);delay();
            cin>>aId;
            delay();
        }

        if(patients[aId] != 0)
        {
            printf("%s :\n", rcpName);
            printf("    This appointment id has already been taken :(\n");delay();
            printf("    We are assigning a new appointment number to you.\n");delay();
            printf("    Sorry for the inconvenience.\n");delay();
            node * newNode = new node(name);
            printf("\n    Appointment number %d, has been allocated to you.\n", newNode->appId);delay();
            return newNode;
        }
        else
        {
            node * newNode = new node(name, aId);
            printf("\n    Appointment number %d, has been allocated to you.\n", newNode->appId);delay();
            return newNode;
        }
    }
    else
    {
        printf("%s :\n", rcpName);delay();
        printf("    Not a problem.\n");delay();
        printf("    We will assign you a new appointment number.\n");delay();
        node * newNode = new node(name);
        printf("\n");
        printf("    Appointment number %d, has been allocated to you.\n", newNode->appId);delay();
        return newNode;
    }
}

void handlingPatient(singleLL * patientList)
{
    if(!patientList || patientList->isEmpty())
    {
        cout<<"** No patients are there to assign to doctor **";delay();
        return;
    }

    int pos = patientList->findSmallestAppNoPatient();

    node *patientDone = patientList->DeleteFromPatientPosition(pos);

    string pName = patientDone->patientName;
    char patientName[1000];
    strcpy(patientName, pName.c_str());

    printf("\n");
    printf(" * Patient with minimum appointment ID will be allocated first *\n\n");
    printf("Patient : %s, is being treated by doctor", patientName);delay();
    printf(".");delay();
    printf(".");delay();
    printf(".");delay();
    printf("\n");

    printf("\n**  Treatment completed, Patient : %s, has been released  **\n", patientName);delay();
}

string validateName(string str)
{
    string name = "";
    str.erase(unique(str.begin(), str.end(), onlySpaces), str.end());
    int index = 0;

    if(str[index]==' ')
        index++;

    while(index<str.size())
    {
        if( (str[index]>='a'&& str[index]<='z') || (str[index]>='A'&&str[index]<='Z') || str[index]==' ')
            name += str[index];
        else
            return "-1";
        index++;
    }
    if(name == "")
        return "-1";
    return name;
}
