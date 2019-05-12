import processing.serial.*;


Serial myport;
byte[] rx_buffer = new byte[132];
int[] sensorValue = new int[64];
String[] sensorValueStrs;
void setup(){
    size(400, 400);
    for(int i=0;i!=64;i++){
        sensorValue[i] = i*16;
    }
    noStroke();
    //myport = new Serial(this,"COM9",1000000);
    myport = new Serial(this,"/dev/cu.usbmodem1411",1000000);

    myport.clear();
    
}

void draw(){
    background(255);
    
    for(int i=0;i!=8;i++){
        for(int j=0;j!=8;j++){
            colorMode(HSB,1024);
            fill(color(sensorValue[i*8+j]/2, 1024, 1024));
            rect(i*50, j*50, 50, 50);
        }
    }
}

void serialEvent(Serial myport){
    String inbuffer = myport.readStringUntil('\n');
    if(inbuffer!=null){
        sensorValueStrs = inbuffer.split(",");
        if(sensorValueStrs.length==65){
            for(int i=0;i!=64;i++){
                sensorValue[i] = int(sensorValueStrs[i]);
            }
        }
    }
    
}
