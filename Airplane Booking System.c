#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_AIRPLANE	5
#define MAX_SEATS		36
#define MAX_NAME		8
#define ADMIN_PASSWORD	"Emzie"

int terminate=0,
	airplaneCount=3,
	state=1,
	currentPlane=-1,
	departureDuration=60,				//Seconds
	departureAllowance=60;				//Seconds


char airplane[MAX_AIRPLANE][MAX_SEATS][MAX_NAME];

char planeName[MAX_AIRPLANE][20];
char departureTime[MAX_AIRPLANE][9];
char departurePlace[MAX_AIRPLANE][10];
int remainingSeats[MAX_AIRPLANE];
int departureHistory[MAX_AIRPLANE];

char errorSpacing[256]="\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
char inputErrorMsg[128]="Option Not Found";
char planeNotAvailable[128]="AirPlane Not Available , Returning to Booking Menu";


int main(int argc, char const *argv[]){
	int i;
	for(i=0;i!=MAX_AIRPLANE;i++){
		clearPlane(i);
	}
	strcpy(planeName[0],"Philippine Air");
	strcpy(planeName[1],"Cebu Pacific Air");
	strcpy(planeName[2],"PAL Express");
	strcpy(planeName[3],"Zest Airways");
	strcpy(planeName[4],"SkyJet");
	strcpy(departurePlace[0],"Manila");
	strcpy(departurePlace[1],"Cebu");
	strcpy(departurePlace[2],"Davao");
	strcpy(departurePlace[3],"Masbate");
	strcpy(departurePlace[4],"Bicol");
	
	assignTime(0,60);
	assignTime(1,120);
	assignTime(2,180);
	assignTime(3,240);
	assignTime(4,300);

	do{
		switch(state){
			case 1:{
				system("cls");
				printf("\n~ Emz\n~ Van\n~ Jazz\n\n\n\n\n\n			Airplane Booking System\n");
				printf("            ______\n");
				printf("            _| _~-|___\n");
				printf("    =  = ==(____AA____D\n");
				printf("                |_____|___________________,-~~~~~~~`-.._\n");
				printf("                /     o O o o o o O O o o o o o o O o  ||_\n");
				printf("                `~-.__        ___..----..                  )\n");
				printf("                      `---~~|___________/------------`````\n");
				printf("                      =  ===(_________D\n\n\n\n\n\n\n");
				system("pause");
				state=2;
				break;
			}
			case 2:{
				system("cls");
				bookMenu();
				printf("Choose the Airplane ID you want to book\nEnter:");
				char input[128];
				int optionFound=0;
				scanf("%s",&input);
				
				if(strcmp(input,"0")==0){
					if(airplaneMap(0))optionFound=1;currentPlane=0;
				}
				else if(strcmp(input,"1")==0){
					if(airplaneMap(1))optionFound=1;currentPlane=1;
				}
				else if(strcmp(input,"2")==0){
					if(airplaneMap(2))optionFound=1;currentPlane=2;
				}
				else if(strcmp(input,"3")==0){
					if(airplaneMap(3))optionFound=1;currentPlane=3;
				}
				else if(strcmp(input,"4")==0){
					if(airplaneMap(4))optionFound=1;currentPlane=4;
				}
				else if(strcmp(input,"back")==0){
					state=1;
				}
				else if(strcmp(input,"admin")==0){
					state=100;
				}
				else{
					warning(inputErrorMsg);
					system("cls");
				}
				if(optionFound==1){
					state=3;
				}
				break;
			}
			case 3:{
				airplaneMap(currentPlane);
				printf("\nChoose Your Seat Number : ");
				char input[128];
				scanf("%s",&input);
				int seat=seatNumber(input,currentPlane);
				if(seat==-1){

				}
				else{
					selectSeat(currentPlane,seat);
				}
				break;
			}
			case 100:{
				system("cls");
				char string[128];
				printf("~Options\n* password\n* back\n");
				printf("			Welcome To Admin Menu\nPlease Enter Admin Password : ");
				scanf("%s",&string);
				if(strcmp(string,"back")==0){
					state=1;
					warning("Returning To Booking Title\n");
					break;
				}
				else if(strcmp(string,ADMIN_PASSWORD)!=0){
					warning("Password Incorrect\n");
					break;
				}
				if(strcmp(string,ADMIN_PASSWORD)==0){
					warning("Login Successful\n");
					system("cls");
					
					adminMenu();
					break;
				}
				break;
			}

		}
	}
	while(!terminate);
}

