#include <WiFi.h>


//network details
char* ssid = "Skeletron:D";
char* password = "87654321";

//webpage to be served to client
char* html = R""""(
  <!DOCTYPE html>
<html>
    <head>
        <meta name="viewport" content="width=device-width, intial-scale=1, minimum-scale=0.1, maximum-scale=10 user-scalable=1">
        <meta name="Description" content="Controlling esp32 using wifi through http query to webserver(esp32)">
    </head>

    <body>
        <h1>esp32 Controls</h1>
        <a href="/?led=1&;"><button>Led On</button></a>
    </body>
</html>
)"""";

//acknowledgment to be sent after request has been read
void accept(NetworkClient client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
}

//setup up webserver port 80 (default port of http)
WiFiServer server(80);   

//can be used for timeout feature
unsigned long current_time = millis();
unsigned long previous_time = 0;
unsigned long connection_timeout = 5000; //5 seconds

int led_status = 0;


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN,LOW);

  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.println("\nConnecting to Wifi...");
  }

  Serial.println("Connected To Wifi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}



void loop() {
  int count = 0;
  NetworkClient client = server.accept();
  String current_line = ""; //every line of http request
  if(client)
  {
    while(client.connected())
    {
      if(client.available())
      {
        // Serial.print(++count);
        // Serial.print(" ");
        char read = client.read();
        Serial.write(read);
        // http request ends with a '\n' '\n'
         if(read == '\n')
         {
          // ie the http request has been read, send acknowledgment
          //lenght will be zero when it reads the penultimate '\n'
          //gets reset to 0 and then reads '/n' again

              if(current_line.length() == 0)
              {
                Serial.write("send webpage");
                accept(client); //acknowledgment
                client.print(html); //send back html webpage back to client
              }
              //check for get request after the webpage has been sent
              else if(current_line.endsWith("GET /?led=1&; HTTP/1.1"))
              {
                if(!led_status)
                {
                  digitalWrite(LED_BUILTIN, HIGH);
                  led_status = 1;
                }
                else
                {
                  digitalWrite(LED_BUILTIN, LOW);
                  led_status = 0;
                }
              }
              current_line="";
          }
          else if(read != '\r')
          {
             current_line += read; //append if not a newline character;
          }
      }
    }
  }
}

