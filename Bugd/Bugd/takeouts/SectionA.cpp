/**
#include <iostream>;
#include <string>;
#include<vector>

using namespace std;

class Student 
{
public:
	 string firstname;
	 string lastname;
	 string studentNumber;
	 int assessments[5];
	 
	 int finalMark= 0;

	 void calculateGrades()
	 {
		 
		 for (int i = 0; i < 5; i++) {
			 finalMark = (finalMark + assessments[i])/5;
		 }
		 if (finalMark < 0)
			 throw(InvalidGradeException("Marks cannot be below zero"));
		 else if (finalMark > 100)
			 throw(InvalidGradeException("Marks too high, please investigate"));
		 //return finalMark;
	 }


	 void gradingStatus(int finalMark)
	 {
		 string status;
		 if (finalMark <= 75)
			 status = "Merit";
		 else if (finalMark < 85)
			 status = "Credit";
		 else if (finalMark < 75)
			 status = "Pass";
		 else if (finalMark < 50)
			 status = "Fail";	  
	 }
};

class InvalidGradeException
{
public:
	InvalidGradeException(const string& msg) : msg_(msg) {}
	~InvalidGradeException() {}

	string getMessage() const { return(msg_); }
private:
	string msg_;
};

int main(void)
{
	vector <Student> students;
	vector <Student> *vectorOfStudents;
	Student me;
	me.firstname = "Anthony";
	me.lastname = "Langford";
	me.studentNumber = "218107951";
	me.assessments[] = {75, 75, 90, 10, 90};
	//vector <Student> testStudents[20];
	//vectorOfStudents->push_back(students);

	try {
		me.calculateGrades();
	}
	catch (InvalidGradeException& e) {
		cout << "InvalidGradeException: " << e.getMessage() << endl;
	}
	
}
**/
//("Anthony", "Langford ", "218107951", { 75, 75, 90, 10, 90 }