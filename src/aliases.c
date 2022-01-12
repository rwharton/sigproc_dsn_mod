#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <string.h>

/* returns the correct TEMPO site code given SIGPROC's telescope_id */
char tempo_site(int telescope_id) /*includefile*/
{
  switch (telescope_id) {
  case 0:
    return('3');
    break;
  case 1:
    return('3'); /*AO*/
    break;
  case 3:
    return('f'); /*Nancay*/
    break;
  case 4:
    return('7'); /*Parkes*/
    break;
  case 5:
    return('8'); /*Jodrell*/
    break;
  case 6:
    return('1'); /*GBT*/
    break;
  case 7:
    return('r'); /*GMRT*/
    break;
  case 8:
    return('g'); /*Effelsberg*/
    break;
  case 9:
    return('a'); /*140ft*/
    break;
  case 10:
    return('z'); /*SRT*/
    break;
  case 11:
    return('t'); /*LOFAR*/
    break;
  case 12:
    return('n'); /*CANBERRA*/
    break;
  case 13:
    return('k'); /*GOLDSTONE*/
    break;
  case 14:
    return('j'); /*ROBLEDO*/
    break;
  case 15:
    return('6'); /*VLA*/
    break;
  case 20:
    return('y'); /*CHIME*/
    break;
  case 21:
    return('0'); /*FAST*/
    break;
  case 64:
    return('q'); /*MeerKAT*/
    break;
  default:
    return('?'); /*unknown*/
    /*error_message("tempo_site: unknown telescope!");*/
    break;
  }
}

char *telescope_name (int telescope_id) /*includefile*/
{
  char *telescope,string[80];
  switch (telescope_id) {
  case 0: 
    strcpy(string,"Fake");
    break;
  case 1: 
    strcpy(string,"Arecibo");
    break;
  case 2: 
    strcpy(string,"Ooty");
    break;
  case 3: 
    strcpy(string,"Nancay");
    break;
  case 4: 
    strcpy(string,"Parkes");
    break;
  case 5: 
    strcpy(string,"Jodrell");
    break;
  case 6: 
    strcpy(string,"GBT");
    break;
  case 7: 
    strcpy(string,"GMRT");
    break;
  case 8: 
    strcpy(string,"Effelsberg");
    break;
  case 9: 
    strcpy(string,"140ft");
    break;
  case 10: 
    strcpy(string,"SRT");
    break;
  case 11: 
    strcpy(string,"LOFAR");
    break;
  case 12: 
    strcpy(string,"CANBERRA");
    break;
  case 13: 
    strcpy(string,"GOLDSTONE");
    break;
  case 14: 
    strcpy(string,"ROBLEDO");
    break;
  case 15: 
    strcpy(string,"VLA");
    break;
  case 20: 
    strcpy(string,"CHIME");
    break;
  case 21: 
    strcpy(string,"FAST");
    break;
  case 64:
    strcpy(string,"MeerKAT");
    break;
  case 82:
    strcpy(string,"eMerlin");
    break;
 
  default: 
    strcpy(string,"???????"); 
    break;
  }
  telescope=(char *) malloc(strlen(string));
  strcpy(telescope,string);
  return(telescope);
}
char *backend_name (int machine_id) /*includefile*/
{
  char *backend, string[80];
  switch (machine_id) {
  case 0:
    strcpy(string,"FAKE");
    break;
  case 1:
    strcpy(string,"PSPM");
    break;
  case 2:
    strcpy(string,"WAPP");
    break;
  case 3:
    strcpy(string,"AOFTM");
    break;
  case 4:
    strcpy(string,"BPP");
    break;
  case 5:
    strcpy(string,"OOTY");
    break;
  case 6:
    strcpy(string,"SCAMP");
    break;
  case 7:
    strcpy(string,"GMRTFB");
    break;
  case 8:
    strcpy(string,"PULSAR2000");
    break;
  case 9:
    strcpy(string,"PARSPEC");
    break;
  case 10:
    strcpy(string,"BPSR");
    break;
  case 14:
    strcpy(string,"GMRTNEW");
    break;
  case 64:
    strcpy(string,"KAT");
    break;
  case 65:
    strcpy(string,"KAT-DC2");
    break;
  case 82:
    strcpy(string,"loft-e");
    break;
  case 83:
    strcpy(string,"ROACH");
    break;
  case 88:
    strcpy(string,"AT-PAF");
    break;
  default:
    strcpy(string,"?????");
    break;
  }
  backend=(char *) malloc(strlen(string));
  strcpy(backend,string);
  return(backend);
}
char *data_category (int data_type) /*includefile*/
{
  char *datatype, string[80];
  switch (data_type) {
  case 0:
    strcpy(string,"raw data");
    break;
  case 1:
    strcpy(string,"filterbank");
    break;
  case 2:
    strcpy(string,"time series");
    break;
  case 3:
    strcpy(string,"pulse profiles");
    break;
  case 4:
    strcpy(string,"amplitude spectrum");
    break;
  case 5:
    strcpy(string,"complex spectrum");
    break;
  case 6:
    strcpy(string,"dedispersed subbands");
    break;
  default:
    strcpy(string,"unknown!");
    break;
  }
  datatype=(char *) malloc(strlen(string));
  strcpy(datatype,string);
  return(datatype);
}
