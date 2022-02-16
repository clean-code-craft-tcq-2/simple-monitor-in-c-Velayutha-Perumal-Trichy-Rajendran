#ifndef __CHECKER_H_
#define __CHECKER_H_

#define TEMP_MIN			0.0f
#define TEMP_MAX			45.0f
#define SOC_MIN				20
#define SOC_MAX				80
#define CHARGERATE_LIMIT	0.8f
#define TOTAL_PARAMETER		3

enum status {GOOD, BAD};
enum alertStatus {NOT_ASSERTED, ASSERTED};
enum battery_conditon {NOT_OK, OK};
enum params_list {TEMPERATURE, SOC, CHARGE_RATE};
enum rangeType {IN_RANGE, TEST_ID_01};

typedef struct _alerts_
{
	int sendAlert;
	char *parameter_name;
}alert;

typedef struct bms
{
	float temperature;
	int soc;
	float chargeRate;
	
}BMS;
#endif