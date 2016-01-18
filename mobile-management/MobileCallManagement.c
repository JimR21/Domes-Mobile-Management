#include <stdio.h>
#include <stdlib.h>
#include "TStoixeiouOuraPlus.h"
#include "OuraPlus.h"
#include <string.h>

TOuraPlus Received=NULL, UnAnswered=NULL, Called=NULL;
int InitializeLists();

int PopulateLists(FILE *in);
/* Reads call data from in and puts them at the end of the appropriate list.
   If a list is longer than limitSize delete oldest call.
   Format of File
   L #number           // #of Calls in list (if list is longer oldest calls are deleted)
   R dd/mm/yyyy time(sec) telephone         // put into Received Call List
   U dd/mm/yyyy time(sec) telephone         // put into Unansewred Call List
   C dd/mm/yyyy time(sec) telephone         // put into Called Call List
*/

int ShowList(FILE *out, TOuraPlus CallList, int order);
/* Prints to out all data calls, one per line (date, number).
   if order >= 0 oldest to newest, otherwise newest to oldest
*/

int DeleteOrChangeCalls(FILE *in);
/* Reads pairs of telephone numbers from in, finds call with the first and replaces with second
   Format of File
   A #telephone     #telephone // change
   D #telephone                // delete
*/
int SearchCallList(FILE * in, FILE *out);
/* Reads telephones from in and searches CallList and writes Call Data
   R dd/mm/yyyy     //one per line
   U dd/mm/yyyy     //one per line
   C dd/mm/yyyy     //one per line
*/

int DestroyLists();

int main(void)
{   FILE *Calls, *Results, *DelorChCall, *Searchcalls, *Searchresults;
	InitializeLists();
    PopulateLists(Calls);
    ShowList(Results, Received, 1);
    ShowList(Results, Called, 1);
    ShowList(Results, UnAnswered, 1);
    ShowList(Results, Received, -1);
    ShowList(Results, Called, -1);
    ShowList(Results, UnAnswered, -1);
    DeleteOrChangeCalls(DelorChCall);
    ShowList(Results, Received, 1);
    ShowList(Results, Called, 1);
    ShowList(Results, UnAnswered, 1);
    ShowList(Results, Received, -1);
    ShowList(Results, Called, -1);
    ShowList(Results, UnAnswered, -1);
    SearchCallList(Searchcalls,Searchresults);
    DestroyLists();

  system("PAUSE");
  return 0;
}

int InitializeLists(){
	OuraPlus_dimiourgia(&Called);
	OuraPlus_dimiourgia(&Received);
	OuraPlus_dimiourgia(&UnAnswered);
}

int PopulateLists(FILE *in){
    TStoixeiouOuraPlus x;
	int max;
	char tupos;
	in = fopen("Calls.txt","r");
	fscanf(in,"%c %d", &tupos, &max);
	while ((feof(in) == 0)){
		do{
			tupos = fgetc(in);}
			while (tupos != 'R' && tupos != 'U' && tupos != 'C' && feof(in) == 0);
		if (tupos == 'R'){
            TSOuraPlus_readValue(in, &x);
            OuraPlus_eisagogiTelos(Received, x);
            if (OuraPlus_megethos(Received)> max){
				OuraPlus_exagogiArxh(Received);
			}
		}
		else if(tupos == 'U'){
            TSOuraPlus_readValue(in, &x);
            OuraPlus_eisagogiTelos(UnAnswered, x);
            if (OuraPlus_megethos(UnAnswered)> max){
				OuraPlus_exagogiArxh(UnAnswered);
			}
		}
		else if(tupos == 'C'){
            TSOuraPlus_readValue(in, &x);
            OuraPlus_eisagogiTelos(Called, x);
            if (OuraPlus_megethos(Called)> max){
				OuraPlus_exagogiArxh(Called);
			}
		}
}
fclose(in);
}


