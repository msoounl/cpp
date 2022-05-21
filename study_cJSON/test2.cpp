#include <iostream>
extern "C" {
    #include "cJSON/cJSON.h"
}
using namespace std;

int main(int argc, char *argv[]) {
    cJSON *cJSON_test = cJSON_CreateObject();
    cJSON_AddStringToObject(cJSON_test, "name", "msoounl");
    cJSON_AddNumberToObject(cJSON_test, "age", 20);

    cout << cJSON_Print(cJSON_test) << endl;
    return 0;
}