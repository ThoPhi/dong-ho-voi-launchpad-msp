/****************************************************/
//
//
//
//
//
//
/****************************************************/
#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )

unsigned char lastSecond;
unsigned char second, minute, hour, day, month;
unsigned int year;
unsigned dayInMonth[] = {
  31,28,31,30,31,30,31,31,30,31,30,31};

/********************* Clock Init *********************/
// Function Name:    clock_init()
// Parametter:       none
// Return value:     none
// Description:      Khoi tao cho dong ho
/****************************************************/
void clock_init(){
  second = 0;
  minute = 0;
  hour = 0;
  day = 20;
  month =12;
  year = 2012;
}

/********************* Clock Set *********************/
// Function Name:    clock_set()
// Parametter:       time
// Return value:     none
// Description:      
/****************************************************/
void clock_set(unsigned long time){
  second = time %60;
  time /= 60;
  minute = time % 60;
  time /= 60;
  hour = time %24;
  time /= 24;  
  year = 0;  
  unsigned int days = 0;
  while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
    year++;
  }  
  year += 1970; 
  days -= LEAP_YEAR(year) ? 366 : 365;
  time  -= days; // now it is days in this year, starting at 0  
  days=0;
  month=0;
  unsigned char monthLength=0;
  for (month=0; month<12; month++) {
    if (month==1) { // february
      if (LEAP_YEAR(year)) {
        monthLength=29;
      } 
      else {
        monthLength=28;
      }
    } 
    else {
      monthLength = dayInMonth[month];
    }

    if (time >= monthLength) {
      time -= monthLength;
    } 
    else {
      break;
    }
  }
  month = month + 1;  // jan is month 1  
  day = time + 1;     // day of month
}

/********************* Clock Increase *********************/
// Function Name:    clock_inc()
// Parametter:       none
// Return value:     none
// Description:      
/****************************************************/
void clock_inc(){
  second ++;
  if(second>=60){
    second =0;
    minute ++;
    if(minute >=60){
      minute =0;
      hour ++;
      if(hour >=24){
        hour=0;
        day ++;
        if(day > dayInMonth[month]){
          if(!LEAP_YEAR(year) || month != 1){
            day = 0;
            month++;
          }
          if(month>12){
            month = 0;
            year++;
          }
        }
      }
    }
  }
}

/*********************  *********************/
// Function Name:    processSyncMessage
// Parametter:       none
// Return value:     none
// Description:      
/****************************************************/
unsigned char getSecond(){
  return second;
}

/*********************  *********************/
// Function Name:    processSyncMessage
// Parametter:       none
// Return value:     none
// Description:      
/****************************************************/
unsigned char getMinute(){
  return minute;
}

/*********************  *********************/
// Function Name:    processSyncMessage
// Parametter:       none
// Return value:     none
// Description:      
/****************************************************/
unsigned char getHour(){
  return hour;
}

/*********************  *********************/
// Function Name:    processSyncMessage
// Parametter:       none
// Return value:     none
// Description:      
/****************************************************/
unsigned char getDay(){
  return day;
}

/*********************  *********************/
// Function Name:    processSyncMessage
// Parametter:       none
// Return value:     none
// Description:      
/****************************************************/
unsigned char getMonth(){
  return month;
}

/*********************  *********************/
// Function Name:    processSyncMessage
// Parametter:       none
// Return value:     none
// Description:      
/****************************************************/
unsigned int getYear(){
  return year;
}

