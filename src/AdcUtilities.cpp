#include "AdcUtilities.h"
#include "config_manager.h"
#include "config/pins_config.h" // Incluir para ADS124S08_DRDY_PIN
#include "debug.h"

#include "ADS124S08.h"
extern ADS124S08 ADC;

float AdcUtilities::measureAdcDifferential(uint8_t muxConfig)
{
    // Configurar MUX
    DEBUG_PRINTF("Configurando MUX: %d\n", muxConfig);
    ADC.regWrite(INPMUX_ADDR_MASK, muxConfig);
    
    // Iniciar una conversión single shot
    ADC.sendCommand(START_OPCODE_MASK);
   
    // Esperar a que DRDY (Data Ready) vaya a BAJO o se agote el tiempo
    unsigned long startTime = millis();
    const unsigned long timeout = 100; // Timeout de 100 ms
    while (digitalRead(ADS124S08_DRDY_PIN) == HIGH) {
    	if (millis() - startTime > timeout) {
    		DEBUG_PRINTLN("Error: Timeout esperando DRDY del ADS124S08");
    		ADC.sendCommand(STOP_OPCODE_MASK); // Intentar detener la conversión
    		return NAN; // Retornar NAN en caso de timeout
    	}
    	// Pequeña pausa para no saturar la CPU
    	delayMicroseconds(10);
    }
    DEBUG_PRINTLN("DRDY detectado bajo, leyendo datos...");
    
    // Leer el resultado ahora que DRDY está bajo
    uint8_t dummy1 = 0, dummy2 = 0;
    int32_t rawData = ADC.dataRead(&dummy1, &dummy2, &dummy2);
    
    // Detener la conversión
    ADC.sendCommand(STOP_OPCODE_MASK);
    
    if (rawData == -1) {  // Error en la lectura
        return NAN;
    }
    
    if (rawData & 0x00800000) {
        // Extender signo si el bit 23 está en 1
        rawData |= 0xFF000000;
    }

    // Convertir a voltaje asumiendo referencia interna de 2.5V
    // ADC de 24 bits => rango ±2^23
    float voltage = (float)rawData / 8388608.0f * 2.5f;
    DEBUG_PRINTF("Voltaje medido: %.3f V\n", voltage);
    return voltage;
}
