
//{						Header Files Used In Program
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
		//}
//{						Functions Used In Program
void intro();			 // 1.  Introductory Screen Module
char* authentication();	 // 2.  Authentication & Access Control Function

void create_ac();		 // 3.  Account Creating Module
void display_all();		 // 4.  Account List Display Module
void dw(char t[30]);	 // 6.  Amount Deposit And Withdraw Control Module
void delete_account();	 // 7.  Account Delete Control Module
void modify_account();	 // 8.  Account Type Modification Control Module
void changeId();		 // 9.  Access Control Setting Module

// void accountMenu(int i); // 10. To Display Account Information List
int	checkAmount(int x);		 // 11. Balance & Amount Checking Module
void modifyThis(char option[5]);			// 12. Account Modification Module
void searchControl(char *ch, char t[30]);	//  5. Search Control and Display Module
void getinput(char o[10], char *data);		// 14. Input Control Mechanism Module
int checkuser(const char acno[12], const char username[30]);
int search(char *acnos, char *names);		// 16. Account Searching Module

void mainmenu(char username[30]);
void usermenu(char username[30]);
void showuser(char username[30]);
char* edituser(char username[30]);
void viewtransac(char *transacacc);
void editpasswd(char username[30]);

int updateuserdata(char acno[12],char addr[30],char ph[12],char uname[30]);

char* userfilelocation = "user.bms";
char* accountfilelocation = "account.bms";
char* transacfilelocation = "transac.bms";
char* tempfilelocation = "temp.bms";


void createuser(
	const char acno[12],
	const char addr[30],
	const char phone[12],
	const char gender[10],
	const char username[30],
	const char password[30]
);
void accountbyusername(char username[30],char *acno,char *name,char *snm, char *type, char *addr, char *ph, char *gender);

int verifyuser(const char uname[30],const char pass[30]);
void userRegister();
void tracktransac(char acno[12], char transactype[30], char amount[12]);
//}
char spc[5]=" ";	//	Cleaner String
typedef struct		//	Data Structure Used in Program
{
	char acno[12];
	char name[20];
	char snm [20];
	char type[10];
	char balance[12];
} account;

typedef struct{
	char acno[12];
	char address[30];
	char phoneno[12];
	char gender[10];
	char username[30];
	char password[30];
} user;
 account ac, s[10];
