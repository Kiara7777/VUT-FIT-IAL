
/* c206.c **********************************************************}
{* T�ma: Dvousm�rn� v�zan� line�rn� seznam
**
**                   N�vrh a referen�n� implementace: Bohuslav K�ena, ��jen 2001
**                            P�epracovan� do jazyka C: Martin Tu�ek, ��jen 2004
**                                            �pravy: Bohuslav K�ena, ��jen 2014
**
** Implementujte abstraktn� datov� typ dvousm�rn� v�zan� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou
** typu tDLList (DL znamen� Double-Linked a slou�� pro odli�en�
** jmen konstant, typ� a funkc� od jmen u jednosm�rn� v�zan�ho line�rn�ho
** seznamu). Definici konstant a typ� naleznete v hlavi�kov�m souboru c206.h.
**
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu
** s v��e uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ
** obousm�rn� v�zan� line�rn� seznam:
**
**      DLInitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DLDisposeList ... zru�en� v�ech prvk� seznamu,
**      DLInsertFirst ... vlo�en� prvku na za��tek seznamu,
**      DLInsertLast .... vlo�en� prvku na konec seznamu,
**      DLFirst ......... nastaven� aktivity na prvn� prvek,
**      DLLast .......... nastaven� aktivity na posledn� prvek,
**      DLCopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DLCopyLast ...... vrac� hodnotu posledn�ho prvku,
**      DLDeleteFirst ... zru�� prvn� prvek seznamu,
**      DLDeleteLast .... zru�� posledn� prvek seznamu,
**      DLPostDelete .... ru�� prvek za aktivn�m prvkem,
**      DLPreDelete ..... ru�� prvek p�ed aktivn�m prvkem,
**      DLPostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      DLPreInsert ..... vlo�� nov� prvek p�ed aktivn� prvek seznamu,
**      DLCopy .......... vrac� hodnotu aktivn�ho prvku,
**      DLActualize ..... p�ep�e obsah aktivn�ho prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal�� prvek seznamu,
**      DLPred .......... posune aktivitu na p�edchoz� prvek seznamu,
**      DLActive ........ zji��uje aktivitu seznamu.
**
** P�i implementaci jednotliv�ch funkc� nevolejte ��dnou z funkc�
** implementovan�ch v r�mci tohoto p��kladu, nen�-li u funkce
** explicitn� uvedeno n�co jin�ho.
**
** Nemus�te o�et�ovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam
** p�ed� n�kdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn� komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepou��v� pojem procedura.
** Proto zde pou��v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tato funkce bude vol�na z n�kter�ch d�le implementovan�ch operac�.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* glob�ln� prom�nn� -- p��znak o�et�en� chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/
    L->Act = NULL;  //NULL vsech ukazatelu
    L->First = NULL;
    L->Last = NULL;


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zru�� v�echny prvky seznamu L a uvede seznam do stavu, v jak�m
** se nach�zel po inicializaci. Ru�en� prvky seznamu budou korektn�
** uvoln�ny vol�n�m operace free.
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vlo�� nov� prvek na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
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
    //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vlo�� nov� prvek na konec seznamu L (symetrick� operace k DLInsertFirst).
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
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
    //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLFirst (tDLList *L) {
/*
** Nastav� aktivitu na prvn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/

    L->Act = L->First;
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLLast (tDLList *L) {
/*
** Nastav� aktivitu na posledn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/

    L->Act = L->Last;
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/

    if (L->First != NULL) // jestli existuje prvni prvek (seznam neni praydny)
         *val = L->First->data; //poslu hodnotu prvku
    else
        DLError();  // je prazdny == NULL, chyba
    //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu posledn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/
    if(L->First != NULL) //jestli existuje koncovz pvek
        *val = L->Last->data;
    else
        DLError();
    //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zru�� prvn� prvek seznamu L. Pokud byl prvn� prvek aktivn�, aktivita
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
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
    //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLDeleteLast (tDLList *L) {
/*
** Zru�� posledn� prvek seznamu L. Pokud byl posledn� prvek aktivn�,
** aktivita seznamu se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zru�� prvek seznamu L za aktivn�m prvkem.
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** posledn�m prvkem seznamu, nic se ned�je.
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
    //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zru�� prvek p�ed aktivn�m prvkem seznamu L .
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** prvn�m prvkem seznamu, nic se ned�je.
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo�� prvek za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
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
        //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vlo�� prvek p�ed aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, vol� funkci DLError ().
**/
if (L->Act != NULL)
    *val = L->Act->data; // jestli je prvek aktivni
else
    DLError();
//solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLActualize (tDLList *L, int val) {
/*
** P�ep�e obsah aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned�l� nic.
**/
    if (L->Act != NULL)
        L->Act->data = val;
//solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na posledn�m prvku se seznam stane neaktivn�m.
**/

    if (L->Act != NULL)
        L->Act = L->Act->rptr;


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na p�edchoz� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na prvn�m prvku se seznam stane neaktivn�m.
**/

    if (L->Act != NULL)
        L->Act = L->Act->lptr;
//solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam aktivn�, vrac� true. V opa�n�m p��pad� vrac� false.
** Funkci implementujte jako jedin� p��kaz.
**/
//solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */

return L->Act != NULL; // false = 0, true = 1...
}

/* Konec c206.c*/
