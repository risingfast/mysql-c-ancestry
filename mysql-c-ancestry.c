// includes and defines

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs50.h"
#include "rf50.h"
#include <ctype.h>
#include <stdbool.h>

#define SQL_LEN 5000
#define HDG_LEN 1000

// function declarations

void fShowMainMenu(void);                                                                 // show the main console menu
void fGetPwdFromConsole(void);                                                       // get a password from the console
void fListPeople(char *, int *, char *, char *, char *);                                    // display a list of people
void fListEvents(char *, int *, char *, char *, char *);                                    // display a list of events
void fPrintListHeading(char *, char*);                                          // print the heading for a console list
void fSetOptions(char *, int *, char *, char *, char *);                                    // main menu to set options
void fShowPersonProfile(char *, int *, char *, char *, char *);                              // show a person's profile

// global declarations

char *sgServer = "192.168.0.13";                                                               //mysqlServer IP address
char *sgUsername = "gjarman";                                                              // mysqlSerer logon username
char sgPassword[20] = {'\0'};                                                     // password to connect to mysqlserver
char *sgDatabase = "risingfast";                                                // default database name on mysqlserver

MYSQL *conn;

int main(int argc, char **argv)
{

// declarations

    char *sPrgNme = strcat(argv[0] + 2, " -- Jarman family and relatives");                             // program name
    bool bHelp = false;                                                                  // help flag to show help text
    bool bExitMainMenu = false;                                                             // flag to exit the program
    char cMainChoice = '0';                                                                         // main menu choice
    int  iDisplayPageLength = 40;                                                      // display page lines for paging
    char cDisplayPageWidth = 'W';                                                  // display page width wide or narrow
    char cDisplayPageFormat = 'T';                                                // display page format (T)ab or (C)SV
    char cDisplayOrder = 'A';                                                 // display order asc or desc on Person ID

// Search for input parameters

    for(int i = 1; i < argc; i++)
    {
        if(strcmp("--help", argv[i]) == 0 || strcmp("--h", argv[i]) == 0)
        {
            bHelp = true;
        }
    }

    if(bHelp == true)
    {
        printf("\n");
        printf("Command line switch --h or --help not specified so help suppressed");
        printf("\n");
    }

// get a password from the console and test the db connection

    fRetitleConsole(sPrgNme);
    fGetPwdFromConsole();
    if(strcmp("BadSoExit", sgPassword) == 0)
    {   
        printf("\n");
        return EXIT_FAILURE;
    }
    fRetitleConsole(sPrgNme);

// Initialize a connection and connect to the database$

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, sgServer, sgUsername, sgPassword, sgDatabase, 0, NULL, 0))
    {
        printf("\n");
        printf("Failed to connect to MySQL Server %s in module %s()", sgServer, __func__);
        printf("\n\n");
        printf("Error: %s\n", mysql_error(conn));
        printf("\n");
        fPressEnterToContinue();
        printf("\n");
        return  EXIT_FAILURE;
    }

