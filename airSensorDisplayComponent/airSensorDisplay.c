#include "legato.h"
#include "interfaces.h"


uint16_t PM1_0_PM_Standard;
uint16_t PM2_5_PM_Standard;
uint16_t PM10_PM_Standard;

uint16_t PM1_0_atmos_env;
uint16_t PM2_5_atmos_env;
uint16_t PM10_atmos_env;
le_timer_Ref_t	updatesensor = NULL;  

static void read_air_sensor
(
	le_timer_Ref_t	timerRef 
)
{
	le_result_t res;
	res= ma_airSensor_ReadIndustrialPM1_0(&PM1_0_PM_Standard);
	if (res!= LE_OK) {
		LE_INFO("FAILED air_ReadIndustrialPM1_0");
	}
	LE_INFO("Industrial PM1_0 = %d ug/m3\n",PM1_0_PM_Standard);

			
	res = ma_airSensor_ReadIndustrialPM2_5(&PM2_5_PM_Standard);

	if (res!= LE_OK) {
		LE_INFO("FAILED air_ReadIndustrialPM2_5");
	}
	LE_INFO("Industrial PM2_5 = %d ug/m3\n",PM2_5_PM_Standard);

	
	res = ma_airSensor_ReadIndustrialPM10(&PM10_PM_Standard);
	if (res!= LE_OK) {
		LE_INFO("FAILED air_ReadIndustrialPM10");
	}
	LE_INFO("Industrial PM10 = %d ug/m3\n",PM10_PM_Standard);

	
	res = ma_airSensor_ReadEnvironmentPM1_0(&PM1_0_atmos_env);
	if (res!= LE_OK) {
		LE_INFO("FAILED air_ReadIndustrialPM10");
	}
	LE_INFO("Environment PM1_0 = %d ug/m3\n",PM1_0_atmos_env);

	res = ma_airSensor_ReadEnvironmentPM2_5(&PM2_5_atmos_env);
	if (res!= LE_OK) {
		LE_INFO("FAILED air_ReadIndustrialPM10");
	}
	LE_INFO("Environment PM2_5 = %d ug/m3\n",PM2_5_atmos_env);
			
	res = ma_airSensor_ReadEnvironmentPM10(&PM10_atmos_env);
	if (res!= LE_OK) {
		LE_INFO("FAILED air_ReadIndustrialPM10");
	}
	LE_INFO("EnvironmentPM10 = %d ug/m3\n",PM10_atmos_env);
}

COMPONENT_INIT
{
	ma_airSensor_Init();
	
	updatesensor = le_timer_Create("update sensor value");     
	le_clk_Time_t	intervalloc = {35, 0 };                    
	le_timer_SetInterval(updatesensor, intervalloc);
	le_timer_SetRepeat(updatesensor, 0);                  
	le_timer_SetHandler(updatesensor, read_air_sensor);
	le_timer_Start(updatesensor);

}
