#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h>

void readConfig()
{
    // open the file "SnakeData.json" in read mode
    File f = SPIFFS.open("/SnakeData.json", "r");

    if (f)
    {
        Serial.println("Got the SnakeData.json file");

        // put json in char buffer
        char json[400];
        while (f.available())
        {
            f.readBytes(json, 400);
            // print the json
            Serial.println(json);
        }

        // convert buffer to json object
        StaticJsonBuffer<600> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(json);
        if (!root.success())
        {
            Serial.println("parseObject() failed");
            return;
        }

        // get values
        const char *xenaName = root["snakes"][0]["name"];
        const char *xenaType = root["snakes"][0]["type"];
        double xenaTempMin = root["snakes"][0]["tempRange"][0];
        double xenaTempMax = root["snakes"][0]["tempRange"][1];
        int xenaHumidMin = root["snakes"][0]["humidRange"][0];
        int xenaHumidMax = root["snakes"][0]["humidRange"][1];

        const char *hanzoName = root["snakes"][1]["name"];
        const char *hanzoType = root["snakes"][1]["type"];
        double hanzoTempMin = root["snakes"][1]["tempRange"][0];
        double hanzoTempMax = root["snakes"][1]["tempRange"][1];
        int hanzoHumidMin = root["snakes"][1]["humidRange"][0];
        int hanzoHumidMax = root["snakes"][1]["humidRange"][1];

        const char *ioName = root["snakes"][2]["name"];
        const char *ioType = root["snakes"][2]["type"];
        double ioTempMin = root["snakes"][2]["tempRange"][0];
        double ioTempMax = root["snakes"][2]["tempRange"][1];
        int ioHumidMin = root["snakes"][2]["humidRange"][0];
        int ioHumidMax = root["snakes"][2]["humidRange"][1];

        Serial.println(xenaName);
        Serial.println(xenaType);
        Serial.println(xenaTempMin);
        Serial.println(xenaTempMax);
        Serial.println(xenaHumidMin);
        Serial.println(xenaHumidMax);
        Serial.println(hanzoName);
        Serial.println(hanzoType);
        Serial.println(hanzoTempMin);
        Serial.println(hanzoTempMax);
        Serial.println(hanzoHumidMin);
        Serial.println(hanzoHumidMax);
        Serial.println(ioName);
        Serial.println(ioType);
        Serial.println(ioTempMin);
        Serial.println(ioTempMax);
        Serial.println(ioHumidMin);
        Serial.println(ioHumidMax);
    }
    else
    {
        Serial.println("File doesn't exist.");
    }

    f.close();
}

void writeConfig()
{
    // open the file "SnakeData.json" in read mode
    File f = SPIFFS.open("/SnakeData.json", "r");

    if (f)
    {
        // open the file in write mode
        File f = SPIFFS.open("/SnakeData.json", "w");

        // put json in char buffer
        char json[300];
        while (f.available())
        {
            f.readBytes(json, 300);
        }

        // convert buffer to json object
        StaticJsonBuffer<500> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(json);
        if (!root.success())
        {
            Serial.println("parseObject() failed");
            return;
        }

        // change some config values
        root["snakes"][0]["tempRange"][0] = 100;
        root["snakes"][0]["tempRange"][1] = 200;
        root["snakes"][0]["humidRange"][0] = 300;
        root["snakes"][0]["humidRange"][1] = 400;

        // get string
        char buffer[400];
        root.prettyPrintTo(buffer, sizeof(buffer));

        // print new config
        Serial.print(buffer);

        // save to file
        while (f.available())
        {
            f.print(buffer);
        }
        
    }
    else
    {
        Serial.println("File doesn't exist.");
    }

    f.close();
}

void setup()
{
    Serial.begin(115200);

    // always use this to "mount" the filesystem
    bool result = SPIFFS.begin();
    Serial.println(" ");
    Serial.println(" ");
    Serial.print("SPIFFS opened: ");
    Serial.println(result);

    //SPIFFS.format();

    readConfig();
    writeConfig();
    readConfig();
}

void loop()
{
    // nothing to do for now, this is just a simple test
}