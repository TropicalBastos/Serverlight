#ifndef SERVERLIGHT_CONFIG
#define SERVERLIGHT_CONFIG

#include <fstream>
#include <ios>

#define DELIMITER_EQUALS '='
#define DELIMITER_NEWLINE '\n'
#define CHAR_BUFF 256
#define CONF_PATH "serverlight.conf"

//mini parser for the config
//using c++ standards for brevity

namespace config{

    std::ifstream input(CONF_PATH);
    bool end = false;

    /* Recursive function to lookup key and return
    its value as a char pointer */

    char* getValue(const char * keyToGet){

        if(end){
            input.open(CONF_PATH);
            end = false;
        }

        char key[CHAR_BUFF];
        char value[CHAR_BUFF];
        input.getline(key, sizeof(char) * CHAR_BUFF, DELIMITER_EQUALS);
        input.getline(value, sizeof(char) * CHAR_BUFF, DELIMITER_NEWLINE);
        if(strcmp(key, keyToGet) != 0){
            return getValue(keyToGet);
        }
        input.close();
        char* valueToReturn = (char *) malloc(sizeof(char) * CHAR_BUFF);
        valueToReturn = strcpy(valueToReturn, value);
        end = true;
        return valueToReturn;

    }

}

#endif