int start(){
	system("pause");
	
}

int adminMenu(){
	system("cls");
	printf("~Options\n* 1-8\n*back\n");
	printf("				  Admin Menu\n");
	printf("	Command ID				Command\n\n");
	printf("	    1				Change Airplane Name\n");
	printf("	    2				Change Airplane Destination\n");
	printf("	    3				Change Departure Duration\n");
	printf("	    4				Change Departure Allowance\n");
	printf("	    5				Change Departure Schedule\n");
	printf("	    6				Remove AirPlane\n");
	printf("	    7				Add AirPlane\n");
	printf("	    8				Terminate Program\n\n");
	printf("Choose Command ID : ");
	char string[128];
	scanf("%s",&string);
	if(strcmp(string,"1")==0){
		changeAirplaneName();
		return 1;
	}
	if(strcmp(string,"2")==0){
		changeAirplaneDestination();
		return 1;
	}
	else if(strcmp(string,"3")==0){
		system("cls");
		printf("~Options\n* strictly numbers only or else the program will terminate prematurely\n\n\n");
		printf("Current Departure Duration : %d\n\n",departureDuration);
		printf("Enter Desired Duration in Seconds : ");
		int temp;
		scanf("%d",&temp);
		system("cls");
		printf(errorSpacing);
		printf("Successfully Changed Departure Duration from %d seconds to %d seconds",departureDuration,temp);
		printf(errorSpacing);
		system("pause");
		system("cls");
		departureDuration=temp;
		adminMenu();
		return 1;
	}
	else if(strcmp(string,"4")==0){
		system("cls");
		printf("~Options\n* strictly numbers only or else the program will terminate prematurely\n\n\n");
		printf("Current Departure Allowance : %d\n\n",departureAllowance);
		printf("Enter Desired Allowance in Seconds : ");
		int temp;
		scanf("%d",&temp);
		system("cls");
		printf(errorSpacing);
		printf("Successfully Changed Departure Allowance from %d seconds to %d seconds",departureAllowance,temp);
		printf(errorSpacing);
		system("pause");
		system("cls");
		departureAllowance=temp;
		adminMenu();
		return 1;
	}
	else if(strcmp(string,"5")==0){
		changeAirplaneSchedule();
		return 1;
	}
	else if(strcmp(string,"6")==0){
		removeAirplane();
		return 1;
	}
	else if(strcmp(string,"7")==0){
		system("cls");
		int temp=-1,i;
		for(i=0;i!=5;i++){
			if(planeName[i][0]=='\0'){
				temp=i;
				break;
			}
		}
		if(temp==-1){
			warning("Airplane number has reached to its Maximum");
			adminMenu();
			return 1;
		}
		else{
			system("cls");
			printf("~Options\n* Name\n\n\n");
			printf("Type a Name for the Airplane you want to add : ");
			scanf("%s",&string);
			//string[0]='\0';
			//char input[11];
			//scanf("%10[0-9a-zA-Z ]", &input);
			printf("Are You sure you want to change the name of Airplane ID : %d to %s \nType 1 ) If yes  2) If no : ",temp,string);
			char string1[128];
			scanf("%s",&string1);
			if(strcmp(string1,"1")==0){
				system("cls");
				printf(errorSpacing);
				printf("Successfully change name from %s to %s\n",planeName[temp],string);
				printf(errorSpacing);
				system("pause");
				strcpy(planeName[temp],string);
				adminMenu();
				return 1;
			}
			else if(strcmp(string1,"2")==0){
				system("cls");
				printf(errorSpacing);
				printf("Returning to Admin Menu\n");
				printf(errorSpacing);
				system("pause");
				strcpy(planeName[temp],string);
				adminMenu();
				return 1;
			}
			else{
				warning(inputErrorMsg);
				system("cls");
				adminMenu();
				adminMenu();
				return 1;
			}
			adminMenu();
			return 1;
		}
		
	}
	else if(strcmp(string,"8")==0){
		system("cls");
		printf(errorSpacing);
		printf("Bye Bye");
		printf(errorSpacing);
		system("pause");
		terminate=1;
		return 1;
	}
	else if(strcmp(string,"back")==0){
		state=1;
		warning("Returning To Booking Title\n");
		return 1;
	}
	else{
		warning(inputErrorMsg);
		system("cls");
		adminMenu();
		return 1;
	}
}
int removeAirplane(){
	
		system("cls");
		printf("			Remove Airplane\n");
		bookMenu();
		printf("Choose Airplane ID you want to remove : ");
		int time;
		char string[128];
		currentPlane=-1;
		scanf("%s",&string);
		
		if(strcmp(string,"0")==0){
			currentPlane=0;
		}
		else if(strcmp(string,"1")==0){
			currentPlane=1;
		}
		else if(strcmp(string,"2")==0){
			currentPlane=2;
		}
		else if(strcmp(string,"3")==0){
			currentPlane=3;
		}
		else if(strcmp(string,"4")==0){
			currentPlane=4;
		}
		else if(strcmp(string,"back")==0){
			warning("Returning to Admin Menu\n");
			adminMenu();	
			return 1;
		}
		else{
			warning(inputErrorMsg);
			removeAirplane();
			return 1;
		}
		if(planeName[currentPlane][0]=='\0'&&currentPlane!=-1){
				warning("Airplane Not Available");
				removeAirplane();
				return 1;
		}
		else{
			system("cls");
			printf(errorSpacing);
			printf("Successfully Airplane with Airplane ID : %d ",currentPlane);
			printf(errorSpacing);
			planeName[currentPlane][0]='\0';
			system("pause");
			adminMenu();
			return 1;
			/*
			//string[0]='\0';
			//char input[11];
			//scanf("%10[0-9a-zA-Z ]", &input);
			printf("Are You sure you want to change %s to %s\nType 1 ) If yes  2) If no : ",planeName[currentPlane],string);
			char string1[128];
			scanf("%s",&string1);
			if(strcmp(string1,"1")==0){
				system("cls");
				printf(errorSpacing);
				printf("Successfully change name from %s to %s\n",planeName[currentPlane],string);
				printf(errorSpacing);
				system("pause");
				strcpy(planeName[currentPlane],string);
				removeAirplane();
			}
			else if(strcmp(string1,"2")==0){
				warning("Returning to Change Airplane Name Command\n");
				removeAirplane();
			}
			else{
				warning("Option Not Found , Returning to Change Airplane Name Command\n");
				removeAirplane();
			}
			*/
		}
}