// print the main menu and execute menu choices

    while(bExitMainMenu == false)
    {
        while(cMainChoice == '0')
        {
            fRetitleConsole(sPrgNme);
            fShowMainMenu();
            cMainChoice = GetChar();
            if(strchr("1234567lLeEpPrRnNsSxX", cMainChoice) == NULL)
            {
                cMainChoice = '0';
                fRetitleConsole(sPrgNme);
                printf("\n");
            }
        }

        if(strchr("1lL", cMainChoice) != NULL)
        {
            printf("\n");
            fListPeople(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDisplayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
        }
        else if(strchr("2eE", cMainChoice) != NULL)
        {
            printf("\n");
            fListEvents(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDisplayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
        }
        else if(strchr("3pP", cMainChoice) != NULL)
        {
            printf("\n");
            fShowPersonProfile(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDisplayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
        }
        else if(strchr("4rR", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 4rR");
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
            fPressEnterToContinue();
        }
        else if(strchr("nN5", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 5nN");
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
            fPressEnterToContinue();
        }
        else if(strchr("sS6", cMainChoice) != NULL)
        {
            printf("\n");
            fSetOptions(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDisplayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
        }
        else if(strchr("xX7", cMainChoice) != NULL)
        {
            bExitMainMenu = true;
        }
    }

    mysql_close(conn);
    system("clear");
    return EXIT_SUCCESS;
}

void fShowMainMenu(void)                                                                                   // main menu
{
    printf("\n");
    printf("Main Menu");
    printf("\n\n");
    printf("1. (L)ist People");
    printf("\n");
    printf("2. List (E)vents");
    printf("\n");
    printf("3. (P)rofile Person");
    printf("\n");
    printf("4. Enter Pe(r)son");
    printf("\n");
    printf("5. E(n)ter Event");
    printf("\n");
    printf("6. Option(s)");
    printf("\n");
    printf("7. E(x)it");
    printf("\n\n");
    printf("Choice: ");

    return;
}

void fGetPwdFromConsole(void)
{
    char *sEnteredPwd = NULL;;
    char *sTempPwd = "Mpa4egu$";                                                         // Temporary disabled password

    printf("\n");
    do
    {
        printf("Password to connect to mysqlDB (or E(x)it): ");
//        sEnteredPwd = GetString();                                                     // Temporary disabled password
        sEnteredPwd = sTempPwd;                                                          // Temporary disabled password
        if((strlen(sEnteredPwd) == 1) && (strchr("xX", sEnteredPwd[0]) != NULL))
        {
            strcpy(sgPassword, "BadSoExit");
            break;
        }
        else
        {
            conn = mysql_init(NULL);

            if (!mysql_real_connect(conn, sgServer, sgUsername, sEnteredPwd, sgDatabase, 0, NULL, 0))
            {
                printf("\n");
                printf("Failed to connect to MySQL server with entered password");
                printf("\n\n");
                fPressEnterToContinue();
                printf("\n");
            }
            else
            {
                strcpy(sgPassword, sEnteredPwd);
            }
        }
    } while(strcmp(sgPassword, sEnteredPwd) != 0);

    return;
}

void fListPeople(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDisplayPageFormat, char *pcDisplayOrder)
{
    int iColCount = 0;
    int *iLengths = NULL;
    int iRowCount = 0;
    char cQueryFilterchoice = '0';
    char caOrder[6] = {'D', 'E', 'S', 'C', '\0'};
    char caSQL[SQL_LEN] = {'\0'};
    bool bEndOfPrintBlock = false;
    bool bExitListMenu = false;
    char caListHeading[HDG_LEN] = {'\0'};

    MYSQL_RES *res;
    MYSQL_ROW row;

    if(*pcDisplayOrder == 'A')
    {
            strcpy(caOrder, "ASC");
        }
        else if(*pcDisplayOrder == 'D')
        {
            strcpy(caOrder, "DESC");
        }
    
    while(bExitListMenu == false)
    {
        fRetitleConsole(sPrgNme);
        printf("\n");
        printf("Main Menu > List People > People names ...");
        printf("\n\n");
        printf("(A)ll, (M)ales, (F)emales, (L)iving, (D)eceased, (C)ohort, (B)irthdays or E(x)it");
        printf("\n\n");
        while(strchr("aAmMfFlLdDcCbBxX", cQueryFilterchoice) == NULL)
        {
            printf("Choice: ");
            cQueryFilterchoice = toupper(GetChar());
        }
        if(toupper(cQueryFilterchoice) == 'X')
        {
            bExitListMenu = true;
            return;
        }
        else if(cQueryFilterchoice == 'A')
        {
            sprintf(caSQL, "SELECT AP.`Person ID` "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Person ID` != 10"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age");
        }
        else if(cQueryFilterchoice == 'M')
        {
            sprintf(caSQL, "SELECT AP.`Person ID` "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Person ID` != 10"
                                "  AND AP.`Gender` = 'Male'"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age");
        }
        else if(cQueryFilterchoice == 'F')
        {
            sprintf(caSQL, "SELECT AP.`Person ID` "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Person ID` != 10"
                                "  AND AP.`Gender` = 'Female'"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age");
        }
        else if(cQueryFilterchoice == 'L')
        {
            sprintf(caSQL, "SELECT AP.`Person ID` "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Person ID` != 10"
                                "  AND AP.`Deceased` = 0"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age");
        }
        else if(cQueryFilterchoice == 'D')
        {
            sprintf(caSQL, "SELECT AP.`Person ID` "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Person ID` != 10"
                                "  AND AP.`Deceased` = 1"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/AgeAtDeath");
        }
        else if(cQueryFilterchoice == 'C')
        {
            sprintf(caSQL, "SELECT AP.`Person ID` as 'ID' "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                                ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) AS 'Age' "
                                ", AC.Cohort "
                                "  FROM risingfast.`Ancestry People` AP "
                                "  LEFT JOIN risingfast.`Ancestry Cohorts` AC on (AP.`Born On` >= AC.`Start`) and (AP.`Born On` <= AC.`Finish`) ")
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age/Cohort");
        }
        else if(cQueryFilterchoice == 'B')
        {
            sprintf(caSQL, "SELECT AP.`Person ID` as 'ID' "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                                ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 0), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 0)) AS 'Current Age' "
                                ", AP.`Born On` "
                                ", IF(MONTH(AP.`Born On`) - MONTH(CURRENT_DATE()) < 0, MONTH(AP.`Born On`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AP.`Born On`) - MONTH(CURRENT_DATE())) 'Mths Away' "
                                "  FROM risingfast.`Ancestry People` AP "
                                "  WHERE IF(MONTH(AP.`Born On`) - MONTH(CURRENT_DATE()) < 0, MONTH(AP.`Born On`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AP.`Born On`) - MONTH(CURRENT_DATE())) < 12 "
                                "  AND AP.`Deceased` = 0 "
                                "  ORDER BY IF(MONTH(AP.`Born On`) - MONTH(CURRENT_DATE()) < 0, MONTH(AP.`Born On`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AP.`Born On`) - MONTH(CURRENT_DATE())) asc ")
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age/Birthday/MonthsAway");
        }
    
    // execute the query and check for no result
    
        if(mysql_query(conn, caSQL) != 0)
        {
            printf("\n");
            printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
            printf("\n\n");
            fPressEnterToContinue();
            return;
        }

// store the result of the query

        res = mysql_store_result(conn);
        if(res == NULL)
        {
            printf("%s() -- no results returned", __func__);
            printf("\n");
    
            mysql_free_result(res);
            return;
        }
    
// fetch the number of fields in the result
    
        if(*pcDisplayPageWidth == 'W')
        {
            iColCount = mysql_num_fields(res);
        }
        else if(*pcDisplayPageWidth == 'N')
        {
            iColCount = mysql_num_fields(res) - 3;
        }
    
// fetch the max width of each column
    
        iLengths = (int *)calloc(iColCount, sizeof(int));
    
        while(row = mysql_fetch_row(res))
        {
            for (int k = 0; k < iColCount; k++)
            {
                if(row[k] != NULL)
                {
                    if(strlen(row[k]) > iLengths[k])
                    {
                         iLengths[k] = strlen(row[k]);
                    }
                }
            }
        }
    
        mysql_data_seek(res, 0);
    
// print a heading 
    
        fPrintListHeading(pcDisplayPageWidth, caListHeading);
   
// print each row of results

        iRowCount = 0;
        while(row = mysql_fetch_row(res))
        {
            if(*pcDisplayPageFormat == 'T')
            {
//                bEndOfPrintBlock = false;
                for(int i = 0; i < iColCount; i++)
                {
                    if((i == 0) || (i == 4) || (i == 6))
                    {
                        printf("  %*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                    else
                    {
                        printf("  %-*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                }
                iRowCount++;
                printf("\n");
                if(iRowCount >= *piDisplayPageLength)
                {
                    printf("\n");
                    fPressEnterToContinue();
                    fRetitleConsole(sPrgNme);
                    printf("\n");
                    printf("Main Menu > List People > People names ...");
                    printf("\n\n");
                    printf("(A)ll, (M)ales, (F)emales, (L)iving, (D)eceased, (C)ohort, (B)irthdays or E(x)it");
                    printf("\n\n");
                    printf("Choice: ");
                    printf("\n");
                    fPrintListHeading(pcDisplayPageWidth, caListHeading);
                    iRowCount = 0;
                }
            }
            else
            {
                for(int i = 0; i < iColCount; i++)
                {
                    if(i == 0)
                    {
                        printf("     ");
                    }
                    else if(i == 3)
                    {
                        continue;
                    }
                    else if(row[i])
                    {
                        printf("%s, ", row[i]);
                    }
                    else
                    {
                        printf("%s", "");
                    }
                }
                printf("\n");
            }
        }

        printf("\n");
        if(bEndOfPrintBlock == false)
        {
            fPressEnterToContinue();
        }
    }

    fRetitleConsole(sPrgNme);
    free(iLengths);
    mysql_free_result(res);
    return;
}

void fPrintListHeading(char *pcDisplayPageWidth, char caListHeading[])
{
    printf("\n");
    if(*pcDisplayPageWidth == 'W')
    {
        printf("%s", caListHeading);
    }
    else if(*pcDisplayPageWidth == 'N')
    {
        printf("   ID  Person");
    }
    printf("\n\n");
}
void fSetOptions(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDispayPageFormat, char *pcDisplayOrder)
{

    int  iOptionChoice = '0';
    bool bExitOptions = false;
    bool bValidOptionChoice = false;

    fRetitleConsole(sPrgNme);

    while(bExitOptions == false)
    {
        while(iOptionChoice == '0')
        {
            printf("\n");
            printf("Main Menu > Set Options");
            printf("\n");
            printf("\n");
            printf("1. Display (L)ength: %9d", *piDisplayPageLength);
            printf("\n");
            printf("2. Display (W)idth: %10s", (*pcDisplayPageWidth == 'N') ? "Narrow" : "Wide");
            printf("\n");
            printf("3. List (F)ormat: %12s", (*pcDispayPageFormat == 'T') ? "Tab" : "CSV");
            printf("\n");
            printf("4. List (O)rder: %13s", (*pcDisplayOrder == 'A') ? "Ascending" : "Descending");
            printf("\n");
            printf("5. (P)rint Options");
            printf("\n");
            printf("6. (R)eset Options");
            printf("\n");
            printf("7. E(x)it");
            printf("\n\n");
            printf("Choice: ");
            iOptionChoice = GetChar();
            if(strchr("1234567LloOpPrRxX", iOptionChoice) == NULL)
            {
                iOptionChoice = '0';
            }
        }
        if(strchr("1lL", iOptionChoice) != NULL)
        {
            printf("\n");
            printf("Display Length: ");
            *piDisplayPageLength = GetInt();
            printf("\n");
            iOptionChoice = '0';
        }
        else if(strchr("2wW", iOptionChoice) != NULL)
        {
            printf("\n");
            while(bValidOptionChoice == false)
            {
                printf("Display Width ((W)ide or (N)arrow) or E(x)it: ");
                *pcDisplayPageWidth = toupper(GetChar());
                if(*pcDisplayPageWidth == 'W')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDisplayPageWidth == 'N')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDisplayPageWidth == 'X')
                {
                    bValidOptionChoice = true;
                }
                else
                {
                    bValidOptionChoice = false;
                }
            }
            printf("\n");
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("3fF", iOptionChoice) != NULL)
        {
            printf("\n");
            while(bValidOptionChoice == false)
            {
                printf("Display Format ((T)ab or (C)SV) or E(x)it: ");
                *pcDispayPageFormat = toupper(GetChar());
                if(*pcDispayPageFormat == 'T')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDispayPageFormat == 'C')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDispayPageFormat == 'X')
                {
                    bValidOptionChoice = true;
                }
                else
                {
                    bValidOptionChoice = false;
                }
            }
            printf("\n");
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("4oO", iOptionChoice) != NULL)
        {
            printf("\n");
            while(bValidOptionChoice == false)
            {
                printf("Display Order ((A)sc or (D)esc or E(x)it): ");
                *pcDisplayOrder = toupper(GetChar());
                if(*pcDisplayOrder == 'A')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDisplayOrder == 'D')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDisplayOrder == 'X')
                {
                    bValidOptionChoice = true;
                }
                else
                {
                    bValidOptionChoice = false;
                }
            }
            printf("\n");
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("5pP", iOptionChoice) != NULL)
        {
            *pcDispayPageFormat = 'C';
            *pcDisplayOrder = 'A';
            *piDisplayPageLength = 1000;
            *pcDisplayPageWidth = 'W';
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("6rR", iOptionChoice) != NULL)
        {
            *pcDispayPageFormat = 'T';
            *pcDisplayOrder = 'A';
            *piDisplayPageLength = 80;
            *pcDisplayPageWidth = 'N';
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("7xX", iOptionChoice) != NULL)
        {
            bExitOptions = true;
        }
        fRetitleConsole(sPrgNme);
    }

    return;
}

void fListEvents(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDisplayPageFormat, char *pcDisplayOrder)
{
    int iColCount = 0;
    int *iLengths = NULL;
    int iRowCount = 0;
    char cQueryFilterchoice = '0';
    char caOrder[6] = {'D', 'E', 'S', 'C', '\0'};
    char caSQL[SQL_LEN] = {'\0'};
    bool bEndOfPrintBlock = false;
    bool bExitListMenu = false;
    char caListHeading[HDG_LEN] = {'\0'};

    MYSQL_RES *res;
    MYSQL_ROW row;

    if(*pcDisplayOrder == 'A')
    {
            strcpy(caOrder, "ASC");
        }
        else if(*pcDisplayOrder == 'D')
        {
            strcpy(caOrder, "DESC");
        }
    
    while(bExitListMenu == false)
    {
        fRetitleConsole(sPrgNme);
        printf("\n");
        printf("Main Menu > List Events ...");
        printf("\n\n");
        printf("(A)ll, (U)pcoming or E(x)it");
        printf("\n\n");
        while(strchr("aAuUxX", cQueryFilterchoice) == NULL)
        {
            printf("Choice: ");
            cQueryFilterchoice = toupper(GetChar());
        }
        if(toupper(cQueryFilterchoice) == 'X')
        {
            bExitListMenu = true;
            return;
        }
        else if(cQueryFilterchoice == 'A')
        {
            sprintf(caSQL, "SELECT AE.`Event ID` "
                                ", AE.`Event Type` "
                                ", CONCAT(AP1.`First Name`, ' ', AP1.`Last Name`) AS `First Person` "
                                ", CONCAT(AP2.`First Name`, ' ', AP2.`Last Name`) AS `First Person` "
                                ", AE.`Event Date` "
                                ", AE.`Event Place` "
                                ", AC.`Country Abbreviation` "
                                "  FROM risingfast.`Ancestry Events` AE "
                                "  LEFT JOIN risingfast.`Ancestry People` AP1 on AE.`Event First Person ID` = AP1.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry People` AP2 on AE.`Event Second Person ID` = AP2.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry Countries` AC on AE.`Event Country ID` = AC.`Country ID`")
                                ;

            cQueryFilterchoice = '0';
            strcpy(caListHeading, "EventID/Event/FirstPerson/SecondPerson/Date/Place/Country");
        }
        else if(cQueryFilterchoice == 'U')
        {
            sprintf(caSQL, "SELECT AE.`Event ID` "
                                ", AE.`Event Type` "
                                ", CONCAT(AP1.`First Name`, ' ', AP1.`Last Name`) AS `First Person` "
                                ", CONCAT(AP2.`First Name`, ' ', AP2.`Last Name`) AS `First Person` "
                                ", AE.`Event Date` "
                                ", AE.`Event Place` "
                                ", AC.`Country Abbreviation` "
                                ", IF(MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AE.`Event Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE())) AS 'Mths Away' "
                                "  FROM risingfast.`Ancestry Events` AE "
                                "  LEFT JOIN risingfast.`Ancestry People` AP1 on AE.`Event First Person ID` = AP1.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry People` AP2 on AE.`Event Second Person ID` = AP2.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry Countries` AC on AE.`Event Country ID` = AC.`Country ID` "
                                "  WHERE IF(MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AE.`Event Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE())) < 12 "
                                "  ORDER BY IF(MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AE.`Event Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE())) asc ")
                                ;

            cQueryFilterchoice = '0';
            strcpy(caListHeading, "EventID/Event/FirstPerson/SecondPerson/Date/Place/Country/MthsAway");
        }
    
    // execute the query and check for no result
    
        if(mysql_query(conn, caSQL) != 0)
        {
            printf("\n");
            printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
            printf("\n\n");
            fPressEnterToContinue();
            return;
        }

// store the result of the query

        res = mysql_store_result(conn);
        if(res == NULL)
        {
            printf("%s() -- no results returned", __func__);
            printf("\n");
    
            mysql_free_result(res);
            return;
        }
    
// fetch the number of fields in the result
    
        if(*pcDisplayPageWidth == 'W')
        {
            iColCount = mysql_num_fields(res);
        }
        else if(*pcDisplayPageWidth == 'N')
        {
            iColCount = mysql_num_fields(res) - 3;
        }
    
// fetch the max width of each column
    
        iLengths = (int *)calloc(iColCount, sizeof(int));
    
        while(row = mysql_fetch_row(res))
        {
            for (int k = 0; k < iColCount; k++)
            {
                if(row[k] != NULL)
                {
                    if(strlen(row[k]) > iLengths[k])
                    {
                         iLengths[k] = strlen(row[k]);
                    }
                }
            }
        }
    
        mysql_data_seek(res, 0);
    
// print a heading 
    
        fPrintListHeading(pcDisplayPageWidth, caListHeading);
   
// print each row of results

        iRowCount = 0;
        while(row = mysql_fetch_row(res))
        {
            if(*pcDisplayPageFormat == 'T')
            {
                for(int i = 0; i < iColCount; i++)
                {
                    if((i == 0) || (i == 4) || (i == 7))
                    {
                        printf("  %*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                    else
                    {
                        printf("  %-*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                }
                iRowCount++;
                printf("\n");
                if(iRowCount >= *piDisplayPageLength)
                {
                    printf("\n");
                    fPressEnterToContinue();
                    fRetitleConsole(sPrgNme);
                    printf("\n");
                    printf("Main Menu > List People > People names ...");
                    printf("\n\n");
                    printf("(A)ll, (U)pcoming or E(x)it");
                    printf("\n\n");
                    printf("Choice: ");
                    printf("\n");
                    fPrintListHeading(pcDisplayPageWidth, caListHeading);
                    iRowCount = 0;
                }
            }
            else
            {
                for(int i = 0; i < iColCount; i++)
                {
                    if(i == 0)
                    {
                        printf("     ");
                    }
                    else if(i == 3)
                    {
                        continue;
                    }
                    else if(row[i])
                    {
                        printf("%s, ", row[i]);
                    }
                    else
                    {
                        printf("%s", "");
                    }
                }
                printf("\n");
            }
        }
        printf("\n");
        fPressEnterToContinue();
    }

    fRetitleConsole(sPrgNme);
    free(iLengths);
    mysql_free_result(res);
    return;
}

void fShowPersonProfile(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDisplayPageFormat, char *pcDisplayOrder)
{
    char cProfileMenuChoice = 'O';
    bool bExitProfileMenu  = false;
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;
    int *iLengths = NULL;
    int  iPersonID = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    while(bExitProfileMenu == false)
    {
        fRetitleConsole(sPrgNme);
        printf("\n");
        printf("Main Menu > Person Profile ...");
        printf("\n\n");
        printf("(S)how, Sea(r)ch or E(x)it");
        printf("\n\n");
        while(strchr("sSrRxX", cProfileMenuChoice) == NULL)
        {
            printf("Choice: ");
            cProfileMenuChoice = toupper(GetChar());
        }
        if(toupper(cProfileMenuChoice) == 'X')
        {
            bExitProfileMenu = true;
            return;
        }
        else if(cProfileMenuChoice == 'S')
        {
            cProfileMenuChoice = '0';

            printf("\n");
            do {
                printf("Person iD (1 - 85): ");
                iPersonID = GetInt();
                printf("\n");
            } while(iPersonID < 1 || iPersonID > 85);


            sprintf(caSQL, "select AP.`Person ID` as 'ID' "
                                ", AP.`First Name` as 'First' "
                                ", AP.`Middle Names` as 'Middle' "
                                ", AP.`Last Name` as 'Last' "
                                ", AP.`Born On` as 'Born' "
                                ", AP.`Birth Place` as 'Born In' "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') as 'Status' "
                                ", AP.`Deceased On` as 'Deceased On' "
                                ", AP.`Deceased Place` as 'Deceased Place' "
                                ", AP.`Cause of Death` as 'Cause of Death' "
                                ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                                ", AP.`Profile` "
                                ", AP.`Education` "
                                " from risingfast.`Ancestry People` AP "
                                " where AP.`Person ID` = %d", iPersonID);

// execute the query and check for no result
    
            if(mysql_query(conn, caSQL) != 0)
            {
                printf("\n");
                printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
                printf("\n\n");
                fPressEnterToContinue();
                return;
            }

// store the result of the query

            res = mysql_store_result(conn);
            if(res == NULL)
            {
                printf("%s() -- no results returned", __func__);
                printf("\n");

                mysql_free_result(res);
                return;
            }

// print the profile

            row = mysql_fetch_row(res);

            printf("Person ID:      %s", row[0]);
            printf("\n");
            printf("First Name:     %s", row[1]);
            printf("\n");
            printf("Middle Name:    %s", row[2]);
            printf("\n");
            printf("Last Name:      %s", row[3]);
            printf("\n");
            printf("Born on:        %s", row[4]);
            printf("\n");
            printf("Birth at:       %s", row[5]);
            printf("\n");
            printf("Status:         %s", row[6]);
            printf("\n");
            printf("Deceased on:    %s", row[7]);
            printf("\n");
            printf("Deceased at:    %s", row[8]);
            printf("\n");
            printf("Cause of Death: %s", row[9]);
            printf("\n");
            printf("Age:            %s", row[10]);
            printf("\n");
            printf("Profile:        %s", row[11]);
            printf("\n");
            printf("Education:      %s", row[12]);
            printf("\n\n");
            fPressEnterToContinue();
        }

        else if(cProfileMenuChoice == 'R')
        {
            cProfileMenuChoice = '0';
            sprintf(caSQL, "SELECT AE.`Event ID` "
                                ", AE.`Event Type` "
                                ", CONCAT(AP1.`First Name`, ' ', AP1.`Last Name`) AS `First Person` "
                                ", CONCAT(AP2.`First Name`, ' ', AP2.`Last Name`) AS `First Person` "
                                ", AE.`Event Date` "
                                ", AE.`Event Place` "
                                ", AC.`Country Abbreviation` "
                                ", IF(MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AE.`Event Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE())) AS 'Mths Away' "
                                "  FROM risingfast.`Ancestry Events` AE "
                                "  LEFT JOIN risingfast.`Ancestry People` AP1 on AE.`Event First Person ID` = AP1.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry People` AP2 on AE.`Event Second Person ID` = AP2.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry Countries` AC on AE.`Event Country ID` = AC.`Country ID` "
                                "  WHERE IF(MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AE.`Event Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE())) < 12 "
                                "  ORDER BY IF(MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AE.`Event Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AE.`Event Date`) - MONTH(CURRENT_DATE())) asc ")
                                ;

// execute the query and check for no result

            if(mysql_query(conn, caSQL) != 0)
            {
                printf("\n");
                printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
                printf("\n\n");
                fPressEnterToContinue();
                return;
            }

// store the result of the query

            res = mysql_store_result(conn);
            if(res == NULL)
            {
                printf("%s() -- no results returned", __func__);
                printf("\n");

                mysql_free_result(res);
                return;
            }

// print each row of results

            iRowCount = 0;
            while(row = mysql_fetch_row(res))
            {
                for(int i = 0; i < iColCount; i++)
                {
                    if((i == 0) || (i == 4) || (i == 7))
                    {
                        printf("  %*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                    else
                    {
                        printf("  %-*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                }
                iRowCount++;
                printf("\n");
                if(iRowCount >= *piDisplayPageLength)
                {
                    printf("\n");
                    fPressEnterToContinue();
                    fRetitleConsole(sPrgNme);
                    printf("\n");
                    printf("Main Menu > Person Profile ...");
                    printf("\n\n");
                    printf("(S)how, Sea(r)ch or E(x)it");
                    printf("\n\n");
                    printf("Choice: ");
                    printf("\n");
                    iRowCount = 0;
                }
            }

            printf("\n");
            fPressEnterToContinue();
        }
    }

    fRetitleConsole(sPrgNme);
    free(iLengths);
    mysql_free_result(res);
    return;
}

