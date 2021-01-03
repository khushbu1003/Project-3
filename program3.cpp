
//******************************************PROGRAM IDENTIFICATIION************************************************************
//*                                                                                                                           *
//* PROGRAM FILE NAME: program3.cpp    ASSIGNMENT #: 3              GRADE:___                                                 *
//*                                                                                                                           *
//* PROGRAM AUTHOR: KHUSHBU SHAH                                                                                              *
//*                                                                                                                           *
//* COURSE # : CSC 24400 11                          DUE DATE- Oct-23, 2019                                                   *
//*                                                                                                                           *
//*****************************************************************************************************************************

//******************************************* PROGRAM DESCRIPTION**************************************************************
//*                                                                                                                           *
//* PROCESS: This program is desinged to read a list of data consisting of student identification numbers                     *
//  and their test average.                                                                                                   *
//*          It is then to echo print the original list of students and scores. It is then to find and                        *
//print the student with the lowest test                                                                                      *
//*          score along with the student's identification number. It is also to find the student with the                    *
//highest test scoreand print the                                                                                             *
//*          student's information. Finally the program is to print the average test score for the entire class.              *
//*                                                                                                                           *
//* USER DEFINED                                                                                                              *
//* MODULES     : ReadData - reads the student IDs and test scores into an empty array                                        *
//                printdata - prints the original data in form of a list                                                      *
//*               PrintData-prints a listing of all students with their test scores                                           *
//*                StudIdHighTolow - sorts the array after the StudentID from high to low                                     *
//*                 average- calculates the test average for all students                                                     *
//*                testgrade - finds the corresponding grade for stidents                                                     *
//*                AvgHighToLow - sorts the array after the average from high to low                                          *
//*                                                                                                                           *
//*****************************************************************************************************************************


#include <iostream>

#include<string> 

#include<iomanip> 

#include<fstream> 

using namespace std;

void Header(ofstream& );
void Footer(ofstream& );
void readfile(ifstream& , float[][50], int[], int, float);
void printData(ofstream&, float[][50], int[], float [], char[]);
void StudIdHighToLow(int [], float [][50]);
void average(float [][50], float []);
void AvgHighToLow(int[], float[][50], float[]);
void TestGrad(float [], char []);



//******************************************************MAIN FUNCTION********************************************************
int main()
{
	//main function for variables, function calls and other definitions
	ifstream infile1("DATA3.TXT", ios::in);      //Tells the processor where to find the input file
	ofstream outfile1("results.txt", ios::out); // to outstream the result file

	//sets up the variable data types
	//declaration of the arrays
	int tempID = 0;
	float tempscores = 0;
	int StudID[50];			                  //Student's IDS
    float Scores[50][50];                     //score in test
	char grade[50];                           //Student Grade Type
	float testAvg[50];                        //average scores by student
	

	Header(outfile1);                         //prints the header to the outfile
	

	
	readfile(infile1, Scores, StudID, tempID, tempscores);
	printData(outfile1, Scores, StudID, testAvg, grade);
	
	
	Footer(outfile1);                         //prints the footer to the outfile
	//closes the files
	infile1.close();
	outfile1.close();
	cin.ignore();
	
			
}

//*****************************************************************************************************************************


//******************************************* FUNCTION READFILE****************************************************************

void readfile(ifstream& infile1, float Scores[][50], int StudID[], int tempID, float tempscores)
{
	//Receives- the data set for student Id's, scores and temerory placeholders
	//task- reads in the data from a file into the arrays
	//returns- the data of ID's in a array and the data of scors in a array
	int size = 0;
	
	
	

	while (infile1 >> tempID && tempscores >= 0 )
	{
		//body of the loop: writes the four values of the test scores to the array
		//tells the program how to call the scores
		
		StudID[size] = tempID;
		infile1 >> tempscores;
		Scores[size][0] = tempscores;
		infile1 >> tempscores;
		Scores[size][1] = tempscores;
		infile1 >> tempscores;
		Scores[size][2] = tempscores;
		infile1 >> tempscores;
		Scores[size][3] = tempscores;
		infile1 >> tempscores;
		size++;                          //update the value of size after one loop
		
	}
}
//*******************************************************************************************************************************


