#include <stdio.h>
#include <assert.h>
#include <checker.h>

#define ENGLISH

#if defined(ENGLISH)
char *warning_message = "out of range!!!";
#elif defined(GERMAN)
char *warning_message = "auber Reichweite!!!";
#endif

sendAlert showAlertMessage = printToConsole;

struct bms battery_parameter[TOTAL_DATA_SETS] = {
													{25.0f, 50, 0.8f},
													{47.0f, 30, 0.5f},
													{20.0f, 45, 0.9f},
													{43.0f, 10, 0.7}
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
	if (g_battery_parameter.temperature < temperatureAlertRange[TEMP_OUT_OF_RANGE].min || 
		g_battery_parameter.temperature > temperatureAlertRange[TEMP_OUT_OF_RANGE].max)
	{
		parameter_alerts[TEMPERATURE].isBreached = OUT_OF_RANGE;
	} 
	 return parameter_alerts[TEMPERATURE].isBreached;
}

int temperatureInRange (int warning_level)
{
	if (g_battery_parameter.temperature > temperatureAlertRange[warning_level].min && 
		g_battery_parameter.temperature <= temperatureAlertRange[warning_level].max)
	{
		parameter_alerts[TEMPERATURE].isInRange = OUT_OF_RANGE;
		showAlertMessage(temperatureAlertRange[warning_level].message);
	} 
	 return parameter_alerts[TEMPERATURE].isInRange;
}

int socOutOfRange ()
{
	if (g_battery_parameter.soc < socAlertRange[SOC_OUT_OF_RANGE].min ||
		g_battery_parameter.soc > socAlertRange[SOC_OUT_OF_RANGE].max)
	{
		parameter_alerts[SOC].isBreached = OUT_OF_RANGE;
	}
	
	return parameter_alerts[SOC].isBreached;
}

int socInRange (int warning_level)
{
	if (g_battery_parameter.soc > socAlertRange[warning_level].min && 
		g_battery_parameter.soc <= socAlertRange[warning_level].max)
	{
		parameter_alerts[SOC].isInRange = OUT_OF_RANGE;
		showAlertMessage(socAlertRange[warning_level].message);
	}
	
	return parameter_alerts[SOC].isInRange;
}

int chargeRateExceedLimit ()
{
	if (g_battery_parameter.chargeRate > chargeRateAlertRange[CR_OUT_OF_RANGE].max)
	{
		parameter_alerts[CHARGE_RATE].isBreached = OUT_OF_RANGE;
	}
	return parameter_alerts[CHARGE_RATE].isBreached;
}

int chargeRateWithinLimit (int warning_level)
{
	if (g_battery_parameter.chargeRate > chargeRateAlertRange[warning_level].min &&
		g_battery_parameter.chargeRate <= chargeRateAlertRange[warning_level].max)
	{
		parameter_alerts[CHARGE_RATE].isInRange = OUT_OF_RANGE;
		showAlertMessage(chargeRateAlertRange[warning_level].message);
	}
	return parameter_alerts[CHARGE_RATE].isInRange;
}

int batteryIsOk ()
{
	int parameter_count, status = GOOD, warning_enabled;
	
	for (parameter_count = TEMPERATURE; parameter_count < TOTAL_PARAMETER_SUPPORTED; parameter_count++)
	{
		warning_enabled = parameter_alerts[parameter_count].warning_enabled;
		status |= parameter_alerts[parameter_count].parameterOutOfRange( );
		if (warning_enabled)
		{
			parameter_alerts[parameter_count].alertIfParameterInRange(warning_enabled);
		}
	}
	return status;
}

void AlertIfBreached (sendAlert pushAlert)
{	
	int parameter_count;
	char warningMesage [256];
	
	for (parameter_count = TEMPERATURE; parameter_count < TOTAL_PARAMETER_SUPPORTED; parameter_count++)
	{
		if (parameter_alerts[parameter_count].isBreached)
		{
			sprintf (warningMesage, "%s %s", parameter_alerts[parameter_count].parameter_name, warning_message );
			pushAlert(warningMesage);
		}		
	}
}

void printToConsole (char * warningMessage)
{
	
	printf ("%s\n", warningMessage);
	return;
}

void resetOldStatus ()
{
	parameter_alerts[TEMPERATURE].isBreached = IN_RANGE;
	parameter_alerts[SOC].isBreached = IN_RANGE;
	parameter_alerts[CHARGE_RATE].isBreached = IN_RANGE;
	parameter_alerts[TEMPERATURE].isInRange = IN_RANGE;
	parameter_alerts[SOC].isInRange = IN_RANGE;
	parameter_alerts[CHARGE_RATE].isInRange = IN_RANGE;
}

int main() {
	
	int data_set = FIRST;
	
	readBatteryParameters(data_set);
	assert(batteryIsOk() == GOOD);
	AlertIfBreached (showAlertMessage);
	resetOldStatus();
	
	for (data_set = SECOND; data_set < TOTAL_DATA_SETS; data_set++)
	{
		readBatteryParameters(data_set);
		assert(batteryIsOk() == BAD);
		AlertIfBreached (showAlertMessage);
		resetOldStatus();
	}	
	return 0;
}
