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



void insertTemp(output=memdump){
    tempdaten[];
    printData( Te923DataSet_t *data, char *iText ) {
      int i;
      printf( "%d:"  , data->timestamp );
      for ( i = 0; i <= 5; i++ ) {

        if ( data->_t[i] == 0 )
          printf( "%0.2f:", data->t[i] );
        else
          printf( "%s:", iText );

        if ( data->_h[i] == 0 )
          printf( "%d:", data->h[i] );
        else
          printf( "%s:", iText );
      }
      if ( data->_uv == 0 )
        printf( "%0.2f:", data->uv );
      else
        printf( "%s:", iText );

      if ( data->_wChill == 0 )
        printf( "%0.2f:", data->wChill );
      else
        printf( "%s:", iText );

      printf( "\n" );
    }
}
void insertTemp(output=memdump){
    datensauge[];
    printData( Te923DataSet_t *data, char *iText ) {
  int i;
  printf( "%d:"  , data->timestamp );

  if ( data->_press == 0 )
    printf( "%0.1f:", data->press );
  else
    printf( "%s:", iText );
  if ( data->_forecast == 0 )
    printf( "%d:", data->forecast );
  else
    printf( "%s:", iText );
  if ( data->_RainCount == 0 )
    printf( "%d", data->RainCount );
  else
    printf( "%s:", iText );

  printf( "\n" );
    }
}

oid printData( Te923DataSet_t *data, char *iText ) {
  int i;
  printf( "%d:"  , data->timestamp );
  for ( i = 0; i <= 5; i++ ) {

    if ( data->_t[i] == 0 )
      printf( "%0.2f:", data->t[i] );
    else
      printf( "%s:", iText );

    if ( data->_h[i] == 0 )
      printf( "%d:", data->h[i] );
    else
      printf( "%s:", iText );
  }

  if ( data->_press == 0 )
    printf( "%0.1f:", data->press );
  else
    printf( "%s:", iText );

  if ( data->_uv == 0 )
    printf( "%0.1f:", data->uv );
  else
    printf( "%s:", iText );

  if ( data->_forecast == 0 )
    printf( "%d:", data->forecast );
  else
    printf( "%s:", iText );

  if ( data->_storm == 0 )
    printf( "%d:", data->storm );
  else
    printf( "%s:", iText );

  if ( data->_wDir == 0 )
    printf( "%d:", data->wDir );
  else
    printf( "%s:", iText );

  if ( data->_wSpeed == 0 )
    printf( "%0.1f:", data->wSpeed );
  else
    printf( "%s:", iText );

  if ( data->_wGust == 0 )
    printf( "%0.1f:", data->wGust );
  else
    printf( "%s:", iText );

  if ( data->_wChill == 0 )
    printf( "%0.1f:", data->wChill );
  else
    printf( "%s:", iText );

  if ( data->_RainCount == 0 )
    printf( "%d", data->RainCount );
  else
    printf( "%s:", iText );

  printf( "\n" );
}

oid printData( Te923DataSet_t *data, char *iText ) {
  int i;
  printf( "%d:"  , data->timestamp );
  for ( i = 0; i <= 5; i++ ) {

    if ( data->_t[i] == 0 )
      printf( "%0.2f:", data->t[i] );
    else
      printf( "%s:", iText );

    if ( data->_h[i] == 0 )
      printf( "%d:", data->h[i] );
    else
      printf( "%s:", iText );
  }

  if ( data->_press == 0 )
    printf( "%0.1f:", data->press );
  else
    printf( "%s:", iText );

  if ( data->_uv == 0 )
    printf( "%0.1f:", data->uv );
  else
    printf( "%s:", iText );

  if ( data->_forecast == 0 )
    printf( "%d:", data->forecast );
  else
    printf( "%s:", iText );

  if ( data->_storm == 0 )
    printf( "%d:", data->storm );
  else
    printf( "%s:", iText );

  if ( data->_wDir == 0 )
    printf( "%d:", data->wDir );
  else
    printf( "%s:", iText );

  if ( data->_wSpeed == 0 )
    printf( "%0.1f:", data->wSpeed );
  else
    printf( "%s:", iText );

  if ( data->_wGust == 0 )
    printf( "%0.1f:", data->wGust );
  else
    printf( "%s:", iText );

  if ( data->_wChill == 0 )
    printf( "%0.1f:", data->wChill );
  else
    printf( "%s:", iText );

  if ( data->_RainCount == 0 )
    printf( "%d", data->RainCount );
  else
    printf( "%s:", iText );

  printf( "\n" );
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
