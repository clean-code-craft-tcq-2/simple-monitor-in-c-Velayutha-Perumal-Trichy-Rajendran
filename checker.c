#include <stdio.h>
#include <assert.h>
#include <checker.h>

#define ENGLISH

#if defined(ENGLISH)
char *warning_message = "out of range!!!";
#elif defined(GERMAN)
char *warning_message = "auber Reichweite!!!";
#endif

struct bms battery_parameter[TOTAL_DATA_SETS] = {
													{25.0f, 10, 0.5f},
													{50.0f, 20, 0.7f},
													{1.0f, 15, 0.6f},
													{40.0f, 27, 0.3f},
													{20.0f, 45, 0.9f},
													{43.0f, 25, 0.7}
												};

int readBatteryParameters (int inputDataSetIndex)
{
	g_battery_parameter.temperature = battery_parameter[inputDataSetIndex].temperature;
	g_battery_parameter.soc = battery_parameter[inputDataSetIndex].soc;
	g_battery_parameter.chargeRate = battery_parameter[inputDataSetIndex].chargeRate;
	
	return inputDataSetIndex;
}

int temperatureOutOfRange (int warning_level)
{
	if (g_battery_parameter.temperature > temperatureAlertRange[warning_level].min && 
		g_battery_parameter.temperature <= temperatureAlertRange[warning_level].max)
	{
		parameter_alerts[TEMPERATURE].breached = ASSERTED;
		parameter_alerts[TEMPERATURE].warning_lvl = warning_level;
		parameter_alerts[TEMPERATURE].warning_type = temperatureAlertRange[warning_level].warning_type;
	} 
	 return parameter_alerts[TEMPERATURE].breached;
}

int socOutOfRange (int warning_level)
{
	if (g_battery_parameter.soc > socAlertRange[warning_level].min && 
		g_battery_parameter.soc <= socAlertRange[warning_level].max)
	{
		parameter_alerts[SOC].breached = ASSERTED;
		parameter_alerts[SOC].warning_lvl = warning_level;
		parameter_alerts[SOC].warning_type = socAlertRange[warning_level].warning_type;
	}
	
	return parameter_alerts[SOC].breached;
}

int chargeRateExceedLimit (int warning_level)
{
	if (g_battery_parameter.chargeRate > chargeRateAlertRange[warning_level].min &&
		g_battery_parameter.chargeRate <= chargeRateAlertRange[warning_level].max)
	{
		parameter_alerts[CHARGE_RATE].breached = ASSERTED;
		parameter_alerts[CHARGE_RATE].warning_lvl = warning_level;
		parameter_alerts[CHARGE_RATE].warning_type = chargeRateAlertRange[warning_level].warning_type;
	}
	return parameter_alerts[CHARGE_RATE].breached;
}

int batteryIsOk ()
{
	int parameter_count, status = GOOD;
	
	for (parameter_count = TEMPERATURE; parameter_count < TOTAL_PARAMETER; parameter_count++)
	{
		status |= parameter_alerts[parameter_count].parameterOutOfRange( parameter_alerts[parameter_count].warning_lvl );
	}
	return status;
}

void printAlertToConsoleIfBreached ()
{	
	int parameter_count;
	
	for (parameter_count = TEMPERATURE; parameter_count < TOTAL_PARAMETER; parameter_count++)
	{
		if (parameter_alerts[parameter_count].breached && 
			parameter_alerts[parameter_count].warning_lvl != NORMAL)
		{
			printf("%s %s: %s\n", parameter_alerts[parameter_count].parameter_name, warning_message, parameter_alerts[parameter_count].warning_type);
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
	
	int data_set;
	
	for (data_set = FIRST; data_set < TOTAL_POSITIVE_DATA_SETS; data_set++)
	{
		readBatteryParameters(data_set);
		assert(batteryIsOk() == GOOD);
		printAlertToConsoleIfBreached ();
		resetOldStatus();
	}
	for (data_set; data_set < TOTAL_DATA_SETS; data_set++)
	{
		readBatteryParameters(data_set);
		assert(batteryIsOk() == BAD);
		printAlertToConsoleIfBreached ();
		resetOldStatus();
	}	
	return 0;
}
