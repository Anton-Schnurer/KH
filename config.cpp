#include "config.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


CConfig::CConfig() {}

QString CConfig::read_config()
{
    QString configfile="../../KH.cfg";
    QString dbname=NULL;

    QFile File(configfile);
    if (!File.exists())
    {
        QMessageBox msg;
        msg.setWindowTitle("Config Error");
        msg.setText("Config File does not exist");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return dbname;
    }

    if (File.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&File);
        QString filedata;
        while (!stream.atEnd())
        {
            filedata = stream.readLine();
            if (filedata.startsWith("#"))
            {
                continue;
            }
            else
            {
                dbname = filedata;
            }
        }
    }
    File.close();
    // dbname="KH.db";
    return dbname;
}