//~~~~~~~~~~~~~~~~	0. Main Module of this Program	~~~~~~~~~~~~~~~~
int main()
{
	char username[30];
	char ch='1';

	system("cls");	intro();	
	strcpy(username,authentication());
	if(strcmp(username,"admin")==0){
		mainmenu(username);
	}else{
		usermenu(username);
	}
return 0;
}
//~~~~~~~~~~~~~~~~	16. Account Modification Control Module 	~~~~~~~~~~~~~~~~~~
void modify_account()
{
	char check[10], ch;
	int x;
	searchControl(check, "Modify Account");
	while(strcmp(check,"selected")==0)
	{	if(ac.type[0]=='S')
		{	strcpy(ac.type,"Current");
			printf("\n\nModify Saving A/C TO Current Account");
		}
		else
		{	strcpy(ac.type,"Saving");
			printf("\n\nModify Current A/C TO Saving Account");
		}
		x=checkAmount(1);
		if(x==0)
		{
			 printf("\n\nEnter : Modify the Account%10s",spc);
			ch=getch();
			if(ch==27) break;
			else if(ch==13)
			{	modifyThis("modify");
				 printf("\n\nAccount is Modified %12s",spc);
				getch();
			}
			else
			{
				printf("\n\nAccount Not Modified%12s",spc);
				getch();
			}
		}
		else
		{
			printf("\n\nYou don''t have sufficient Balance to Modify this A/C");
			getch();
		} 	break;
	}
}
//~~~~~~~~~~~~~~~~	15. Account Modifier Module 	~~~~~~~~~~~~~~~~~~
void modifyThis(char option[5])
{
	char ch;
	FILE *fp,*fpx;
	fp=fopen(accountfilelocation,"r");
	fpx=fopen(tempfilelocation,"w");
	do
	{	ch=fscanf(fp,"%s %s %s %s %s",s[0].acno,s[0].name, s[0].snm ,s[0].type,s[0].balance);
		if(ch==EOF) break;
		if(strcmp(ac.acno,s[0].acno)==0)
		{	if(strcmp(option,"del")!=0)
			fprintf(fpx, "%s %s %s %s %s ",ac.acno, ac.name, ac.snm, ac.type, ac.balance);
		}
		else
		fprintf(fpx, "%s %s %s %s %s ",s[0].acno, s[0].name, s[0].snm, s[0].type, s[0].balance);
	}while(1==1);
	fclose(fp);
	fclose(fpx);
	remove(accountfilelocation);
	rename(tempfilelocation,accountfilelocation);
}
//~~~~~~~~~~~~~~~~	14. Deposit And Withdraw Control Module 	~~~~~~~~~~~~~~~~~~
void dw(char title[30])
{
	long int temp;
	char check[10],ch;
	char amount[12];
	searchControl(check, title);
	while(strcmp(check,"selected")==0)
	{	printf("\n\n%30s",spc);
		printf("\n\nEnter Amount : %12s",spc);

		printf("\n\nEnter : %s  %15s",title,spc);
		getinput("number",amount);

		if(amount[0]=='\0') break;
		if(strcmp(title,"Deposit Amount")==0)
				temp = atol(ac.balance)+atol(amount);
		else 	temp= atol(ac.balance)-atol(amount);

		ltoa(temp,ac.balance,10);

		if(checkAmount(0)==1)
		{
			printf("\n\nNot Sufficient Balance");
			getch(); break;
		}

			printf("\n\n%-30s",ac.balance);
        printf("\n\nEnter : Confirm        Any Key : Abort");
		ch=getch();

		if(ch==27) break;
		if(ch==13)
		{	modifyThis("deposit");
			tracktransac(ac.acno,title,amount);
			printf("\n\nBalance Successfully Updated %12s",spc); getch();
		}
		else
		{
			printf("\n\nBalance Not Updated%12s",spc); getch();
		}	break;
	}
}
//~~~~~~~~~~~~~~~~	13. Account Deleting Control Module 	~~~~~~~~~~~~~~~~~~
void delete_account()
{
	char check[10],ch;
	searchControl(check, "Delete Account");
	while(strcmp(check,"selected")==0)
	{	printf("\n\nEnter : Delete the Account%10s",spc);
		ch=getch();
		if(ch==27) break;
		else if(ch==13)
		{	modifyThis("del");

			printf("\n\nAccount is Deleted %12s",spc);
		} else
		{
			printf("\n\nAccount Not Deleted%12s",spc);
		}	getch(); break;
	}
}
//~~~~~~~~~~~~~~~~	12. Account Searching Module 	~~~~~~~~~~~~~~~~~~
int search(char *acnos, char *names)
{
	FILE *fp;
	char ch;
	int a=0;

	fp=fopen(accountfilelocation,"r");
	do
	{	ch=fscanf(fp,"%s %s %s %s %s",s[a].acno,s[a].name,s[a].snm,s[a].type,s[a].balance);
		if(ch==EOF) break;
		if(acnos[0]!=1)
		{	if(atol(acnos)==atol(s[a].acno))//strcmp(acnos,s[a].acno)==0)
			{	a=a+1;		break;		}
		}
		else if(strcmp(names,s[a].name)==0)
		a=a+1;
	}while(ch!=EOF);
	fclose(fp); return a;
}
//~~~~~~~~~~~~~~~~	11. Search Control and Display Module 	~~~~~~~~~~~~~~~~~~
void searchControl(char *check, char title[30])
{
	int a=0, i=0, m, c;
	char acnos[12], names[30]="iii",ch;
	m=strcmp(title,"Search Account");
	do
	{
	    i=0;
	    do
		{	//accountMenu(2);
		    system("cls");i++;
            printf("\n\n\t*************** %s ************** ",title);
            printf("\n\t\t\t\t\t\t\tESC : Main Menu");

            if(i%2==1)
            {
                printf("\n\t\t\t\t\t\t\tTAB : Search By Name");
                printf("\n\n   Search Account Number (Number Only)  : ");
                getinput("acnos", acnos);		// A/C No Search Input
                if(acnos[0]=='\0'||acnos[0]!=1) break;
                else continue;
            }
            else
            {
                printf("\n\t\t\t\t\t\t\tTAB : Search By Number");
                printf("\n\n   Search A/C Holder's Name             : ");
                getinput("names", names);		// A/C Name Search Input
                if(names[0]=='\0'||names[0]!=1) break;
                else continue;
            }
		}while(1);
		if(acnos[0]=='\0'||names[0]=='\0') break;

		a=search(acnos,names);
		if(a>0)
		{	for(i=0;i<a;i++)
			{	c=i;
                system("cls");
                printf("\n\n\t*************** %s ************** ",title);
                printf("\n\t\t\t\t\t\t\tESC : Main Menu");
                printf("\n\t\t\t\t\t\t\tTAB : Next Result");
                if(m!=0) printf("\n\t\t\t\t\t\tEnter : Select");
                else printf("\n");
                if(acnos[0]==1)
                    printf("\n   Search A/C Holder's Name             : %s",names);
                else
                    printf("\n   Search Account Number (Number Only)  : %s",acnos);
                printf("\n\n\n\t\t Search Details ");
				printf("\n\n\t Account Number    : %-30s",s[c].acno);
				printf("\n\n\t A/C Holder's Name : %s %-20s",s[c].name,s[c].snm);
				printf("\n\n\t A/C Type          : %-30s",s[c].type);
				printf("\n\n\t Balance Amount    : %-30s",s[c].balance);
				printf("\n\n\t      Account Found",a);

				ch=getch();
				if(ch==9)continue;
				else break;
				if(m!=0)
				{

					printf("\n\n\tEnter: Select to %s",title);

				}
				if(a!=1&&i<a-1)	ch=getch(); if(ch==27)	break;
				if(m!=0&&ch==13) break;
				if(a!=1&&i==a-1)	printf("\n\n\tNo More Results %20s",spc);
			}
			if(a==1||i==a) ch=getch();
			if(ch!=13){
				printf("\n\tDo you want to search another account Y/N");
			}
			if(m!=0&&ch==13)
			{	strcpy(ac.acno,s[c].acno);
				strcpy(ac.name,s[c].name);
				strcpy(ac.snm,s[c].snm);
				strcpy(ac.type,s[c].type);
				strcpy(ac.balance,s[c].balance);
				strcpy(check,"selected");
				printf("\n\t  This Account is Selected %20s",spc);
			}
		}
		else
		{	printf("\n\t  No Account Found       ");
			printf("\n\tDo u want to search another account Y/N");
			ch=getch();
		}
	}while(ch=='Y'||ch=='y');
}
//~~~~~~~~~~~~~~~~	10. Account List Display Module 	~~~~~~~~~~~~~~~~~~
void display_all()
{
	int sno=0, page=1, i;
	char ch, fch;
	FILE *fp;

    fp=fopen(accountfilelocation,"r");

    do
    {
	system("cls");
	 printf("\n\t    ********** List of All Bank Accounts **********");
	 printf("\n     Page %2d\t\t\t\t\t\t   Enter : Next Page",page);
	 printf("\n\t\t\t\t\t\t\t   ESC   : Main Menu");

	printf("\n Sn ");
	printf(" A/C Number ");
	printf("       A/C Holder's Name      ");
	printf("  A/C Type ");		printf(" Total Balance \n");
	for(i=0;i<38;i++) printf("__");

    do
    {

		fch=fscanf(fp,"%s %s %s %s %s",ac.acno, ac.name, ac.snm, ac.type, ac.balance);
		if(fch==EOF) break;

		sno++;
		printf("\n %2d ",sno);
		printf(" %-10s",ac.acno);
		printf("  %15s %-15s",ac.name,ac.snm);
		printf("%-10s",ac.type);
		printf("Rs %-10s",ac.balance);

    }while(sno%18!=0);
    ch=getch();
    if(ch==27) break;
    page++;
	}while(fch!=EOF);
	fclose(fp);
}
//~~~~~~~~~~~~~~~~	9. Balance & Amount Checking Module 	~~~~~~~~~~~~~~~~~~
int checkAmount(int x)
{
	int a=0;
	if(strcmp(ac.type,"Saving")==0)
	{	if(atol(ac.balance)<500) a=1;
		if(x==1) printf("\a Min : 500");
	}
	else
	{	if(atol(ac.balance)<1000) a=1;
		if(x==1) printf("\a Min : 1000");
	}

	return a;
}
//~~~~~~~~~~~~~~~~	8. Account Creating Module 	~~~~~~~~~~~~~~~~~~
void create_ac()
{
	int a=0,i;
	char ch;
	FILE *fp;
	do
	{
	    system("cls");

		printf("\n\n\t*************** New Account ************** ");
        printf("\n\t\t\t\t\t\t\t\tESC : Main Menu");

			printf("\n\n\t1.  Account Number (Number Only)\t: ");
			getinput("acno", ac.acno);
			if(ac.acno[0]=='\0') break;				//	ESC Key
			a=search(ac.acno,ac.name);				//Check if Account Exists
			if(a>0)
			{
				printf("\n\n\tAccount Number Already Exists");
				printf("\a");
				getch();
				continue;
			}

		printf("\n\n\t2.  A/C Holder's Name\t\t\t: ");
		getinput("name",ac.name);
		if(ac.name[0]=='\0') break;					//ESC Key

        printf("\n\n\t3.  A/C Holder's Surname\t\t: ");
		getinput("name",ac.snm);
		if(ac.snm[0]=='\0') break;

		printf("\n\n\t4.  Account Type (S:Saving  C: Current) : ");
		getinput("type", ac.type); strupr(ac.type);
		if(ac.type[0]=='S') strcpy(ac.type,"Saving");
		else strcpy(ac.type,"Current");
		if(ac.type[0]=='\0') break;				//ESC Key

        printf("\n\n\t5.  Balance Amount ");
		do
		{
		    if(a!=0)
            {
                for(i=1;i<=70;i++)
                printf("%c%c%c",8,32,8);
                printf("\t5.  Balance Amount ");
            }
            checkAmount(1);
            printf("\t\t: ");
            getinput("number", ac.balance);
			if(ac.balance[0]=='\0') break;		//ESC Key
			a=checkAmount(0);

		} while(a==1);
		if(ac.balance[0]=='\0') break;				//ESC Key


		printf("\n\n\t  Are you sure to create this Account Y/N");
		ch=getch();

		if(ac.balance[0]=='\0') break;
		else if (ch=='y'||ch=='Y')
		{	printf("\n\n\t\t\tAccount Created");
			fp = fopen(accountfilelocation,"a");
			fprintf(fp, "%s %s %s %s %s ", ac.acno, ac.name, ac.snm, ac.type, ac.balance);
			fclose(fp);
		}
		else printf("\n\n\t\t  Account Not Not Created");
		printf("\n\t  Do you want to create another account Y/N");
		ch=getch();
	}while((ch=='Y'||ch=='y')||a>0);
}

