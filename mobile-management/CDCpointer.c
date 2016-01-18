/**************************************************************************
Arxeio Ylopoihshs	: CDCpointer.c
Syggrafeas			:
Skopos				: Ylopihsh ATD OuraPlus vs
                      Dipla Syndedemenh Kyklikh Lista me deiktes
Ana8ewrhsh			:
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "OuraPlus.h"

typedef struct typos_komvou *typos_deikti;

typedef struct typos_komvou{
	TStoixeiouOuraPlus dedomena;	/*ta dedomena*/
	typos_deikti    epomenos; 	    /*deikths ston epomeno komvo*/
	typos_deikti    proigoumenos; 	/*deikths ston prohgoymeno komvo*/
} typos_komvou;	   /*o typos toy kombou ths ouraPs*/


typedef struct GeneralNode{
        typos_deikti Head,   /* h arxh ths ouraPlus (NULL if list empty) */
                     Last,   /* to telos ths ouraPluss (NULL if list empty) */
                     Current;/* o trexon komvos ths ouraPlus (NULL if list empty) */
        int ListSize;
}GeneralNode;

/*dhlwseis synarthsewn*/

/*dhmioyrgia kai katastrofh ouraPs*/
void OuraPlus_dimiourgia(TOuraPlus * const ouraP){
	*ouraP = malloc(sizeof(GeneralNode));
	(*ouraP)->Current = NULL;
	(*ouraP)->Head = NULL;
	(*ouraP)->Last = NULL;
	(*ouraP)->ListSize = 0;
	} /* initializes Current as NULL  ++++ */

void OuraPlus_katastrofi(TOuraPlus * const ouraP){
	free(*ouraP);
	}

/*prakseis elegxoy*/
int	OuraPlus_keni(const TOuraPlus ouraP){
	if(ouraP->ListSize == 0) return 1;
	else return 0;
	}

int OuraPlus_megethos(const TOuraPlus ouraP){
	return(ouraP->ListSize);
	}

/*prakseis prosbashs-allazei to Current*/
int OuraPlus_periexomenoTrexon(const TOuraPlus ouraP, TStoixeiouOuraPlus * const value){
	if (ouraP->Current == NULL || OuraPlus_keni(ouraP))
	    return 0;
	else
	TSOuraPlus_setValue(value, ouraP->Current->dedomena);
	return 1;
	} /* error if Current invalid */

int OuraPlus_allagiTrexon(const TOuraPlus ouraP, TStoixeiouOuraPlus stoixeio){
	if(ouraP->Current == NULL)
		return 0;
	else
		TSOuraPlus_setValue(&(ouraP->Current->dedomena), stoixeio);
		return 1;
		} /* error if Current invalid */

/*prakseis eisagwgh-diagrafh Current as prodeiktis */
int OuraPlus_eisagogiTelos(const TOuraPlus ouraP, TStoixeiouOuraPlus stoixeio){
	typos_deikti prosorinos;
	prosorinos = malloc(sizeof(typos_komvou));
	TSOuraPlus_setValue(&prosorinos->dedomena, stoixeio);
	if (OuraPlus_keni(ouraP)) {
		ouraP->Head = prosorinos;
		ouraP->Current = prosorinos;
		ouraP->Last = prosorinos;
		ouraP->Last->epomenos = ouraP->Head;
	}
	else{
		prosorinos->proigoumenos = ouraP->Last;
		prosorinos->epomenos = ouraP->Last->epomenos;
		ouraP->Last->epomenos = prosorinos;
  		if(prosorinos->epomenos != NULL)
		    prosorinos->epomenos->proigoumenos = prosorinos;
		ouraP->Current = prosorinos;
		ouraP->Last = prosorinos;
	}
	ouraP->ListSize = ouraP->ListSize + 1;

		} /* sto telos */

int OuraPlus_exagogiArxh(const TOuraPlus ouraP){
	if(OuraPlus_keni(ouraP)) {
		return 0;
	}
	else {
  typos_deikti prosorinos;
		prosorinos = ouraP->Head;
		ouraP->Last->epomenos = prosorinos->epomenos;
		if(prosorinos->epomenos!=NULL)
			prosorinos->epomenos->proigoumenos = ouraP->Last;
		free(prosorinos);
	}
	ouraP->Head = ouraP->Last->epomenos;
	ouraP->Current = ouraP->Last->epomenos;
	ouraP->ListSize = ouraP->ListSize - 1;
	return 1;
}/*  sthn arxh  */

