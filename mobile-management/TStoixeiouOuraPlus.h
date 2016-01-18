#ifndef __TStoixeiouOuraPlus_H__
#define __TStoixeiouOuraPlus_H__
typedef struct{
	int year, month, day;
}Fulldate;

typedef struct{
	int sec;
	char number[15];
	Fulldate date;
}TStoixeiouOuraPlus;

int TSOuraPlus_setValue (TStoixeiouOuraPlus *target, TStoixeiouOuraPlus source);
int TSOuraPlus_readValue (FILE *from,  TStoixeiouOuraPlus *Elem);
int TSOuraPlus_writeValue(FILE *to, TStoixeiouOuraPlus Elem);

int TSOuraPlus_iso(TStoixeiouOuraPlus Elem1, TStoixeiouOuraPlus Elem2);


#endif