// 	printf("\n\nESC : Main Menu");
// }
//~~~~~~~~~~~~~~~~	6. Access Control Setting Module	~~~~~~~~~~~~~~
void changeId()
{
char ch='1';
char username[30]="admin", inuser[30],temp[30];
char password[30]="admin", inpass[30];
do
	{
 system("cls");
	printf("\n\n\t\t1.	Change Username");
	printf("\n\n\t\t2.	Change Password");
	printf("\n\n\t\t3.	Lock Screen");
	printf("\n\n\t\t4.	Back");
		if(ch<49||ch>52)
		{		printf("\n\n%c",ch);

			printf("\n\nInvalid Choice. Choose Valid Option");
		}


			printf("\n\n SECURITY SETTINGS ");
			printf("\n\nSelect Your Option (1-4) : ");
		ch=getch();
		switch(ch)
		{
			case '1':
				do
				{	 system("cls");
					printf("\t\t Enter a new Username");


					printf("\n\n CHANGE USERNAME ");
					getinput("user",inuser);
					printf("\n\nEnter Password to change your Username");
					getinput("password",inpass);

					// cs_id("scan",username,password);
					if(strcmp(password,inpass)==0)
					{	
						// cs_id("change",inuser,password);
						printf("\n\n            Username Changed            ");
					}
					else
					{	printf("\n\n          Username Not Changed          ");

						printf("\a"); printf("\n\nWrong Password : Try Again Y/N");
					}
					ch=getch();
				}while(ch=='y'||ch=='Y');
			break;
			case '2':
				do
				{	
					// cs_id("scan",username,password);
				 system("cls");
					printf("\n\n\t   Enter Old Password :");
					printf("\n\n\t   Enter New Password :");


						printf("\n\n CHANGE PASSWORD ");
						getinput("password",temp);

					if(strcmp(password,temp)!=0)
					{
						printf("\n\nWrong Password :");
					}
					else
					{		getinput("password",inpass);
						printf("New Password Again :");
							getinput("password",temp);


						if(strcmp(inpass,temp)!=0)
						printf("\n\nNew Passwords do not Match :");
						else
						{	printf("\n\nAre you sure to change your Password Y/N");
							ch=getch();
							if(ch=='y'||ch=='Y')
							{	
								// cs_id("change",username,inpass);
								printf("\n\n%13sPassword Changed%13s",spc,spc);
								getch();
								break;
							}
							else printf("\n\n%12sPassword Not Changed%12s",spc,spc);
						}
					}

					printf("\n\nTry Again Y/N");
					printf("\a");
					ch=getch();
				}while(ch=='y'||ch=='Y');
			break;
			case '3':
				authentication();
				ch='4';
			break;
			case '4':
			break;
			default :
				 printf("\a");
		 }
	}while(ch!='4');
}

