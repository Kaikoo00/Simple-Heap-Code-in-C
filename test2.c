#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define arr_size 500
const char PATH[] = "./Patient.txt";

struct birth_date{
    int day, month, year;
};

typedef struct patient{
    char name[40];
    int age;
    char gender;
    struct birth_date date;
    char bpjs[20];
    char issue[50];
    int urgency;
    int hour;
    int min;
}patient;

void swap(patient *a, patient *b){
    patient temp = *a;
    *a = *b;
    *b = temp;
}

bool isValidBirthDate(int day, int month, int year) {
    if (year < 1900 || year > 2023) return false;

    if (month < 1 || month > 12) return false;

    int maxDay;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) maxDay = 29;
        else maxDay = 28;
    }else if (month == 4 || month == 6 || month == 9 || month == 11) maxDay = 30;
    else maxDay = 31;
    
    if (day < 1 || day > maxDay) return false;
    return true;
}

void insert(patient arr[], int *last_index){
    while(true){ //name input
        bool name_status = true;
        printf("Name Input [Input 0 to cancel the input]: ");scanf("%[^\n]", arr[*last_index].name);getchar();
        if(arr[*last_index].name[0]=='0'){
            printf("Input function cancelled!\n");
            memset(&arr[(*last_index)], 0, sizeof(patient));
            return;
        }
        if(strlen(arr[*last_index].name)>3){
            for(int i=0; arr[*last_index].name[i]!='\0'; i++){
                if(!isalpha(arr[*last_index].name[i]) && arr[*last_index].name[i] != ' '){
                    name_status = false;break;
                }
            }
            if(name_status) break;
        }else continue;
    }

    while(true){ //gender input
        printf("Gender Input (Input 0 to cancel input): ");scanf("%c", &arr[*last_index].gender);getchar();
        if(arr[*last_index].gender=='0'){
            printf("Input function canceled!\n");
            memset(&arr[(*last_index)], 0, sizeof(patient));
            return;
        }
        if(tolower(arr[*last_index].gender) == 'm'|| tolower(arr[*last_index].gender) == 'f'){
            break;
        }else continue;
    }

    while(true){  //birth date Input
            printf("Input birth date (day-month-year) [Input 0-0-0 to cancel input]: ");
            scanf("%d-%d-%d", &arr[*last_index].date.day, &arr[*last_index].date.month, &arr[*last_index].date.year);
            getchar();
            if(arr[*last_index].date.day == 0){
                puts("Input Cancelled\n");
                memset(&arr[(*last_index)], 0, sizeof(patient));
                return;
            }
            if(isValidBirthDate(arr[*last_index].date.day, arr[*last_index].date.month, arr[*last_index].date.year)) break;
            else puts("Invalid Birth Date");
        }

    arr[*last_index].age = 2023 - arr[*last_index].date.year;

    int ch = 1;
    while(true){
        system("cls");
        switch (ch)
        {
        case 1:
            puts("======================");
            puts("|     BPJS Y/N ?     |");
            puts("======================");
            puts("| > Yes            < |");
            puts("|   No               |");
            puts("======================");
            break;
        case 2:
            puts("======================");
            puts("|     BPJS Y/N ?     |");
            puts("======================");
            puts("|   Yes              |");
            puts("| > No             < |");
            puts("======================");
            break;
        }
        int inp = getch();
        if(inp==72 || inp ==75 || inp == 119 || inp == 97){
            if(ch>1) ch--;
            else if(ch==1) ch=2;
            else continue;
        }else if(inp == 80 || inp == 77 || inp == 115 || inp == 100){
            if(ch<2) ch++;
            else if(ch==2) ch=1;
            else continue;
        }else if(inp==13){
            break;
        }
    }
    
    if(ch==1){
        bool bpjs_status = true;
        while(true){ //bpjs input
            printf("BPJS Input[Input -1 to cancel the input]: "); scanf("%[^\n]", arr[*last_index].bpjs); getchar();
            if(arr[*last_index].bpjs[0] == '-'){
                memset(&arr[(*last_index)], 0, sizeof(patient));
                puts("Input Cancelled");
                return;
            }
            if(strlen(arr[*last_index].bpjs)>=10 || strlen(arr[*last_index].bpjs)<15){
                for(int i=0; arr[*last_index].bpjs[i]!='\0'; i++){
                    if(!isdigit(arr[*last_index].bpjs[i])){
                        bpjs_status = false; break;
                    }
                }
                if(bpjs_status) break;
                else printf("Input Invalid\n");
            }else printf("Input Invalid\n");
        } 
    }else if(ch==2){
        arr[*last_index].bpjs[0] = '-';arr[*last_index].bpjs[1] = '\0';
    }
     
    while(true){ //issue input
        printf("Issue Input [Input 0 to Cancel the Input]: ");scanf("%[^\n]", arr[*last_index].issue); getchar();
        if(arr[*last_index].issue[0] == '0' && arr[*last_index].issue[1] == '\0'){
            puts("Input Cancelled");
            memset(&arr[(*last_index)], 0, sizeof(patient));
            return;
        }
        if(strlen(arr[*last_index].issue)>=10) break;
        else puts("Invalid Input\n");
    }

    while(true){ //urgency input
        printf("Urgency Input [Input 0 to Cancel the Input]: "); scanf("%d", &arr[*last_index].urgency); getchar();
        if(arr[*last_index].urgency == 0){
            puts("Input Cancelled");
            memset(&arr[(*last_index)], 0, sizeof(patient));
            return;
        }
        if(arr[*last_index].urgency>0) break;
        else puts("Input Invalid\n");
    }
    
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    arr[*last_index].hour = local_time->tm_hour;
    arr[*last_index].min = local_time->tm_min;

    int i=*last_index;
    while(i>0 && arr[(i-1)/2].urgency < arr[i].urgency){
        swap(&arr[i], &arr[(i-1)/2]);
        i=(i-1)/2;
    }
    (*last_index)++;
    printf("Success\n");
    return;
}

