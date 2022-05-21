#include <stdio.h>
#include "cJSON/cJSON.h"
int main(int argc, char *argv[]) {
    cJSON *cJSON_test = cJSON_CreateObject();
    cJSON_AddStringToObject(cJSON_test, "name", "msoounl");
    cJSON_AddNumberToObject(cJSON_test, "age", 20);

    printf("%s\n", cJSON_Print(cJSON_test));

    return 0;
}