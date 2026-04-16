#include "variant_web.h"


WiFiServer server(80);

void web_setup(){
    
    WiFi.beginAP("PCBA_Tester");
    server.begin();
    Serial.println("WiFi AP started.");
    Serial.println("Connect to WiFi network: PCBA_Tester");
    Serial.print("Then open browser and go to: http://");
    Serial.println(WiFi.localIP());
}

void web_loop(){
    WiFiClient client = server.available();
    if (!client) return;

    String request = client.readStringUntil('\r');

    if (request.indexOf("GET / ") != -1) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        client.println("<html><body>");
        client.println("<h1>PCBA Tester</h1>");
        client.println("<a href=\"/test?id=1\"><button>OR gate analog</button></a>");
        client.println("<a href=\"/test?id=2\"><button>AND gate analog</button></a>");
        client.println("<a href=\"/test?id=3\"><button>Cycle time</button></a>");
        client.println("<a href=\"/test?id=4\"><button>SIPO test</button></a>");
        client.println("<a href=\"/test?id=5\"><button>Voltage test</button></a>");
        client.println("<a href=\"/test?id=6\"><button>Connection test</button></a>");
        client.println("<a href=\"/test?id=all\"><button>Run all tests</button></a>");
        client.println("</body></html>");
    } else if (request.indexOf("/test?id=") != -1) {
        int start = request.indexOf("id=") + 3;
        int end = request.indexOf(" ", start);
        String number = request.substring(start, end);

        String result = runTestByNumber(number);

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/plain");
        client.println();
        client.println(result);
    }

    client.stop();

}