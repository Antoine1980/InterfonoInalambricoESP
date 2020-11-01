/*
 Name:		InterfonoLUZ_WifiAndo_ConLightSleep.ino
 Created:	10/19/2020 11:43:16 AM
 Author:	ainza
*/

#include <PubSubClient.h>
#include <ESP8266WiFi.h>

//definir las variables para la comunicacion Wifi
const char* ssid = "Livebox-00B5";
const char* pass = "5C0F66EA70CAA739A4321F5906";

//Y el sevidor de MQTT con cloudMQTT
const char* mqtt_server = "m21.cloudmqtt.com"; //Se puede realizar con ip, hacer ping al servidor y sabremos su IP
const int mqtt_port = 16369;  //Este puerrto necesuta usuario y contraseña para el acceso
char USER[50] = "bjnwhbwq";
char PASSWORD[50] = "6wjV4Beno-t9";


//Varaible de tipo Wificlient para la conexion a una red Wifi
WiFiClient espClient;

//Ajustar el cliente wifi como cliente MQTT
PubSubClient client(espClient);

//Variable para el mensaje que hay que enviar al CloudMQTT "topic + (mensage + valor)"
char msg[10];
int valor = 0;
//Pin donde recoge el sensor
const byte pinSonido = 2;
boolean detectadoTimbre;

void setup() {
    //Inicializacion comunicacion Serie
    Serial.begin(115600);

    //Ajuste de modo de pin
    pinMode(pinSonido, INPUT);


    //Inicializar conexiones, servicios, etc. del wifi y del MQTT
    gpio_init();
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);  //Mirar exactamente que hace y para que sirve, creo que es para mensajes que se mandan a la placa, ¿¿es decir subscripcion??

}

//Realizar la conexion al WIFI
void setup_wifi() {

    delay(10);
    // Empieza la conexion con la wifi
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    //Pasamos los datos de la wifi a la que hay que conectarse
    WiFi.mode(WIFI_STA);  //Poner el WIFI en modo estacion
    WiFi.begin(ssid, pass);
    //Espera mientras se conecta
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    //Conectado
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //PROBAR DESCONECTAR EL WIFI CUANDO NO ES NECESARIO CON wIFI.MODE(WIFI_OFF)
    //Turn off WiFi
    //WiFi.mode(WIFI_OFF);    //This also works
    //WiFi.forceSleepBegin(); //This also works
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    //Enciende el led si el primer valor es 1
    if ((char)payload[0] == '1') {
        Serial.println("Rele Encendido, llaman");
    }
    else {
        //digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
        Serial.println("Rele Apagado");
    }

}


// Intenta conectar con usuario y contraseña. Tambien se usa para reconnectar si se desconecta
void reconnect() {
    // Intenta conectar con usuario y contraseña. Tambien se usa para reconnectar si se desconecta
    while (!client.connected()) {
        Serial.print("Esperando conexion MQTT...");
        // Espera conexion, y le pasamos el usuario y contraseña de servidor cloudMQTT
        if (client.connect("ESP8266", USER, PASSWORD)) {
            Serial.println("Conectado");
            // una vez conectado, publicar anuncio...
            client.publish("Antoine-Timbre", "hello world");
            // ... and resubscribe
            //client.subscribe("inTopic");
        }
        else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" intenta de nuevo tras 5seg");
            // Esperar 5 segundos
            delay(5000);
        }
    }
}

//Configuracion para el LightSleep mode, y Mandar a dormir, LightSleep
void LightSleepESP() {
    client.disconnect();
    wifi_station_disconnect();
    WiFi.mode(WIFI_OFF);
    wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);  //Configirar el modo de Sleep en LIGHT_SLEEP
    wifi_fpm_open();      //Habilitar el modo de Sleep del ESP
    gpio_pin_wakeup_enable(GPIO_ID_PIN(pinSonido), GPIO_PIN_INTR_HILEVEL);
    wifi_fpm_do_sleep(0xFFFFFFF);   
}

//Envio comandos MQTT
void EnvioDatosMQTT() {
    //Activar Luz
    snprintf(msg, 10, "%ld", 1);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Antoine-Timbre/relay/0/set", msg); //Escribir el topic(Antoine-Timbre/relay/0/set) del servidor mqtt, y el valor a enviar msg(1)
    detectadoTimbre = true;
    delay(2000);
    //Desactivar luz
    snprintf(msg, 10, "%ld", 0);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("Antoine-Timbre/relay/0/set", msg); //Escribir el topic(Antoine-Timbre/relay/0/set) del servidor mqtt, y el valor a enviar msg(0)
    delay(2000);
}



void loop() {

   
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

        EnvioDatosMQTT();
        EnvioDatosMQTT();
    

    //Mandar a Dormir el ESP
    Serial.println("A dormir");
    LightSleepESP();
    delay(200);
    Serial.println("Espera a despertarse");
    setup_wifi();
}




