#include <stdio.h>
#include <assert.h>

enum status {BAD, GOOD};
typedef struct bms
{
	float actual_value;
	struct range
	{
		float min;
		float max;
	}limits;
}BMS;


int batteryIsOk (BMS battery_params)
{
	int battery_status = GOOD;
	
	if (battery_params.actual_value < battery_params.limits.min || 
		battery_params.actual_value > battery_params.limits.max )
	{
		printf("out of range!\n");
		battery_status = BAD;
	}
	return battery_status;
}

int main() {
	float battery_temperature [] = {25.0f, 50.0f};
	int battery_soc [] = {70, 85};
	float battery_charge_rate [] = {0.7f, 0.0f};
	BMS battery_parameter;
	int reading_index;
	
	for (reading_index = 0; reading_index < 2; reading_index++)
	{
		battery_parameter.limits.min = 0.0f;
		battery_parameter.limits.max = 45.0f;
		battery_parameter.actual_value = battery_temperature[reading_index];
		assert(batteryIsOk(battery_parameter));
		
		battery_parameter.limits.min = 20;
		battery_parameter.limits.max = 80;
		battery_parameter.actual_value = battery_soc[reading_index];
		assert(batteryIsOk(battery_parameter));
		
		battery_parameter.limits.min = 0.0f;
		battery_parameter.limits.max = 0.8f;
		battery_parameter.actual_value = battery_charge_rate[reading_index];
		assert(batteryIsOk(battery_parameter));
	}
	
}
