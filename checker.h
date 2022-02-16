#ifndef __CHECKER_H_
#define __CHECKER_H_

/* #define TEMP_MIN			0.0f
#define TEMP_MAX			45.0f
#define SOC_MIN				20
#define SOC_MAX				80
#define CHARGERATE_LIMIT	0.8f */
#define TOTAL_PARAMETER				 3
#define TOTAL_POSITIVE_DATA_SETS     3
#define TOTAL_DATA_SETS     		 6
#define NORMAL						 2					

enum battery_conditon {GOOD, BAD};
enum dataSet {FIRST, SECOND};
enum alertStatus {NOT_ASSERTED, ASSERTED};
enum params_list {TEMPERATURE, SOC, CHARGE_RATE};
enum rangeType {IN_RANGE, TEST_ID_01};
enum TemperatureWarningLevel{LOW_TEMP_BREACH, LOW_TEMP_WARNING, NORMAL_TEMP, HIGH_TEMP_WARNING, HIGH_TEMP_BREACH};
enum socWarningLevel{LOW_SOC_BREACH, LOW_SOC_WARNING, NORMAL_SOC, HIGH_SOC_WARNING, HIGH_SOC_BREACH};
enum chargeRateWarningLevel{LOW_CR_BREACH, LOW_CR_WARNING, NORMAL_CR, HIGH_CR_WARNING, HIGH_CR_BREACH};

/*Parameter validator Function declaration */
int temperatureOutOfRange (int warning_lvl);
int socOutOfRange (int warning_lvl);
int chargeRateExceedLimit (int warning_lvl);

struct bms
{
	float temperature;
	int soc;
	float chargeRate;
}g_battery_parameter;

typedef int (*isParamterNormal)(int);

struct alert
{
	int breached;
	char *parameter_name;
	isParamterNormal parameterOutOfRange;
	int warning_lvl;
	char *warning_type;
} parameter_alerts[TOTAL_PARAMETER] = 	{
											{NOT_ASSERTED, "TEMPERATURE", temperatureOutOfRange, HIGH_TEMP_WARNING, NULL},
											{NOT_ASSERTED, "SOC", socOutOfRange, NORMAL_SOC, NULL},
											{NOT_ASSERTED, "CHARGE_RATE", chargeRateExceedLimit, HIGH_CR_BREACH, NULL}
										};

struct socAlerts
{
	int min;
	int max;
	char *warning_type;
} socAlertRange[5] =	{
							{0, 20, "LOW_SOC_BREACH"},
							{20, 24, "LOW_SOC_WARNING"},
							{24, 75, "NORMAL_SOC"},
							{75, 80, "HIGH_TEMP_WARNING"},
							{80, 100, "HIGH_TEMP_BREACH"}
						};
struct temperatureAlerts
{
	float min;
	float max;
	char *warning_type;
}temperatureAlertRange[5] = {
								{0.0f, 5.0f, "LOW_TEMP_BREACH"},
								{5.0f, 10.0f, "LOW_TEMP_WARNING"},
								{10.0f, 40.0f, "NORMAL_TEMP"},
								{40.0f, 45.0f, "HIGH_TEMP_WARNING"},
								{45.0f, 60.0f, "HIGH_TEMP_BREACH"}
							};
							
struct chargeRateAlerts 
{
	float min;
	float max;
	char *warning_type;
}chargeRateAlertRange[5] = {
									{0.0f, 0.4f, "LOW_CR_BREACH"},
									{0.4f, 0.6f, "LOW_CR_WARNING"},
									{0.6f, 0.8f, "NORMAL_CR"},
									{0.8f, 0.9f, "HIGH_CR_WARNING"},
									{0.8f, 1.0f, "HIGH_CR_BREACH"}
							};
#endif