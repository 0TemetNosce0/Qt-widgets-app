#include "util.h"

#include <QSettings>

bool Util::writeInit(QString path, QString user_key, QString user_value)
{
    if(path.isEmpty() || user_key.isEmpty())
    {
        return false;
    }
    else
    {
        //���������ļ���������
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        //����Ϣд�������ļ�
        config->beginGroup("config");
        config->setValue(user_key, user_value);
        config->endGroup();

        return true;
    }
}

bool Util::readInit(QString path, QString user_key, QString &user_value)
{
    user_value = QString("");
    if(path.isEmpty() || user_key.isEmpty())
    {
        return false;
    }
    else
    {
        //���������ļ���������
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        //��ȡ�û�������Ϣ
        user_value = config->value(QString("config/") + user_key).toString();

        return true;
    }
}

