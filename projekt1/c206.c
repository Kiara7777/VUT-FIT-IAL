
/* c206.c **********************************************************}
{* Téma: Dvousmìrnì vázaný lineární seznam
**
**                   Návrh a referenèní implementace: Bohuslav Køena, øíjen 2001
**                            Pøepracované do jazyka C: Martin Tuèek, øíjen 2004
**                                            Úpravy: Bohuslav Køena, øíjen 2014
**
** Implementujte abstraktní datový typ dvousmìrnì vázaný lineární seznam.
** U¾iteèným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou
** typu tDLList (DL znamená Double-Linked a slou¾í pro odli¹ení
** jmen konstant, typù a funkcí od jmen u jednosmìrnì vázaného lineárního
** seznamu). Definici konstant a typù naleznete v hlavièkovém souboru c206.h.
**
** Va¹ím úkolem je implementovat následující operace, které spolu
** s vý¹e uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ
** obousmìrnì vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DLDisposeList ... zru¹ení v¹ech prvkù seznamu,
**      DLInsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      DLInsertLast .... vlo¾ení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zru¹í první prvek seznamu,
**      DLDeleteLast .... zru¹í poslední prvek seznamu,
**      DLPostDelete .... ru¹í prvek za aktivním prvkem,
**      DLPreDelete ..... ru¹í prvek pøed aktivním prvkem,
**      DLPostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vlo¾í nový prvek pøed aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal¹í prvek seznamu,
**      DLPred .......... posune aktivitu na pøedchozí prvek seznamu,
**      DLActive ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci jednotlivých funkcí nevolejte ¾ádnou z funkcí
** implementovaných v rámci tohoto pøíkladu, není-li u funkce
** explicitnì uvedeno nìco jiného.
**
** Nemusíte o¹etøovat situaci, kdy místo legálního ukazatele na seznam
** pøedá nìkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnì komentujte!
**
** Terminologická poznámka: Jazyk C nepou¾ívá pojem procedura.
** Proto zde pou¾íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tato funkce bude volána z nìkterých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální promìnná -- pøíznak o¹etøení chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/
    L->Act = NULL;  //NULL vsech ukazatelu
    L->First = NULL;
    L->Last = NULL;


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Ru¹ené prvky seznamu budou korektnì
** uvolnìny voláním operace free.
**/
    tDLElemPtr PomUk = NULL;

    while (L->First != NULL)
    {
        PomUk = L->First;
        L->First = PomUk->rptr;
        free(PomUk);
    }

    L->Act = NULL;
    L->Last = NULL;


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vlo¾í nový prvek na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    tDLElemPtr PomUk = NULL;

    PomUk = (tDLElemPtr) malloc(sizeof(struct tDLElem));

    if (PomUk == NULL) //kontrola mallocu
    {
        DLError();
        return;
    }

    PomUk->data = val;
    PomUk->lptr = NULL; //levy ukazatel ukazuje na pocatek seznamu, neboli na NULL
    PomUk->rptr = L->First; //pravy uk. bude ukazovat bude na NULL, nebo na momentalni prvni prvek

    if (L->First != NULL) //v seznamu jiz neco je
        L->First->lptr = PomUk; //momentalni prvni bude levym uk. ukayovat na novy prvek
    else
        L->Last = PomUk; //vkladam do prazdneho seznamu

    L->First = PomUk; //ukazatel na pocatek
    //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vlo¾í nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/

    tDLElemPtr PomUk = NULL;

    PomUk = (tDLElemPtr) malloc(sizeof(struct tDLElem));

    if (PomUk == NULL) //kontrola mallocu
    {
        DLError();
        return;
    }
    PomUk->data = val;
    PomUk->lptr = L->Last; //levy ukazatel ukazuje na momentalne posledni prvek
    PomUk->rptr = NULL; //pravy uk. ukazuje na konec seznamu

    if (L->First != NULL) //v seznamu jiz neco je
        L->Last->rptr = PomUk; //momentalni posledni pvek bude ukazovat na novy
    else
        L->First = PomUk; //vkladam do prazdneho seznamu

    L->Last = PomUk; //ukazatel na konec
    //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/

    L->Act = L->First;
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/

    L->Act = L->Last;
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    if (L->First != NULL) // jestli existuje prvni prvek (seznam neni praydny)
         *val = L->First->data; //poslu hodnotu prvku
    else
        DLError();  // je prazdny == NULL, chyba
    //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
    if(L->First != NULL) //jestli existuje koncovz pvek
        *val = L->Last->data;
    else
        DLError();
    //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zru¹í první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/
    tDLElemPtr PomUk = NULL;

    if (L->First != NULL) // seznam neni prazdny
    {
        PomUk = L->First;

        if (L->Act == L->First) //pvni prvek je prvkem aktivnim, rusi se aktivita
            L->Act = NULL;

        if (L->First == L->Last) //prvni prvek je jedinym prvkem
        {
            L->Last = NULL;
            L->First = NULL;
        }
        else
        {
            L->First = L->First->rptr; //novym prvnim prvkem, bude momentalne jeho naslednik
            L->First->lptr = NULL; //levy ukazatel na NULL
        }

        free(PomUk);
    }
    //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLDeleteLast (tDLList *L) {
