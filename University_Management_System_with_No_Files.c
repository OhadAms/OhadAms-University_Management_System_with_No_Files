#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "University_Manegment_System_with_No_Files.h"

/*-----------------------------Declarations-------------------------*/

Clist* Create_Element(int num, char* name);
Slist* Create_Student(char* student_name, int stud_id, int grade);
void Free_All_Courses_And_Students(Clist** head);
int Delete_Student(Clist** courses);
void Delete_Student_List(Clist** courses);
int Add_Course(Clist** courses);
int Delete_Course(Clist** courses);
void Update_Name(char** str);
int Rename_Course(Clist** clist);
int Updeate_Grade(Clist** courses);
int Insert_or_Update_A_Class(Clist** courses);
Slist* Search_Student_Help(Slist** student, int id);
Clist* Search_Course(Clist** courses, int course_number);
int Insert_A_Student(Clist** courses);
int Insert_Or_update_A_Student(Clist** courses);
Slist* Search_Student(Clist** courses, int id);
Slist* Student_Exist(Clist** courses);
void Print_Classes_List(Clist* head);
void Print_Student_List(Clist* courses);
int Print_By_Class_With_Its_Students(Clist** list);
void Print_Line(Slist** student_list);
void Print_All_Classes_With_Their_Computed_Scores(Clist** courses_head);
int Id_Exist_Name_Deferent(Clist** course, Slist** student);
int Fix_Id(char* ch);
int Fix_Name(char* ch);
void Flush_Input();

/*----------------------------Functions-------------------------*/

