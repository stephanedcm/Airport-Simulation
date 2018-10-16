#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define TAILLE_MAX 1000

//structure of plane
typedef struct avion avion;
struct avion
{
    char identifiant[7];
    int carburant;
    int consommation;
    int heure;
    int minute;
    char request;

};
//structure of linked list depart
struct Depart
{
   avion data;
   struct Depart *next_dep;
}*front_dep = NULL,*rear_dep = NULL;

//structure of linked list arrive
struct Arrive
{
   avion data;
   struct Arrive *next_arr;
}*front_arr = NULL,*rear_arr = NULL;

//function to import planes in the .txt files
avion Addavion_txt(int cpt)
{
    avion avion1;
    int random;
    FILE *identifiant = NULL;
    if(cpt==0)
    {
        identifiant = fopen("arrive.txt", "r");
    }
    if(cpt==1)
    {
        identifiant = fopen("arrive1.txt", "r");
    }
    if(cpt==2)
    {
        identifiant = fopen("arrive2.txt", "r");
    }
    if (identifiant != NULL)
    {
        fgets(avion1.identifiant, 7, identifiant);
    }
    avion1.carburant=rand()%(1500-1000)+1000;
    avion1.consommation=rand()%20;
    avion1.heure=rand()%24;
    avion1.minute=rand()%60;
    random=rand()%100;
    if(random < 50)
        avion1.request = 'A';
    else
        avion1.request = 'U';
    return avion1;
}

//function to add avion in the departure linked list
avion Addavion_dep(time)
{
    avion avion1;
    printf("Please enter the flight number: ");
    scanf("%s", avion1.identifiant);
    printf("Enter the time of the take off like this xx:xx : ");
    scanf("%d:%d", &avion1.heure,&avion1.minute);
    while(avion1.heure<=time/60 && avion1.minute<=time%60)
    {
        printf("You can't add a flight after its take off time !");
        printf("Enter the time of the take off like this xx:xx : ");
        scanf("%d:%d", &avion1.heure,&avion1.minute);
    }
    avion1.request = 'D';
    return avion1;
}

//function to add flights in the departure linkedlist
avion Addavion_arr(time)
{
    avion avion1;
    printf("Please enter the flight number: ");
    scanf("%s", avion1.identifiant);
    printf("Enter the fuel remaining: ");
    scanf("%d", &avion1.carburant);
    printf("Enter now the consumption per minute of this plane: ");
    scanf("%d", &avion1.consommation);
    printf("Enter the time of the take off like this xx:xx : ");
    scanf("%d:%d", &avion1.heure,&avion1.minute);
    while(avion1.heure<=time/60 && avion1.minute<=time%60 || avion1.heure>23 || avion1.minute>59)
    {
        printf("You can't add a flight after its landing time and you must enter a valid time !");
        printf("Enter the time of the take off like this xx:xx : ");
        scanf("%d:%d", &avion1.heure,&avion1.minute);
    }
    printf("Enter the request of the plane : ");
    scanf("%s",&avion1.request);
    return avion1;
}

//main loop
int main()
{
   printf("--Welcome in the Airport Management Software of Stéphane and Yanis-- \nWhat do you want to do ?\n\n");
   int choice,time=0,x=0,i,cpt;
   char a,test;
   avion avion1;
   for(cpt=0;cpt<3;cpt++)
   {
        avion1=Addavion_txt(cpt);
        insert_arriv(avion1);
   }

   while(time<1440){
      printf("It is: %d:%d o'clock\n",time/60,time%60);
      printf("1. Manage the departures\n2. Manage the arrivals\n3. Display all the list of flights\n4. to wait an hour\n5. to wait 5 min \n6. to quit.\n\n");
      printf("Enter your choice: ");
      scanf("%d",&choice);
      switch(choice){
	  case 1:
	      x=0;
	     while(x==0){
            printf("\nAIRPORT MANAGEMENT - MANAGEMENT OF THE DEPARTURES\n\n");
            printf("1. Insert a flight\n2. Delete a departure flight\n3. Display the departure list\n4. Return to the main menu\n\n");
            printf("Enter your choice: ");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    printf("Enter plane characteristics to be insert:\n");
                    avion1=Addavion_dep(time);
                    insert_depart(avion1);
                    break;
                case 2:
                    delete_number_dep(); break;
                case 3:
                    display_depart(); break;
                case 4:
                    x=1; break;
                default:
                    printf("\nWrong selection. Please try again.\n");
                            }
                }
                break;

	 case 2:
	     x=0;
	     while(x==0){
            printf("\nAIRPORT MANAGEMENT - MANAGEMENT OF THE ARRIVALS\n\n");
            printf("1. Insert a flight\n2. Prioritize an arrival flight \n3. Display the arrival list\n4. Return to the main menu\n\n");
            printf("Enter your choice: ");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    printf("Enter plane characteristics to be insert:\n");
                    avion1=Addavion_arr(time);
                    insert_arriv(avion1);
                    break;
                case 2: emergency(); break;
                case 3: display_arriv(); break;
                case 4: x=1; break;
                default: printf("\nWrong selection. Please try again.\n"); break;
                            }
                }
                break;
     case 3:
        display_total();break;

     case 4:
         time+=60;
         planning_dep(time);
         planning_arr(time);
         break;

     case 5:
         time+=5;
         planning_dep(time);
         planning_arr(time);
         break;

     case 6:
        exit(0);break;

     default: printf("\nWrong selection. Please try again.\n"); break;
   }
   }
   return(0);
}