//~~~~~~~~~~~~~~~~	4. Input Control Mechanism Module	~~~~~~~~~~~~~~
void getinput(char option[10], char *data)
{
	int i, a, s=0,g=0;
	char temp;
	char string1[31]="\0";

	if(strcmp(option,"number")==0) a=9;
	else if (strcmp(option,"type")==0) a=1;
	else if (strcmp(option,"gender")==0) {a=1,g=1;}
	else if (strcmp(option,"acno")==0) a=10;
	else if (strcmp(option,"acnos")==0) {a=10; s=1;}
	else if (strcmp(option,"names")==0) {a=15; s=1;}
	else if (strcmp(option,"name")==0) a=15;
	else a=30;


	while(string1[0]=='\0')
	{	for(i=0;i<a+1;)
		{	temp=getch();
			  if(temp==8)				// Action of Backspace Key
				 {	if(i<1) break;		// Prevents Unwanted Backspace
					printf("%c%c%c",8,32,8);
					i-=2;
				 }		//	TAB and Esc does nothing If Password and Username
			  else if(((strcmp(option,"password")==0)||(strcmp(option,"user")==0))&&(temp==9))
			  i--;
			  else if(temp==27) break;
			  else if(temp==9||temp==13) break;	// Action of TaB and Enter
			  else if(temp==32) i--;			// Action of Esc Key and Space
			  else if(i==a) i--;				// Prevents array Overflow Typings
			  else if (((a==1)&&(g==1))&&((temp==70||temp==102||temp==77||temp==109))==0)
			  i--;								// Input only M, m, OR F, f
			  else if (((a==1)&&(g==0))&&((temp==99||temp==115||temp==67||temp==83))==0)
			  i--;								// Input only S, C, OR s, c
			  else if(((a==9)||(a==10))&&(temp<48||temp>57))
			  i--;								// Filters Number
			  else
				{	string1[i]=temp;
					if(strcmp(option,"password")==0)
					printf("*");
					else
					printf("%c",string1[i]);
				}
			i++;
			string1[i]='\0'; // put null at the end of the array
		}
		if(temp==27) { string1[0]='\0'; break;}
		if(s==1&&temp==9) { string1[0]=1; break;}
	}

	strcpy(data,string1);
}
//~~~~~~~~~~~~~~~~	3. Autentication & Access Control Fucntion	~~~~~~~~~~~~~~~~~~~~~~
char* authentication()
{
	char username[30]="admin";		// Actual & Default Username at first run
	char password[30]="admin";		// Actual & Default Password at first run
	user newuser;
	char inuser[30], inpass[30];	// Username & Password received from input
	int attempts;
	char *uservalue;
	int auth = 0;

	strcpy(newuser.acno,"0");
	strcpy(newuser.address,"NA");
	strcpy(newuser.phoneno,"NA");
	strcpy(newuser.gender,"NA");
	strcpy(newuser.username,"admin");
	strcpy(newuser.password,"admin");

	if(checkuser("0","0")==0){
		createuser(newuser.acno,newuser.address,newuser.phoneno,newuser.gender,newuser.username,newuser.password);
	}
	do{

		for(attempts=5;attempts>0;attempts--)
		{	// To erase the previous inputs
			system("cls");
			printf("\n\t\t\t\t\t\t\t  Press ESC To Register");
			printf("\n\n\n\t\t\t  WEL-COME TO");
			printf("\n\n\t\t\tBANK MANAGEMENT");
			printf("\n\n\t\t\t    SYSTEM");

			if(attempts<5)
			{
				printf("\n\n\n\tAccess Denied. Re-enter Username and Password.");
				printf("\n\t            Attempts Left: %i"    ,attempts);

			}
			else printf("\n\n\n\n");

			// getinput is userdefined input module
			printf("\n\n\n\n\n\t\t\tUsername: ");
			getinput("user",inuser);
			if(inuser[0]=='\0') break;	
			printf("\n\n\t\t\tPassword: ");
			getinput("password",inpass);
			if(inpass[0]=='\0') break;	


			if(verifyuser(inuser,inpass))
			{	printf("\n\n\tUsername and password authenticated. Access Granted");
				printf("\n\n\t            Press any key to continue");
				getch();
				auth = 1;
				strcpy(uservalue,inuser);
				return uservalue;
				break;
			}
			else if(attempts==1)
			{	system("cls");
				printf("\n\n\n\tYour are not Authenticated. Access Denied.");
				system("color f0");
				getch();
				exit(0);
			}
		}
		if(auth == 1){
			break;
		}
		userRegister();
	}while(1);
	return NULL;
}
//~~~~~~~~~~~~~~~~	2. Introductory Screen Module	~~~~~~~~~~~~~~~~
void intro()
{
	system("cls");
    system("color f0");
		printf("\n\n\n\n\t\t\t  WEL-COME TO");
		printf("\n\n\t\t\tBANK MANAGEMENT");
		printf("\n\n\t\t\t    SYSTEM");
		printf("\n\n\n\n\n\n\n\tSubmitted by: ");
		printf("\n\n\tSubmitted to: Asia Pacific University College of Technology and Innovation " );
	getch();
}

