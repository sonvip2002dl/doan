#define BLINKER_WIFI
#include <Blinker.h>
#include "DHT.h"
#define DHTPIN 2       //DHT11 out引脚
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
float temperature=0.0;//当前温度数据
float humidity =0.0;  //当前湿度数据
float last_temp=0.0; //上一个温度数据
float last_humi=0.0; //上一个湿度数据
char auth[] = "XXXXXXX";    // key
char ssid[] = "XXXXXXX";    // wifi name 
char pswd[] = "XXXXXXX";    // wifi passpord 

// 新建组件对象
BlinkerButton Button1("btn-refresh");   //刷新
BlinkerButton Button2("btn-alarm");     //报警
BlinkerNumber Number1("num-tem");       //温度
BlinkerNumber Number2("num-hum");       //湿度

void dataRead(const String & data)
{
    Number1.print(temperature);
    Number2.print(humidity);
    Serial.println("dataRead更新数据");
}

void button1_callback(const String & state) {  //刷新温湿度数据
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    Number1.print(temperature);
    Number2.print(humidity); 
    Serial.print("Refresh温度:");
    Serial.print(temperature);
    Serial.print("湿度:");
    Serial.println(humidity);
}
void button2_callback(const String & state){
    Serial.println("Alarm");
}
void dataStorage()//建立存储数据对象 
{
    Blinker.dataStorage("num-tem", temperature);
    Blinker.dataStorage("num-hum", humidity);
}
void rtData() //开启实时数据
{
    Blinker.sendRtData("num-tem", temperature);
    Blinker.sendRtData("num-hum", humidity);
    Blinker.printRtData();
    Serial.print("rtData温度:");
    Serial.print(temperature);
    Serial.print("湿度:");
    Serial.println(humidity);
}
void heartbeat() //心跳包
{
    Blinker.print("num-tem", temperature);
    Blinker.print("num-hum", humidity);
    Serial.print("heartbeat温度:");
    Serial.print(temperature);
    Serial.print("湿度:");
    Serial.println(humidity);
  
}
void setup() {
    dht.begin();
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Blinker.attachHeartbeat(heartbeat);//注册心跳包 
    Blinker.attachData(dataRead);
    Blinker.attachRTData(rtData);
    Blinker.attachDataStorage(dataStorage);

}
void loop() 
{
  Blinker.run();
  Serial.println("Loop");
  temperature = dht.readTemperature();//获取温度
  humidity = dht.readHumidity();//获取湿度
  if(isnan(temperature)||isnan(humidity)) //判断是否为NAN
  {
    temperature = last_temp;
    humidity = last_humi;
  }else
  {
    last_temp = temperature;
    last_humi = humidity;
  }
  //警报
  if(humidity<30)
  {
    Button2.color("#87CEFA");
    Button2.text("轻度");
    Button2.print("on");
  }else if(humidity<50)
  {
    Button2.color("#4169E1");
    Button2.text("中度");
    Button2.print("on");
  }else if(humidity<80)
  {
    Button2.color("#191970");
    Button2.text("重度");
    Button2.print("on");
  }
  Blinker.delay(1000);
  
}
