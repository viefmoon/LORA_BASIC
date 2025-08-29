#ifndef LORA_CONFIG_H
#define LORA_CONFIG_H

// Configuración de reloj SPI para LoRa
#define SPI_LORA_CLOCK       1000000

// Tamaño máximo de payload LoRa
#define MAX_LORA_PAYLOAD     200

// LoRa (OTAA) - Valores por defecto
#define DEFAULT_JOIN_EUI    "00,00,00,00,00,00,00,00"
#define DEFAULT_DEV_EUI     "63,66,e0,dc,66,04,2c,0d"
#define DEFAULT_APP_KEY     "98,28,42,10,47,6b,15,e4,a2,78,7c,5f,9e,23,80,ec"
#define DEFAULT_NWK_KEY     "3f,1e,71,0e,44,33,8d,f8,8c,41,d3,f2,d3,72,a0,d0"

// LoRa Region y SubBand
#define LORA_REGION         US915
#define LORA_SUBBAND        2       // For US915, use 2; for other regions, use 0

#endif // LORA_CONFIG_H 