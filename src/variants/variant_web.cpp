#include "variant_web.h"

void setMode(Mode mode);

WiFiServer server(80);

void web_setup(){
    //connect to wifi, wifi ssid and passwords are saved in arduino_secrets.h file
    //#define SECRET_SSID "YOUR_SSID"
    //#define SECRET_PASS "YOUR_PASSWORD"
    WiFi.begin(SECRET_SSID,SECRET_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }

    server.begin();
    Serial.println(WiFi.localIP());
}

void web_loop(){
    WiFiClient client = server.available();

    if (client) {
        String request = client.readStringUntil('\r');

        if (request.indexOf("GET / ") != -1) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println();

            client.println("<html>");
            client.println("<body>");

            client.println("<h1>PCBA Tester</h1>");

            client.println("<a href=\"/test?id=1\"><button>2 Port Logic Analog AND</button></a>");
            client.println("<a href=\"/test?id=2\"><button>2 Port Logic Analog OR</button></a>");
            client.println("<a href=\"/test?id=3\"><button>Cycle Time</button></a>");
            client.println("<a href=\"/test?id=4\"><button>SIPO Test</button></a>");
            client.println("<a href=\"/test?id=5\"><button>Voltage Test</button></a>");
            client.println("<a href=\"/test?id=6\"><button>Connection Test</button></a>");
            client.println("<a href=\"/test?id=all\"><button>Run All Tests</button></a>");
            client.println("<a href=\"/test?id=serial\"><button>Serial Mode</button></a>");

            client.println("</body>");
            client.println("</html>");
        }

        else if (request.indexOf("/test?id=") != -1) {
            int start = request.indexOf("id=") + 3;
            int end = request.indexOf(" ", start);
            String number = request.substring(start, end);

            if(number == "serial"){
            setMode(serial);
            return;
        }
            String result = runTestByNumber(number);

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/plain");
            client.println();
            client.println(result);
        }

        client.stop();
    }
}