#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "te923con.h"
#include "te923usb.h"
#include "te923com.h"


unsigned short debug = FALSE;
unsigned short bigmem = TRUE;

enum output { rtdata, memdump, status };


/*
static char datetime, innenTemp, aussenTemp1, aussenTemp2, aussenTemp3, aussenTemp4, aussenTemp5, aussenHum1, aussenTemp2, aussenHum2, aussenTemp3, aussenHum3,
            aussenTemp4, aussenHum4, aussenTemp5, aussenHum5, luftdruck, uv, vorhersage, sturmwarnung, windrichtung, windgeschwindigkeit, boengeschwindigkeit,
            gefühlteTemp, regenmenge, ;
*/

void insertSpeicher(char memsql[count]){
    *output = memdump;
    char *str[], *query;
    char ptr = "', '";
    memsql = query;
    printf(%s, memsql);
    printData( Te923DataSet_t *data, char *iText ) {
    int i;
    str[0]= "INSERT INTO stationsdaten (datetime, innenTemp, innenHum, aussenTemp1, aussenHum1, aussenTemp2, aussenHum2, aussenTemp3, aussenHum3,"
            "aussenTemp4, aussenHum4, aussenTemp5, aussenHum5, luftdruck, uv, vorhersage, sturmwarnung, windrichtung, windgeschwindigkeit, boengeschwindigkeit,"
            "gefühlteTemp, regenmenge) VALUES ('";
    str[1] = data->timestamp;
    str[2] = ptr;
      for ( i = 0; i <= 5; i++ ) {
        char temp = "---";
        char hum = "---";
        if ( data->_t[i] == 0 )
             temp = data->t[i];
         else
            printf( "%s:", iText );

        if ( data->_h[i] == 0 )
             hum = data->h[i];
         else
            printf( "%s:", iText );
        
        for(int e = 3; e <= 9 ; e++)
            str[e] = strcat(temp+ptr+hum+ptr);
      }

      if ( data->_press == 0 )
        str[9] = data->press;
        str[10] = ptr;
      else
        printf( "%s:", iText );

      if ( data->_uv == 0 )
        str[11] = data->uv;
        str[12] = ptr;
      else
        printf( "%s:", iText );

      if ( data->_forecast == 0 )
        str[13] = data->forecast;
        str[14] = ptr;
      else
        printf( "%s:", iText );

      if ( data->_storm == 0 )
        str[15] = data->storm ;
        str[16] = ptr;
      else
        printf( "%s:", iText );

      if ( data->_wDir == 0 )
        str[17] = data->wDir;
        str[18] = ptr;
      else
        printf( "%s:", iText );

      if ( data->_wSpeed == 0 )
        str[19] = data->wSpeed;
        str[20] = ptr;
      else
        printf( "%s:", iText );

      if ( data->_wGust == 0 )
        str[21] data->wGust;
        str[22] = ptr;
      else
        printf( "%s:", iText );

      if ( data->_wChill == 0 )
        str[23] = data->wChill;
        str[24] = ptr;
      else
        printf( "%s:", iText );

      if ( data->_RainCount == 0 )
        str[25] data->RainCount;
        str[26] = "'); \0";
      else
        printf( "%s:", iText );




    for (i=0; i < 26; i++){
        size+=strlen(str[i]);   /* Speicherplatz für den Anfragestring reservieren */
        query = malloc(size + 1);
        strcpy(query, str[0]);
        for(i = 1; i < 9; i++){
            strcat(query, str[i]);
        }
    }
}


  if ( iText == NULL )
    iText = "i";

  struct usb_dev_handle *devh;
  devh = te923_handle();
  if ( devh == NULL )
    return 1;

  if (debug > 0)
    printf("[DEBUG] VER %s\n",VERSION);

  if ( ( output == rtdata ) || ( output == memdump ) ) {
    Te923DataSet_t *data;
    data = ( Te923DataSet_t* )malloc( sizeof( Te923DataSet_t ) );
    memset ( data, 0, sizeof ( Te923DataSet_t ) );
    if ( output == rtdata ) {
      get_te923_lifedata( devh, data );
      printData( data, iText);
    }
    if ( output == memdump ) {
      int i;
      int count;
      count = 208;
      if ( bigmem == TRUE ) {
	count = 3442;
      }
      for ( i = 0; i < count; i++ ) {
	get_te923_memdata( devh, data, bigmem );
	printData( data, iText);
      }
    }
  }

  if ( output == status ) {
    Te923DevSet_t *status;
    status = ( Te923DevSet_t* )malloc( sizeof( Te923DevSet_t ) );
    get_te923_devstate( devh, status );
    printf( "0x%x:0x%x:0x%x:0x%x:0x%x:%d:%d:%d:%d:%d:%d:%d:%d\n",
	    status->SysVer, status->BarVer, status->UvVer, status->RccVer, status->WindVer,
	    status->batteryRain, status->batteryUV, status->batteryWind, status->battery5,
	    status->battery4, status->battery3, status->battery2, status->battery1
	    );
  }

  te923_close( devh );