//function which insert in the linked list
void insert_depart(avion avion1)
{
   struct Depart *newDepart;
   newDepart = (struct Depart*)malloc(sizeof(struct Depart));
   newDepart->data = avion1;
   newDepart -> next_dep = NULL;
   if(front_dep == NULL)
      front_dep = rear_dep = newDepart;
    else{
      if(newDepart->data.heure>front_dep->data.heure)
      {
          rear_dep -> next_dep = newDepart;
          rear_dep = newDepart;
      }

    if(newDepart->data.heure<front_dep->data.heure)
      {
          newDepart->next_dep=front_dep;
          front_dep=newDepart;
      }

    if(newDepart->data.heure==front_dep->data.heure)
      {
         if(newDepart->data.minute>front_dep->data.minute)
      {
          rear_dep -> next_dep = newDepart;
          rear_dep = newDepart;
      }

    if(newDepart->data.minute<front_dep->data.minute)
      {
          newDepart->next_dep=front_dep;
          front_dep=newDepart;
      }
      }



}}

//function which insert in the linked list arriv
void insert_arriv(avion avion1)
{
   struct Arrive *newarriv,*temp;
   newarriv = (struct Depart*)malloc(sizeof(struct Depart));
   newarriv->data = avion1;
   newarriv -> next_arr = NULL;
   if(front_arr == NULL)
      front_arr = rear_arr = newarriv;
    else{
        if(newarriv->data.heure<front_arr->data.heure)
      {
          rear_arr -> next_arr = newarriv;
          rear_arr = newarriv;
      }

    if(newarriv->data.heure>front_arr->data.heure)
      {
          newarriv->next_arr=front_arr;
          front_arr=newarriv;
      }

    }



   printf("\nFlight added.\n");
}


//function didn't used in the file
void delete_first_added()
{
   if(front_dep == NULL)
      printf("\nThere isn't any flight.\n");
   else{
      struct Depart *temp = front_dep;
      front_dep = front_dep -> next_dep;
      printf("\nDeleted flight: %s\n", temp->data.identifiant);
      free(temp);
   }
}


void delete_number()
{
   int check;
   char todelete[7];
   if(front_dep == NULL)
      printf("\nThere isn't any flight to delete.\n");
   else{
      struct Depart *temp = front_dep;
      scanf("%s",&todelete);
      check=strcmp(temp->data.identifiant,todelete);
      while(check!=0)
      {
          temp = temp -> next_dep;
          check=strcmp(temp->data.identifiant,todelete);
      }
      if(check==0)
      {
          front_dep = front_dep -> next_dep;
          printf("\nDeleted flight: %s\n", temp->data.identifiant);
          free(temp);
      }

   }
}

//function which allow to enter the ID of the plan you want to delete in the departures
void delete_number_dep()
{
   int check;
   char todelete[7];
   if(front_dep == NULL)
      printf("\nThere isn't any flight to delete.\n");
   else{
      struct Depart *temp = front_dep,*temp1;
      scanf("%s",&todelete);
      check=strcmp(temp->data.identifiant,todelete);
      if(temp->next_dep==NULL)
      {
          front_dep = front_dep -> next_dep;
          printf("\nDeleted flight: %s\n", temp->data.identifiant);
          free(temp);
      }
      while(temp->next_dep !=NULL && check!=0)
      {
          if(temp->next_dep==NULL)
            printf("Didn't find");
          temp1=temp;
          temp=temp->next_dep;
          check=strcmp(temp->data.identifiant,todelete);
      }
      temp1->next_dep=temp->next_dep;
   }
}