void resort(patient arr[], int index){
    int left = 2*(index) + 1;
    int right = 2*(index) + 2;

    if(arr[left].urgency > arr[index].urgency && arr[right].urgency > arr[index].urgency){
        if(arr[left].urgency>arr[right].urgency){
            swap(&arr[index], &arr[left]);
            resort(arr, left);
        }else{
            swap(&arr[index], &arr[right]);
            resort(arr, right);
        }
    }else if(arr[left].urgency > arr[index].urgency && arr[right].urgency < arr[index].urgency){
        swap(&arr[index], &arr[left]);
        resort(arr, left);
    }else if(arr[right].urgency > arr[index].urgency && arr[left].urgency < arr[index].urgency){
        swap(&arr[index], &arr[right]);
        resort(arr, right);
    }else if(arr[right].urgency==arr[index].urgency){
        swap(&arr[index], &arr[right]);
        resort(arr, right);
    }
    return;
}


void pop(patient arr[], int *last_inserted_index){
    if(*last_inserted_index == 0){
        printf("No data found\n");    
        system("pause");
        return;
    }
    int left = 1, right = 2;
    FILE *fp = fopen(PATH, "a");
    if(fp==NULL){
        fp = fopen(PATH, "w");
    }
    fprintf(fp, "Name: %s | Age: %d | Gender: %c | Birth Date: %d/%d/%d | Data Input Time: %d:%d | BPJS: %s | Issues: %s | Urgency Level: %d\n", arr[0].name, arr[0].age, arr[0].gender, arr[0].date.day, arr[0].date.month, arr[0].date.year, arr[0].hour,arr[0].min,arr[0].bpjs, arr[0].issue, arr[0].urgency);
    fclose(fp);
    arr[0] = arr[(*last_inserted_index) - 1];
    memset(&arr[(*last_inserted_index) - 1], 0, sizeof(patient));
    (*last_inserted_index)--; resort(arr, 0);
    return;
}

