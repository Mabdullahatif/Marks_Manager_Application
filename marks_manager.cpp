
/* Made by L21-5695 && L21-6225 */

#include<iostream>
#include<iomanip>
#include<fstream>
#include <windows.h>
using namespace std;

const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int LIGHTGRAY = 7;
const int DARKGRAY = 8;
const int LIGHTBLUE = 9;
const int LIGHTGREEN = 10;
const int LIGHTCYAN = 11;
const int LIGHTRED = 12;
const int LIGHTMAGENTA = 13;
const int LIGHTYELLOW = 14;
const int WHITE = 15;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


int TotalStudents;
bool isLoaded;
int MagicNo, Evaluation_Count, MGN, Weightage, space_count;
int ID[100];
double Marks[100][11], TotalMarks[100], Weight[100], Sorted[100][11];
double Statistics[10][11];


void LoadWarn(){
	setColor(4);
	cout << endl << "Please Load the files first!" << endl
         << "Press any key to continue further..." << endl;
    setColor(7);
    cin.get();
    cin.get();
}

void SwapElem(double A[][11], int row1, int row2, int col1, int col2){
    int M;
    M = A[row1][col1];
    A[row1][col1] = A[row2][col2];
    A[row2][col2] = M;
}


int presentMenu()
{
    int Choice = 0;
    do {
    	setColor(3);
        cout << "\t Marks Manager" << endl << endl;
        setColor(14);
        cout << "1. Load Data" << endl
             << "2. Save" << endl
             << "3. Add" << endl
             << "4. Delete" << endl
             << "5. Sort" << endl
             << "6. View All" << endl
             << "7. Search" << endl;
        setColor(4);
        cout << "8. Exit" << endl;
        setColor(10);
        cout << endl << "Enter Your Choice (1-8) ";

        if (Choice < 0 || Choice > 8)
        setColor(4);
            cout << endl << "Please enter a valid choice between 1 and 8 " << endl;
        setColor(7);

        cin >> Choice;
    } while (Choice < 1 || Choice > 8);

    return Choice;
}


void CalStat(){

    for(int r=0; r<=TotalStudents; r++){                // Reseting Total + Weight
        TotalMarks[r] = 0;
        Weight[r] = 0;
    }

    for(int r=0; r<=TotalStudents; r++)                 // Calculating Total
    {
        for(int c=0; c<=Evaluation_Count; c++)
        {
            TotalMarks[r] = TotalMarks[r] + Marks[r][c];
        }
    }

     for(int r=1, c; r<=TotalStudents; r++)                // Calculating Weightage
    {
        for(c=0; c<=Evaluation_Count; c++)
        {
                Weight[r] = Weight[r] + (Marks[r][c]*Weightage);
        }
            Weight[r] = Weight[r] / (Evaluation_Count*Weightage);
    }

    for(int r=1, c=0, i=0; r<=TotalStudents; r++){      // Storing ID in Statistics
		Statistics[r][c] = ID[i];
		i++;
	}

    for(int r=0; r<=TotalStudents; r++)                 // Storing Marks in Statistics
    {
        for(int c=1,i=0; c<=Evaluation_Count; c++){
            Statistics[r][c] = Marks[r][i];
            i++;
         }
    }

    for(int r=0; r<=TotalStudents; r++)                 // Storing Total Marks and Weightage in Statistics
    {
        Statistics[r][Evaluation_Count+1] = TotalMarks[r];
        Statistics[r][Evaluation_Count+2] = Weight[r];
    }
}

void LoadData(){

	if(isLoaded){
		setColor(2);
		cout << endl << "Data already Loaded!" << endl
			 << "Press any key to continue.." << endl;
		setColor(7);
		cin.get(); cin.get();
		return;
	}
	ifstream ReadStudent, ReadMarks;
	ReadStudent.open("STUDENT.DAT");
    ReadMarks.open("MARKS.DAT");

    ReadStudent >> MagicNo >> TotalStudents;

	for(int i=0; i<TotalStudents; i++)                  // ID Fetch
		ReadStudent >> ID[i];

    ReadMarks >> MGN >> Weightage >> Evaluation_Count;

    for(int r=0; r<=TotalStudents; r++){                // Evaluations Fetch
    	for(int c=0; c<Evaluation_Count; c++)
    		ReadMarks >> Marks[r][c];
	}

	ReadStudent.close();
	ReadMarks.close();
	setColor(10);
	cout<<"----------------------------------";
	cout << " \nData Loaded Successfully! \n";
	cout << "Magic No: " << MagicNo << endl;
	cout << "Total Students: " << TotalStudents << endl << endl;
	setColor(7);

	isLoaded = true;
	CalStat();
}

