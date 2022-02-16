#include <stdio.h>
#include <assert.h>
#include <checker.h>

const int total_row_index = 6;
BMS g_battery_parameter;

alert parameter_alerts[TOTAL_PARAMETER] = 	{
												{NOT_ASSERTED, "TEMPERATURE", temperatureOutOfRange},
												{NOT_ASSERTED, "SOC", socOutOfRange},
												{NOT_ASSERTED, "CHARGE_RATE", chargeRateExceedLimit}
											};
BMS battery_parameter[total_row_index] = 	{
												{25.0f, 50, 0.5f},
												{50.0f, 70, 0.7f},
												{-1.0f, 30, 0.6f},
												{30.0f, 90, 0.4f},
												{40.0f, 10, 0.3f},
												{20.0f, 45, 0.9f}
											};

int readBatteryParameters (int inputDataSetIndex)
{
	g_battery_parameter.temperature = battery_parameter[inputDataSetIndex].temperature;
	g_battery_parameter.soc = battery_parameter[inputDataSetIndex].soc;
	g_battery_parameter.chargeRate = battery_parameter[inputDataSetIndex].chargeRate;
	
	return inputDataSetIndex;
}

int temperatureOutOfRange ()
{
	if (g_battery_parameter.temperature < TEMP_MIN || 
		g_battery_parameter.temperature > TEMP_MAX)
	{
		parameter_alerts[TEMPERATURE].breached = ASSERTED;
	} 
	 return parameter_alerts[TEMPERATURE].breached;
}

int socOutOfRange ()
{
	if (g_battery_parameter.soc < SOC_MIN || 
		g_battery_parameter.soc > SOC_MAX)
	{
		parameter_alerts[SOC].breached = ASSERTED;
	}
	
	return parameter_alerts[SOC].breached;
}

int chargeRateExceedLimit ()
{
	if (g_battery_parameter.chargeRate > CHARGERATE_LIMIT)
	{
		parameter_alerts[CHARGE_RATE].breached = ASSERTED;
	}
	return parameter_alerts[CHARGE_RATE].breached;
}

int batteryIsOk ()
{
	int parameter_count, status = GOOD;
	
	for (parameter_count = TEMPERATURE; parameter_count < TOTAL_PARAMETER; parameter_count++)
	{
		status |= parameter_alerts[parameter_count].parameterOutOfRange();
	}
	return status;
}

void printAlertToConsoleIfBreached ()
{	
	int parameter_count;
	
	for (parameter_count = TEMPERATURE; parameter_count < TOTAL_PARAMETER; parameter_count++)
	{
		if (parameter_alerts[parameter_count].breached)
		{
			printf("%s out of range!\n", parameter_alerts[parameter_count].parameter_name);
		}		
	}
}

void resetOldStatus ()
{
	parameter_alerts[TEMPERATURE].breached = NOT_ASSERTED;
	parameter_alerts[SOC].breached = NOT_ASSERTED;
	parameter_alerts[CHARGE_RATE].breached = NOT_ASSERTED;
}

int main() {
	
	int read_index = Index_01;
	
	readBatteryParameters(read_index);
	assert(batteryIsOk() == GOOD);
	printAlertToConsoleIfBreached ();
	resetOldStatus();
	for (read_index = Index_02; read_index < total_row_index; read_index++)
	{
		readBatteryParameters(read_index);
		assert(batteryIsOk() == BAD);
		printAlertToConsoleIfBreached ();
		resetOldStatus();
	}	
	return 0;
}
