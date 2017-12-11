#include "util.h"
#include <QFile>
#include <QDomDocument>
#include <QCoreApplication>

QString Util::exePath()
{
    return QCoreApplication::applicationDirPath();
}

QList<ToolUtil> Util::parse(QString file_name)
{
    QList<ToolUtil> toolList;

    if(file_name.isEmpty())
    {
        return toolList;
    }

    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return toolList;
    }

    QDomDocument document;
    QString error;
    int row = 0, column = 0;
    if(!document.setContent(&file, false, &error, &row, &column))
    {
        return toolList;
    }

    if(document.isNull())
    {
        return toolList;
    }

    QDomElement root = document.documentElement();
    QDomNodeList list = root.childNodes();
    int count = list.count();
    for(int i=0; i < count; ++i)
    {
        QDomNode dom_node = list.item(i);
        QDomElement element = dom_node.toElement();

        //获取子节点，数目为，包括：toolexename、tooltip、toolicon、website
        QDomNodeList child_list = element.childNodes();
        int child_count = child_list.count();

        ToolUtil tool;

        for(int j = 0; j < child_count; ++j)
        {
            QDomNode child_dom_node = child_list.item(j);
            QDomElement child_element = child_dom_node.toElement();
            QString child_tag_name = child_element.tagName();
            QString child__tag_value = child_element.text();

            if(QString::compare(child_tag_name, "parentID") == 0)
            {
                 tool.parentId = child__tag_value.toInt();
            }
            else if(QString::compare(child_tag_name, "ID") == 0)
            {
                 tool.id = child__tag_value.toInt();
            }
            else if(QString::compare(child_tag_name, "text") == 0)
            {
                 tool.text = child__tag_value;
            }
            else if(QString::compare(child_tag_name, "tooltip") == 0)
            {
                 tool.tooltip = child__tag_value;
            }
            else if(QString::compare(child_tag_name, "toolicon") == 0)
            {
                 tool.toolicon = child__tag_value;
            }
       }
        toolList.append(tool);
    }

    return toolList;
}
