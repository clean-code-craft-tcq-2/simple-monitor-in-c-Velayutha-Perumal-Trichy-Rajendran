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

typedef int (*isParamterNormal)(void);

typedef struct _alerts_
{
	int breached;
	char *parameter_name;
	isParamterNormal parameterOutOfRange;
}alert;

typedef struct bms
{
	float temperature;
	int soc;
	float chargeRate;
}BMS;


int temperatureOutOfRange ();
int socOutOfRange ();
int chargeRateExceedLimit ();

#endif