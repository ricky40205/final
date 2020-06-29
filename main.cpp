#include "mbed.h"



//motor start
#define CENTER_BASE 1500
PwmOut servo_LEFT(D9);
PwmOut servo_RIGHT(D8);
//motot end
//Serial uart(D1, D0);
// ping

//DigitalInOut ping_origin(D10);
//parallax_ping  ping(ping_origin);
//parallax_encoder encoder( Din_11, encoder_ticker );

// XBee
/*
void background_Acc();
RawSerial pc(USBTX, USBRX);
RawSerial xbee(D12, D11);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

void xbee_setting(void);
void xbee_rx_interrupt(void);
void xbee_rx(void);
void reply_messange(char *xbee_reply, char *messange);
void check_addr(char *xbee_reply, char *messenger);
void classification();

void getLog(Arguments *in, Reply *out);
RPCFunction rpcLog(&getLog, "getLog");
*/
//encoder start 
DigitalIn encoder(D3);
DigitalOut stop(LED3);
Ticker encoder_ticker;
volatile int steps;
int dick = 0;
volatile int last;
//encoder end

//Serial pc(USBTX, USBRX);

int state_wait = 0;




void servo_control_LEFT(int speed){
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;
    servo_LEFT = (CENTER_BASE + speed)/20000.0f;
}


void servo_control_RIGHT(int speed){
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;
    servo_RIGHT = (CENTER_BASE + speed)/20000.0f;
}


void encoder_control(){
    int value = encoder;

    if(!last && value){
        steps++;
        dick++;
        }


    last = value;

}


//int stop = 0;

