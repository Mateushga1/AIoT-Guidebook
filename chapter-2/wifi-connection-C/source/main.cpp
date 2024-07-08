#include "mbed.h"
#include "wifi_helper.h"

static constexpr size_t MAX_NUMBER_OF_ACCESS_POINTS = 10;
static constexpr size_t MAX_MESSAGE_RECEIVED_LENGTH = 100;

static constexpr size_t REMOTE_PORT = 80; // standard HTTP port

NetworkInterface *net;
SocketAddress address;
TCPSocket socket;

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
    char host[]="ifconfig.io";
    if (!resolve_hostname(host)) {
        return -1;
    }

    // On ouvre le socket pour allouer les ressources nécessaires
    result = socket.open(net);
    if (result != 0) {
        printf("Error! socket.open() returned: %d\r\n", result);
        return -1;
    }

    // on definit le port à utiliser pour la connection
    address.set_port(REMOTE_PORT);

    // Nous avons besoin maintenant d'ouvrir une connection via un socket
    printf("Opening connection to remote port %d\r\n", REMOTE_PORT);
    result = socket.connect(address);
    if (result != 0) {
        printf("Error! socket.connect() returned: %d\r\n", result);
        return -1;
    }

    // On peut envoyer maintenant une requête et récupérer une réponse HTTP
    if (!send_http_request()) {
    return -1;
    }

    if (!receive_http_response()) {
    return -1;
    }

    // fin de la démonstration
    printf("Demo concluded successfully \r\n");
    
    return 0;
}