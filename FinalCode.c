#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 9     // Number of courses 
#define m 2     // Number of students

int roll_No = 4500; // Base Roll Number
int registered = 0; 

// Array containing pointers pointing to all n Available Courses
char *courses[n] = {"Math", "English", "Hindi Litreature", "Sanskrit", "Arts", "Logic", "Social Science", "Humanities", "Music"};

// Node data type for storing opted course index for each student  
typedef struct node
{
    int data;
    struct node *next;
} node;

// Student data type for storing all student details
typedef struct student
{
    char *Name;
    node *classes; // List of Course Indices 
    int rollNo;
} student;

// Course data type for storing course index and Roll Numbers of students who have opted for that course
typedef struct Course {
    int name;
    node * studentRollNum;
} Course;

// Array containing pointers pointing to all m registered students
student *list[m + 1]; //can later change to list[m]

// Array containing pointers pointing to all students who have opted of a specific course 
Course *ListOfCourses[n] = {NULL};

// Function to create a new Linked List (of type Node) for a given Course Index
node *newNode(int val) // O(1)
{
    node *new = (node *)malloc(sizeof(node)); 
    new->data = val;
    new->next = NULL;
    return new;
}

// Function to create a new Linked List (of type Student) for a given First and Last Name
student *newStudent(char *Name) // O(1)
{
    char *Name2;  
    Name2=(char *)malloc(30);
    strcpy(Name2, Name);
    student *new = (student *)malloc(sizeof(student));
    new->Name=Name2;
    new->classes = NULL;
    return new;
}

// Function to create a new Linked List (of type course) for a given course Index
Course *newCourse(int name) { // O(1)
    Course* new = (Course*)malloc(sizeof(Course));
    new->name = name; 
    new->studentRollNum = NULL;
    return new;
}

// Function which prints all n available courses [Report 1]
void listCourses() //O(n)
{
	int i;
    printf("List of Courses Open for Registration:\n");
    for (i = 0; i < n; i++) 
    {
        printf("%d. %s\n", i + 1, courses[i]);
    }
}

// Function registers opted courses for each student and stores them in linked list (node). Thus, registration is completed.
void StartRegistration(student *curr, int RollNo)
{
    listCourses();
    printf("Select your desired courses, by entering the Course Index.\nTo confirm registration enter ZERO and press ENTER\n>>");
    
    int i;
    node *classList; // head node for list of opted courses 
    
    for (i = 0; i < n;) 
    {
        int t; //stores selected course Index
        scanf("%d", &t);

        if (t > n || t < 0) //User enters an invalid Course Index
        {
            printf("Please Enter a Valid Course Index\n");
            continue;
        }

        if (t == 0 && i == 0) //User tries to exit function with selecting any course
        {
            printf("Please register for atleast 1 Course\n");
            continue;
        }

        if (t == 0) //User Confirms Registration
        {break;}

       
        node *num = newNode(t - 1); //newNode creates List for courses opted by current student, (t-1) fetches index of course 
        if (curr->classes == NULL) //Previously no courses have been registered
        {
            curr->classes = num; 
        }
        else
        {
            num->next = curr->classes; //Previously some courses have been registered, so new node is inserted and the beginning 
            curr->classes = num; //head pointer shifts
        }
		// Systematically stores the Roll Number of each student who opts for a specific course in ListofCourses
        if(ListOfCourses[t-1] == NULL) { //Previously no students have selected course(t-1)
            ListOfCourses[t-1] = newCourse(t-1); //pointer pointing to list of students in course (t-1) is stored at the index (t-1) in array
            node* new = newNode(RollNo); //new list created with pointer pointing to roll number of student who opted for this course
            ListOfCourses[t-1]->studentRollNum = new; //insert this pointer poitning to roll number of student who opted for this course in the linked list Course
        }
        else { //previously some student has opted for course(t-1)
            node* new = newNode(RollNo); //new list created with pointer pointing to roll number of student who opted for this course
            new->next = ListOfCourses[t-1]->studentRollNum; //inserting new node in the beginning so, shifitng the previous node to new->next
            ListOfCourses[t-1]->studentRollNum = new; //now the the fist node has changed, change the pointer stored in ListofCourse[t-1]
        }
        i++;
    }
    getchar();
}

