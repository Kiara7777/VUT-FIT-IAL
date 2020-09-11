
/* c401.c: **********************************************************}
{* T�ma: Rekurzivn� implementace operac� nad BVS
**                                         Vytvo�il: Petr P�ikryl, listopad 1994
**                                         �pravy: Andrea N�mcov�, prosinec 1995
**                                                      Petr P�ikryl, duben 1996
**                                                   Petr P�ikryl, listopad 1997
**                                  P�evod do jazyka C: Martin Tu�ek, ��jen 2005
**                                         �pravy: Bohuslav K�ena, listopad 2009
**                                         �pravy: Karel Masa��k, ��jen 2013
**                                         �pravy: Radek Hranick�, ��jen 2014
**
** Implementujte rekurzivn�m zp�sobem operace nad bin�rn�m vyhled�vac�m
** stromem (BVS; v angli�tin� BST - Binary Search Tree).
**
** Kl��em uzlu stromu je jeden znak (obecn� j�m m��e b�t cokoliv, podle
** �eho se vyhled�v�). U�ite�n�m (vyhled�van�m) obsahem je zde integer.
** Uzly s men��m kl��em le�� vlevo, uzly s v�t��m kl��em le�� ve stromu
** vpravo. Vyu�ijte dynamick�ho p�id�lov�n� pam�ti.
** Rekurzivn�m zp�sobem implementujte n�sleduj�c� funkce:
**
**   BSTInit ...... inicializace vyhled�vac�ho stromu
**   BSTSearch .... vyhled�v�n� hodnoty uzlu zadan�ho kl��em
**   BSTInsert .... vkl�d�n� nov� hodnoty
**   BSTDelete .... zru�en� uzlu se zadan�m kl��em
**   BSTDispose ... zru�en� cel�ho stromu
**
** ADT BVS je reprezentov�n ko�enov�m ukazatelem stromu (typ tBSTNodePtr).
** Uzel stromu (struktura typu tBSTNode) obsahuje kl�� (typu char), podle
** kter�ho se ve stromu vyhled�v�, vlastn� obsah uzlu (pro jednoduchost
** typu int) a ukazatel na lev� a prav� podstrom (LPtr a RPtr). P�esnou definici typ�
** naleznete v souboru c401.h.
**
** Pozor! Je t�eba spr�vn� rozli�ovat, kdy pou��t dereferen�n� oper�tor *
** (typicky p�i modifikaci) a kdy budeme pracovat pouze se samotn�m ukazatelem
** (nap�. p�i vyhled�v�n�). V tomto p��kladu v�m napov� prototypy funkc�.
** Pokud pracujeme s ukazatelem na ukazatel, pou�ijeme dereferenci.
**/

#include "c401.h"
int solved;

void BSTInit (tBSTNodePtr *RootPtr) {
/*   -------
** Funkce provede po��te�n� inicializaci stromu p�ed jeho prvn�m pou�it�m.
**
** Ov��it, zda byl ji� strom p�edan� p�es RootPtr inicializov�n, nelze,
** proto�e p�ed prvn� inicializac� m� ukazatel nedefinovanou (tedy libovolnou)
** hodnotu. Program�tor vyu��vaj�c� ADT BVS tedy mus� zajistit, aby inicializace
** byla vol�na pouze jednou, a to p�ed vlastn� prac� s BVS. Proveden�
** inicializace nad nepr�zdn�m stromem by toti� mohlo v�st ke ztr�t� p��stupu
** k dynamicky alokovan� pam�ti (tzv. "memory leak").
**
** V�imn�te si, �e se v hlavi�ce objevuje typ ukazatel na ukazatel.
** Proto je t�eba p�i p�i�azen� p�es RootPtr pou��t dereferen�n� oper�tor *.
** Ten bude pou�it i ve funkc�ch BSTDelete, BSTInsert a BSTDispose.
**/


	*RootPtr = NULL; //vytvorit prazdny strom
	 //solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */

}

int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content)	{
/*  ---------
** Funkce vyhled� uzel v BVS s kl��em K.
**
** Pokud je takov� nalezen, vrac� funkce hodnotu TRUE a v prom�nn� Content se
** vrac� obsah p��slu�n�ho uzlu.�Pokud p��slu�n� uzel nen� nalezen, vrac� funkce
** hodnotu FALSE a obsah prom�nn� Content nen� definov�n (nic do n� proto
** nep�i�azujte).
**
** P�i vyhled�v�n� v bin�rn�m stromu bychom typicky pou�ili cyklus ukon�en�
** testem dosa�en� listu nebo nalezen� uzlu s kl��em K. V tomto p��pad� ale
** probl�m �e�te rekurzivn�m vol�n� t�to funkce, p�i�em� nedeklarujte ��dnou
** pomocnou funkci.
**/
	if (RootPtr == NULL)    //zda je strom prazdny
        return FALSE;
    else
    {
        if (RootPtr->Key != K) //strom neni prazdny a klic nebzl nalezen
        {
            if (RootPtr->Key > K) // test zda je aktualni klic vetsi/mensi nez vyhledavany
                return BSTSearch(RootPtr->LPtr, K, Content); //je vetsi, rekurzivni volani leveho syna
            else
                return BSTSearch(RootPtr->RPtr, K, Content); //je mensi, rekuryivni volani praveho syna
        }
        else //klic se nasel
        {
            *Content = RootPtr->BSTNodeCont; //vraceni hodnoty
            return TRUE;
        }
    }


	 //solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */
}

