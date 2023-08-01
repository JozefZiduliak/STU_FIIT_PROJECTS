#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Pocet structov v subore 57
//Struktura ktora drzi udaje zo suboru
struct node{

    //Jednotlive premenne na data zo subora
    long long ID_cislo_mer_osoby;
    char meno_osoby[31];
    char mer_modul[4];
    char typ_mer_veliciny[3];
    double hodnota;
    char cas_merania[5];
    char datum[9];

    struct node* next; //Ukazovatel na dalsiu nodu v spojenom zozname
};
typedef struct node node_t;

//Funckia ktora vytvori  ukazovatel novy struct
// Pointer na dalsiu nodu v liste bude NULL
node_t *create_new_node()
{
    node_t *result = malloc(sizeof(node_t));
    result->next = NULL;
    return result;
}

node_t *n_function(FILE *fPtr, node_t *head_of_list_ptr)
{

    if(fPtr != NULL) { //Ak je subor otvoreny

        node_t *current_node_of_a_list; //Pointer ktory ukazuje na nodu s ktorou sa aktualne pracuje

        current_node_of_a_list = head_of_list_ptr;

        if(head_of_list_ptr != NULL) //Ak uz bol prikaz N spusteny v minulosti
        {

            while (current_node_of_a_list != NULL) {
                node_t *tmp = current_node_of_a_list->next;
                free(current_node_of_a_list);
                current_node_of_a_list = tmp;
            }
        }

        head_of_list_ptr = NULL;

        int number_of_lines = 0; // Udzruje udaj o pocte riadkov v subore
        char c; // Premenna ktora pomaha pri pocitani riadku v subore

        rewind(fPtr); //Refreshenm subor
        // Zistí pocet riadkov v programe
        for (c = getc(fPtr); c != EOF; c = getc(fPtr))
            if (c == '\n') // Increment count if this character is newline
                number_of_lines++;
        number_of_lines++; //Ak vydelim 8 dostanem cislo structov v subore

        //Vytvaranie structov
        rewind(fPtr); //Refreshnem subor
        for (int i = 0; i < number_of_lines/8; i++) {
            if(i == 0)
            {
                head_of_list_ptr = create_new_node(); //Vytvori novu node a ulozi jej smernik do hlavicky
                current_node_of_a_list = head_of_list_ptr;
            }

            else
            {
                current_node_of_a_list->next = create_new_node(); //Vytvori novu node a ulozi do predchadzajucej nody
                current_node_of_a_list = current_node_of_a_list->next;
            }

        }
        current_node_of_a_list = head_of_list_ptr;
        rewind(fPtr);
        char filler_variable[4]; //Urcena na nacitavanie $$$ v programe

        while(current_node_of_a_list != NULL)
        {
            fscanf(fPtr,"%s",filler_variable);
            fscanf(fPtr,"%lld", &current_node_of_a_list->ID_cislo_mer_osoby);
            fgets(filler_variable, 3, fPtr); // Musim nacitat 3 chari kvoli tej medzere na konci ID merajuceho
            fscanf(fPtr,"%[^\n]%*c",current_node_of_a_list->meno_osoby);
            fscanf(fPtr,"%s", current_node_of_a_list->mer_modul);
            fscanf(fPtr,"%s", current_node_of_a_list->typ_mer_veliciny);
            fscanf(fPtr,"%lf", &current_node_of_a_list->hodnota);
            fscanf(fPtr,"%s", current_node_of_a_list->cas_merania);
            fscanf(fPtr,"%s", current_node_of_a_list->datum);

            current_node_of_a_list = current_node_of_a_list->next; //Hybanie sa po liste
        }
        printf("Nacitalo sa %d zaznamov\n",number_of_lines/8);
        return head_of_list_ptr;
    }

    else {

        printf("Zaznamy neboli nacitane!\n");
        return NULL;
    }
}; //Vrati pointer na hlavicku listu

void v_function(FILE *fPtr, node_t *head_of_list_ptr){

    if(head_of_list_ptr != NULL) { //Ak boli structy vytvorene
        node_t *current_node_of_a_list; //Pointer ktory ukazuje na nodu s ktorou sa aktualne pracuje

        current_node_of_a_list = head_of_list_ptr;

        int node_counter = 1;

        while (current_node_of_a_list != NULL) {

            printf("%d:\n", node_counter);
            printf("ID cislo mer. osoby: %lld\n", current_node_of_a_list->ID_cislo_mer_osoby);
            printf("Meno osoby: %s\n", current_node_of_a_list->meno_osoby);
            printf("Mer. modul: %s\n", current_node_of_a_list->mer_modul);
            printf("Typ mer. veliciny: %s\n", current_node_of_a_list->typ_mer_veliciny);
            printf("Hodnota: %lf\n", current_node_of_a_list->hodnota);
            printf("Cas merania: %s\n", current_node_of_a_list->cas_merania);
            printf("Datum: %s\n", current_node_of_a_list->datum);
            node_counter++;
            current_node_of_a_list = current_node_of_a_list->next;
        }
    }
};