//function which display the departures
void display_depart()
{
   if(front_dep == NULL)
      printf("\nThere are no plane ready to take off.\n");
   else{
      struct Depart *temp = front_dep;
      while(temp->next_dep != NULL){
            printf("%s-%c-%d%d\n",temp->data.identifiant,temp->data.request,temp->data.heure,temp->data.minute);
            temp = temp -> next_dep;
                               }
      printf("%s-%c-%d%d\n",temp->data.identifiant,temp->data.request,temp->data.heure,temp->data.minute);
   }
}

//function which display the arrivals
void display_arriv()
{
   if(front_arr == NULL)
      printf("\nThere are no plane ready to land.\n");
   else{
      struct Arrive *temp = front_arr;
      while(temp->next_arr != NULL){
            printf("%s-%c-%d-%d\n",temp->data.identifiant,temp->data.request,temp->data.carburant,temp->data.consommation);
            temp = temp -> next_arr;
                               }
      printf("%s-%c-%d-%d\n",temp->data.identifiant,temp->data.request,temp->data.carburant,temp->data.consommation);
   }
}

//function which display all the flights (departure & arrivals)
void display_total()
{
    if(front_dep == NULL)
      printf("\nThere aren't any planes planned to take off.\n\n");
    else{
      struct Depart *temp = front_dep;
      printf("------------DEPARTURE------------\n");
      while(temp->next_dep != NULL){
            printf("%s-%c-%d%d\n",temp->data.identifiant,temp->data.request,temp->data.heure,temp->data.minute);
            temp = temp -> next_dep;
                               }
      printf("%s-%c-%d%d\n",temp->data.identifiant,temp->data.request,temp->data.heure,temp->data.minute);
   }
   if(front_arr == NULL)
      printf("\nThere aren't any planes planned to land.\n\n");
    else{
      struct Arrive *temp = front_arr;
      printf("------------ARRIVAL------------\n");
      while(temp->next_arr != NULL){
            printf("%s-%c-%d-%d\n",temp->data.identifiant,temp->data.request,temp->data.carburant,temp->data.consommation);
            temp = temp -> next_arr;
                               }
      printf("%s-%c-%d-%d\n",temp->data.identifiant,temp->data.request,temp->data.carburant,temp->data.consommation);
   }
}

//function which prioritize the flights when you enter the ID
void emergency()
{
    int check;
   char toprioritize[7];
   if(front_arr == NULL)
      printf("\nThere isn't any flight to prioritize.\n");
   else{
      struct Arrive *temp = front_arr;
      scanf("%s",&toprioritize);
      check=strcmp(temp->data.identifiant,toprioritize);
      while(check!=0)
      {
          temp = temp -> next_arr;
          check=strcmp(temp->data.identifiant,toprioritize);
      }
      if(check==0)
      {
          temp->data.request='U';
          printf("\nPrioritized flight: %s\n", temp->data.identifiant);
      }

   }
}

//funtion which check with the time if a plane must take off according to its time of takeoff
void planning_dep(time)
{
    if(front_dep !=NULL)
    {
        struct Depart *temp = front_dep;
        while(temp != NULL)
        {
            if(((temp->data.heure)*60)+(temp->data.minute)<=time )
            {

                front_dep = front_dep -> next_dep;
                printf("\nThis flight took off: %s\n", temp->data.identifiant);
                break;

            }
            else{
                temp = temp -> next_dep;
                }
        }
    }
}

//funtion which check with the time if a plane must land
void planning_arr(time)
{
    if(front_arr !=NULL)
    {
        struct Arrive *temp = front_arr;
        while(temp != NULL)
        {
            if(((temp->data.heure)*60)+(temp->data.minute)<=time )
            {

                front_arr = front_arr -> next_arr;
                printf("\nThis flight landed: %s\n", temp->data.identifiant);
                break;

            }
            else{
                temp = temp -> next_arr;
                }
        }
    }
}

//funtion which check if a plane have enough fuel to achieve its flight, if not, the function prioritized the flights
void fuel(time)
{
    if(front_arr !=NULL)
    {
        struct Arrive *temp = front_arr;
        while(temp != NULL)
        {
            if(temp->data.consommation*((((temp->data.heure)*60)+(temp->data.minute))-time)<temp->data.carburant)
            {
                temp->data.request='U';
                printf("\nThis flight become a priority to land !: %s\n", temp->data.identifiant);
                break;

            }
            else{
                temp = temp -> next_arr;
                }
        }
    }
}