void userRegister(){
	char ch;
	int a = 0, usercheck = 0;
	char checkpassword[30];
	user us;
	FILE *fp;
	system("cls");
	do
	{
	    system("cls");

		printf("\n\t*************** Register User ************** ");
		printf("\n\t  User Must Have Account in Bank To Register");
        printf("\n\t\t\t\t\t\t\t\tESC : Main Page ");

			printf("\n\n\t1.  Account Number (Number Only)\t: ");
			if(usercheck>1)
			printf("%s",us.acno);
			else
			getinput("acno", us.acno);
			if(us.acno[0]=='\0') break;				//	ESC Key
			a=search(us.acno," ");				//Check if Account Exists
			if(a==0)
			{
				printf("\n\n\tAccount Number Does Not Exists");
				printf("\a");
				getch();
				continue;
			}
			if(usercheck==0)
			usercheck = checkuser(us.acno," ");
			if(usercheck==1){
				printf("\n\n\t\t\tUser already exists");
				printf("\n\n\t\tIf you forget you password contact Manager");
				printf("\a");
				usercheck = 0;
				getch();
				continue;
			}

		printf("\n\n\t2.  A/C Holder's Name\t\t\t: ");
		printf(s[0].name);
		// getinput("name",ac.name);
		// if(ac.name[0]=='\0') break;					//ESC Key

        printf("\n\n\t3.  A/C Holder's Surname\t\t: ");
		printf(s[0].snm);
		// getinput("name",ac.snm);
		// if(ac.snm[0]=='\0') break;

		printf("\n\n\t4.  Account Type (S:Saving  C: Current) : ");
		// getinput("type", ac.type); strupr(ac.type);
		if(s[0].type[0]=='S') strcpy(s[0].type,"Saving");
		else strcpy(ac.type,"Current");
		printf(s[0].type);
		// if(ac.type[0]=='\0') break;				//ESC Key

		printf("\n\n\t5.  Address \t\t\t\t: ");
		if(usercheck>1)
		printf("%s",us.address);
		else
		getinput("user",us.address);
		if(us.address[0]=='\0') break;					//ESC Key

		printf("\n\n\t6.  Phone Number \t\t\t: ");
		if(usercheck>1)
		printf("%s",us.phoneno);
		else
		getinput("acno",us.phoneno);
		if(us.phoneno[0]=='\0') break;					//ESC Key

		printf("\n\n\t7.  Gender (M:Male  F: Female) \t\t: ");
		if(usercheck>1)
		printf("%s",us.gender);
		else
		getinput("gender",us.gender);
		if(us.gender[0]=='\0') break;					//ESC Key

		printf("\n\n\t8.  Username \t\t\t\t: ");
		if(usercheck>2)
		printf("%s",us.username);
		else
		getinput("user",us.username);
		if(us.username[0]=='\0') break; 				//ESC Key
		usercheck = checkuser("-1",us.username);
		if(usercheck==1){
				printf("\n\n\t\t\tUsername already exists");
				printf("\n\n\t\tPlease any key to enter another username");
				printf("\a");
				usercheck = 2;
				getch();
				continue;
			}

		printf("\n\n\t9.  Password \t\t\t\t: ");
		getinput("password",us.password);
		if(us.password[0]=='\0') break;					//ESC Key
		
		printf("\n\n\t10.  Confirm Password \t\t\t: ");
		getinput("password",checkpassword);
		if(checkpassword[0]=='\0') break;					//ESC Key

				if(strcmp(us.password,checkpassword)!=0){
				printf("\n\n\t\t\tPassword no not Match");
				printf("\n\n\t\tPress any to re-enter password");
				printf("\a");
				usercheck = 3;
				getch();
				continue;
			}
			fp = fopen(userfilelocation,"a");
			fprintf(fp, "%s %s %s %s %s %s ", us.acno,us.address,us.phoneno,us.gender,us.username,us.password);
			fclose(fp);
			printf("\n\n\t\t\tUser Registered");
		ch=getch();
	}while(usercheck);
}

