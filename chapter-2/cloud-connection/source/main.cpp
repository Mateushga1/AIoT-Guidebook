#include "mbed.h"
#include "wifi_helper.h"

static constexpr size_t MAX_NUMBER_OF_ACCESS_POINTS = 10;
static constexpr size_t MAX_MESSAGE_RECEIVED_LENGTH = 100;

static constexpr size_t REMOTE_PORT = 80; // standard HTTP port

NetworkInterface *net;
SocketAddress address;
TCPSocket socket;

#define thingspeak_APIkey_write "2Z3VIUSVH62S4FIK" //mettre la clé écriture de votre canal TS
#define thingspeak_APIkey_read "IUWXT480JLT79G8O" //mettre la clé lecture de votre canal TS

AnalogIn analog_value0(A0);
AnalogIn analog_value1(A1);

nsapi_error_t response;
char sbuffer[256];
char message[64];
float captX;
float captY;
float captZ;

void wifi_scan()
{
    WiFiInterface *wifi = net->wifiInterface();
    WiFiAccessPoint ap[MAX_NUMBER_OF_ACCESS_POINTS];

    /* scan call returns number of access points found */
    int result = wifi->scan(ap, MAX_NUMBER_OF_ACCESS_POINTS);

    if (result <= 0) {
        printf("WiFiInterface::scan() failed with return value: %d\r\n", result);
        return;
    }

    printf("%d networks available:\r\n", result);

    for (int i = 0; i < result; i++) {
        printf("Network: %s secured: %s BSSID: %hhX:%hhX:%hhX:%hhx:%hhx:%hhx RSSI: %hhd Ch: %hhd\r\n",
        ap[i].get_ssid(), get_security_string(ap[i].get_security()),
        ap[i].get_bssid()[0], ap[i].get_bssid()[1], ap[i].get_bssid()[2],
        ap[i].get_bssid()[3], ap[i].get_bssid()[4], ap[i].get_bssid()[5],
        ap[i].get_rssi(), ap[i].get_channel());
    }
    printf("\r\n");
}

bool resolve_hostname(char *hostname)
{
    /* get the host address */
    printf("\nResolve hostname %s\r\n", hostname);
    nsapi_size_or_error_t result = net->gethostbyname(hostname, &address);
    if (result != 0) {
        printf("Error! gethostbyname(%s) returned: %d\r\n", hostname, result);
        return false;
    }
    printf("%s address is %s\r\n", hostname, (address.get_ip_address() ? address.get_ip_address() : "None") );
    return true;
}

void print_network_info()
{
    /* print the network info */
    SocketAddress a;
    net->get_ip_address(&a);
    printf("IP address: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
    net->get_netmask(&a);
    printf("Netmask: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
    net->get_gateway(&a);
    printf("Gateway: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
}

bool send_http_request()
{
    /* loop until whole request sent */
    const char buffer[] = "GET / HTTP/1.1\r\n"
    "Host: ifconfig.io\r\n"
    "Connection: close\r\n"
    "\r\n";

    nsapi_size_t bytes_to_send = strlen(buffer);
    nsapi_size_or_error_t bytes_sent = 0;

    printf("\r\nSending message: \r\n%s", buffer);

    while (bytes_to_send) {
        bytes_sent = socket.send(buffer + bytes_sent, bytes_to_send);
        if (bytes_sent < 0) {
        printf("Error! socket.send() returned: %d\r\n", bytes_sent);
        return false;
        } else {
            printf("sent %d bytes\r\n", bytes_sent);
        }

            bytes_to_send -= bytes_sent;
    }
    printf("Complete message sent\r\n");

    return true;
}

bool receive_http_response()
{
    char buffer[MAX_MESSAGE_RECEIVED_LENGTH];
    int remaining_bytes = MAX_MESSAGE_RECEIVED_LENGTH;
    int received_bytes = 0;

    /* loop until there is nothing received or we've ran out of buffer space */

    nsapi_size_or_error_t result = remaining_bytes;
    while (result > 0 && remaining_bytes > 0) {
        result = socket.recv(buffer + received_bytes, remaining_bytes);
        if (result < 0) {
            printf("Error! socket.recv() returned: %d\r\n", result);
            return false;
        }

        received_bytes += result;
        remaining_bytes -= result;
    }
    /* the message is likely larger but we only want the HTTP response code */
    printf("received %d bytes:\r\n%.*s\r\n\r\n", received_bytes, strstr(buffer, "\n") - buffer, buffer);

    return true;
}

int main() {

    printf("\r\nStarting socket demo\r\n\r\n");

    // on recupere l'instance d'interface réseau par défaut
    net=NetworkInterface::get_default_instance();
    if (!net) {
        printf("Error! No network interface found.\r\n");
        return -1;
    }

    // si on dispose d'une interface wifi on effectue un scan rapide du réseau

    // pour afficher les points d'accès visibles
    // commenter le code si jamais ça bloque à cette étape
    if (net->wifiInterface()) {
        wifi_scan();
    }

    // On se connecte sur le réseau
    printf("Connecting to the network...\r\n");
    nsapi_size_or_error_t result = net->connect();
    if (result != 0) {
        printf("Error! net->connect() returned: %d\r\n", result);
        return -1;
    }

    // on affiche les informations du réseau (IP address netmask et gateway)
    print_network_info();

    // on verifie si on trouve l'hote sur le réseau
    char hostname[]="api.thingspeak.com";
    if (!resolve_hostname(hostname)) {
        return -1;
    }
    address.set_port(REMOTE_PORT);

    while(true)
    {
        // Nous avons besoin maintenant d'ouvrir une connection à un socket
        result = socket.open(net);
        if (result != 0) {
            printf("Error! socket.open() returned: %d\r\n", result);
            return -1;
        }

        printf("\r\n\r\nOpening connection to remote port %d\r\n", REMOTE_PORT);

        result = socket.connect(address);
        if (result != 0) {
            printf("Error! socket.connect() returned: %d\r\n", result);
            return -1;
        }

        captX=analog_value0.read();
        captY=analog_value1.read();
        captZ=0;   

        // message à transmettre (données des capteurs)
        sprintf(message, "{\"field1\": %0.2f, \"field2\": %0.2f, \"field3\": %0.2f}", captX, captY, captZ);
        printf("Message = %s\r\n", (message));
        // Phase de transmission des données à ThingSpeaks.com
        sprintf(sbuffer, "GET /update?api_key=%s HTTP/1.1\r\nHost: api.thingspeak.com\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s", thingspeak_APIkey_write, (int)strlen(message),message);

        printf("HTTP command %s\r\n", sbuffer);

        printf("Sending HTTP request to thingspeak.com...\n");//
        nsapi_size_t size = strlen(sbuffer);
        response = 0;   
        while(size)
        {
            response = socket.send(sbuffer+response, size);
            if (response < 0)
            {
                printf("Error sending data: %d\n", response);
                socket.close();
                return -1;
            }
            else
            {
            size -= response;
            }
        }
        printf("request sent to thingspeak.com...\n");//

        // Receive a simple http response and print out the response line
        char rbuffer[64];
        response = socket.recv(rbuffer, sizeof rbuffer);
        if (response < 0)
        {
            printf("Error receiving data: %d\n", response);
        }
        else
        {
            printf("recv %d [%.*s]\n", response, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);
        }

        // Close the socket to return its memory and bring down the network interface
        socket.close();
        ThisThread::sleep_for(5000ms); // attente 1 seconde
    }
    net->disconnect();
    return 0;
}