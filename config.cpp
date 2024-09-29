#include "config.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


CConfig::CConfig() {}

QString CConfig::read_config()
{
    QString configfile="../../KH.cfg";                              // since this program is only started via Qt we use a fixed, relative path
    QString dbname=NULL;

    QFile File(configfile);
    if (!File.exists())
    {
        // config must exist
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
                // comments start with a #
                continue;
            }
            else
            {
                // uncommented line should be the path+filename of the db
                dbname = filedata;
            }
        }
    }
    File.close();
    // dbname="KH.db";
    return dbname;
}