/*
** Zru¹í poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/

    if (L->First != NULL) // seznam neni prazdny
    {
        tDLElemPtr PomUk = NULL;
        PomUk = L->Last;

        if (L->Act == L->Last) //posledni prvek je prvkem aktivnim, rusi se aktivita
            L->Act = NULL;

        if (L->First == L->Last) //posledni prvek je jedinym prvkem
        {
            L->Last = NULL;
            L->First = NULL;
        }
        else
        {
            L->Last = L->Last->lptr; //novym poslednim prvkem, bude momentalne predposledni
            L->Last->rptr = NULL; //pravy ukazatel na NULL
        }

        free(PomUk);
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zru¹í prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se nedìje.
**/
    if (L->Act != NULL && L->Act->rptr != NULL) //je aktivni a neni posledni
    {
        tDLElemPtr PomUk = NULL;
        PomUk = L->Act->rptr; //ulayatel ruseneho
        L->Act->rptr = PomUk->rptr; //pospojovani seznamu, preskoceni ruseneho

        if (PomUk == L->Last)
            L->Last = L->Act; // jeli ruseny posledni, aktivni bude posledni
        else //rusi se bezny prvek
            PomUk->rptr->lptr = L->Act; //prvek po rusebem ukayuje do leva na aktivni

        free(PomUk);
    }
    //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zru¹í prvek pøed aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se nedìje.
**/

    if (L->Act != NULL && L->Act->lptr != NULL) //je aktivni a neni prvni
    {
        tDLElemPtr PomUk = NULL;
        PomUk = L->Act->lptr; //ulayatel ruseneho
        L->Act->lptr = PomUk->lptr; //pospojovani seznamu, preskoceni ruseneho

        if (PomUk == L->First)
            L->First = L->Act; // jeli ruseny prvni, aktivni bude prvni
        else //rusi se bezny prvek
            PomUk->lptr->rptr = L->Act; //prvek po rusebem ukazuje do leva na aktivni

        free(PomUk);
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    if (L->Act != NULL) //jeli seznam prazdny
    {
        tDLElemPtr PomUk = NULL;

        PomUk = (tDLElemPtr) malloc(sizeof(struct tDLElem));

        if (PomUk == NULL) //kontrola mallocu
        {
            DLError();
            return;
        }

        PomUk->data = val;
        PomUk->rptr = L->Act->rptr;
        PomUk->lptr = L->Act; //pospojovani seznamu

        L->Act->rptr = PomUk; //vloyeni noveho prvku

        if (L->Act == L->Last) //jele aktivni poslednim prvkem
            L->Last = PomUk;
        else // bezny prvek
            PomUk->rptr->lptr = PomUk;
        }
        //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek pøed aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/

if (L->Act != NULL) //jeli seznam prazdny
    {
        tDLElemPtr PomUk = NULL;

        PomUk = (tDLElemPtr) malloc(sizeof(struct tDLElem));

        if (PomUk == NULL) //kontrola mallocu
        {
            DLError();
            return;
        }

        PomUk->data = val;
        PomUk->lptr = L->Act->lptr;
        PomUk->rptr = L->Act; //pospojovani seznamu

        L->Act->lptr = PomUk; //vloyeni noveho prvku

        if (L->Act == L->First)// je-li aktivni prvni prvek
            L->First = PomUk;
        else
            PomUk->lptr->rptr = PomUk;
        }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
if (L->Act != NULL)
    *val = L->Act->data; // jestli je prvek aktivni
else
    DLError();
//solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLActualize (tDLList *L, int val) {
/*
** Pøepí¹e obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedìlá nic.
**/
    if (L->Act != NULL)
        L->Act->data = val;
//solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na posledním prvku se seznam stane neaktivním.
**/

    if (L->Act != NULL)
        L->Act = L->Act->rptr;


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na pøedchozí prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na prvním prvku se seznam stane neaktivním.
**/

    if (L->Act != NULL)
        L->Act = L->Act->lptr;
//solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam aktivní, vrací true. V opaèném pøípadì vrací false.
** Funkci implementujte jako jediný pøíkaz.
**/
//solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */

return L->Act != NULL; // false = 0, true = 1...
}

/* Konec c206.c*/