//******************************************PRINTDATA FUNCTION********************************************************************
void printData(ofstream& outfile1, float Scores[][50], int StudID[], float testAvg[], char grade[])
{
outfile1<< "The original Student Data is:"  <<endl;
outfile1 << "Student ID  Test1  Test 2  Test 3  Test 4" << endl;
outfile1 << "---------- ------  ------   ------  -----" << endl;
outfile1 << endl;                        //line space
for (int i = 0; StudID[i] >= 0; i++)
{
	outfile1 << setw(8) << StudID[i] << setw(10);
	outfile1 << fixed << showpoint << setprecision(1);
	outfile1 << Scores[i][0] << setw(8) << Scores[i][1] << setw(8) << setw(8) << Scores[i][2];
	outfile1 << setw(8) << Scores[i][3] << endl;
}
// heading for the data sorted from high to low
outfile1 << "The List of Students sorted by ID Number high to low is :" << endl;
outfile1 << "Student ID    Test1     Test2     Test3    Test4" << endl;
outfile1<<  "----------   --------   -------   -------   ------" << endl;

StudIdHighToLow(StudID, Scores);             //sorts the studentID from high to low
                                             // and get the corresponding dtata with
                                             //student ID

// prints the sorted data in the correct format
for (int i = 0; StudID[i] >= 0; i++)
{
	outfile1 << setw(8) << StudID[i] << setw(12);
	outfile1 << fixed << showpoint << setprecision(1);
	outfile1 << Scores[i][0] << setw(8) << Scores[i][1] << setw(8) << setw(8) << Scores[i][2];
	outfile1 << setw(8) << Scores[i][3] << endl;
}
outfile1 << endl;                       //line space

// prints the heading for data with average scores
outfile1 << "The List of students with their test average and course grade is :" << endl;
outfile1 << "                                                   Test        Course" << endl;
outfile1 << "Student ID    Test1    Test2    Test3    Test4    Average      Grade" << endl;
outfile1 << "----------     -----    -----   -----   -------   --------     -------" << endl;

//prints the sorted data +average scores and grades in correct form
for (int i = 0; StudID[i] >= 0; i++)
{

	outfile1 << setw(8) << StudID[i] << setw(12);
	outfile1 << fixed << showpoint << setprecision(2);
	average(Scores, testAvg);         //calculates the average of the scores
	TestGrad(testAvg, grade);         //set the grade after the average score
	outfile1 << Scores[i][0] << setw(8) << Scores[i][1] << setw(8) << Scores[i][2];
	outfile1 << setw(8) << Scores[i][3] << setw(8) << testAvg[i] << setw(8) << grade[i] << endl;
}

outfile1 << endl;                    //line space

//prints the heading for the data sorted by average
outfile1 << "The list of students sorted by test average high to low is :"<< endl;
outfile1 << "                                               Test      Course" << endl;
outfile1 << "Student ID      Test1   Test2   Test3  Test4  Average   Grade" << endl;
outfile1 << "----------     -----    -----   -----  ------ ------- -------" << endl;
//prints the complete data set sorted by the average score
for (int i = 0; StudID[i] >= 0; i++)
{
	outfile1 << setw(8) << StudID[i] << setw(12);
	outfile1 << fixed << showpoint << setprecision(1);

	average(Scores, testAvg);                          //calculates the average of the scores
	AvgHighToLow(StudID, Scores, testAvg);             // sorts the data after average high to low
	TestGrad(testAvg, grade);                          //nsets the grade after the average score


	outfile1 << Scores[i][10] << setw(8) << Scores[i][1] << setw(8) << Scores[i][2];
	outfile1 << setw(8) << Scores[i][3] << setw(8) << testAvg[i] << setw(8) << grade[i] << endl;
}

return;
}
//***************************************************************************************************************************


//**************************************************FUNCTION STUDIDHIGHTOLOW*************************************************
void StudIdHighToLow(int StudID[], float Scores[][50])
{
	//Receives - the data of the array studentID and scores
	//Task - Sort the data after Student ID high to low
	//Returns- Asorted list after printing student ID 
	int temp =0;                                  //temperory storage for sorting
	float temp1 = 0.0;                                //temperory storage for sorting
	//sorts the student ID from high to low and connects the scores with the belonging ID
	for (int i = 0; i < 50; i++)
	{
		for (int j = (i + 1); j < 50; j++)
		{
			if (StudID[i] < StudID[j])
			{
				//swaps the positions of the scores and ID in case the ID is higher than one
				temp = StudID[i];
				StudID[i] = StudID[j];
				StudID[j] = temp;

				temp1 = Scores[i][0];
				Scores[i][0] = Scores[j][0];
				Scores[j][0] = temp1;

				temp1 = Scores[i][1];
				Scores[i][1] = Scores[j][1];
				Scores[j][1] = temp1;

				temp1 = Scores[i][2];
				Scores[i][2] = Scores[j][2];
				Scores[j][2] = temp1;

				temp1 = Scores[i][3];
				Scores[i][3] = Scores[j][3];
				Scores[j][3] = temp1;
			}
		}
	}
	return;
}
//****************************************************************************************************************************

