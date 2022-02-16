#ifndef __CHECKER_H_
#define __CHECKER_H_

#define TEMP_MIN			0.0f
#define TEMP_MAX			45.0f
#define SOC_MIN				20
#define SOC_MAX				80
#define CHARGERATE_LIMIT	0.8f
#define TOTAL_PARAMETER		3
#define TOTAL_DATA_SETS     6

enum battery_conditon {GOOD, BAD};
enum dataSet {FIRST, SECOND};
enum alertStatus {NOT_ASSERTED, ASSERTED};
enum params_list {TEMPERATURE, SOC, CHARGE_RATE};
enum rangeType {IN_RANGE, TEST_ID_01};

/*Parameter validator Function declaration */
int temperatureOutOfRange ();
int socOutOfRange ();
int chargeRateExceedLimit ();

struct bms
{
	float temperature;
	int soc;
	float chargeRate;
}g_battery_parameter;

typedef int (*isParamterNormal)(void);

struct alert
{
	int breached;
	char *parameter_name;
	isParamterNormal parameterOutOfRange;
} parameter_alerts[TOTAL_PARAMETER] = 	{
											{NOT_ASSERTED, "TEMPERATURE", temperatureOutOfRange},
											{NOT_ASSERTED, "SOC", socOutOfRange},
											{NOT_ASSERTED, "CHARGE_RATE", chargeRateExceedLimit}
										};


#endif