Clist* Create_Element(int num, char* name)
{
	Clist* item = (Clist*)malloc(sizeof(Clist));
	item->course_num = num;
	item->next = NULL;
	item->student = NULL;
	item->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(item->name, name);

	return item;
}
Slist* Create_Student(char* student_name, int stud_id, int grade)
{
	Slist* new_student = (Slist*)malloc(sizeof(Slist));
	new_student->student_id = stud_id;
	new_student->student_grade = 0;
	new_student->next = NULL;
	new_student->student_name = (char*)malloc(sizeof(char) * stud_id);
	strcpy(new_student->student_name, student_name);
	return new_student;
}
void Free_All_Courses_And_Students(Clist** head)
{
	Clist* temp = *head;
	while (*head != NULL)
	{
		*head = (*head)->next;
		Delete_Student_List(&temp);
		free(temp->name);
		free(temp);
		temp = *head;
	}
}
void Print_Classes_List(Clist* head)
{
	printf("\n");
	printf(" Courses are: \n");
	if (head == NULL)
	{
		printf("-----------\n");
		printf(" No courses in system.\n");
		printf("-----------\n");
		return;
	}
	printf("-------------------------------------------------\n");
	while (head != NULL)
	{
		printf(" Course number: %-8d Course name: %s\n", head->course_num, head->name);
		head = head->next;
	}
	printf("-------------------------------------------------\n");
}
void Print_Student_List(Clist* courses)
{
	printf(" Students are: \n");
	while (courses->student != NULL)
	{
		printf("%-14d: %s %-4d:\n", courses->student->student_id, courses->student->student_name, courses->student->student_grade);
		courses = courses->next;
	}
}
int Add_Course(Clist** courses)
{
	int num;
	char name[200];
	printf("\n");
	printf(" 1. Enter course number: ");
	
	char id_befor_fix[200];
	rewind(stdin);
	gets(id_befor_fix);
	num = Fix_Id(id_befor_fix);
	if (!num)
	{
		printf(" Error, invalid input.\n");
		return 0;
	}
	
	/*if (scanf_s("%d", &num) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}*/

	printf(" 2. Enter course name: ");
	rewind(stdin);
	gets(name);

	if (Search_Course(courses, num) != NULL)
	{
		printf(" Error, Course number is alrady in system.\n");
		return 0;
	}

	Clist* item = Create_Element(num, name);
	item->next = *courses;
	*courses = item;

	return 1;
}
int Delete_Course(Clist** courses)
{
	int num;

	printf("\n");
	printf(" 1. Enter Course number: ");
	if (scanf("%d", &num) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}

	if (*courses == NULL)
	{
		printf(" Error, No cursses in system..\n");
		return 0;
	}

	if ((*courses)->course_num == num)
	{
		Clist* temp = *courses;
		*courses = (*courses)->next;
		Delete_Student_List(&temp);
		free(temp->name);
		free(temp);
	}
	else
	{
		Clist* curr = *courses;
		while (curr->next != NULL && curr->next->course_num != num)
			curr = curr->next;

		if (curr->next == NULL)
		{
			printf(" Error, Course not found.\n");
			return 0;
		}

		Clist* temp = curr->next;
		curr->next = temp->next;
		Delete_Student_List(&temp);
		free(temp->name);
		free(temp);
	}

	return 1;
}
void Delete_Student_List(Clist** courses)
{
	if ((*courses)->student == NULL)
	{
		return 0;
	}

	while ((*courses)->student != NULL)
	{
		Slist* temp = (*courses)->student;
		(*courses)->student = (*courses)->student->next;
		free(temp->student_name);
		free(temp);
	}
}
void Delete_Student_Actual(Slist** curr_stud)
{
	int num = (*curr_stud)->student_id;

	if (*curr_stud == NULL)
		return 0;

	if ((*curr_stud)->student_id == num)
	{
		Slist* temp = *curr_stud;
		*curr_stud = (*curr_stud)->next;
		free(temp->student_name);
		free(temp);
	}
	else
	{
		Slist* curr = *curr_stud;
		while (curr->next != NULL && curr->next->student_id != num)
			curr = curr->next;

		if (curr->next == NULL)
			return 0;

		Slist* temp = curr->next;
		curr->next = temp->next;
		free(temp->student_name);
		free(temp);
	}

	return 1;
}
void Update_Name(char** str)
{
	int i;
	char new_char[200];
	printf(" 2. Enter the new name for course '%s':\n", *str);
	rewind(stdin);
	printf(" ");
	gets(new_char);

	*str = (char*)realloc(*str, (strlen(new_char) + 1));

	strcpy(*str, new_char);
}
int Rename_Course(Clist** clist)
{
	Clist* head = *clist;
	Clist* current = head;
	int num;
	printf("\n");
	printf(" 1. Please enter the course number you want to update: ");
	if (scanf("%d", &num) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}

	while (current != NULL)
	{
		if (current->course_num == num)
		{
			Update_Name((&(current)->name)); 
			return 1;
		}
		current = current->next;
	}
	printf(" Error, Course not found.\n");
	return 0;
}
int Updeate_Grade(Clist** courses)
{
	Clist* head = *courses;
	Clist* Current_course = NULL;
	Slist* curr_stud = NULL;
	int new_grade;
	int id;
	int num_of_course;
	printf("\n");
	printf(" 1. Student id number: ");
	
	if (scanf("%d", &id) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.");
		return 0;
	}
	printf(" 2. Number of relevant course: ");
	if (scanf("%d", &num_of_course) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}

	Current_course = Search_Course(courses, num_of_course);
	if (Current_course == NULL)
	{
		printf(" Error, Course not found.");
		return 0;
	}
	curr_stud = Search_Student(&Current_course, id);
	if (curr_stud != NULL)
	{
		printf(" 3. Enter new Grade: ");
		if (scanf("%d", &new_grade) != 1)
		{
			Flush_Input();
			printf(" Error, invalid input.\n");
			return 0;
		}
		curr_stud->student_grade = new_grade;
		return 1;
	}
	printf(" Error, Student not found.");
	return 0;
}
int Id_Exist_Name_Deferent(Clist** course, Slist** student)
{
	Clist* course_current = *course;
	Slist* student_compare = NULL;
	Slist* student_compare_save = NULL;
	while (course_current != NULL)
	{
		student_compare = Search_Student(&course_current, (*student)->student_id);
		if (student_compare != NULL)
		{
			if ((*student)->student_id == student_compare->student_id && (strcmp((*student)->student_name, student_compare->student_name) != 0))
			{
				printf(" Error, Student id %d alrady in system, name don't metch.\n", (*student)->student_id);
				return 0;
			}
		}
		else if(student_compare == NULL && student_compare_save == NULL)
		{
			 student_compare_save = *student;
		}
		course_current = course_current->next;
	}
	return 1;
}
int Insert_A_Student(Clist** courses)
{
	Clist* C_head = *courses;
	Clist* current = *courses;
	Slist* student = NULL;

	char name[200];
	int id;
	int course_number;
	printf("\n");
	printf(" # Enter student info:\n 1. Name: ");
	rewind(stdin);
	gets(name);
	if (!Fix_Name(name))
	{
		printf(" Error, invalid input.\n");
		return 0;
	}
	int grade = 0;
	printf(" 2. ID: ");
	
	char id_befor_fix[200];
	gets(id_befor_fix);
	id = Fix_Id(id_befor_fix);
	if (!id)
	{
		printf(" Error, invalid input.\n");
		return 0;
	}
	
	/*if (scanf("%d", &id) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}*/

	student = Create_Student(name, id, grade);
	if (!Id_Exist_Name_Deferent(courses, &student))
	{
		return 0;
	}

	printf(" 3. Enter the course number you want to add the student to: ");
	if (scanf("%d", &course_number) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		free(student->student_name);
		free(student);
		return 0;
	}

	current = Search_Course(courses, course_number);
	if (current == NULL)
	{
		printf(" Error, Course not found.");
		free(student->student_name);
		free(student);
		return 0;
	}
	if (student == Search_Student(&current, student->student_id))
	{
		printf(" Error, Student is alrady in system.");
		free(student->student_name);
		free(student);
		return 0;
	}
	else if (current->student == NULL)
	{
		current->student = student;
	}
	else
	{
		student->next = current->student;
		current->student = student;
	}
	return 1;
}
Slist* Student_Exist(Clist** courses)
{
	Clist* head = *courses;
	Clist* Current_course = NULL;
	Slist* curr_stud = NULL;
	int course_number;
	int id;

	printf("1. Student id number: ");
	if (scanf("%d", &id) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}

	printf("2. Number of relevant course: ");
	if (scanf("%d", &course_number) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}

	Current_course = Search_Course(courses, course_number);
	curr_stud = Search_Student(&Current_course, id);
	return curr_stud;

	// not in use yet.
}
Slist* Search_Student_Help(Slist** student, int id)
{
	Slist* head = *student;
	Slist* current = head;

	if (head == NULL)
	{
		return;
	}
	while (current != NULL)
	{
		if (current->student_id == id)
		{
			return current;
		}
		current = current->next;
	}
	return;
}
Slist* Search_Student(Clist** courses, int id)
{
	Clist* current = *courses;
	Slist* student = NULL;
	if (current == NULL)
	{
		return;
	}
	student = Search_Student_Help(&current->student, id);

	return student;
}
Clist* Search_Course(Clist** courses, int course_number)
{
	Clist* head = *courses;
	Clist* current = head;

	if (head == NULL)
	{
		return;
	}
	while (current != NULL)
	{
		if (current->course_num == course_number)
		{
			return current;
		}
		current = current->next;
	}
	return current;
}
void Print_Line(Slist** student_list)
{
	Slist* current = *student_list;
	while (current != NULL)
	{
		printf(" Student id: %-10d   Student name: %-10s   Course grade: %-10d \n", current->student_id, current->student_name, current->student_grade);
		current = current->next;
	}
}
void Print_Line_Computed_Data(Slist** student_list)
{
	Slist* head = *student_list;
	Slist* current = head;
	int Average_course_score = 0;
	int number_of_students = 0;
	int grade_sum = 0;
	int minimum_grade_in_course = 100;
	int maximum_grade_in_course = 0;

	while (current != NULL)
	{
		grade_sum += current->student_grade;
		number_of_students++;
		current = current->next;
	}
	if (number_of_students == 0)
	{
		number_of_students = 1;
	}
	Average_course_score = grade_sum / number_of_students;

	current = head;

	while (current != NULL)
	{
		if (current->student_grade < minimum_grade_in_course)
		{
			minimum_grade_in_course = current->student_grade;
		}
		if (current->student_grade > maximum_grade_in_course)
		{
			maximum_grade_in_course = current->student_grade;
		}
		current = current->next;
	}
	if (head == NULL)
	{
		minimum_grade_in_course = 0;
		maximum_grade_in_course = 0;
		number_of_students = 0;
	}
	printf(" Computed scores:\n");
	printf("-----------------\n");
	printf(" A. Average score: %10d \n B. Minimum score: %10d \n C. Maximum score: %10d \n D. Grades sum: %13d \n E. Number of students: %5d \n", Average_course_score, minimum_grade_in_course, maximum_grade_in_course, grade_sum, number_of_students);
	printf("-----------------------------\n");
}
int Insert_or_Update_A_Class(Clist** courses)
{
	int selection;
	printf(" Enter selection: \n 1. Exit. \n 2. Add class. \n 3. Remove class. \n 4. Rename class. \n 5. Print classes. \n 6. Main menu. \n Answer: ");
	if (scanf("%d", &selection) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}

	do
	{
		if (selection < 1 || selection > 6)
		{
			printf(" Error: unrecognized operation.\n");
			return 0;
		}
		switch (selection)
		{
		case 1:	printf("\n Bye Bye!");	return 1;
		case 2:	if (Add_Course(courses))
			printf(" Course added.\n"); break;
		case 3:	if (Delete_Course(courses))
			printf(" Course removed.\n"); break;
		case 4:  if (Rename_Course((courses)))
			printf(" Name was updated.\n"); break;
		case 5:	Print_Classes_List(*courses); break;
		case 6:  return 0;
		}
		printf("\n");
		printf(" Enter selection: \n 1. Exit. \n 2. Add class. \n 3. Remove class. \n 4. Rename class. \n 5. Print classes. \n 6. Main menu. \n Answer: ");
		if (scanf_s("%d", &selection) != 1)
		{
			Flush_Input();
			printf(" Error, invalid input.\n");
			return 0;
		}
	} while (selection);
	return 0;
}
int Insert_Or_update_A_Student(Clist** courses)
{
	int selection;

	printf(" Please select an operation:\n 1. Add a new student.\n 2. Update a student.\n Answer: ");
	if (scanf_s("%d", &selection) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}
	if (selection < 1 || selection > 2)
	{
		printf(" Error: unrecognized operation.\n");
		return 0;
	}
	switch (selection)
	{
	case 1: if (Insert_A_Student(courses))
		printf(" Student added succsessfully."); break;
	case 2: if (Updeate_Grade(courses))
		printf(" Grade was updated.");  break;
	default: printf(" Error: unrecognized Error.");
		break;
	}
	printf("\n");
	return 0;
}
int Delete_Student(Clist** courses)
{
	Clist* head = *courses;
	Clist* current_course = head;
	Slist* curr_stud = NULL;
	Slist* runner = NULL;
	Slist* temp = NULL;
	Slist* temp_2 = NULL;
	int id;
	int coures_number;

	printf(" 1. Enter student id: ");
	if (scanf("%d", &id) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}
	printf(" 2. Enter relevant course number: ");
	if (scanf("%d", &coures_number) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}

	if (*courses == NULL)
	{
		return 0;
	}

	while (current_course != NULL)
	{
		if (current_course->course_num == coures_number)
		{
			break;
		}
		current_course = current_course->next;
	}
	if (current_course == NULL)
	{
		printf(" Error, Course not found.\n");
		return 0;
	}

	curr_stud = Search_Student(&(current_course), id);

	if (curr_stud == NULL)
	{
		printf(" Error, Student not found.\n");
		return 0;
	}

	runner = current_course->student;
	temp = runner->next;

	if (runner->student_id == id && runner->next == NULL)
	{
		free(runner->student_name);
		free(runner);
		current_course->student = NULL;
		return 1;
	}
	else if (runner->student_id == id && runner->next != NULL)
	{
		temp_2 = current_course->student;
		runner = runner->next;
		temp = runner->next;
		free(temp_2->student_name);
		free(temp_2);
		current_course->student = runner;
		return 1;
	}

	while ((runner != NULL) && (temp != NULL))
	{
		if ((temp->next == NULL) && (temp->student_id == curr_stud->student_id))
		{
			free(temp);
			runner->next = NULL;
			printf("\n");
			return 1;
		}
		else if ((temp->student_id == curr_stud->student_id))
		{
			temp = temp->next;
			free(runner->next);
			runner->next = temp;
			return 1;
		}
		else
		{
			temp = temp->next;
			runner = runner->next;
		}
	}
	printf(" Error, Student not found.\n");
	return 0;
}
int Print_By_Class_With_Its_Students(Clist** list)
{
	int course_number;
	printf(" 1. Enter the course number to print: ");
	if (scanf("%d", &course_number) != 1)
	{
		Flush_Input();
		printf(" Error, invalid input.\n");
		return 0;
	}

	Clist* curr_course = Search_Course(list, course_number);
	if (curr_course == NULL)
	{
		printf("-----------------\n");
		printf(" Class not found.\n");
		printf("-----------------\n");
		return 0;
	}
	else if (curr_course->student == NULL)
	{
		printf("-----------------\n");
		printf(" Course is empty.\n");
		printf("-----------------\n");
		return 0;
	}
	else
	{
		printf(" Course Number: %-10d   Cours name: %s \n", curr_course->course_num, curr_course->name);
		printf("----------------------------------------\n");
		Print_Line(&(curr_course)->student);
		curr_course = (curr_course)->next;
	}
	printf("-------------------------------------------------------------------------\n");
}
void Print_All_Classes_With_Their_Computed_Scores(Clist** courses_head)
{
	Clist* current_classes = *courses_head;
	Slist* curent_student = current_classes;
	while (current_classes != NULL)
	{
		printf(" Course Number: %-10d   Cours name: %s  \n", current_classes->course_num, current_classes->name);
		printf("----------------------------------------------\n");
		Print_Line_Computed_Data(&current_classes->student);
		current_classes = current_classes->next;
		printf("\n");
	}
}
int Fix_Id(char* ch)
{
	int fix_id = 0;
	char* ch_runner = ch;
	while (*ch_runner)
	{
		if (*ch_runner >= '0' && *ch_runner <= '9')
		{
			fix_id = (fix_id * 10) + (*ch_runner - 48);
		}
		else if (*ch_runner != ' ')
		{
			return 0;
		}

		ch_runner++;
	}
	return fix_id;
}
int Fix_Name(char* ch)
{
	char* ch_runner = ch;
	while (*ch_runner != '\0')
	{
		if ((*ch_runner >= 'a' && *ch_runner <= 'z') || (*ch_runner >= 'A' && *ch_runner >= 'Z') || *ch_runner == ' ')
		{
			ch_runner++;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
void Flush_Input()
{
	int c;
	while ((c = getchar()) != EOF && c != '\n');
}

/*-----------------------------Main-------------------------*/

void main()
{
	int selection;
	int flag = 0;
	Clist* courses = NULL;
	Slist* student = NULL;

	do
	{
		printf(" Please select an operation:\n 1. Exit.\n 2. Insert or update a class.\n 3. Insert or update a student.\n 4. Remove a student from classes.\n 5. Print a class with its students.\n 6. Print all classes with their computed scores.\n Answer: ");
		if (scanf_s("%d", &selection) != 1)
		{
			Flush_Input();
			printf(" Error, invalid input.\n");
			printf("\n");
			continue;
		}

		printf("\n");
		if (selection < 1 || selection > 6)
		{
			printf(" Error: unrecognized operation.\n\n");
			continue;
		}
		switch (selection)
		{
		case 1: printf(" Bye bye.\n"); break;
		case 2: if (Insert_or_Update_A_Class(&courses))
		{
			flag = 1;
		}
			  break;
		case 3: if (Insert_Or_update_A_Student(&courses)); break;
		case 4: if (Delete_Student(&courses))
			printf(" Student deleted.\n"); break;
		case 5: Print_By_Class_With_Its_Students(&courses); break;
		case 6: Print_All_Classes_With_Their_Computed_Scores(&courses); break;
		default: printf(" Error: Unrecognized error:\n");
			break;
		}
		printf("\n");
		if (flag == 1)
			break;
	} while (selection != 1);

	Free_All_Courses_And_Students(&courses);
}
