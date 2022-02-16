#include <stdio.h>
#include <assert.h>
#include <checker.h>

const int total_test_case = 6;

alert parameter_alerts[TOTAL_PARAMETER] = 	{
												{0, "TEMPERATURE"},
												{0, "SOC"},
												{0, "CHARGE_RATE"}
											};
BMS battery_parameter[total_test_case] = 	{
												{25.0f, 50, 0.5f},
												{50.0f, 70, 0.7f},
												{-1.0f, 30, 0.6f},
												{30.0f, 90, 0.4f},
												{40.0f, 10, 0.3f},
												{20.0f, 45, 0.9f}
											};

int temperatureOutOfRange (float temperature)
{
	int status = GOOD;
	
	if (temperature < TEMP_MIN || temperature > TEMP_MAX)
	{
		status = BAD;
		parameter_alerts[TEMPERATURE].sendAlert = 1;
	} 
	 return status;
}

int socOutOfRange (int soc)
{
	int status = GOOD;
	if (soc < SOC_MIN || soc > SOC_MAX)
	{
		status = BAD;
		parameter_alerts[SOC].sendAlert = 1;
	}
	
	return status;
}

int chargeRateExceedLimit (float chargeRate)
{
	int status = GOOD;
	if (chargeRate > CHARGERATE_LIMIT)
	{
		status = BAD;
		parameter_alerts[CHARGE_RATE].sendAlert = 1;
	}
	return status;
}

int batteryIsOk (BMS battery_params)
{
	int battery_status = OK;

	if (temperatureOutOfRange(battery_params.temperature) || 
		socOutOfRange(battery_params.soc) || 
		chargeRateExceedLimit (battery_params.chargeRate))
	{
		battery_status = NOT_OK;
	}
	
	return battery_status;
}

int alertIsSet(int alert)
{
	int alert_status = alert? ASSERTED : NOT_ASSERTED;
	return alert_status;	
}
void printAlertToConsole (char *parameter_name)
{	
	printf("%s out of range!\n", parameter_name);
}

int main() {
	
	int test_case;
	int parameter_count;
	
	assert(batteryIsOk(battery_parameter[IN_RANGE]));
	
	for (test_case = TEST_ID_01; test_case < total_test_case; test_case++)
	{
		assert(!batteryIsOk(battery_parameter[test_case]));
	}
	
	for (parameter_count = TEMPERATURE; parameter_count < TOTAL_PARAMETER; parameter_count++)
	{
		if (alertIsSet(parameter_alerts[parameter_count].sendAlert))
		{
			printAlertToConsole(parameter_alerts[parameter_count].parameter_name);
		}
			
	}
		
	return 0;
}