int changeAirplaneSchedule(){
	
		system("cls");
		printf("			Change Airplane Schedule\n");
		bookMenu();
		printf("Choose Airplane ID you want to change the Schedule : ");
		int time;
		char string[128];
		currentPlane=-1;
		scanf("%s",&string);
		
		if(strcmp(string,"0")==0){
			currentPlane=0;
		}
		else if(strcmp(string,"1")==0){
			currentPlane=1;
		}
		else if(strcmp(string,"2")==0){
			currentPlane=2;
		}
		else if(strcmp(string,"3")==0){
			currentPlane=3;
		}
		else if(strcmp(string,"4")==0){
			currentPlane=4;
		}
		else if(strcmp(string,"back")==0){
			warning("Returning to Admin Menu\n");
			adminMenu();	
			return 1;
		}
		else{
			warning(inputErrorMsg);
			changeAirplaneSchedule();
		}
		if(planeName[currentPlane][0]=='\0'&&currentPlane!=-1){
				warning("Airplane Not Available");
				changeAirplaneSchedule();
				return 1;
		}
		else{
			printf("Enter a Time that you want to change from Airplane Schedule %s in seconds starting this time\nEnter : ",departureTime[currentPlane]);
			
			scanf("%d",&time);
			
			strcpy(string,departureTime[currentPlane]);
			
			assignTime(currentPlane,time);
			system("cls");
			printf(errorSpacing);
			printf("Successfully Changed Schedule of Airplane %s from %s to %s",planeName[currentPlane],string,departureTime[currentPlane]);
			printf(errorSpacing);
			system("pause");
			adminMenu();
			return 1;
			/*
			//string[0]='\0';
			//char input[11];
			//scanf("%10[0-9a-zA-Z ]", &input);
			printf("Are You sure you want to change %s to %s\nType 1 ) If yes  2) If no : ",planeName[currentPlane],string);
			char string1[128];
			scanf("%s",&string1);
			if(strcmp(string1,"1")==0){
				system("cls");
				printf(errorSpacing);
				printf("Successfully change name from %s to %s\n",planeName[currentPlane],string);
				printf(errorSpacing);
				system("pause");
				strcpy(planeName[currentPlane],string);
				changeAirplaneSchedule();
			}
			else if(strcmp(string1,"2")==0){
				warning("Returning to Change Airplane Name Command\n");
				changeAirplaneSchedule();
			}
			else{
				warning("Option Not Found , Returning to Change Airplane Name Command\n");
				changeAirplaneSchedule();
			}
			*/
		}
}
int changeAirplaneDestination(){
	
		system("cls");
		printf("			Change Airplane Destination\n");
		bookMenu();
		printf("Choose Airplane ID you want to change the Destination : ");
		char string[128];
		currentPlane=-1;
		scanf("%s",&string);
		
		if(strcmp(string,"0")==0){
			currentPlane=0;
			
		}
		else if(strcmp(string,"1")==0){
			currentPlane=1;
		}
		else if(strcmp(string,"2")==0){
			currentPlane=2;
		}
		else if(strcmp(string,"3")==0){
			currentPlane=3;
		}
		else if(strcmp(string,"4")==0){
			currentPlane=4;
		}
		else if(strcmp(string,"back")==0){
			warning("Returning to Admin Menu\n");
			adminMenu();	
			return 1;
		}
		else{
			warning(inputErrorMsg);
			changeAirplaneDestination();
			return 1;
		}
		/*
		if(departurePlace[currentPlane][0]=='\0'&&currentPlane!=-1){
				warning("Airplane Not Available");
				changeAirplaneDestination();
				return 1;
		}
		*/
		//else{
			printf("Enter a Name that you want to change from Airplane Destination %s\nEnter : ",departurePlace[currentPlane]);
			scanf("%s",&string);
			//string[0]='\0';
			//char input[11];
			//scanf("%10[0-9a-zA-Z ]", &input);
			printf("Are You sure you want to change destination from %s to %s\nType 1 ) If yes  2) If no : ",departurePlace[currentPlane],string);
			char string1[128];
			scanf("%s",&string1);
			if(strcmp(string1,"1")==0){
				system("cls");
				printf(errorSpacing);
				printf("Successfully destination from %s to %s\n",departurePlace[currentPlane],string);
				printf(errorSpacing);
				system("pause");
				strcpy(departurePlace[currentPlane],string);
				changeAirplaneDestination();
				return 1;
			}
			else if(strcmp(string1,"2")==0){
				warning("Returning to Change Airplane Destination Command\n");
				changeAirplaneDestination();
				return 1;
			}
			else{
				warning("Option Not Found , Returning to Change Airplane Destination Command\n");
				changeAirplaneDestination();
				return 1;
			}
		//}
}
int changeAirplaneName(){
	
		system("cls");
		printf("			Change Airplane Name\n");
		bookMenu();
		printf("Choose Airplane ID you want to change the name : ");
		char string[128];
		currentPlane=-1;
		scanf("%s",&string);
		
		if(strcmp(string,"0")==0){
			currentPlane=0;
			
		}
		else if(strcmp(string,"1")==0){
			currentPlane=1;
		}
		else if(strcmp(string,"2")==0){
			currentPlane=2;
		}
		else if(strcmp(string,"3")==0){
			currentPlane=3;
		}
		else if(strcmp(string,"4")==0){
			currentPlane=4;
		}
		else if(strcmp(string,"back")==0){
			warning("Returning to Admin Menu\n");
			adminMenu();	
			return 1;
		}
		else{
			warning(inputErrorMsg);
			changeAirplaneName();
			return 1;
		}
		if(planeName[currentPlane][0]=='\0'&&currentPlane!=-1){
				warning("Airplane Not Available");
				changeAirplaneName();
				return 1;
		}
		else{
			printf("Enter a Name that you want to change from Airplane Name %s\nEnter : ",planeName[currentPlane]);
			scanf("%s",&string);
			//string[0]='\0';
			//char input[11];
			//scanf("%10[0-9a-zA-Z ]", &input);
			printf("Are You sure you want to change %s to %s\nType 1 ) If yes  2) If no : ",planeName[currentPlane],string);
			char string1[128];
			scanf("%s",&string1);
			if(strcmp(string1,"1")==0){
				system("cls");
				printf(errorSpacing);
				printf("Successfully change name from %s to %s\n",planeName[currentPlane],string);
				printf(errorSpacing);
				system("pause");
				strcpy(planeName[currentPlane],string);
				changeAirplaneName();
				return 1;
			}
			else if(strcmp(string1,"2")==0){
				warning("Returning to Change Airplane Name Command\n");
				changeAirplaneName();
				return 1;
			}
			else{
				warning("Option Not Found , Returning to Change Airplane Name Command\n");
				changeAirplaneName();
				return 1;
			}
		}
}

