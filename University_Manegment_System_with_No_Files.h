#define N 200

typedef struct Student_list
{
	char* student_name;
	int student_id;
	int student_grade;
	struct Student_list* next;

}Slist;

typedef struct Clist
{
	int course_num;
	char* name;
	struct Clist* next;
	Slist* student;
}Clist;