void search(patient arr[], int *last_inserted_index){
    printf("Search by name: "); char inp[40];
    scanf("%[^\n]", inp); getchar();
    bool found = false;
    for(int i=0; i<*last_inserted_index; i++){
        if(!strcmp(arr[i].name, inp)){
            puts("==============================================================================================================================================");
            puts("| Name                           | Age | Gender    | Birth Date  | Data Input Time | BPJS           |  Issues                       |Urg. Lvl|");
            puts("==============================================================================================================================================");
            printf("| %30s | %3d |", arr[i].name, arr[i].age);
            if(tolower(arr[i].gender)=='m') printf(" Male      ");
            else printf(" Female    ");
            printf("| %2d/%2d/%4d  |          %2d: %2d | %14s |%30s |     %2d |\n", arr[i].date.day, arr[i].date.month, arr[i].date.year, arr[i].hour, arr[i].min,arr[i].bpjs, arr[i].issue, arr[i].urgency);
            puts("----------------------------------------------------------------------------------------------------------------------------------------------");
            printf("Found\n");
            found = true;
            break;
        }
    }
    if(!found) printf("Data Not Found\n");system("pause");
}

void modify(patient arr[], int *last_inserted_index){
    printf("Search by name: "); char inp[40];
    scanf("%[^\n]", inp); getchar();
    bool found = false;
    for(int i=0; i<*last_inserted_index; i++){
        if(!strcmp(arr[i].name, inp)){
            puts("==============================================================================================================================================");
            puts("| Name                           | Age | Gender    | Birth Date  | Data Input Time | BPJS           |  Issues                       |Urg. Lvl|");
            puts("==============================================================================================================================================");
            int i =0;
            printf("| %30s | %3d |", arr[i].name, arr[i].age);
            if(tolower(arr[i].gender)=='m') printf(" Male      ");
            else printf(" Female    ");
            printf("| %2d/%2d/%4d  |          %2d: %2d | %14s |%30s |     %2d |\n", arr[i].date.day, arr[i].date.month, arr[i].date.year, arr[i].hour, arr[i].min,arr[i].bpjs, arr[i].issue, arr[i].urgency);
            puts("----------------------------------------------------------------------------------------------------------------------------------------------");
            puts("Found\n");
            //modify data
            while(true){ //issue input
                printf("Issue Input: ");scanf("%[^\n]", arr[i].issue); getchar();
                if(strlen(arr[i].issue)>10) break;
                else puts("Invalid Input\n");
            }
            int temp = arr[i].urgency;
            while(true){ //urgency input
                printf("Urgency Input: "); scanf("%d", &arr[i].urgency); getchar();
                if(arr[i].urgency>0) break;
                else puts("Input Invalid\n");
            }
            bool found = true;
            if(temp == arr[i].urgency) resort(arr, 0);
            puts("Edit Success");
            break;
        }
    }
    if(!found) printf("Data Not Found\n");system("pause");
}

void print(patient arr[], int *data_count){
    if(*data_count == 0){
        puts("Please input new data first");
        return;
    }
    puts("===============================================================================================================================================");
    puts("| Name                           | Age | Gender    | Birth Date  |  Data Input Time | BPJS           |  Issues                       |Urg. Lvl|");
    puts("===============================================================================================================================================");
    int i =0;
    while(i != *data_count){
        printf("| %30s | %3d |", arr[i].name, arr[i].age);
        if(tolower(arr[i].gender)=='m') printf(" Male      ");
        else printf(" Female    ");
        printf("| %2d/%2d/%4d  |           %2d: %2d | %14s |%30s |     %2d |\n", arr[i].date.day, arr[i].date.month, arr[i].date.year, arr[i].hour, arr[i].min,arr[i].bpjs, arr[i].issue, arr[i].urgency);
        puts("-----------------------------------------------------------------------------------------------------------------------------------------------");
        i++;
    }
    return;
}