int airplaneMap(planeNumber){
	if(planeName[planeNumber][0]=='\0'){
		warning(planeNotAvailable);
		return 0;
	}
	else if(strcmp(departureTime[planeNumber],"DEPARTED")==0){
		warning("Airplane Already Departed\n");
		return 0;
	}
	system("cls");
	printf("~Options\n* 0-32\n* back\n\n");
	printf("\n\n			%8s SEAT MAP		\n",planeName[planeNumber]);
	printf("	BUSINESS CLASS		|		ECONOMIC CLASS\n");
	printf("				|\n");
	int i;
	int availableSeats=36,
		occupiedSeats=0;
	for(i=0;i<2;i++){
		int j;
		for(j=0;j!=4;j++){
			if(seatLabel(planeNumber,(j*4)+i))availableSeats--;
		}
		printf("	|	  ");
		for(j=0;j!=5;j++){
			if(seatLabel(planeNumber,(j*4)+i+16))availableSeats--;
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<2;i++){
		int j;
		for(j=0;j!=4;j++){
			if(seatLabel(planeNumber,(j*4)+i+2))availableSeats--;
		}
		printf("	|	  ");
		for(j=0;j!=5;j++){
			if(seatLabel(planeNumber,(j*4)+i+16+2))availableSeats--;
		}
		printf("\n");
	}
	remainingSeats[planeNumber]=availableSeats;
	printf("\nAvailable Seats : %d seats\n\n",availableSeats);
	printf("Occupied Seat List : \n");
	
	for(i=0;i!=36;i++){
		if(airplane[planeNumber][i][0]!='\0'){
			printf("%2d) %8s   ",i,airplane[planeNumber][i]);
			occupiedSeats++;
			if((occupiedSeats%5)==0){															//	List Escape line
				printf("\n");
			}
		}
		
	}
	return 1;
	
}

int seatLabel(planeNumber,seat){
	if(airplane[planeNumber][seat][0]!='\0'){
		printf("XX     ");
		return 1;
	}
	else{
		printf("%2d     ",seat);
		
	}
	return 0;
}

int clearPlane(planeNumber){
	int i;
	for(i=0;i!=MAX_SEATS;i++){
		airplane[planeNumber][i][0]='\0';
	}
	remainingSeats[planeNumber]=36;
}

int bookMenu(){
	int i;
	for(i=0;i<MAX_AIRPLANE;i++){
		update(i);
	}
	printf("~Options:\n* 0-4\n* admin\n* back\n\n");
	printf("				    Booking Menu\n\n");
	printf(" ID      Airplane Name          Outbound      Departure Time     Remaining Seats\n\n");
	for(i=0;i!=MAX_AIRPLANE;i++){
		if(planeName[i][0]!='\0')printf(" %d  %-20s     %-10s          %-8s               %-2d\n\n",i,planeName[i],departurePlace[i],departureTime[i],remainingSeats[i]);
	}
}

int selectSeat(planeNumber,seat){

	if(airplane[planeNumber][seat][0]!='\0'){
		warning("Seat Number Occupied , Returning to Seat Selection\n");
		return 0;
	}
	char input[128];
	printf("You Chose Seat Number %d , \nPlease Enter Your Name: ",seat);
	scanf("%s",&input);
	input[MAX_NAME-1]='\0';
	printf("\nAre You Sure You Want To book %s in seat %d,\nEnter 1).If Yes  2.) If No : ",input,seat);
	char input1[128];
	scanf("%s",&input1);
	if(strcmp(input1,"1")==0){
		
		strcpy(airplane[currentPlane][seat],input);
		remainingSeats[currentPlane]--;
		system("cls");
		printf(errorSpacing);
		printf("You have successfully booked %s in Seat Number %d ,\n Thank You for Patronizing our Services ,\nPrinting your Boarding Pass\n",input,seat);
		printf(errorSpacing);
		system("pause");
		
		state=1;
	}
	else if(strcmp(input1,"2")==0){
		warning("Returning to Seat Selection\n");
	}
	else if(strcmp(input1,"back")==0){
		warning("Returning to Seat Selection\n");
	}
	else if(strcmp(input1,"admin")==0){
		
	}
	else{
		warning("Option Not Found , Returning to Seat Selection\n");
		system("pause");
	}
	
}

int seatNumber(char number[128],int planeNumber){
	
	if(strcmp(number,"0")==0)return 0;
	else if(strcmp(number,"1")==0)return 1;
	else if(strcmp(number,"2")==0)return 2;
	else if(strcmp(number,"3")==0)return 3;
	else if(strcmp(number,"4")==0)return 4;
	else if(strcmp(number,"5")==0)return 5;
	else if(strcmp(number,"6")==0)return 6;
	else if(strcmp(number,"7")==0)return 7;
	else if(strcmp(number,"8")==0)return 8;
	else if(strcmp(number,"9")==0)return 9;
	else if(strcmp(number,"10")==0)return 10;
	else if(strcmp(number,"11")==0)return 11;
	else if(strcmp(number,"12")==0)return 12;
	else if(strcmp(number,"13")==0)return 13;
	else if(strcmp(number,"14")==0)return 14;
	else if(strcmp(number,"15")==0)return 15;
	else if(strcmp(number,"16")==0)return 16;
	else if(strcmp(number,"17")==0)return 17;
	else if(strcmp(number,"18")==0)return 18;
	else if(strcmp(number,"19")==0)return 19;
	else if(strcmp(number,"20")==0)return 20;
	else if(strcmp(number,"21")==0)return 21;
	else if(strcmp(number,"22")==0)return 22;
	else if(strcmp(number,"23")==0)return 23;
	else if(strcmp(number,"24")==0)return 24;
	else if(strcmp(number,"25")==0)return 25;
	else if(strcmp(number,"26")==0)return 26;
	else if(strcmp(number,"27")==0)return 27;
	else if(strcmp(number,"28")==0)return 28;
	else if(strcmp(number,"29")==0)return 29;
	else if(strcmp(number,"30")==0)return 30;
	else if(strcmp(number,"31")==0)return 31;
	else if(strcmp(number,"32")==0)return 32;
	else if(strcmp(number,"33")==0)return 33;
	else if(strcmp(number,"34")==0)return 34;
	else if(strcmp(number,"35")==0)return 35;
	else if(strcmp(number,"back")==0){
		warning("Returning to Book Menu");
		state=2;
		return -1;
	}
	else{
		warning("Invalid Seat Number , Returning to Airplane Map\n");
		state=3;
		return -1;
	}
}

int checksize(char string[128]){
	int i,size=0;
	for(i=0;i!=128;i++){
		if(string[i]!='\0')size++;
	}
	return size;
}

int update(planeNumber){

   time_t rawtime;
   struct tm *info;	
	char store[80];
   rawtime = time( NULL );
   int i;
   for(i=0;i<MAX_AIRPLANE;i++){
		if((strcmp(departureTime[planeNumber],"DEPARTED")!=0)&&departureHistory[planeNumber]<=rawtime){
   			strcpy(departureTime[planeNumber],"DEPARTED");
		}
		else if((rawtime-departureHistory[planeNumber])>=departureDuration){
			clearPlane(planeNumber);
			assignTime(planeNumber,departureAllowance);
		}
   	
   }
   return(0);

}

int assignTime(planeNumber,seconds){
	time_t rawtime;
   struct tm *info;
   char store[80];
   rawtime = time( NULL )+seconds;
   info = localtime( &rawtime );
   strftime(store,80,"%I:%M%p", info);
   strcpy(departureTime[planeNumber],store);
   departureHistory[planeNumber]=rawtime;
  
   return(0);
}

int warning(char string[128]){
	system("cls");
	printf(errorSpacing);
	printf(string);
	printf(errorSpacing);
	system("pause");
}

/*

PLANE SEATS MAP

0	4	8	12	|	16	20	24	28	32
1	5	9	13	|	17	21	25	29	33
				|
2	6	10	14	|	18	22	26	30	34
3	7	11	15	|	19	23	27	31	35






     __o__   _______ _ _  _                                     /     /
     \    ~\                                                  /      /
       \     '\                                         ..../      .'
        . ' ' . ~\                                      ' /       /
       .  _    .  ~ \  .+~\~ ~ ' ' " " ' ' ~ - - - - - -''_      /
      .  <#  .  - - -/' . ' \  __                          '~ - \
       .. -           ~-.._ / |__|  ( )  ( )  ( )  0  o    _ _    ~ .
     .-'                                               .- ~    '-.    -.
    <                      . ~ ' ' .             . - ~             ~ -.__~_. _ _
      ~- .       N121PP  .          . . . . ,- ~
            ' ~ - - - - =.   <#>    .         \.._
                        .     ~      ____ _ .. ..  .- .
                         .         '        ~ -.        ~ -.
                           ' . . '               ~ - .       ~-.
                                                       ~ - .      ~ .
                                                              ~ -...0..~. ____
                                                              
                                                              
printf("            ______\n");
printf("            _| _~-|___\n");
printf("    =  = ==(____AA____D\n");
printf("                |_____|___________________,-~~~~~~~`-.._\n");
printf("                /     o O o o o o O O o o o o o o O o  ||_\n");
printf("                `~-.__        ___..----..                  )\n");
printf("                      `---~~|___________/------------`````\n");
printf("                      =  ===(_________D\n");
                      
                      
                                           ********
                                          *      *
                                         *      *
      ***********************************      *
    *  (  )      () () () () () ()            *
  *           *        *                   *
 *             *        *               *
  ************************************  -ds
                  *       *
                   *********
                   
                   
printf("                             _\n");
printf("                            | \\n");
printf("                           _|  \______________________________________\n");
printf("                          - ______        ________________          \_`,\n");
printf("                        -(_______            -=    -=        USAF       )\n");
printf("                                 `--------=============----------------`   -\n");



printf("                                       |\n");
printf("   BOEING 777                          |\n");
printf("   by Jon Hyatt                        |\n");
printf("   whatfer@u.washington.edu          .-'-.\n");
printf("                                    ' ___ '\n");
printf("                          ---------'  .-.  '---------\n");
printf("          _________________________'  '-'  '_________________________\n");
printf("           ''''''-|---|--/    \==][^',_m_,'^][==/    \--|---|-''''''\n");
printf("                         \    /  ||/   H   \||  \    /\n");
printf("                          '--'   OO   O|O   OO   '--'\n");
*/
