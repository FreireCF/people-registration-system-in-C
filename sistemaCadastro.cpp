#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char name[20], cpf[12], sex; //cpf is the id number in Brazil
    Date birth;
} Person;

void addPerson(Person *people, int *position) {
  printf("Enter the person's name: ");
    scanf("%s", people[*position].name);

  printf("Enter the person's CPF (only numbers): ");
    scanf("%s", people[*position].cpf);

  printf("Enter the person's sex (M/F): "); //M to Male and F to Female
    scanf(" %c", &people[*position].sex);

  printf("Enter the person's birth day (dd/mm/yyyy): "); //dd/mm/yyyy is the brazilian standard to date
    scanf("%d/%d/%d", &people[*position].birth.day,
        &people[*position].birth.month, &people[*position].birth.year);

  (*position)++;
}

void showPerson(Person *person, int current_year) {
    if (person == NULL) {
        printf("\nInvalid person data.");
    } else {
        int current_age = current_year - person->birth.year;//feature added
    
        printf("\nName: %s\n", person->name);
        printf("\nBirth day: %d/%d/%d\n", person->birth.day, person->birth.month, person->birth.year);
        printf("\nIdade Atual: %d", current_age);// feature added
        printf("\nSex: %c\n", person->sex);
        printf("\nCPF: %s\n", person->cpf);
    }
}

int searchPerson(char *searchedCpf, Person *people, int nascidos, int current_year) {
    for (int i = 0; i < nascidos; i++) {
        if (strcmp(searchedCpf, people[i].cpf) == 0) {
            showPerson(&people[i], current_year);
            return i; //returns the position in array of the person being searched for
        }
    }
    printf("\nNo one registered with this cpf");
    return -1;
}

void searchByDate(Person *people, int born, int day, int month, int year, int current_year) {
    int searchDate = year * 365 + month * 30 + day; //“transform” the date into days to make the search easier
    int found = 0;

    for (int i = 0; i < born; i++) {
        int birth = people[i].birth.year* 365 + people[i].birth.month * 30 + people[i].birth.day;
        if (searchDate == birth) {
            showPerson(&people[i], current_year);
            found++;
        }
    }
    if (!found) {
        printf("\nNo one registered that day");
    }
}

void searchBetweenDates(Person *people, int born, int day1, int month1, int year1, int day2, int month2, int year2,
    int current_year) {

    int oldDate = year1 * 365 + month1 * 30 + day1; 
    int recentDate = year2 * 365 + month2 * 30 + day2;

    int amount = 0, found = 0;

    for (int i = 0; i < born; i++) {
        int birth = people[i].birth.year * 365 + people[i].birth.month * 30 + people[i].birth.day;

        if (oldDate <= birth && birth <= recentDate) {
            showPerson(&people[i], current_year);
            amount++;
            found++;
        }
    }
    if (found!=0) {
        printf("\nNumber of people born between those dates: %d", amount);
    } else {
        printf("\nNo one born between those dates");
    }
}

void numberOfMales(Person *people, int born) {
    int males = 0;
    for (int i = 0; i < born; i++) {
        if (people[i].sex == 'M' || people[i].sex == 'm') {
            males++;
        }
    }
    if (males > 0) {
        printf("\n%d registered males", males);
    } else {
        printf("\nNo males registred");
    }
}

void numberOfFemales(Person  *people, int born) {
    int female = 0;
    for (int i = 0; i < born; i++) {
        if (people[i].sex == 'F' || people[i].sex == 'f') {
            female++;
        }
    }
    if (female > 0) {
        printf("\n%d registred females", female);
    } else {
        printf("\nNo females registred");
    }
}

void edit(Person *people, int amount) {
    char editCpf[12];
    printf("\nEnter the CPF to edit the register: ");
    scanf("%s", editCpf);

    for (int i = 0; i < amount; i++) {
        if (strcmp(people[i].cpf, editCpf) == 0) {
         printf("\nEnter the new name: ");
            scanf("%s", people[i].name);

        printf("\nEnter the new CPF: ");
            scanf("%11s", people[i].cpf);

        printf("\nEnter the new sex (M/F): ");
            scanf(" %c", &people[i].sex);

        printf("\nEnter the new birth day (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &people[i].birth.day,
                    &people[i].birth.month, &people[i].birth.year);
        }
    }
        printf("\nRegister not found");
}

