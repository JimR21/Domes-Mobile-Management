/***************************************************************************************
Arxeio Epikefalidas	: OuraPlus.h
Syggrafeas			: Y. Cotronis
Skopos			    : 
  O typos ATD OuraPlus symperiferetai ws oura (3 basikes praxeis): 
     a) stoixeia eisagontai sto telos
     b) stoixeia exagontai apo thn arxh
     c) elegxoume gia kenh
   Epipleon omws mporoume
     d) na kini9oume se olh thn oura (prwtos, teleytaios, epomenos, proigoumenos)
     e) na doume kai na allaxoume to periexomeno tou trexontos stoixeiou
     f) na diagrapsoume ton trexonta kombo
     g) na anazhthsoume stoixeio me kapoio krithrio isothtas 
     
   Ylopoieitai me Olikh apokrypsi 
     h) dimiourgia kai katastrofi
     
Ana8ewrhsh:             
****************************************************************************************/
#ifndef __OuraPlus__ 
#define __OuraPlus__
#include "TStoixeiouOuraPlus.h"

/*dhlwseis typou*/
typedef struct GeneralNode *TOuraPlus;

/*dhlwseis synarthsewn*/

/*dhmioyrgia kai katastrofh ouraPs*/
void OuraPlus_dimiourgia(TOuraPlus * const ouraP);

void OuraPlus_katastrofi(TOuraPlus *const ouraP);

/*prakseis elegxoy*/
int	OuraPlus_keni(const TOuraPlus ouraP);

int OuraPlus_megethos(const TOuraPlus ouraP);

/*prakseis prosbashs-allazei to Current*/
int OuraPlus_periexomenoTrexon(const TOuraPlus ouraP, TStoixeiouOuraPlus * const value); /* error if Current invalid */

int OuraPlus_allagiTrexon(const TOuraPlus ouraP, TStoixeiouOuraPlus stoixeio); /* error if Current invalid */

/*prakseis eisagwgh-diagrafh Current */
int OuraPlus_eisagogiTelos(const TOuraPlus ouraP, TStoixeiouOuraPlus stoixeio); /* panta sto telos */

int OuraPlus_exagogiArxh(const TOuraPlus ouraP); /*  panta apo thn arxh  */ 

int OuraPlus_diagrafiTrexon(const TOuraPlus ouraP); /* apo apoydhpote (Current) */

/* Epilogh Kombou Current */
int OuraPlus_epomenos(const TOuraPlus ouraP); /* if noNext no move + error */

int OuraPlus_proigoymenos(const TOuraPlus ouraP); /* if noPrev no move + error*/

int OuraPlus_prwtos(const TOuraPlus ouraP); /* to First - if empty error */

int OuraPlus_teleytaios(const TOuraPlus ouraP); /* to Last - if empty to Current=Last + error */

/*prakseis anazhthshs*/
int OuraPlus_anazitisi(const TOuraPlus ouraP, TStoixeiouOuraPlus stoixeio, 
                    int (*iso)(TStoixeiouOuraPlus , TStoixeiouOuraPlus));

int OuraPlus_delete(const TOuraPlus ouraP, char *number, int max);

int OuraPlus_allagh(const TOuraPlus ouraP, char *number1, char *number2, int max);
#endif /*#ifndef __GenList__ */
