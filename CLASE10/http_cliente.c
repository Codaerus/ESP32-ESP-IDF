#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "protocol_examples_common.h"

esp_err_t clientEvent(esp_http_client_event_t *evento){
    switch(evento->event_id){
        case HTTP_EVENT_ON_DATA:
            printf("%.*s\n",evento->data_len,(char*)evento->data);
            break;
        default:
            break;
    }
    return ESP_OK;
}

void app_main(void)
{
    //iniciar la memoria flash
    nvs_flash_init();
    //Inicia interfaz
    esp_netif_init();
    //Sistema de loop de eventos para conexión wifi
    esp_event_loop_create_default();
    //Utilizaremos la función de ejemplo para conexión wifi
    example_connect();

    esp_http_client_config_t clientConfig = {
        .url = "http://192.168.1.9/dashboard/PRUEBA/datos.txt",
        .event_handler = clientEvent,
    };

    //Crea el cliente
    esp_http_client_handle_t client = esp_http_client_init(&clientConfig);
    //Realizamos la petición con el cliente configurado
    esp_http_client_perform(client);
    //Limpiamos y liberarmos recursos despues de terminada la solicitud
    esp_http_client_cleanup(client);
}
