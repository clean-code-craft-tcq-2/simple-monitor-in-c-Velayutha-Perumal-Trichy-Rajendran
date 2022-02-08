#include <stdio.h>
#include <assert.h>

enum status {BAD, GOOD};
const int total_parameter = 3;
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
	float battery_param_in_range [] = {25.0f, 70, 0.7f};
	float battery_param_out_of_range [] = {50.0f, 85, 0.0f};
	BMS battery_parameter[total_parameter];
	int parameter_count;
	float limit_min [] = {0.0f, 20, 0.4f };
	float limit_max [] = {45.0f, 80, 0.9f};
	
	for (parameter_count = 0; parameter_count < total_parameter; parameter_count++)
	{
		battery_parameter[parameter_count].limits.min = limit_min[parameter_count];
		battery_parameter[parameter_count].limits.max = limit_max[parameter_count];
		battery_parameter[parameter_count].actual_value = battery_param_in_range[parameter_count];
		assert(batteryIsOk(battery_parameter[parameter_count]));
		battery_parameter[parameter_count].actual_value = battery_param_out_of_range[parameter_count];
		assert(!batteryIsOk(battery_parameter[parameter_count]));
	}
}
