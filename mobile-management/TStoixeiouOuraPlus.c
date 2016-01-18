#include <stdio.h>
#include <string.h>
#include "TStoixeiouOuraPlus.h"



int TSOuraPlus_setValue (TStoixeiouOuraPlus *target, TStoixeiouOuraPlus source){
	*target=source;
}

int TSOuraPlus_readValue (FILE *from, TStoixeiouOuraPlus *ElemPtr){
     return fscanf(from, "%d/%d/%d %d %s", &ElemPtr->date.day, &ElemPtr->date.month, &ElemPtr->date.year, &ElemPtr->sec, ElemPtr->number);
}

int TSOuraPlus_writeValue(FILE *to, TStoixeiouOuraPlus Elem){
	fprintf(to, "%02d/%02d/%d %d %s\n", Elem.date.day, Elem.date.month, Elem.date.year, Elem.sec, Elem.number);
}

int TSOuraPlus_iso(TStoixeiouOuraPlus Elem1, TStoixeiouOuraPlus Elem2){
	if(Elem1.date.year == Elem2.date.year){
		if(Elem1.date.month == Elem2.date.month){
			if(Elem1.date.day == Elem2.date.day)
			   return 1;
			}
		}
		return 0;
}