int OuraPlus_diagrafiTrexon(const TOuraPlus ouraP){
	if(OuraPlus_keni(ouraP))
		return 0;
	else{
		typos_deikti prosorinos;
		if(ouraP->Current == ouraP->Head){
			OuraPlus_exagogiArxh(ouraP);
			return 1;
		}
		else if(ouraP->Current == ouraP->Last){
			prosorinos = ouraP->Last;
			ouraP->Head->proigoumenos = ouraP->Last->proigoumenos;
			prosorinos->proigoumenos->epomenos = ouraP->Head;
			free(prosorinos);
			ouraP->Last = ouraP->Head->proigoumenos;
			ouraP->Current = ouraP->Head;
			ouraP->ListSize = ouraP->ListSize - 1;
			return 1;
		}
		else{
			prosorinos = ouraP->Current;
			ouraP->Current = ouraP->Current->epomenos;
			prosorinos->proigoumenos->epomenos = prosorinos->epomenos;
			prosorinos->epomenos->proigoumenos = prosorinos->proigoumenos;
			free(prosorinos);
			ouraP->ListSize = ouraP->ListSize - 1;
			return 1;
		}
	}
	}	/* diagrafei *trexonta* komvo apo apoydhpote */

/* Epilogh Kombou Current */

int OuraPlus_epomenos(const TOuraPlus ouraP){
	if(ouraP->Current->epomenos == ouraP->Last->epomenos)
	    return 0;
	else{
	ouraP->Current = ouraP->Current->epomenos;
	return 1;}
	} /* if noNext no move + error */

int OuraPlus_proigoymenos(const TOuraPlus ouraP){
	if (ouraP->Current->proigoumenos == ouraP->Head->proigoumenos)
	    return 0;
	else{
	ouraP->Current = ouraP->Current->proigoumenos;
	return 1;}
	} /* if noPrev no move + error*/

int OuraPlus_prwtos(const TOuraPlus ouraP){
	if(OuraPlus_keni(ouraP))
	    return 0;
	else{
	ouraP->Current = ouraP->Head;
	return 1;}
	} /* to First - if empty to Head + error */

int OuraPlus_teleytaios(const TOuraPlus ouraP){
	if(OuraPlus_keni(ouraP))
	    return 0;
	else{
	ouraP->Current = ouraP->Last;
	return 1;}
	} /* to Last - if empty to Last + null*/

/*prakseis anazhthshs*/

int OuraPlus_anazitisi(const TOuraPlus ouraP, TStoixeiouOuraPlus stoixeio,
                    int (*iso)(TStoixeiouOuraPlus , TStoixeiouOuraPlus)){
	int i;
	ouraP->Current = ouraP->Head;
	for(i = 0; i < ouraP->ListSize; i++){
		if(TSOuraPlus_iso(stoixeio, ouraP->Current->dedomena))
			return 1;
		if(ouraP->ListSize - i > 1)
		ouraP->Current = ouraP->Current->epomenos;
	}
	return 0;
}


int OuraPlus_delete(const TOuraPlus ouraP, char *number, int max){
    TStoixeiouOuraPlus x;
    int i;
            OuraPlus_prwtos(ouraP);
			OuraPlus_periexomenoTrexon(ouraP, &x);
			if(strcmp(number,x.number)== 0){
				OuraPlus_diagrafiTrexon(ouraP);
				if(!OuraPlus_keni(ouraP))
					OuraPlus_proigoymenos(ouraP);
		    	}
			for(i=1;i<max;i++){
       	        OuraPlus_epomenos(ouraP);
           	    OuraPlus_periexomenoTrexon(ouraP, &x);
			if(strcmp(number,x.number)== 0){
				OuraPlus_diagrafiTrexon(ouraP);
				if(!OuraPlus_keni(ouraP))
				OuraPlus_proigoymenos(ouraP);
			}
		}
}   /* sugrinei tous arithmous k diagrafei*/
	
	
	
int OuraPlus_allagh(const TOuraPlus ouraP, char *number1, char *number2, int max){
	TStoixeiouOuraPlus x;
    int i;
            OuraPlus_prwtos(ouraP);
			OuraPlus_periexomenoTrexon(ouraP, &x);
			if(strcmp(number1,x.number)== 0){
				strcpy(ouraP->Current->dedomena.number, number2);
			}
			for(i=1;i<max;i++){
       	        OuraPlus_epomenos(ouraP);
           	    OuraPlus_periexomenoTrexon(ouraP, &x);
			if(strcmp(number1,x.number)== 0){
               strcpy(ouraP->Current->dedomena.number, number2);
			}
			}
}   /* allazei mono tous arithmous xwris na peiraksei ta alla dedomena(imerominia,wra) */