void oldOrYounger(Person *people, int amount) {
    int older = 0;
    int younger = 0;

    for (int i = 1; i < amount; i++) {
        if ((people[i].birth.year * 365 + people[i].birth.month * 30 + people[i].birth.day) <
            (people[older].birth.year * 365 + people[older].birth.month * 30 +
            people[older].birth.day)) {
            older = i;
        }
        if ((people[i].birth.year * 365 + people[i].birth.month * 30 + people[i].birth.day) >
            (people[younger].birth.year * 365 + people[younger].birth.month * 30
             + people[younger].birth.day)) {
            younger = i;
        }
    }
        printf("\nElder's name: %s\n", people[older].name);
        printf("\nYoungest's name: %s\n", people[younger].name);
}

void birthdayInTheMonth(Person *people, int amount) {
    int month[12] = {0};

    for (int i = 0; i < amount; i++) {
        if (people[i].birth.month >= 1 && people[i].birth.month <= 12) {
            month[people[i].birth.month - 1]++;
        } else {
            printf("\nNon-existent month for %s", people[i].name);
        }
    }

    char *monthNames[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    for (int i = 0; i < 12; i++) {
        printf("%s: %d\n", monthNames[i], month[i]);
    }
}

int menu() {
    int option;
    printf("\n\n======= MENU =======\n");
    printf("\n1 - Resgister a person");
    printf("\n2 - Search person by CPF");
    printf("\n3 - Search person by birth day");
    printf("\n4 - Search person between dates");
    printf("\n5 - See number of registered men");
    printf("\n6 - See number of registered women");
    printf("\n7 - Edit register");
    printf("\n8 - See older and younger person");
    printf("\n9 - See the number of birthdays in a month");
    printf("\n0 - Exit\n");
    printf("\n\n======= ++++ =======\n");
    printf("\nEnter the option: ");
    scanf("%d", &option);
    return option;
}

int main() {
    int option = -1, amount = 0;
    //char editCpf[12];

    // Obtem o tempo atual
    time_t current_time;
    time(&current_time);

    // Estrutura de tempo local
    struct tm *local_time = localtime(&current_time);
    int current_year = local_time->tm_year + 1900;// extrai o numero de anos desde 1900 e soma mais 1900

   Person people[10000];

    while (option != 0) {
        option = menu();

        switch (option) {
            case 1:
                addPerson(people, &amount);
                break;

            case 2: 
                char searchedCpf[12];
                printf("\nEnter the CPF for search (only numbers): ");
                scanf("%s", searchedCpf);
                searchPerson(searchedCpf, people, amount, current_year);
                break;
            
            case 3: 
                int day, month, year;
                printf("\nEnter the date for search (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &day, &month, &year);
                searchByDate(people, amount, day, month, year, current_year);
                break;

            case 4: 
                int oldDay, oldMonth, oldYear, youngerDay, youngerMonth, youngerYear;
                printf("\nEnter the older date for seach (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &oldDay, &oldMonth, &oldYear);

                printf("\nEnter the younger date for seach (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &youngerDay, &youngerMonth, &youngerYear);

                searchBetweenDates(people, amount, oldDay, oldMonth, oldYear, youngerDay, 
                youngerMonth, youngerYear, current_year);
                break;

            case 5:
                numberOfMales(people, amount);
                break;

            case 6:
                numberOfFemales(people, amount);
                break;
                
            case 7:
                edit(people, amount);
                break;

            case 8:
                oldOrYounger(people, amount);
                break;

            case 9:
                birthdayInTheMonth(people, amount);
                break;

            case 0:
                printf("\nProgram closed");
                break;

            default:
                printf("\nInvalid option");
                break;
        }
    }
    printf("\n\n"); //just to organize the terminal 
}