int checkuser(const char acno[12],const char username[30]){
	FILE *j;
	char ch;
	user us;
	int res = 0;
	j = fopen(userfilelocation,"r");
	if(j!=NULL){
		do{
			ch = fscanf(j,"%s %s %s %s %s %s",us.acno,us.address,us.phoneno,us.gender,us.username,us.password);
			if(ch == EOF) break;
			if((atol(acno)==atol(us.acno))||strcmp(username,us.username)==0)
			{ 
				// res = 1; break;
				return 1;
				}
		}while(1);
	}
	fclose(j);
	return res;
}

int verifyuser(const char username[30] ,const char password[30]){
	FILE *k;
	char ch;
	user us;
	int re = 0;
	k = fopen(userfilelocation,"r");
	if(k!=NULL){
		do{
			ch = fscanf(k,"%s %s %s %s %s %s",us.acno,us.address,us.phoneno,us.gender,us.username,us.password);
			if(ch == EOF) break;
			if(strcmp(username,us.username)==0&&strcmp(password,us.password)==0){
				// re = 1;
				// break;
				return 1;
			}
		}while(1);
	}
	fclose(k);
	return re;
}

void createuser(
	const char acno[12],
	const char addr[30],
	const char phone[12],
	const char gender[10],
	const char username[30],
	const char password[30]
){
	FILE *fp;
	char ch;

	fp = fopen(userfilelocation,"a");
	fprintf(fp,"%s %s %s %s %s %s ",acno,addr,phone,gender,username,password);
	fclose(fp);
}

void mainmenu(char username[30]){
	char ch='1';

	do					//	Main Menu of Program
	{	system("cls");
        printf("\n\t********* BANKING ACCOUNT SYSTEM : ADMIN ********* ");
		printf("\n\n\t\t01. NEW ACCOUNT");
		printf("\n\n\t\t02. Register User");
		printf("\n\n\t\t03. DEPOSIT AMOUNT");
		printf("\n\n\t\t04. WITHDRAW AMOUNT");
		printf("\n\n\t\t05. BALANCE ENQUIRY");
		printf("\n\n\t\t06. ALL ACCOUNT HOLDER LIST");
		printf("\n\n\t\t07. CLOSE AN ACCOUNT");
		printf("\n\n\t\t08. MODIFY AN ACCOUNT");
		printf("\n\n\t\t09. CHANGE PASSWORD");
		printf("\n\n\t\t0. EXIT");

		printf("\n\n\tSelect Your Option ");

		if(ch<49||ch>57)
		{
		    printf("%c",ch);
			printf("\n\n\tInvalid Choice. Choose Valid Option");
		}
		ch=getch();
		switch(ch)
		{
		case '1':	create_ac(); 			break;
		case '2':	userRegister();			break;
		case '3':	dw("Deposit Amount");	break;
		case '4':	dw("Withdraw Amount");	break;
		case '5':	searchControl(" ","Search Account");
											break;
		case '6':	display_all();			break;
		case '7':	delete_account();		break;
		case '8':	modify_account();		break;
		case '9':	editpasswd(username);	break;
		case '0':
			system("cls");
			printf("\n\n\n\n\t\t  Are you sure to exit the Program Y/N");
			ch=getch();
			if(ch=='Y'||ch=='y')
			{	printf("\n\n\n\t\tThanks for using bank management system");
				getch();
				system("color 0f");
				ch='9';
			}
			break;
		default :	printf("\a");
		}
    }while(ch!='9');
}

void usermenu(char username[30]){
		char ch='1';
		char titlename [30];

	do					//	Main Menu of Program
	{	
		system("cls");
		strcpy(titlename, username);
        printf("\n\t********* BANKING ACCOUNT SYSTEM : %s ********* ",strupr(titlename));
		printf("\n\n\t\t1. SHOW ACCOUNT INFORMATION");
		printf("\n\n\t\t2. EDIT USER INFORMATION");
		printf("\n\n\t\t3. View Transaction History");
		printf("\n\n\t\t4. CHANGE PASSWORD");
		printf("\n\n\t\t0. EXIT");

		printf("\n\n\tSelect Your Option ");

		if(ch<49||ch>57)
		{
		    printf("%c",ch);
			printf("\n\n\tInvalid Choice. Choose Valid Option");
		}
		ch=getch();
		switch(ch)
		{
		case '1':	showuser(username); 	break;
		case '2':	
		strcpy(username,edituser(username));
		printf("\n %s",username);
		break;
		case '3':	viewtransac(username);	break;
		case '4':	editpasswd(username);	break;
		case '0':
			system("cls");
			printf("\n\n\n\n\t\t  Are you sure to exit the Program Y/N");
			ch=getch();
			if(ch=='Y'||ch=='y')
			{	printf("\n\n\n\t\tThanks for using bank management system");
				getch();
				system("color 0f");
				ch='9';
			}
			break;
		default :	printf("\a");
		}
    }while(ch!='9');
}