//******************************************************FUNCTION AVERAGE*******************************************************

void average(float Scores[][50], float testAvg[])
{
	//receives- the data of the array scores and test average
	//Task- calculates the average test score for each student
	//return- the test average from each student

	//calculates the average scores for students
	for (int i = 0; i < 50; i++)
	{
		//calculates all 4 scores per student together and divides by 4 test scores
		testAvg[i] = ((Scores[i][0] + Scores[i][i] + Scores[i][2] + Scores[i][3]) /(int) 4);
	}
	return;
	}
//****************************************************************************************************************************

//******************************************************FUNCTION TESTGRAD******************************************************
void TestGrad(float testAvg[], char grade[])
    //Receives- gets the test average
	//task- finds the belonging grade by getting the average
	//Returns- A grade for each student

{
	for (int i = 0; i < 50; i++)                           //sets the grade to A for 90 or more than 90
	{
		if (testAvg[i] >= 90)
			grade[i] = 'A';

	}
	for (int i = 0; i < 50; i++)                           //sets the grade between 80 to 90
	{
		if (testAvg[i] >= 80 && testAvg[i] <90)
			grade[i] = 'B';

	}
	for (int i = 0; i < 50; i++)                           //sets the grade between 70 to 80
	{
		if (testAvg[i] >= 70 && testAvg[i] < 80)
			grade[i] = 'C';

	}
	for (int i = 0; i < 50; i++)                           //sets the grade between 60 to 70
	{
		if (testAvg[i] >= 60 && testAvg[i] < 70)
			grade[i] = 'D';

	}
	for (int i = 0; i < 50; i++)                           //sets the grade between 60 to 70
	{
		if (testAvg[i]< 60)
			grade[i] = 'F';

	}
}
//****************************************************************************************************************************


//******************************************************FUNCTION AVGHIGHTOLOW*************************************************
void AvgHighToLow(int StudID[], float Scores[][50], float testAvg[])
{
    //Receives - the data of the arrays student ID, scores and the value of test averages
	//Task- sorts the data by average from high to low
	// Returns- A list of sorted data by average from high to low
	int temp;                                         //temperory placeholder              
	float temp1;                                     //temperory placeholder              
	for (int i = 0; i < 50; i++)
	{
		for (int j = (i + 1); j < 50; j++)
		{
         //sorts the entire data after average from high to low
         //swaps the position of the scores and ID in case the ID is higher than the next one
			if (testAvg[i] < testAvg[j])
			{
				temp = testAvg[i];
				testAvg[i] = testAvg[j];
				testAvg[j] = temp;

				temp1 = Scores[i][0];

				Scores[i][0] = Scores[j][0];
				Scores[j][0] = temp1;

				temp1 = Scores[i][1];
				Scores[i][1] = Scores[j][1];
				Scores[j][1] = temp1;

				temp1 = Scores[i][2];
				Scores[i][2] = Scores[j][2];
				Scores[j][2] = temp1;

				temp1 = Scores[i][3];
				Scores[i][3] = Scores[j][3];
				Scores[j][3] = temp1;

			}

		}
	 }
	return;

}
//****************************************************************************************************************************

//******************************************************FUNCTION HEADER********************************************************

void Header(ofstream & outfile1)
{
 //Receives - the output file
 // task - Prints the output premble
 // Returns - Nothing
 outfile1 << setw(30) << "Khushbu Shah";
 outfile1 << setw(17) << "CSC 24400";
 outfile1 << setw(15) << "Section 11" << endl;
 outfile1 << setw(30) << "FALL 2019";
 outfile1 << setw(20) << "Assignment 3" << endl;
 outfile1 << setw(35) << "--------------------------------------------";
 outfile1 << setw(35) << "--------------------------------------------" << endl << endl;

return;
}
//*****************************************************************************************************************************

//******************************************************FUNCTION FOOTER********************************************************

void Footer(ofstream & outfile1)

{
 //receives- the output file
 //Task- Prints the output salutation
 //Returns- Nothing

   outfile1 << endl;

   outfile1 << setw(35) << "--------------------------------------------" << endl;

   outfile1 << setw(35) << "|         END OF PROGRAM OUTPUT             |" << endl;

   outfile1 << setw(35) << "--------------------------------------------" << endl;

return;

}
		
//***********************************************************************************************************************************
