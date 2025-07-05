#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <esp_system.h>
#include <esp_netif.h> //Necesario para configurar la IP estática

//MODO STA: IP Estática
#define WIFI_SSID "MOVISTAR_78A8"
#define WIFI_PASS "NS2ajtQJ7TtDt9m"

#define STATIC_IP "192.168.1.108"
#define GATEWAY_IP "192.168.1.1"
#define NETMASK_IP "255.255.255.0"

void wifi_init_sta(void){
  esp_netif_init(); //Inicializa la interfaz de red de la ESP32
  esp_event_loop_create_default();//Crea el bucle de eventos wifi, desconexión, etc
  /********************************************************************************/
  esp_netif_t *ret = esp_netif_create_default_wifi_sta();//Configura el modo estación
  esp_netif_dhcpc_stop(ret); //DHCP Stop
  esp_netif_ip_info_t ip_info;
  uint32_t ip_val = esp_ip4addr_aton(STATIC_IP);
  uint32_t gateway_val = esp_ip4addr_aton(GATEWAY_IP);
  uint32_t netmask_val = esp_ip4addr_aton(NETMASK_IP);
  ip_info.ip.addr = ip_val;
  ip_info.netmask.addr = netmask_val;
  ip_info.gw.addr = gateway_val;
  //Asignamos la configuración de la red estática
  esp_netif_set_ip_info(esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"),&ip_info);
  /******************************************************************************* */
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg); //Inicia wifi con una configuración por defecto
  wifi_config_t wifi_config = {
    .sta={
      .ssid = WIFI_SSID,
      .password = WIFI_PASS
    },
  };
  esp_wifi_set_mode(WIFI_MODE_STA); //Establece el modo estación (STA)
  esp_wifi_set_config(WIFI_IF_STA,&wifi_config);
  esp_wifi_start();//Iniciar el modulo wifi
  esp_wifi_connect(); //Intenta conectarse a la red configurada
}

void app_main(void)
{
  esp_err_t ret = nvs_flash_init();
  if(ret != ESP_OK){
    return;
  }
  wifi_init_sta();
}