void showuser(char username[30]){
	char ch;
	user us;
	account acc;
	FILE *fp, *fpx;
	system("cls");
	fp = fopen(userfilelocation,"r");
	if(fp!=NULL){
		do{
			ch = fscanf(fp,"%s %s %s %s %s %s",us.acno,us.address,us.phoneno,us.gender,us.username,us.password);
			if(ch == EOF) break;
			if((strcmp(username,us.username)==0))
			break;
		}while(1);
	}
	fclose(fp);
	fpx = fopen(accountfilelocation,"r");
	if(fpx!=NULL){
		do{
			ch = fscanf(fpx,"%s %s %s %s %s",acc.acno,acc.name,acc.snm,acc.type,acc.balance);
			if(ch == EOF) break;
			if(atol(us.acno)==atol(acc.acno))
			break;
		}while(1);
	}
	fclose(fpx);

	printf("\n\t*************** Your Account Details  ************** ");

	printf("\n\n\t Account Number    \t: %-30s",acc.acno);
	printf("\n\n\t A/C Holder's Name \t: %s %-20s",acc.name, acc.snm);
	printf("\n\n\t A/C Type          \t: %-30s",acc.type);
	printf("\n\n\t Balance Amount    \t: %-30s",acc.balance);
	printf("\n\n\t Address           \t: %-30s",us.address);
	printf("\n\n\t Phone Number      \t: %-30s",us.phoneno);
	printf("\n\n\t Gender            \t: %-30s",us.gender);
	printf("\n\n\t Username          \t: %-30s",us.username);
	

	printf("\n\n\n\t\t Press any key to return main menu");
	getch();
}

char* edituser(char username[30]){
	char* cuname = "empty";
	char ch; user us;
	int a = 1, usercheck = 0;
	char acno[12], name[20],snm[20],type[10],addr[30],ph[12],gender[10],uname[30];
	accountbyusername(username,acno,name,snm,type,addr,ph,gender);
	system("cls");

	do
	{
	    system("cls");

		printf("\n\t*************** Edit User Information ************** ");
		printf("\n\t  User is not allowed to change all details");
        printf("\n\t\t\t\t\t\t\t\tESC : Main Menu");

			printf("\n\n\t1.  Account Number   \t\t: ");
			printf("%s",acno);

		printf("\n\n\t2.  A/C Holder's Name\t\t: ");
		printf("%s %s",name,snm);

		printf("\n\n\t4.  Account Type \t\t: ");
		if(type[0]=='S') strcpy(type,"Saving");
		else strcpy(type,"Current");
		printf(type);

		printf("\n\n\t5.  Address \t\t\t: ");
		printf("%s",addr);
		printf("\n\t    New Address \t\t: ");
		if(usercheck>1)
		printf("%s",us.address);
		else
		getinput("user",us.address);
		if(us.address[0]=='\0') break;					//ESC Key

		printf("\n\n\t6.  Phone Number \t\t: ");
		printf("%s",ph);
		printf("\n\t    Phone Number \t\t: ");
		if(usercheck>1)
		printf("%s",us.phoneno);
		else
		getinput("acno",us.phoneno);
		if(us.phoneno[0]=='\0') break;					//ESC Key

		printf("\n\n\t7.  Gender (Change Not Allowed) : ");
		printf("%s",gender);

		printf("\n\n\t8.  Username \t\t\t: ");
		printf("%s",username);
		printf("\n\t    New Username \t\t: ");
		getinput("user",us.username);
		if(us.username[0]=='\0') break; 				//ESC Key
		if(strcmp(us.username,username)!=0){
			usercheck = checkuser("-1",us.username);
			if(usercheck==1){
				printf("\n\n\t\t\tUsername already exists");
				printf("\n\n\t\tPlease any key to enter another username");
				printf("\a");
				usercheck = 2;
				getch();
				continue;
			}
		}
		a = updateuserdata(acno,us.address,us.phoneno,us.username);
		if(a==0){
			printf("\n\n\t\t\tUser Update Sucess. Press any key");
			// strcpy(cuname,newus.username);
			cuname = us.username;
		}else{
			printf("\n\n\t\t\tUser Not Updated. Press any key");
			// strcpy(cuname,us.username);
			cuname = username;
		}
		ch=getch();
	}while(usercheck);
	return cuname;
}

