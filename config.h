#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class CConfig
{
public:
    CConfig();

    QString read_config();                              // reads the database path+name from the config file

};

#endif // CONFIG_H
