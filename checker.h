#ifndef __CHECKER_H_
#define __CHECKER_H_

#define TOTAL_ALERT_COUNT	6
#define TOTAL_PARAMETER_SUPPORTED		3
#define TOTAL_DATA_SETS     4
#define NORMAL				2					

enum battery_conditon {GOOD, BAD};
enum dataSet {FIRST, SECOND};
enum params_list {TEMPERATURE, SOC, CHARGE_RATE};
enum rangeType {IN_RANGE, OUT_OF_RANGE};
enum TemperatureWarningLevel{TEMP_OUT_OF_RANGE, LOW_TEMP_BREACH, LOW_TEMP_WARNING, NORMAL_TEMP, HIGH_TEMP_WARNING, HIGH_TEMP_BREACH};
enum socWarningLevel{SOC_OUT_OF_RANGE, LOW_SOC_BREACH, LOW_SOC_WARNING, NORMAL_SOC, HIGH_SOC_WARNING, HIGH_SOC_BREACH};
enum chargeRateWarningLevel{CR_OUT_OF_RANGE, LOW_CR_BREACH, LOW_CR_WARNING, NORMAL_CR, HIGH_CR_WARNING, HIGH_CR_BREACH};

/*Parameter validator Function declaration */
int temperatureOutOfRange ();
int socOutOfRange ();
int chargeRateExceedLimit ();
int temperatureInRange (int warning_lvl);
int socInRange (int warning_lvl);
int chargeRateWithinLimit (int warning_lvl);
void printToConsole (char * warningMessage);

struct bms
{
	float temperature;
	int soc;
	float chargeRate;
}g_battery_parameter;

typedef int (*isParamterNormal)();
typedef int (*inRange)(int);
typedef void (*sendAlert)(char *);

struct alert
{
	int isInRange;
	int isBreached;
	char *parameter_name;
	isParamterNormal parameterOutOfRange;
	inRange alertIfParameterInRange;
	int warning_enabled;
} parameter_alerts[TOTAL_PARAMETER_SUPPORTED] = {
													{IN_RANGE, IN_RANGE, "TEMPERATURE", temperatureOutOfRange, temperatureInRange, HIGH_TEMP_WARNING},
													{IN_RANGE, IN_RANGE, "SOC", socOutOfRange, socInRange, NORMAL_SOC},
													{IN_RANGE, IN_RANGE, "CHARGE_RATE", chargeRateExceedLimit, chargeRateWithinLimit, HIGH_CR_BREACH}
												};

struct socAlerts
{
	int min;
	int max;
	char *message;
} socAlertRange[TOTAL_ALERT_COUNT] =	{
											{20, 80, "SOC OUT OF RANGE"},
											{0, 20, "LOW SOC BREACH"},
											{20, 24, "LOW SOC WARNING"},
											{24, 75, "NORMAL SOC"},
											{75, 80, "HIGH TEMP WARNING"},
											{80, 100, "HIGH TEMP BREACH"}
										};
struct temperatureAlerts
{
	float min;
	float max;
	char *message;
}temperatureAlertRange[TOTAL_ALERT_COUNT] = {	
												{0.0f, 45.0f, "TEMPERATURE OUT OF RANGE"},
												{0.0f, 5.0f, "LOW TEMPERATURE BREACH"},
												{5.0f, 10.0f, "LOW TEMPERATURE WARNING"},
												{10.0f, 40.0f, "NORMAL TEMPERATURE"},
												{40.0f, 45.0f, "HIGH TEMPERATURE WARNING"},
												{45.0f, 60.0f, "HIGH TEMPERATURE BREACH"}
											};
							
struct chargeRateAlerts 
{
	float min;
	float max;
	char *message;
}chargeRateAlertRange[TOTAL_ALERT_COUNT] = {
												{0.0f, 0.8f, "CHARGE RATE OUT OF RANGE"},
												{0.0f, 0.4f, "LOW CHARGE RATE BREACH"},
												{0.4f, 0.6f, "LOW CHARGE RATE WARNING"},
												{0.6f, 0.8f, "NORMAL CHARGE RATE"},
												{0.8f, 0.9f, "HIGH CHARGE RATE WARNING"},
												{0.8f, 1.0f, "HIGH CHARGE RATE BREACH"}
											};
#endif