void Add(){
	if(!isLoaded){
		LoadWarn();
		return;
	}
	cout << endl << "Enter the maximum marks of the component: "<<endl;
	for(int r=0; r<=TotalStudents; r++){                // Adding Marks
        if(r!=0){
            cout << "Enter the marks of Roll No. " << ID[r-1] << "\t";
            do{

                if(Marks[r][Evaluation_Count] > Marks[0][Evaluation_Count])
                    cout << "Please enter valid marks within the maximum range:  ";

                cin >> Marks[r][Evaluation_Count];

            }while(Marks[r][Evaluation_Count] > Marks[0][Evaluation_Count]);
        }
        else
            cin >> Marks[r][Evaluation_Count];

    }
    Evaluation_Count++;
    space_count = space_count+4;

    CalStat();
}

void Save(){

	if(!isLoaded){
		LoadWarn();
		return;
	}
	ofstream WriteMarks;
    WriteMarks.open("MARKS.DAT");
    WriteMarks << MGN << endl
               << Weightage << endl
               << Evaluation_Count << endl;

    for(int r=0; r<=10; r++)                            // Writing Data into files
    {
        for(int c=0; c<10; c++){
            if(Marks[r][c]!=0)
                WriteMarks << Marks[r][c] << "\t";
        }
        if(Marks[r][0]!=0)
        WriteMarks << endl;
    }
    WriteMarks.close();
    setColor(2);
    cout << endl << endl << "Data saved to files successfully." << endl;
    setColor(7);
}

void Delete(){
	if(!isLoaded){
		LoadWarn();
		return;
	}
	setColor(4);	
	cout << endl << "Enter a component to delete the marks [0 ---- so on....]: "<<endl;
	setColor(7);
    int del_comp;
    cin >> del_comp;

    for(int r=0; r<=TotalStudents; r++)                 // Deleting column component
        Marks[r][del_comp] = 0;

    Evaluation_Count--;
    space_count--;
    CalStat();
}

void Sort(){
    if(!isLoaded){
		LoadWarn();
		return;
	}

	int choice;

	do{
	cout << "\n\t How do you want to sort the data? \n\n"
         << "1. Roll No (Ascending) \n"
         << "2. Roll No (Descending) \n"
         << "3. Total(Ascending)\n"
         << "4. Total (Descending)"
         << endl << endl
         << "\t Please enter a valid choice [1-2] \n";
    cin >> choice;

    if(choice < 1 || choice > 4)
        cout << endl << "Please enter a valid choice!" << endl << endl;

	}while(choice < 1 || choice > 4);

	int Statistics_count = Evaluation_Count+2;

	if(choice == 1){
        for(int s=1; s<=TotalStudents; s++)
        {   for(int j=s+1; j<=TotalStudents; j++)
        		if(Statistics[s][0] > Statistics[j][0]){
        			for(int c=0; c<=Statistics_count; c++)
                        SwapElem(Statistics, s, j, c, c);
        		}
			}
    	}

    if(choice == 2){
        for(int s=1; s<=TotalStudents; s++)
        {   for(int j=s+1; j<=TotalStudents; j++)
        		if(Statistics[s][0] < Statistics[j][0]){
        			for(int c=0; c<=Statistics_count; c++)
                        SwapElem(Statistics, s, j, c, c);
        		}
			}
    	}

    if(choice == 3){
        for(int s=1; s<=TotalStudents; s++)
        {   for(int j=s+1; j<=TotalStudents; j++)
        		if(Statistics[s][Evaluation_Count+1]>Statistics[j][Evaluation_Count+1]){
        			for(int c=0; c<=Statistics_count; c++)
                        SwapElem(Statistics, s, j, c, c);
        		}
			}
        }

    if(choice == 4){
        for(int s=1; s<=TotalStudents; s++)
        {   for(int j=s+1; j<=TotalStudents; j++)
        		if(Statistics[s][Evaluation_Count+1] < Statistics[j][Evaluation_Count+1]){
        			for(int c=0; c<=Statistics_count; c++)
                        SwapElem(Statistics, s, j, c, c);
        		}
			}
        }
	setColor(2);
    cout << endl << "\tThe record have been sorted successfully!" << endl
    << "\tUse ViewAll(6) to view the sorted record." << endl << endl;
    setColor(7);
    }