int ShowList(FILE *out, TOuraPlus CallList, int order){
    TStoixeiouOuraPlus x;
	int i;
	out = fopen("Showlist.txt", "w");
	if(OuraPlus_keni(CallList))
	    return 1;
	if(order == 1){
		OuraPlus_prwtos(CallList);
		OuraPlus_periexomenoTrexon(CallList, &x);
		TSOuraPlus_writeValue(out, x);
        for(i=1; i < OuraPlus_megethos(CallList) ; i++){
            OuraPlus_epomenos(CallList);
            OuraPlus_periexomenoTrexon(CallList, &x);
            TSOuraPlus_writeValue(out, x);
		}
	}
	else if(order == -1){
        OuraPlus_teleytaios(CallList);
        OuraPlus_periexomenoTrexon(CallList, &x);
		TSOuraPlus_writeValue(out, x);
		for(i=1; i < OuraPlus_megethos(CallList); i++){
            OuraPlus_proigoymenos(CallList);
            OuraPlus_periexomenoTrexon(CallList, &x);
            TSOuraPlus_writeValue(out, x);
		}
	}
	else printf("Error. Wrong order");
	fclose(out);
}


int DeleteOrChangeCalls(FILE *in){
	int maxU, maxR, maxC;
	char tupos, buf[15], buf2[15];
    in = fopen("DelorChNumber.txt", "r");
    maxU = OuraPlus_megethos(UnAnswered);
	maxC = OuraPlus_megethos(Called);
	maxR = OuraPlus_megethos(Received);
    while((feof(in) == 0)){
        do{
			tupos = fgetc(in);}
			while (tupos != 'D' && tupos != 'A' && feof(in) == 0);
        if(tupos == 'D'){
            tupos = fgetc(in);
			fgets(buf, 11, in);
   			if(!OuraPlus_keni(UnAnswered)){
				OuraPlus_delete(UnAnswered, buf, maxU);
				}
			if(!OuraPlus_keni(Called)){
				OuraPlus_delete(Called, buf, maxC);
		}
			if(!OuraPlus_keni(Received)){
				OuraPlus_delete(Received, buf, maxR);
			}
		}
		else if(tupos == 'A'){
			tupos = fgetc(in);
			fgets(buf, 11, in);
			tupos = fgetc(in);
			fgets(buf2, 11, in);
   			if(!OuraPlus_keni(UnAnswered)){
				OuraPlus_allagh(UnAnswered, buf, buf2, maxU);
				}
			if(!OuraPlus_keni(Called)){
				OuraPlus_allagh(Called, buf, buf2, maxC);
		}
			if(!OuraPlus_keni(Received)){
				OuraPlus_allagh(Received, buf, buf2, maxR);
			}
		}
	}
	fclose(in);
}


int SearchCallList(FILE *in, FILE *out){
    TStoixeiouOuraPlus x;
	char tupos;
	in = fopen("SearchCalls.txt", "r");
	out = fopen("SearchResults.txt", "w");
	while ((feof(in) == 0)){
		do{
			tupos = fgetc(in);}
			while (tupos != 'R' && tupos != 'U' && tupos != 'C' && feof(in) == 0);
		if (tupos == 'R'){
			TSOuraPlus_readValue(in, &x);
            if(OuraPlus_anazitisi(Received, x, TSOuraPlus_iso)){
	            OuraPlus_periexomenoTrexon(Received, &x);
	            TSOuraPlus_writeValue(out, x);
				}
			}
		else if(tupos == 'U'){
            TSOuraPlus_readValue(in, &x);
             if(OuraPlus_anazitisi(UnAnswered, x, TSOuraPlus_iso)){
	            OuraPlus_periexomenoTrexon(UnAnswered, &x);
	            TSOuraPlus_writeValue(out, x);
				}
			}
		else if(tupos == 'C'){
            TSOuraPlus_readValue(in, &x);
            if(OuraPlus_anazitisi(Called, x, TSOuraPlus_iso)){
	            OuraPlus_periexomenoTrexon(Called, &x);
	            TSOuraPlus_writeValue(out, x);
				}
			}
	}
	fclose(in);
	fclose(out);
}

int DestroyLists(){
	OuraPlus_katastrofi(&Called);
	OuraPlus_katastrofi(&Received);
	OuraPlus_katastrofi(&UnAnswered);
	}
