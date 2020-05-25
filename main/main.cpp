#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// adv_data and _adv_params come from esp-idf's bluetooth examples.
static esp_ble_adv_data_t adv_data = {
    .set_scan_rsp = false,
    .include_name = true,
    .include_txpower = true,
    .min_interval = 512,
    .max_interval = 1024,
    .appearance = 0,
    .manufacturer_len = 0,
    .p_manufacturer_data = NULL,
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = 0,
    .p_service_uuid = NULL,
    .flag = (ESP_BLE_ADV_FLAG_NON_LIMIT_DISC)};

static esp_ble_adv_params_t adv_params = {
    .adv_int_min = 512,
    .adv_int_max = 1024,
    .adv_type = ADV_TYPE_NONCONN_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .peer_addr = {
        0x00,
    },
    .peer_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

// user defined data (what you actually want to advertise, for example: sensor data)
uint8_t user_adv_data[4] = {0xE1, 0xE2, 0xE3, 0xE4};

void advertise_data()
{
	vTaskDelay( 2000 / portTICK_RATE_MS );
	ESP_LOGI( "advertise", "Start advertising data" );

	if( user_adv_data[3] != 0 )
	{
		user_adv_data[3] --;
	}
	else
	{
		user_adv_data[3] = 0xE4;
	}
	
	adv_data.service_data_len = 4;  // length of user_adv_data
	adv_data.p_service_data = user_adv_data;  // pointer to user_adv_data
	ESP_ERROR_CHECK( esp_ble_gap_config_adv_data(&adv_data) );
	ESP_ERROR_CHECK( esp_ble_gap_start_advertising(&adv_params) );
}

void gap_event_callback( esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t* param )
{
	switch( event )
	{
		case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
			break;
		case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
			advertise_data();
			break;
		default:
			break;
	}
}

extern "C"
{
void app_main(void)
{
	esp_err_t ret = nvs_flash_init();
	if( ret == ESP_ERR_NVS_NO_FREE_PAGES )
	{
		ESP_ERROR_CHECK( nvs_flash_erase() );
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK( ret );



	ESP_ERROR_CHECK( esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT) );

	esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK( esp_bt_controller_init(&bt_cfg) );
	ESP_ERROR_CHECK( esp_bt_controller_enable(ESP_BT_MODE_BLE) );

	ESP_ERROR_CHECK( esp_bluedroid_init() );
	ESP_ERROR_CHECK( esp_bluedroid_enable() );

	ESP_ERROR_CHECK( esp_ble_gap_set_device_name("ESP32-ADVERTISER") );
	ESP_ERROR_CHECK( esp_ble_gap_config_adv_data(&adv_data) );
	ESP_ERROR_CHECK( esp_ble_gap_register_callback(gap_event_callback) );
	ESP_ERROR_CHECK( esp_ble_gap_start_advertising(&adv_params) );

	while (1)
    {
        vTaskDelay( 1000 / portTICK_RATE_MS );
        ESP_LOGI( "main", "Running" );
    }

}
}