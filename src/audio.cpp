#include <Arduino.h>
#include "audio.h"
#include "config.h"
#include <driver/i2s.h>
#include "ES8388.h"

ES8388 es8388(18,23,400000);

size_t bytes_read;

void configureES8388(){
    Serial.println("Configuring ES8388");    
    if (!es8388.init()) Serial.println("Init Fail");
    es8388.inputSelect(IN1);
    es8388.setInputGain(0);
    Serial.println("ES8388 Configured");    

}
void setupAudio(){
    configureES8388();
    i2s_config_t i2sConfig = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 2,
        .dma_buf_len = 1024,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0};

    /*Setting up I2S pin config*/
    i2s_pin_config_t pinConfig = {
        .bck_io_num = 5, .ws_io_num = 25, .data_out_num = 26, .data_in_num = 35};

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1); 
    WRITE_PERI_REG(PIN_CTRL, 0xFFF0);

    Serial.println("Attempting to setup I2S ES8388");

    if (ESP_OK != i2s_driver_install(I2S_NUM_0, &i2sConfig, 0, NULL))
    {
        Serial.println("Error installing I2S. Halt!");
        while (1)
            ;
    }
    
    if (ESP_OK != i2s_set_pin(I2S_NUM_0, &pinConfig))
    {
        Serial.println("Error setting I2S pins. Halt!");
        while (1)
            ;
    }
    Serial.println("I2S configured");    
}