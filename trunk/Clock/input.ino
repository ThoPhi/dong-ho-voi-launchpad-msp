/****************************************************/
//
//
//
//
//
//
/****************************************************/

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by unix time_t as ten ascii digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

/*********************  *********************/
// Ham doc cac lenh tu com de dieu khien
/****************************************************/
void read_serial(){
  unsigned char tmpinput;
  if(Serial.available()){
     tmpinput = Serial.read();
     switch(tmpinput){
       case 'a':
       
       break;
       case 'b':
       default: break;
     }
  }
}

/*********************  *********************/
// Hien chua co nút nhấn, se thay the bang nut touch
// Function Name:    processSyncMessage
// Parametter:       none
// Return value:     none
// Description:      
/****************************************************/
void read_button(){
  
}

/********************* SYNC MESSAGE *********************/
// Function Name:    processSyncMessage
// Parametter:       none
// Return value:     none
// Description:      Ham dong bo voi chuong trinh chinh gio tren may tinh
/****************************************************/
void processSyncMessage() {
  // if time sync available from serial port, update time and return true
  while(Serial.available() >=  TIME_MSG_LEN ){  // time message consists of a header and ten ascii digits
    char c = Serial.read() ; 
    Serial.print(c);  
    if( c == TIME_HEADER ) {       
      unsigned long pctime = 0;
      for(int i=0; i < TIME_MSG_LEN -1; i++){   
        c = Serial.read();          
        if( c >= '0' && c <= '9'){   
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
        }
      }   
      clock_set(pctime);   // Sync Arduino clock to the time received on the serial port
    }  
  }
}
