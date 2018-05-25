#include<stdio.h>
#include<string.h>
#include<conio.h>

struct student{
	int studentNum;
	char studentName[50];
	char bookName[50];
	int bookNum;
};

void lists(FILE *);
void addRecord(FILE *);
void deleteRecord(FILE *);
void search(FILE *);



int main(void){
	FILE *Sptr;
	int choice;
	if((Sptr=fopen("student.txt","r+"))==NULL)
		printf("file failed to open");
	else{
		do{
			printf("1-Add Record \n");
			printf("2-Delete Record \n");
			printf("3-Search Record \n");
			printf("4-List Record \n");
			printf("5-Exit \n");
			choice=getche();
			
			switch(choice){
				case'1':addRecord(Sptr);break;
				case'2':deleteRecord(Sptr);break;
				case'3':search(Sptr);break;
				case'4':lists(Sptr);break;
				case'5':break;
			}
		}while(choice!='5');
			fclose(Sptr);
		getch();
	}

}

void addRecord(FILE *Sptr){
	int studentNum;
	struct student stuAccount={0,"","",0};
	printf("Enter student number pleas... \n");
	scanf("%d",&studentNum);
	fseek(Sptr,(studentNum-1)*sizeof(struct student),SEEK_SET);
	fread(&stuAccount,sizeof(struct student),1,Sptr);
	if(stuAccount.studentNum!=0)
		printf("this number already exists ");
	else{
	
		printf("Enter student name, book name and book id \n");
		scanf("%s%s%d",stuAccount.studentName,stuAccount.bookName,
		stuAccount.bookNum);
		fseek(Sptr,(studentNum)*sizeof(struct student),SEEK_SET);
		fwrite(&stuAccount,sizeof(struct student),1,Sptr);
	}
}
	
	
void deleteRecord(FILE *Sptr){
	struct student stuAccount,emptyAccount={0,"","",0};
	int studentNum;
	printf("enter the number you want to delete");
	scanf("%d",&studentNum);
	fseek(Sptr,(studentNum-1)*sizeof(struct student),SEEK_SET);
	fwrite(&emptyAccount,sizeof(struct student),1,Sptr);
}
void search(FILE *Sptr){
	struct student stuAccount ={0,"","",0};
	int searchofnumber;
	printf("enter the search of number \n");
	scanf("%d",&searchofnumber);
	fseek(Sptr,(searchofnumber-1)*sizeof(struct student),SEEK_SET);
	fread(&stuAccount,sizeof(struct student),1,Sptr);
		printf("%s%s%d",stuAccount.studentName,stuAccount.bookName,
		stuAccount.bookNum);
	
}
void lists(FILE *Sptr){
	struct student stuAccount={0,"","",0};
	
	printf("%-10s%-10s%-10s%-10s\n","\nStudent Number","Student Name",
	"Book Name","Book Number");
	while(!feof(Sptr)){
		fread(&stuAccount,sizeof(struct student),1,Sptr);
		if(stuAccount.studentNum!=0)
			printf("%-10s%-10s%-10s%-10s\n",stuAccount.studentNum,
			stuAccount.studentName,stuAccount.bookName,
			stuAccount.bookNum);
	}
	fclose(Sptr);
	getchar();
}


