#ifdef USE_WIFI

#include "variant_web.h"

WiFiServer server(80);

// ============================================================
// CSS
// ============================================================

static void sendCSS(WiFiClient& client) {
    client.println("<style>");
    client.println("*{box-sizing:border-box}");
    client.println("html,body{height:100%;margin:0;padding:0}");
    client.println("body{font-family:Arial,sans-serif;background:#1e1e2e;color:#cdd6f4;padding:24px}");
    client.println("h1{color:#cba6f7;text-align:center;font-size:3em;margin-bottom:32px}");
    client.println(".grid{display:grid;grid-template-columns:repeat(2,1fr);gap:16px;max-width:900px;height:60vh;margin:0 auto 16px}");
    client.println(".btn{border:none;border-radius:12px;font-size:1.6em;font-weight:bold;background:#313244;color:#cdd6f4;text-decoration:none;text-align:center;display:flex;align-items:center;justify-content:center}");
    client.println(".btn-all{background:#cba6f7;color:#1e1e2e;font-weight:bold;font-size:1.8em;border-radius:12px;text-decoration:none;display:flex;align-items:center;justify-content:center;max-width:900px;height:10vh;margin:0 auto}");
    client.println(".back{display:inline-block;margin-top:20px;padding:14px 28px;background:#313244;color:#cdd6f4;border-radius:8px;text-decoration:none;font-size:1.2em}");
    client.println(".card{background:#313244;border-radius:10px;padding:24px;max-width:700px;margin:0 auto}");
    client.println(".title{font-size:1.8em;font-weight:bold;margin-bottom:14px}");
    client.println(".pass{color:#a6e3a1}");
    client.println(".fail{color:#f38ba8}");
    client.println(".details{background:#1e1e2e;border-radius:6px;padding:16px;margin-top:14px;font-family:monospace;font-size:1.5em;white-space:pre-wrap}");
    client.println(".prompt{background:#45475a;border-radius:6px;padding:16px;margin-bottom:12px;font-size:1.2em;color:#cdd6f4}");
    client.println(".badge{padding:6px 18px;border-radius:20px;font-size:1em;font-weight:bold}");
    client.println(".bp{background:#a6e3a1;color:#1e1e2e}");
    client.println(".bf{background:#f38ba8;color:#1e1e2e}");
    client.println("details{background:#313244;border-radius:10px;margin-bottom:10px;overflow:hidden}");
    client.println("summary{display:flex;justify-content:space-between;align-items:center;padding:14px 18px;background:#1e1e2e;font-size:1.3em;font-weight:bold;color:#cdd6f4;cursor:pointer;list-style:none}");
    client.println("summary::-webkit-details-marker{display:none}");
    client.println("summary:hover span:first-child{color:#6c7086}");
    client.println(".detail-body{padding:16px;font-family:monospace;font-size:1.2em;white-space:pre-wrap;color:#cdd6f4}");
    client.println("</style>");
}

// ============================================================
// SHARED HEADER (HTTP headers + <head> + CSS)
// ============================================================

static void sendHeaders(WiFiClient& client, const char* title) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html; charset=utf-8");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE html><html><head>");
    client.println("<meta charset=\"utf-8\">");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.print("<title>");
    client.print(title);
    client.println("</title>");
    sendCSS(client);
    client.println("</head><body>");
    client.println("<h1>PCBA Tester</h1>");
}

// ============================================================
// PAGES
// ============================================================

static void sendMainPage(WiFiClient& client) {
    sendHeaders(client, "PCBA Tester");
    client.println("<div class=\"grid\">");
    for (int i = 0; i < TEST_COUNT; i++) {
        client.print("<a href=\"/test?id=");
        client.print(i + 1);
        client.print("\" class=\"btn\">");
        client.print(TEST_REGISTRY[i].name);
        client.println("</a>");
    }
    client.println("</div>");
    client.println("<a href=\"/test?id=all\" class=\"btn-all\">&#9654; Run All Tests</a>");
    client.println("</body></html>");
}

