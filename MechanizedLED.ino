#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Thejas A12"; // CHANGE IT
const char* password = "Abcd@1234"; // CHANGE IT 

WebServer server(80);

const int ledPins[10] = {2, 4, 5, 12, 13, 14, 15, 18, 19, 21}; // Assign GPIO pins for LEDs
const char* letters = "MECHANIZED"; // Map to corresponding letters

void blinkLED(int pin) {
    digitalWrite(pin, LOW); // Ensure it's off before blinking
    delay(200);

    for (int i = 0; i < 3; i++) { // Blinking pattern
        digitalWrite(pin, HIGH);
        delay(200);
        digitalWrite(pin, LOW);
        delay(200);
    }

    digitalWrite(pin, LOW); // Stay ON after blinking
}

void handleRoot() {
    server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Mechanized</title>
        <style>
            body {
                background-image: url('https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/Bg.jpg');
                background-size: cover;
                background-position: center;
                text-align: center;
                font-family: Arial, sans-serif;
            }

            #logo {
                width: 400px;
                height: auto;
                margin-bottom: 20px;
            }

            .button-container {
                display: grid;
                grid-template-columns: repeat(5, minmax(80px, 1fr));
                gap: 10px;
                justify-content: center;
                align-items: center;
                width: 80%;
                margin: auto;
            }

            .letter-btn {
                background-color: transparent;
                border: none;
                cursor: pointer;
                width: 100px;
                height: 100px;
            }

            .letter-btn img {
                width: 100%;
                max-width: 100px;
                height: auto;
            }

            @media (max-width: 600px) {
                .button-container {
                    grid-template-columns: repeat(5, 1fr);
                }
                .letter-btn {
                    width: 60px;
                    height: 60px;
                }
            }

            @media (max-width: 400px) {
                .button-container {
                    grid-template-columns: repeat(5, 1fr);
                }
                .letter-btn {
                    width: 50px;
                    height: 50px;
                }
            }
        </style>
    </head>
    <body>
        <img id="logo" src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/Mechanized.png" alt="Mechanized Logo">

        <div class="button-container">
            <button class="letter-btn" id="M" onclick="toggle('M')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/M_off.png" id="M_img">
            </button>
            <button class="letter-btn" id="E" onclick="toggle('E')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/E_off.png" id="E_img">
            </button>
            <button class="letter-btn" id="C" onclick="toggle('C')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/C_off.png" id="C_img">
            </button>
            <button class="letter-btn" id="H" onclick="toggle('H')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/H_off.png" id="H_img">
            </button>
            <button class="letter-btn" id="A" onclick="toggle('A')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/A_off.png" id="A_img">
            </button>
            <button class="letter-btn" id="N" onclick="toggle('N')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/N_off.png" id="N_img">
            </button>
            <button class="letter-btn" id="I" onclick="toggle('I')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/I_off.png" id="I_img">
            </button>
            <button class="letter-btn" id="Z" onclick="toggle('Z')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/Z_off.png" id="Z_img">
            </button>
            <button class="letter-btn" id="E2" onclick="toggle('E2')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/E2_off.png" id="E2_img">
            </button>
            <button class="letter-btn" id="D" onclick="toggle('D')">
                <img src="https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/D_off.png" id="D_img">
            </button>
        </div>

        <script>
            function toggle(letter) {
                let img = document.getElementById(letter + "_img");
                let currentSrc = img.src;

                if (currentSrc.includes("_off")) {
                    img.src = `https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/${letter}_on.png`;
                } else {
                    img.src = `https://raw.githubusercontent.com/Thejasvenan/Mechanized_IoT/main/${letter}_off.png`;
                }

                fetch(`/toggle?led=${letter}`)
                    .then(response => console.log("Toggled: " + letter))
                    .catch(error => console.error("Error:", error));
            }
        </script>
    </body>
    </html>
    )rawliteral");
}

void handleToggle() {
    if (server.hasArg("led")) {
        String letter = server.arg("led");

        // Handle E2 separately
        int index = (letter == "E2") ? 8 : String(letters).indexOf(letter);

        if (index != -1) {
            Serial.println("Toggling: " + letter);
            blinkLED(ledPins[index]);
        }
    }
    server.send(200, "text/plain", "OK");
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("ESP32 Web Server's IP address: ");
    Serial.println(WiFi.localIP());

    for (int i = 0; i < 10; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], HIGH);
    }

    server.on("/", handleRoot);
    server.on("/toggle", handleToggle);
    server.begin();
}

void loop() {
    server.handleClient();
}