void ViewAll(){

	if(!isLoaded){
		LoadWarn();
		return;
	}

	cout << setprecision(4);
        if(Evaluation_Count==0){
        	setColor(13);
            cout << left << setw(4) << "----" << right << setw(18) << "-------------" << setw(17) << "-----\n"<<endl;
            cout << left << setw(4) << " ID" << right << setw(18) << "Maximum Marks" << setw(17) << "Total\n"<<endl;
            cout << left << setw(4) << "----" << right << setw(18) << "-------------" << setw(17) << "-----\n"<<endl;
            setColor(7);
        }
        else{
        	setColor(13);
            cout << left << setw(4) << "----" << right << setw(8+space_count) << "-----------" << setw(12) << "-----\n"<<endl;
            cout << left << setw(4) << " ID" << right << setw(8+space_count)  << "Maximum Marks" << setw(12) << "Total\n"<<endl;
            cout << left << setw(4) << "----" << right << setw(8+space_count) << "-----------" << setw(12) << "-----\n"<<endl;
            setColor(7);
        }
    for(int r=0; r<=TotalStudents; r++)                  // Viewing ID + Marks
    {
        for(int c = 0; c<=Evaluation_Count+2; c++){
            if(c==0){
                if(Statistics[r][c] !=0)
                    cout << left << setw(8) << Statistics[r][c];
                else
                    cout << left << setw(8) << " ";
            }
            else if(c == Evaluation_Count+1 && Statistics[r][c] !=0)   {      // Total
                cout << setw(11) << Statistics[r][c];
            }
            else if(c == Evaluation_Count+2 && Statistics[r][c] !=0){    // Weightage
                cout << setfill('-') << setw(7) << Statistics[r][c] << setfill(' ');
            }
            else if(Statistics[r][c] !=0){                              // Marks
                cout << right << setw(5) << Statistics[r][c];
            }
         }
            if((Statistics[r][0] !=0) || (r==0))
                cout << endl;
            if(r==0)
                cout << endl;
    }
    cout << endl;
}

void specific_Record_show(){

        if(!isLoaded){
		LoadWarn();
		return;
	}
        cout << endl << "Enter the roll no. of the student to show record: ";
        int record, Statistics_count, rec;
        cin >> record;
        Statistics_count = Evaluation_Count+2;

        for(int i=0; i<=TotalStudents; i++)
        {
            if(Statistics[i][0]== record)
                rec = i;
        }

        cout << endl << "\t The record of the student specified is: " << endl << endl;
        for(int c=0; c<=Statistics_count; c++)
        {
            if(Statistics[rec][c] !=0)
                cout << Statistics[rec][c] << "\t";
        }
        cout << endl << endl;

}

int main()
{
    int Selection = 0;
    do {
        Selection = presentMenu();
        if (Selection == 1) {
        	setColor(10);
            cout << endl << "Loading Data: " << endl;
            setColor(7);
            LoadData();
        }
        else if (Selection == 2) {
            Save();
        }
        else if (Selection == 3) {
            Add();
        }
        else if (Selection == 4) {
            Delete();
        }
        else if (Selection == 5) {
            Sort();
        }
        else if (Selection == 6) {
            ViewAll();
        }
        else if (Selection == 7) {
            specific_Record_show();
        }

    } while (Selection != 8);

    return 0;
}