static void sendAllResults(WiFiClient& client) {
    sendHeaders(client, "All Results");
    client.println("<div class=\"card\">");
    for (int i = 0; i < TEST_COUNT; i++) {
        if (strcmp(TEST_REGISTRY[i].name, "Button test") == 0) {
            client.println("<div class=\"prompt\">&#9654; Press the button within 5 seconds...</div>");
            client.flush();
        }
        TestResult r = TEST_REGISTRY[i].run();
        client.println("<details>");
        client.println("<summary>");
        client.print("<span>");
        client.print(r.test_name);
        client.println("</span>");
        if (r.passed)
            client.println("<span class=\"badge bp\">PASS &#8250;</span>");
        else
            client.println("<span class=\"badge bf\">FAIL &#8250;</span>");
        client.println("</summary>");
        client.print("<div class=\"detail-body\">");
        client.print(r.details);
        client.println("</div>");
        client.println("</details>");
    }
    client.println("</div>");
    client.println("<div style=\"text-align:center\">");
    client.println("<a href=\"/\" class=\"back\">&#8592; Back to Tests</a>");
    client.println("</div></body></html>");
}

static void sendSingleResult(WiFiClient& client, int id) {
    sendHeaders(client, "Test Result");
    if (id >= 0 && id < TEST_COUNT) {
        if (strcmp(TEST_REGISTRY[id].name, "Button test") == 0) {
            client.println("<div class=\"card\">");
            client.println("<div class=\"title\">Button Test</div>");
            client.println("<div class=\"prompt\">&#9654; Press the button within 5 seconds...</div>");
            client.println("</div>");
            client.flush();
        }
        TestResult r = TEST_REGISTRY[id].run();
        client.println("<div class=\"card\">");
        client.print("<div class=\"title ");
        client.print(r.passed ? "pass" : "fail");
        client.print("\">");
        client.print(r.test_name);
        client.print(" &#8212; ");
        client.println(r.passed ? "PASSED" : "FAILED");
        client.println("</div>");
        client.print("<div class=\"details\">");
        client.print(r.details);
        client.println("</div>");
        client.println("</div>");
    } else {
        client.println("<div class=\"card\"><p>Invalid test ID.</p></div>");
    }
    client.println("<div style=\"text-align:center\">");
    client.println("<a href=\"/\" class=\"back\">&#8592; Back to Tests</a>");
    client.println("</div></body></html>");
}

// ============================================================
// ROUTER
// ============================================================

static void handleRequest(WiFiClient& client, String& request) {
    if (request.indexOf("GET / ") != -1) {
        sendMainPage(client);
    } else if (request.indexOf("/test?id=") != -1) {
        int start = request.indexOf("id=") + 3;
        int end   = request.indexOf(" ", start);
        String number = request.substring(start, end);

        if (number.equalsIgnoreCase("all")) {
            sendAllResults(client);
        } else {
            int id = number.toInt() - 1;
            sendSingleResult(client, id);
        }
    }
}

// ============================================================
// SETUP & LOOP
// ============================================================

void web_setup() {
    WiFi.beginAP("PCBA_Tester");
    delay(2000);
    server.begin();
    Serial.println("WiFi AP started.");
    Serial.println("Connect to WiFi network: PCBA_Tester");
    Serial.print("Then open browser and go to: http://");
    Serial.println(WiFi.localIP());
}

void web_loop() {
    WiFiClient client = server.available();
    if (!client) return;

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 2000) {
            client.stop();
            return;
        }
    }

    String request = "";
    while (client.available()) {
        char c = client.read();
        if (c == '\n') break;
        request += c;
    }
    Serial.println("Request: [" + request + "]");

    handleRequest(client, request);

    client.flush();
    client.stop();
}

#endif // USE_WIFI