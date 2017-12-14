#include "console_reader.h"

console_reader::console_reader(QObject *parent)
    : QObject(parent)
{
    internal_splitBehavior = QString::KeepEmptyParts;
    m_process.setOutputChannelMode(QProcess::MergedChannels);
    QObject::connect(&m_process, SIGNAL(readyRead()), this, SLOT(read_console_output()));
}

console_reader::~console_reader()
{
    m_process.kill();
    m_process.waitForFinished(-1);
}

QString console_reader::QByteArray_to_QString(QByteArray & m_byteArray)
{
    return QString::fromLocal8Bit(m_byteArray);
}

void console_reader::read_console_output()
{
    QByteArray temp_bytearray;
    bool newLineAtTheEnd;
    QStringList m_output_lines;
    temp_bytearray = m_process.readAllStandardOutput();
    m_uncomplete_line.append(QByteArray_to_QString(temp_bytearray));

    m_uncomplete_line.replace("\x0D\x0A", "\x0A");
    m_uncomplete_line.replace("\x0D", "\x0A");

    newLineAtTheEnd = m_uncomplete_line.endsWith(10);

    m_output_lines = m_uncomplete_line.split(10, internal_splitBehavior);

    if (m_output_lines.isEmpty())
    {
        m_uncomplete_line = "";
    }
    else
    {
        if (!newLineAtTheEnd)
        {
            m_uncomplete_line = m_output_lines.takeLast();
        }
        else
        {
            m_uncomplete_line = "";
        }

        if (!m_output_lines.isEmpty())
        {
            interpretate_console_output(m_output_lines);
        }
    }
}