int main() {
        /*
    pc.baud(9600);
    xbee.baud(9600);
    uart.baud(9600);
    xbee_setting(); */

    servo_LEFT.period(.02);
    servo_RIGHT.period(.02);

    encoder_ticker.attach(&encoder_control, .001);

    steps = 0;
    last = 0;



    
    while(1) {
        //150m 
        if(dick <201){
            servo_control_LEFT(37);
            servo_control_RIGHT(-98); //right wheel is negative.
                       
        }
        
        //turn left
        else if(dick >=201 && dick < 223){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;
            }
            servo_control_LEFT(-70);
            servo_control_RIGHT(0); //right wheel is special.            
        }
        
        //mission one straight
        else if(dick >= 223 && dick <319){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        
        //turn right
        else if(dick >= 319 && dick <333){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(1);
                stop = 1;                
            }
            servo_control_LEFT(70);
            servo_control_RIGHT(70);            
        }
        
        //back parking
        else if(dick >= 333 && dick <390){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(-31);
            servo_control_RIGHT(100);            
        }
        
        //leave
        else if(dick >= 390 && dick <437){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        //turn left
        else if(dick >= 437 && dick <459){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(-70);
            servo_control_RIGHT(0);            
        }
        
        //forward ready to read num
        else if(dick >= 459 && dick <487){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }

        //turn right 
        else if(dick >= 487 && dick <512){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(70);
            servo_control_RIGHT(0);            
        }
        //move back a little 
        else if(dick >= 512 && dick <522){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(-31);
            servo_control_RIGHT(100);            
        }
        //straight
        else if(dick >= 522 && dick <532){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(5);
                stop = 0;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        

        //right
        else if(dick >= 532 && dick <556){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(70);
            servo_control_RIGHT(0);            
        }

        //straight
        else if(dick >= 556 && dick <637){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        
        //turn right enter road to mission 2
        else if(dick >= 637 && dick <651){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(70);
            servo_control_RIGHT(70);            
        }
        
        //150m
        else if(dick >= 651 && dick <830){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        
        //turn right 
        else if(dick >= 830 && dick <855){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(70);
            servo_control_RIGHT(0);            
        }
        
        //straight??
        else if(dick >= 855 && dick <910){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        
        //turn right for mission 2
        else if(dick >= 910 && dick <924){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(70);
            servo_control_RIGHT(70);            
        }

        else if(dick >= 924 && dick <949){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        
        //scan
        else if(dick >= 949 && dick <955){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(70);
            servo_control_RIGHT(0);            
        }
        else if(dick >= 955 && dick <958){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(-70);
            servo_control_RIGHT(0);            
        }

        //back
        else if(dick >= 958 && dick <978){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(1);
                stop = 1;                
            }
            servo_control_LEFT(-37);
            servo_control_RIGHT(99);            
        }
        
        
        else if(dick >= 978 && dick <1002){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(-70);
            servo_control_RIGHT(0);            
        }
        
        
        else if(dick >= 1002 && dick <1102){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        
        else if(dick >= 1102 && dick <1126){
            if(stop==1){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 0;                
            }
            servo_control_LEFT(70);
            servo_control_RIGHT(0);            
        }
        

        else if(dick >= 1126 && dick <1349){
            if(stop==0){
                servo_control_LEFT(0);
                servo_control_RIGHT(0);
                wait(0.5);
                stop = 1;                
            }
            servo_control_LEFT(37);
            servo_control_RIGHT(-98);            
        }
        
    


        else{
            servo_control_LEFT(0);
            servo_control_RIGHT(0);
        }

        wait(0.01);


    }
    


}

/*
void classification()
{
    float ping_dis[3];
    //scan
    if(dick >= 949 && dick <958){

        for(int i = 0; i < 4; i ++){
        ping_dis[i] = float(ping1);
        wait(0.25);
        }
                       
    }



    if(ping_dis[0] > ping_dis[1] && ping_dis[2] < ping_dis[3]) { //triangle
      xbee.printf("Triangle!!\r\n");
    }else if(ping_dis[0] == ping_dis[1] && ping_dis[1] == ping_dis[2] && ping_dis[2] == ping_dis[3]) { //rectangle
      xbee.printf("Rectangle!!\r\n");
    }else if(ping_dis[0] > ping_dis[1] && ping_dis[1] > ping_dis[2] && ping_dis[2] > ping_dis[3]) { //right triangle
      xbee.printf("Right Triangle!!\r\n");
    }else {
      xbee.printf("Tooth Pattern!!\r\n");
    }

    wait(2);
}

void getLog(Arguments *in, Reply *out){
    if(dick < 201){                         
        xbee.printf("go forward \r\n");          
    }else if(dick >= 201 && dick < 223){  
        xbee.printf("turn left\r\n");     
    }else if(dick >= 223 && dick <319){   
        xbee.printf("go forward \r\n");    
    }else if(dick >= 319 && dick < 333){  
        xbee.printf("turn right\r\n");         
    }else if(dick >= 333 && dick < 390){  
        xbee.printf("go backward\r\n");    
    }else if(dick >= 390 && dick < 437){  
        xbee.printf("go forward\r\n");  
    }else if(dick >= 437 && dick < 459){  
        xbee.printf("turn left\r\n");    
    }else if(dick >= 459 && dick < 487){  
        xbee.printf("go forward\r\n");    
    }else if(dick >= 487 && dick < 512){  
        xbee.printf("turn right and take a picture\r\n");
    }else if(dick >= 512 && dick < 522){  
        xbee.printf("go forward\r\n");                 
    }else if(dick >= 522 && dick < 532){ 
        xbee.printf("turn right\r\n");    
    }else if(dick >= 532 && dick < 556){ 
        xbee.printf("go forward to leave mission1\r\n");      
    }else if(dick >= 556 && dick < 637){ 
        xbee.printf("turn right\r\n");         
    }else if(dick >= 637 && dick < 651){  
        xbee.printf("go forward to start mission2\r\n");    
    }else if(dick >= 651 && dick < 830){  
        xbee.printf("turn right\r\n");      
    }else if(dick >= 830 && dick < 855){  
        xbee.printf("go forward to mission2\r\n");  
    }else if(dick >= 855 && dick < 910){  
        xbee.printf("turn right\r\n");
    }else if(dick >= 910 && dick < 924){  
        xbee.printf("go forward\r\n");   
    }else if(dick >= 924 && dick < 949){  
        xbee.printf("turn right scan\r\n");
    }else if(dick >= 949 && dick < 955){  
        xbee.printf("turn left scan\r\n");
    }else if(dick >= 955 && dick < 958){ 
        xbee.printf("go backward\r\n");    
    }else if(dick >= 958 && dick < 978){  
        xbee.printf("turn left\r\n");
    }else if(dick >= 1002 && dick < 1102){ 
        xbee.printf("go forward to leave mission2\r\n");
    }else if(dick >= 1102 && dick < 1126){ 
        xbee.printf("turn right\r\n");
    }else if(dick >= 1126 && dick < 1349){   
        xbee.printf("go forward to finish\r\n");   
    }else{
        xbee.printf("no action\r\n");
    }
}

void xbee_setting(){
    char xbee_reply[4];

    // XBee setting
    xbee.baud(9600);
    xbee.printf("+++");
    xbee_reply[0] = xbee.getc();
    xbee_reply[1] = xbee.getc();
    if(xbee_reply[0] == 'O' && xbee_reply[1] == 'K'){
        pc.printf("enter AT mode.\r\n");
        xbee_reply[0] = '\0';
        xbee_reply[1] = '\0';
    }
    xbee.printf("ATMY 0x262\r\n");
    reply_messange(xbee_reply, "setting MY : 0x262");

    xbee.printf("ATDL 0x162\r\n");
    reply_messange(xbee_reply, "setting DL : 0x162");

    xbee.printf("ATID 0x1\r\n");
    reply_messange(xbee_reply, "setting PAN ID : 0x1");

    xbee.printf("ATWR\r\n");
    reply_messange(xbee_reply, "write config");

    xbee.printf("ATMY\r\n");
    check_addr(xbee_reply, "MY");

    xbee.printf("ATDL\r\n");
    check_addr(xbee_reply, "DL");

    xbee.printf("ATCN\r\n");
    reply_messange(xbee_reply, "exit AT mode");
    xbee.getc();

    // start

  pc.printf("start\r\n");

  t.start(callback(&queue, &EventQueue::dispatch_forever));


  // Setup a serial interrupt function to receive data from xbee

  xbee.attach(xbee_rx_interrupt, Serial::RxIrq);
}

void xbee_rx_interrupt(void)

{

  xbee.attach(NULL, Serial::RxIrq); // detach interrupt

  queue.call(&xbee_rx);

}


void xbee_rx(void)

{

  static int i = 0;

  static char buf[100] = {0};

  while(xbee.readable()){

    char c = xbee.getc();

    if(c!='\r' && c!='\n'){

      buf[i] = c;

      i++;

      buf[i] = '\0';

    }else{

      i = 0;

      pc.printf("Get: %s\r\n", buf);

      xbee.printf("%s", buf);

    }

  }

  wait(0.1);

  xbee.attach(xbee_rx_interrupt, Serial::RxIrq); // reattach interrupt

}


void reply_messange(char *xbee_reply, char *messange){

  xbee_reply[0] = xbee.getc();

  xbee_reply[1] = xbee.getc();

  xbee_reply[2] = xbee.getc();

  if(xbee_reply[1] == 'O' && xbee_reply[2] == 'K'){

   pc.printf("%s\r\n", messange);

   xbee_reply[0] = '\0';

   xbee_reply[1] = '\0';

   xbee_reply[2] = '\0';

  }

}


void check_addr(char *xbee_reply, char *messenger){

  xbee_reply[0] = xbee.getc();

  xbee_reply[1] = xbee.getc();

  xbee_reply[2] = xbee.getc();

  xbee_reply[3] = xbee.getc();

  pc.printf("%s = %c%c%c\r\n", messenger, xbee_reply[1], xbee_reply[2], xbee_reply[3]);

  xbee_reply[0] = '\0';

  xbee_reply[1] = '\0';

  xbee_reply[2] = '\0';

  xbee_reply[3] = '\0';

}

*/