void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content)	{
/*   ---------
** Vlo�� do stromu RootPtr hodnotu Content s kl��em K.
**
** Pokud ji� uzel se zadan�m kl��em ve stromu existuje, bude obsah uzlu
** s kl��em K nahrazen novou hodnotou. Pokud bude do stromu vlo�en nov�
** uzel, bude vlo�en v�dy jako list stromu.
**
** Funkci implementujte rekurzivn�. Nedeklarujte ��dnou pomocnou funkci.
**
** Rekurzivn� implementace je m�n� efektivn�, proto�e se p�i ka�d�m
** rekurzivn�m zano�en� ukl�d� na z�sobn�k obsah uzlu (zde integer).
** Nerekurzivn� varianta by v tomto p��pad� byla efektivn�j�� jak z hlediska
** rychlosti, tak z hlediska pam�ov�ch n�rok�. Zde jde ale o �koln�
** p��klad, na kter�m si chceme uk�zat eleganci rekurzivn�ho z�pisu.
**/
 if (*RootPtr == NULL)
    {
        tBSTNodePtr PomUk;
        PomUk = malloc(sizeof(struct tBSTNode)); //vytvoreni noveho uzlu
        //if (PomUk == NULL) dle fora neni nutno kontrolu pouzivat
            //return;

            //vytvoreni korene nebo terminalniho uzlu
        PomUk->Key = K;
        PomUk->BSTNodeCont = Content;
        PomUk->LPtr = NULL;
        PomUk->RPtr = NULL;
        *RootPtr = PomUk; //vloz do stromu
    }
     else //naajit kam se vlozit
    {
        if ((*RootPtr)->Key > K)
            BSTInsert(&((*RootPtr)->LPtr), K, Content); //pokracuj v levem stromu
        else
        {
            if ((*RootPtr)->Key < K)
                BSTInsert(&((*RootPtr)->RPtr), K, Content); //pokracuj v pravem stromu

            else
                (*RootPtr)->BSTNodeCont = Content; //pokud uz existuje klic
        }

    }



	 //solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */

}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {
/*   ------------------
** Pomocn� funkce pro vyhled�n�, p�esun a uvoln�n� nejprav�j��ho uzlu.
**
** Ukazatel PtrReplaced ukazuje na uzel, do kter�ho bude p�esunuta hodnota
** nejprav�j��ho uzlu v podstromu, kter� je ur�en ukazatelem RootPtr.
** P�edpokl�d� se, �e hodnota ukazatele RootPtr nebude NULL (zajist�te to
** testov�n�m p�ed vol�n� t�to funkce). Tuto funkci implementujte rekurzivn�.
**
** Tato pomocn� funkce bude pou�ita d�le. Ne� ji za�nete implementovat,
** p�e�t�te si koment�� k funkci BSTDelete().
**/
    tBSTNodePtr PomUk = NULL;

    if ((*RootPtr)->RPtr != NULL) //hledani jepravejsi hodnoty
        ReplaceByRightmost(PtrReplaced, &((*RootPtr)->RPtr));
    else    //nejpravesji hodnota se nasla, ulozit ji do PtrREplaced
    {
        PomUk = *RootPtr; //uloyeni naleyeneho
        PtrReplaced->BSTNodeCont = PomUk->BSTNodeCont; //hodnota uzlu
        PtrReplaced->Key = PomUk->Key; //klic
        (*RootPtr) = PomUk->LPtr; //pospojovani
        free(PomUk);
    }



	 //solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */

}

void BSTDelete (tBSTNodePtr *RootPtr, char K) 		{
/*   ---------
** Zru�� uzel stromu, kter� obsahuje kl�� K.
**
** Pokud uzel se zadan�m kl��em neexistuje, ned�l� funkce nic.
** Pokud m� ru�en� uzel jen jeden podstrom, pak jej zd�d� otec ru�en�ho uzlu.
** Pokud m� ru�en� uzel oba podstromy, pak je ru�en� uzel nahrazen nejprav�j��m
** uzlem lev�ho podstromu. Pozor! Nejprav�j�� uzel nemus� b�t listem.
**
** Tuto funkci implementujte rekurzivn� s vyu�it�m d��ve deklarovan�
** pomocn� funkce ReplaceByRightmost.
**/
    if ((*RootPtr) != NULL) //kdyz mam co odstraniovat
    {
        if ((*RootPtr)->Key > K) //vyhledavani klice v levem
            BSTDelete(&((*RootPtr)->LPtr), K);
        else
        {
            if ((*RootPtr)->Key < K) //vyhledavani klice v pravem
                BSTDelete(&((*RootPtr)->RPtr), K);
            else
            {
               tBSTNodePtr PomUk = NULL;
               PomUk = (*RootPtr);

               if (PomUk->RPtr == NULL) //ma jenom levy podstrom
                   {
                     *RootPtr = PomUk->LPtr;
                     free(PomUk);
                   }

               else
               {
                   if (PomUk->LPtr == NULL) //ma jenom pravy podstom
                        {
                            *RootPtr = PomUk->RPtr;
                            free(PomUk);
                        }
                    else
                    ReplaceByRightmost(*RootPtr, &(PomUk->LPtr)); //ma oba podtromy
               }
               //free(PomUk);
            }


        }


    }


	 //solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */

}

void BSTDispose (tBSTNodePtr *RootPtr) {
/*   ----------
** Zru�� cel� bin�rn� vyhled�vac� strom a korektn� uvoln� pam�.
**
** Po zru�en� se bude BVS nach�zet ve stejn�m stavu, jako se nach�zel po
** inicializaci. Tuto funkci implementujte rekurzivn� bez deklarov�n� pomocn�
** funkce.
**/
    if (*RootPtr != NULL) //strom ma uzly
    {
        BSTDispose(&((*RootPtr)->LPtr)); //az do posledniho leveho prvku
        BSTDispose(&((*RootPtr)->RPtr)); //az do posledniho praveho prvku
        free(*RootPtr);
        *RootPtr = NULL;
    }

	 //solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */

}

/* konec c401.c */