// Starting of Registration process. Student details are registered, stored, and Roll Numbers are allocated 
void CourseRegis()
{
	int i;
    char Name[30];
    for (i = 0; i < m; i++) 
    {
        printf("\n\nEnter your Name\t: ");
        fgets(Name,30,stdin);
        student *student = newStudent(Name);
        student->rollNo = i + roll_No;
        list[i] = student;
        StartRegistration(student,i+roll_No); 
        printf("Registration Successful!\nYour Roll Number is %d\n", i + roll_No);
    }
    printf("\n\n\nRegistration Ended\n\n\n");
    registered = 1;
}

// Function to print the courses that each student has opted for 
void List2() 
{
	int i;
    if(!registered) {
        printf("Please Register and get your roll_Number first\n");
    }

    printf("\n\nList of Courses for each Student\n\n");
    for (i = 0; i <m; i++) 
    {
        student *curr = list[i]; //points to the current student who's opted courses will be printed
        printf("Name = %s\nRoll Number = %d\nOpted Course List\n", curr->Name, curr->rollNo);
        node *temp = curr->classes; //pointing to list of classes opted by current student
        int i = 1;
        while (temp != NULL)
        {
            printf("%d.%s\n", i++,courses[temp->data]); //temp->data give us the course index, using this value we can obtain the name of course from courses array
            temp = temp->next;
        }
        printf("\n\n");
    }
}

// Function to print the names of students who have opted for a course
void List2Type2() {
	int i;
    int j = 1;
    for(i = 0;i<n;i++) { 
        
        if(ListOfCourses[i] == NULL) continue; //this particular course index, i, hasn't been selected by student so it contains no pointer pointing to the list os students
        //will skip this iteration and we're back again at for loop
        node* stds = ListOfCourses[i]->studentRollNum; //stds pointing to list containing roll numbers of students in course
        char* cname = courses[ListOfCourses[i]->name]; // fetching name of course using course index
        printf("%d.List of Students in Course %s\n",j,cname);j++;
        int k = 1;
        while(stds != NULL) {
            int rn = stds->data - roll_No; //stds->data gives us roll number of student in course - baseRollNumber(4500)
            char* SName = list[rn]->Name; //fetches name of student from List containing all m students
            printf("\t%d.%s %s\n",k,SName);
            stds = stds->next;
            k++;
        }printf("\n");
    }
}

// Function to allow user to reapeat any function they like
void repeat() {

    int c;
    printf("Enter Your Choice \n");
    while (1) {

        printf("1. List all Available Courses\n");
        printf("2. List all Opted Courses for a Specific Student\n");
        printf("3. List Courses Opted by All Students\n");
        printf("4. List Students in each Course\n");
        printf("5. Quit\n");
        printf(">> ");

        scanf("%d", &c);
        if (c == 1){
            listCourses();
            printf("\n");
        }
        else if (c == 2) {

            int rn;
            printf("\nPlease Enter your Roll Number\n>> ");
            scanf("%d", &rn);
            if (rn >=roll_No && rn <= roll_No + m) {
                int idx = rn - roll_No;
                student *curr = list[idx];
                printf("\tName = %s\n", curr->Name);
                node *temp = curr->classes;
                // printf("subject = %s %d\n",curr->name,temp->data);
                int c = 1;
                while (temp != NULL)
                {
                    printf("\t%d.%s\n",c++, courses[temp->data]);
                    // printf("%d\n",temp->data);
                    temp = temp->next;
                }
                printf("\n");
            }
            else {
                printf("\nInvalid Roll_Number\n\n");
            }
        }

        else if(c == 3) {
            List2();printf("\n");
        }
        else if (c == 4) {
        	    printf("\n");List2Type2();printf("\n");
            }
         else if (c == 5) {
                return;
            }   
        else {
            printf("\nInvalid Responce\n\n");
            printf("\nTry Again\n\n");
        }

    }
    printf("\n");
}


void main()
{
    printf("Welcome to XYZ University Student Portal\n\n\n");
    listCourses();
    CourseRegis();
    List2();
    List2Type2();
    repeat();
    printf("\n\nThank You for using XYZ University Student Portal\n");
}