node_t *z_function(node_t *head_of_list_ptr){

    node_t *current_node_of_a_list; //Pointer ktory ukazuje na nodu s ktorou sa aktualne pracuje
    current_node_of_a_list = head_of_list_ptr;

    long long ID_to_be_deleted;
    scanf("%lld",&ID_to_be_deleted); //Input pouzivatele ktory urcuje, co sa ma vymazat

    //Vymazavanie udajov v hlavicke zoznamu
    while((current_node_of_a_list == head_of_list_ptr) && current_node_of_a_list->ID_cislo_mer_osoby == ID_to_be_deleted)
    {
        printf("Zaznam pre ID: %lld pre modul %s bol vymazany\n",ID_to_be_deleted,current_node_of_a_list->mer_modul);
        current_node_of_a_list = current_node_of_a_list->next;
        free(head_of_list_ptr);
        head_of_list_ptr = current_node_of_a_list;
    }

    node_t *previous_node = head_of_list_ptr;
    current_node_of_a_list = previous_node->next;

    //Vymazavanie udajov, ak uz boli vsetky udaje na zaciatku vymazane
    int b_end_of_a_list = 0; // Funguje ako bool, kontroluje ci sme presli zoznam

    while(!b_end_of_a_list)
    {

        if(current_node_of_a_list->ID_cislo_mer_osoby == ID_to_be_deleted)
        {
            printf("Zaznam pre ID: %lld pre modul %s bol vymazany\n",ID_to_be_deleted,current_node_of_a_list->mer_modul);
            previous_node->next = current_node_of_a_list->next; //Predosla zacne ukazovat na to co aktualna
            free(current_node_of_a_list); // Vymazem aktualnu
            current_node_of_a_list = previous_node->next; //Posunieme sa dalej

            if(current_node_of_a_list->next == NULL)
                b_end_of_a_list = 1; //Ak sme na konci zoznamu, cyklus sa  ukonci

        }
        else //Posuvanie po linked liste
        {
            previous_node = previous_node->next;
            if(current_node_of_a_list->next == NULL) //Ak sme na konci , tak sa skonci funkcia
                b_end_of_a_list = 1;
            else
            current_node_of_a_list = current_node_of_a_list->next;
        }
    }

    return head_of_list_ptr;
};

void u_function(){};

node_t *p_function(FILE *fPtr, node_t *head_of_list_ptr){

    int add_node_at_index; //Premenna ktora urcuje na ktorom indexe sa ma zapisat novy zaznam
    scanf("%d", &add_node_at_index);

    node_t *user_input = create_new_node(); //Vytvaranie nody, ktora sa ma pridat

    //Nacitavanie udajov od pouzivatela
    scanf("%lld", &user_input->ID_cislo_mer_osoby);
    getchar();
    fgets(user_input->meno_osoby, 30, stdin);
    user_input->meno_osoby[strcspn(user_input->meno_osoby, "\n")] = 0;
    //scanf(" %s", user_input->meno_osoby);
    //gets(user_input->meno_osoby);
    scanf("%s",user_input->mer_modul);
    scanf("%s", user_input->typ_mer_veliciny);
    scanf("%lf", &user_input->hodnota);
    scanf("%s", user_input->cas_merania);
    scanf("%s", user_input->datum);

    int b_node_connected = 0; // Premenná ktorá v cykle kontroluje, či sa nová noda pripojila k listu


    node_t *pointing_to_current_node = head_of_list_ptr; //Predchadzajuca noda

    if(add_node_at_index == 1) //Ak sa ma dat noda nazaciatok
    {
        user_input->next = head_of_list_ptr;
        return user_input;
    }

    for(int i = 2; !b_node_connected; i++)
    {

        if(i == add_node_at_index) //Ak sa ma ulozit medzi prvy a posledny
        {
            user_input->next = pointing_to_current_node->next;
            pointing_to_current_node->next = user_input;
            b_node_connected = 1;//Cyklus sa ukonci
        }

        if(pointing_to_current_node->next == NULL) //Ak sme na poslednom node
        {
            pointing_to_current_node->next = user_input;
            b_node_connected = 1;//Cyklus sa ukonci
        }

        pointing_to_current_node = pointing_to_current_node->next;

    }

    return head_of_list_ptr;
};