void editpasswd(char username[30]){

	char ch;
	int a = 1, usercheck = 0;
	char confirmpassword[30];
	FILE *one, *two;
	user myuser,temp;
	system("cls");

	do
	{
	    system("cls");

		printf("\n\t*************** Change Password ************** ");

		printf("\n\n\n");

		printf("\n\n\tNew  Password \t\t: ");
		getinput("password",myuser.password);
		if(myuser.password[0]=='\0') break;					//ESC Key
		
		printf("\n\n\tConfirm Password \t: ");
		getinput("password",confirmpassword);
		if(confirmpassword[0]=='\0') break;					//ESC Key

				if(strcmp(myuser.password,confirmpassword)!=0){
				printf("\n\n\t\t\tPassword no not Match");
				printf("\n\n\t\tPress any to re-enter password");
				printf("\a");
				usercheck = 2;
				getch();
				continue;
			}
			one=fopen(userfilelocation,"r");
			two=fopen(tempfilelocation,"w");
			do{
				ch = fscanf(one,"%s %s %s %s %s %s",temp.acno,temp.address,temp.phoneno,temp.gender,temp.username,temp.password);
				if(ch==EOF) continue;
				if(strcmp(username,temp.username)==0)
					fprintf(two,"%s %s %s %s %s %s ",temp.acno,temp.address,temp.phoneno,temp.gender,username,myuser.password);
				else
				fprintf(two, "%s %s %s %s %s %s ", temp.acno,temp.address,temp.phoneno,temp.gender,temp.username,temp.password);

			}while(ch!=EOF);

			fclose(one);
			fclose(two);

			remove(userfilelocation);
			a = rename(tempfilelocation,userfilelocation);
			if(a ==0){
				printf("\n\n\n\n\t\t\t Password Changed");
			}
			else{
				printf("\n\n\n\n\t Unable to Change :  Internal Error");
			}
		ch=getch();
		break;
	}while(usercheck);
}

void accountbyusername(char username[30],char *acno,char *name,char *snm, char *type, char *addr, char *ph, char *gender){
	char ch,balance[20];
	FILE *a, *b;
	user us;
	a = fopen(userfilelocation,"r");
	if(a!=NULL){
		do{
			ch = fscanf(a,"%s %s %s %s %s %s",us.acno,addr,ph,gender,us.username,us.password);
			if(ch == EOF) break;
			if((strcmp(username,us.username)==0))
			break;
		}while(1);
		fclose(a);
	}
	b = fopen(accountfilelocation,"r");
		if(b!=NULL){
		do{
			ch = fscanf(b,"%s %s %s %s %s",acno,name,snm,type,balance);
			if(ch == EOF) break;
			if(atol(us.acno)==atol(acno)){
				break;
			}
		}while(1);
		fclose(b);
	}
}

int updateuserdata(char acno[12],char addr[30],char ph[12],char uname[30]){
	FILE *ax, *bx;
	char ch;
	user us;
			ax=fopen(userfilelocation,"r");
			bx=fopen(tempfilelocation,"w");
			do
			{	
				ch = fscanf(ax,"%s %s %s %s %s %s",us.acno,us.address,us.phoneno,us.gender,us.username,us.password);
				if(ch==EOF) break;
				if(atol(us.acno)==atol(acno))
					fprintf(bx,"%s %s %s %s %s %s ",acno,addr,ph,us.gender,uname,us.password);
				else
				fprintf(bx, "%s %s %s %s %s %s ", us.acno,us.address,us.phoneno,us.gender,us.username,us.password);
			}while(1);
		// }
		fclose(ax);
		fclose(bx);

		remove(userfilelocation);
		return rename(tempfilelocation,userfilelocation);
}

void tracktransac(char acno[12], char transactype[30], char amount[12]){
	FILE *fileptr;
	fileptr = fopen(transacfilelocation,"a");
	fprintf(fileptr,"%s %s %s ", acno,transactype,amount);
	fclose(fileptr);
}

void viewtransac(char *tranacc){
	int sno=0, page=1, i;
	char ch, fch;
	char *accountnumber;
	FILE *fp;

	FILE *a, *b;
	user us;
	a = fopen(userfilelocation,"r");
	if(a!=NULL){
		do{
			ch = fscanf(a,"%s %s %s %s %s %s",us.acno,us.address,us.phoneno,us.gender,us.username,us.password);
			if(ch == EOF) break;
			if((strcmp(tranacc,us.username)==0))
			break;
		}while(1);
		fclose(a);
		accountnumber = us.acno;
	}
    fp=fopen(transacfilelocation,"r");

    do
    {
	system("cls");
	 printf("\n\t    ********** List of Transactions **********");
	 printf("\n     Page %2d\t\t\t\t\t\t   Enter : Next Page",page);
	 printf("\n\t\t\t\t\t\t\t   ESC    : Main Menu");
	 printf("\n\t\t\t\t\t\t\t   User   : %s",tranacc);

	printf("\n Sn ");
	printf("       Transaction Type      ");		printf("        Amount \n");
	for(i=0;i<38;i++) printf("__");

    do
    {

		fch=fscanf(fp,"%s %s %s",ac.acno, ac.name, ac.snm);
		if(fch==EOF) break;
		if(strcmp(ac.acno,accountnumber)==0){
			sno++;
			printf("\n %2d ",sno);
			printf("  %16s %-16s",ac.name);
			printf("Rs %-10s",ac.snm);
		}
    }while(sno%18!=0);
    ch=getch();
    if(ch==27) break;
    page++;
	}while(fch!=EOF);
	fclose(fp);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    			END OF PROJECT
//***************************************************************