int main(){
    printf("\033[47m"); // Set background color to white
    printf("\033[30m"); // Set text color to black
    system("cls");
    puts("=================================================================");
    puts("||                                                             ||");
    puts("||                Use Arrow Keys or WASD to Navigate           ||");
    puts("||                                                             ||");
    puts("=================================================================\n");
    puts("");
    system("pause");

    int ch = 1;
    patient patient_list[arr_size];
    int data_count = 0;
    while(true){
        while(true){
            system("cls");
        switch(ch){
            case 1:
            puts("===========================================");
            puts("|                                         |");
            puts("|      Hospital Patient Data System       |");
            puts("|                                         |");
            puts("===========================================");
            puts("| > Insert New Patient Data             < |");
            puts("|   Display Patient Data as a Table       |");
            puts("|   Patient Served                        |");
            puts("|   Search Certain Patient Data           |");
            puts("|   Modify Certain Patient Data           |");
            puts("|   Exit the Program                      |");
            puts("===========================================");
            break;
            
            case 2:
            puts("===========================================");
            puts("|                                         |");
            puts("|      Hospital Patient Data System       |");
            puts("|                                         |");
            puts("===========================================");
            puts("|   Insert New Patient Data               |");
            puts("| > Display Patient Data as a Table     < |");
            puts("|   Patient Served                        |");
            puts("|   Search Certain Patient Data           |");
            puts("|   Modify Certain Patient Data           |");
            puts("|   Exit the Program                      |");
            puts("===========================================");
            break;

            case 3:
            puts("===========================================");
            puts("|                                         |");
            puts("|      Hospital Patient Data System       |");
            puts("|                                         |");
            puts("===========================================");
            puts("|   Insert New Patient Data               |");
            puts("|   Display Patient Data as a Table       |");
            puts("| > Patient Served                      < |");
            puts("|   Search Certain Patient Data           |");
            puts("|   Modify Certain Patient Data           |");
            puts("|   Exit the Program                      |");
            puts("===========================================");
            break;

            case 4:
            puts("===========================================");
            puts("|                                         |");
            puts("|      Hospital Patient Data System       |");
            puts("|                                         |");
            puts("===========================================");
            puts("|   Insert New Patient Data               |");
            puts("|   Display Patient Data as a Table       |");
            puts("|   Patient Served                        |");
            puts("| > Search Certain Patient Data         < |");
            puts("|   Modify Certain Patient Data           |");
            puts("|   Exit the Program                      |");
            puts("===========================================");
            break;

            case 5:
            puts("===========================================");
            puts("|                                         |");
            puts("|      Hospital Patient Data System       |");
            puts("|                                         |");
            puts("===========================================");
            puts("|   Insert New Patient Data               |");
            puts("|   Display Patient Data as a Table       |");
            puts("|   Patient Served                        |");
            puts("|   Search Certain Patient Data           |");
            puts("| > Modify Certain Patient Data         < |");
            puts("|   Exit the Program                      |");
            puts("===========================================");
            break;

            case 6:
            puts("===========================================");
            puts("|                                         |");
            puts("|      Hospital Patient Data System       |");
            puts("|                                         |");
            puts("===========================================");
            puts("|   Insert New Patient Data               |");
            puts("|   Display Patient Data as a Table       |");
            puts("|   Patient Served                        |");
            puts("|   Search Certain Patient Data           |");
            puts("|   Modify Certain Patient Data           |");
            puts("| > Exit the Program                    < |");
            puts("===========================================");
            break;
        }
        int inp = getch();
        if(inp==72 || inp ==75 || inp == 119 || inp == 97){
            if(ch>1) ch--;
            else if(ch==1) ch=6;
            else continue;
        }else if(inp == 80 || inp == 77 || inp == 115 || inp == 100){
            if(ch<6) ch++;
            else if(ch==6) ch=1;
            else continue;
        }else if(inp==13){
            break;
        }
        }
        
    
        if(ch==1){
            insert(patient_list, &data_count);
            system("pause");
            continue;
        }else if(ch==2){
            print(patient_list, &data_count);
            system("pause");
            continue;
        }else if(ch==3){
            pop(patient_list, &data_count);
            continue;
        }else if(ch==4){   
            search(patient_list, &data_count);
            continue;
        }else if(ch==5){
            modify(patient_list, &data_count);
            continue;
        }else if(ch==6){
            exit(0);
        }
    }
}