void h_function(FILE *fPtr, node_t *head_of_list_ptr){

    char zadany_meraci_modul[4];
    scanf("%s", zadany_meraci_modul);

    node_t *current_node_of_a_list; //Pointer ktory ukazuje na nodu s ktorou sa aktualne pracuje
    current_node_of_a_list = head_of_list_ptr;

    int node_counter = 1;

    while (current_node_of_a_list != NULL)
    {
        if(!strcmp(current_node_of_a_list->mer_modul,zadany_meraci_modul))
        {
            printf("%d:\n", node_counter);
            printf("ID cislo mer. osoby: %lld\n", current_node_of_a_list->ID_cislo_mer_osoby);
            printf("Meno osoby: %s\n", current_node_of_a_list->meno_osoby);
            printf("Mer. modul: %s\n", current_node_of_a_list->mer_modul);
            printf("Typ mer. veliciny: %s\n", current_node_of_a_list->typ_mer_veliciny);
            printf("Hodnota: %lf\n", current_node_of_a_list->hodnota);
            printf("Cas merania: %s\n", current_node_of_a_list->cas_merania);
            printf("Datum: %s\n", current_node_of_a_list->datum);
            node_counter++;
        }
        current_node_of_a_list = current_node_of_a_list->next;
    }

};

void r_function(node_t *head_of_list_ptr){

    int node_index_1, node_index_2;
    scanf("%d %d", &node_index_1, &node_index_2); //Premenne ktore urcuju ktore nody sa maju vymenit

    node_t *current_node_of_a_list = head_of_list_ptr; //Pointer ktory ukazuje na nodu s ktorou sa aktualne pracuje
    node_t *tmp_1 = create_new_node(); //Pomocna premenna
    node_t *tmp_2 = create_new_node(); // Pomocna premenna 2
    node_t *ptr_node_1, *ptr_node_2; //Ukazovatele na nody ktore sa maju vymenit

    int b_end_of_list = 0; // Premenna ktora kontroluje, ci sme nie na konci cyklu

    for(int i = 1; !b_end_of_list; i++)
    {
        if(i == node_index_1)
            ptr_node_1 = current_node_of_a_list;

        else if(i == node_index_2)
            ptr_node_2 = current_node_of_a_list;

        if(current_node_of_a_list->next == NULL) {
            b_end_of_list = 1; //Ak sme na konci zoznamu, tak sa cyklus ukonci
        }
        else
            current_node_of_a_list = current_node_of_a_list->next;
    }


    *tmp_1 = *ptr_node_1;
    *tmp_2 = *ptr_node_2;

    *ptr_node_1 = *tmp_2;
    *ptr_node_2 = *tmp_1;

    ptr_node_1->next = tmp_1->next;
    ptr_node_2->next = tmp_2->next;

    free(tmp_1);
    free(tmp_2);

    node_t *ptr_tmp;

};

void k_function(node_t *head_of_list_ptr){

    node_t *current_node_of_a_list; //Pointer ktory ukazuje na nodu s ktorou sa aktualne pracuje

    current_node_of_a_list = head_of_list_ptr;

    if(head_of_list_ptr != NULL) //Ak uz bol prikaz N spusteny v minulosti, tak sa structy dealokuju
    {
        printf("Prikaz n uz bol spusteny\n");
        while (current_node_of_a_list != NULL) {
            node_t *tmp = current_node_of_a_list->next;
            free(current_node_of_a_list);
            current_node_of_a_list = tmp;
        }
    }

};

int main()
{

    //Otvorenie suboru
    FILE *fPtr = NULL;
    fPtr = fopen("dataloger_V2.txt","r");

    //Hlavicka spajaneho zoznamu
    node_t *head = NULL;


    char user_input;
    while(1)
    {
        scanf("%c", &user_input);

        switch(user_input)
        {
            case 'n':
               head = n_function(fPtr,head);
                break;

            case 'v':
                v_function(fPtr,head);
                break;

            case 'z':
                head = z_function(head);
                break;

            case 'u':
                u_function();
                break;

            case 'p':
                head = p_function(fPtr,head);
                break;

            case 'h':
                h_function(fPtr,head);
                break;

            case 'r':
               r_function(head);
                break;

            case 'k':
                k_function(head);
                return 0;
                break;

        }

    }

    return 0;
}
