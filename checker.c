#include <stdio.h>
#include <assert.h>

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
	if (battery_params.actual_value < battery_params.limits.min || 
		battery_params.actual_value > battery_params.limits.max )
	{
		printf("out of range!\n");
		return 0;
	}
}

/* int batteryIsOk(float temperature, float soc, float chargeRate) {
  if(temperature < 0 || temperature > 45) {
    printf("Temperature out of range!\n");
    return 0;
  } else if(soc < 20 || soc > 80) {
    printf("State of Charge out of range!\n");
    return 0;
  } else if(chargeRate > 0.8) {
    printf("Charge Rate out of range!\n");
    return 0;
  }
  return 1;
} */

int main() {
	float battery_temperature [] = {25.0f, 50.0f};
	int battery_soc [] = {70, 85};
	float battery_charge_rate [] = {0.7f, 0.0f};
	BMS battery_parameter;
	int reading_index;
	
	for (reading_index = 0; reading_index < 2; reading_index++)
	{
		battery_parameters.limits.min = 0.0f;
		battery_parameters.limits.max = 45.0f;
		battery_parameter.actual_value = battery_temperature[reading_index];
		assert(batteryIsOk(battery_parameter));
		
		battery_parameters.limits.min = 20;
		battery_parameters.limits.max = 80;
		battery_parameter.actual_value = battery_soc[reading_index];
		assert(batteryIsOk(battery_parameter));
		
		battery_parameters.limits.min = 0.0f;
		battery_parameters.limits.max = 0.8f;
		battery_parameter.actual_value = battery_charge_rate[reading_index];
		assert(batteryIsOk(battery_parameter));
	}
	/* assert(batteryIsOk(25, 70, 0.7));
	assert(!batteryIsOk(50, 85, 0)); */
}
