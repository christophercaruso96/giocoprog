/**************************************************************************************************************************
 * Author: Christopher Caruso
 * Date: 2024/03/07
 *
 * Object: Lo scopo di oggi è realizzare un piccolo gioco di domanda/risposta in C,
 * il numero e le domande sono a vostra scelta. Il gioco dovrà funzionare in modo tale da:
 *      - [x] Presentare una rapida introduzione all’utente con lo scopo del programma.
 *      - [x] Mostrare all’utente un menu di scelta iniziale tra:
 *          A) Iniziare una nuova partita;
 *          B) Uscire dal gioco.
 *      - [x] Ricevere in input la scelta dell’utente.
 *      - [x] Creare o meno una nuova partita in base all’input utente.
 *      - [x] Ricevere in input nome dell’utente in caso di nuova partita.
 *      - [x] Presentare un set di domande all’utente a risposta multipla (almeno 3 risposte a domanda).
 *      - [x] Valutare la risposta utente per ogni domanda ed aggiornare una variabile «punteggio in caso di risposta esatta».
 *      - [x] Scrivere a schermo a fine partita il punteggio totalizzato dal giocatore corrente.
 *      - [x] Presentare nuovamente il testo per la scelta tra:
 *          A) Iniziare una nuova partita;
 *          B) Uscire dal gioco.
 *
 *
**************************************************************************************************************************/

//Direttive al preprocessore
#include <stdio.h>
#include <stdlib.h>
#define NUMOPTIONS 2
#define NUMQUESTION 3

//Prototipi delle funzioni
void makeChoice (const char *[], char *, char, char);
void makeMatch(const char *[], char, char, char);

//Corpo principale del programma
int main(){

    //dichirazioni
    const char *menuchoice[NUMOPTIONS] = {"A) Iniziare una nuova partita;", "B) Uscire dal gioco."};
    char *choice;
    const char *questions[NUMQUESTION] = {"1) Dove si trova la nazione ITALIA?\nA) EU\nB) USA\nC) UK\n", "2) Quante dita ha una mano?\nA) 10\nB) 5\nC) 15\n", "3) Quanti sono i nani di biancaneve?\nA) 3\nB) 4\nC) 7\n"};

    //intro utente
    printf("Lo scopo del gioco consiste nel rispondere ad una serie di 3 domande\ne totalizzare il punteggio massimo in base alle risposte (corretta: 3 pts, errata: -1 pts) !\n\n");
    do{

        //chiedo di fare una scelta
        makeChoice(menuchoice, choice, 'A', 'B');

        //in base alla scelta esce o gioca
        switch (*choice){
            case 'A':
                printf("Giochiamo!\n");
                makeMatch(questions, 'A', 'B', 'C');
                break;
            case 'B':
                exit(0);
                break;
            //il default non si verificherà mai grazie al do-while nella funzione makeChoice
        }
    }while(*choice != 'B');

    return 0;
}

//Definizione delle funzioni

void makeChoice (const char *menuchoice[], char *choice, char opt1, char opt2){


    int sentinel = 0;
    char *temp;
    printf("Fai una scelta digitando il carattere corrispondente\n\n");

    for(int i=0; i<NUMOPTIONS; i++){
        temp=menuchoice[i];
        while (*menuchoice[i] != '\0'){
            printf("%c", *menuchoice[i]);
            menuchoice[i]++;
        }
        menuchoice[i]=temp;
        printf("\n");
    }

    do{
        if(sentinel != 0){
            printf("L'opzione inserita non risulta corretta, inserire %c o %c\n\n", opt1, opt2);
        }
        scanf(" %c", choice);
        sentinel++;
    }while(*choice != opt1 && *choice!= opt2);


}

void makeMatch(const char *questions[], char opt1, char opt2, char opt3){
    char *username;
    int numcharusr = 10; //numero massimo di caratteri che deve avere il nome utente
    char sel;
    int sentinel = 0;
    int points = 0;
    char *temp2, *temp3;
    username = (char*)malloc((numcharusr+1)*sizeof(char)); //+1 per il carattere di fine stringa '\0' (sizeof(char) restituisce 1 e si potrebbe omettere)

    if(username==NULL){
        printf("Errore allocazione memoria per lo username\n\n");
        exit(1);
    }
    else{
        printf("Inserisci il tuo nome utente:\n\n");
        if(scanf("%s", username) != 1){
            printf("Errore inserimento username\n\n");
            exit(1);
        }
    }

    printf("Benvenuto ");
    temp3=username;
    while (*username != '\0'){
        printf("%c", *username);
        username++;
    }
    username=temp3;
    printf(" !\nScegli le risposte corrette alle seguenti domande:\n");

    for(int i=0; i<NUMQUESTION; i++){
        temp2=questions[i];
        while (*questions[i] != '\0'){
            printf("%c", *questions[i]);
            questions[i]++;
        }
        questions[i]=temp2;
        do{
            if(sentinel != 0){
                printf("L'opzione inserita non risulta corretta, inserire %c , %c o %c\n\n", opt1, opt2, opt3);
            }
            scanf(" %c", &sel);
            sentinel++;
        }while(sel != opt1 && sel!= opt2 && sel!= opt3);

        sentinel = 0;

        switch(i){
            case 0:
                if(sel==opt1){
                    points +=3;
                }
                else{
                    points--;
                }
                break;
            case 1:
                if(sel==opt2){
                    points +=3;
                }
                else{
                    points--;
                }
                break;
            case 2:
                if(sel==opt3){
                    points +=3;
                }
                else{
                    points--;
                }
                break;
        }
        //avrei potuto passare un array answers per le risposte
        //ma non l'ho fatto perchè per lo scopo del programma va bene anche questo tipo di simulazione

        sel = '\0';
        printf("\n");

    }

    printf("Il giocatore ");
    while (*username != '\0'){
        printf("%c", *username);
        username++;
    }
    printf(" ha totalizzato %d punti!\n\n", points);
    free(username);
}

