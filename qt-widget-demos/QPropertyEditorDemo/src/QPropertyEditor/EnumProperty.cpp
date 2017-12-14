// *************************************************************************************************
//
// QPropertyEditor v 0.3
//   
// --------------------------------------
// Copyright (C) 2007 Volker Wiendl
// Acknowledgements to Roman alias banal from qt-apps.org for the Enum enhancement
//
//
// The QPropertyEditor Library is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 3 of the License 
//
// The Horde3D Scene Editor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// *************************************************************************************************
#include "EnumProperty.h"


EnumProperty::EnumProperty(const QString &name /* = QString()*/, 
						   QObject *propertyObject /* = 0*/, QObject *parent /* = 0*/)
    : Property(name, propertyObject, parent)
{
	// get the meta property object
	const QMetaObject* meta = propertyObject->metaObject();
	QMetaProperty prop = meta->property(meta->indexOfProperty(qPrintable(name)));

	// if it is indeed an enum type, fill the QStringList member with the keys
    if(prop.isEnumType())
    {
		QMetaEnum qenum = prop.enumerator();
        for(int i=0; i < qenum.keyCount(); i++)
        {
			m_enum << qenum.key(i);
		}
	}
}

QVariant EnumProperty::value(int role /* = Qt::UserRole */) const
{
    if(role == Qt::DisplayRole)
    {
        if (m_propertyObject)
        {
			// resolve the value to the corresponding enum key
			int index = m_propertyObject->property(qPrintable(objectName())).toInt();

			const QMetaObject* meta = m_propertyObject->metaObject();
			QMetaProperty prop = meta->property(meta->indexOfProperty(qPrintable(objectName())));
			return QVariant(prop.enumerator().valueToKey(index));
        }
        else
        {
			return QVariant();
		}
    }
    else
    {
		return Property::value(role);
	}
}

QWidget* EnumProperty::createEditor(QWidget* parent, const QStyleOptionViewItem& option)
{
	// create a QComboBox and fill it with the QStringList values
    Q_UNUSED(option);
	QComboBox* editor = new QComboBox(parent);
	editor->addItems(m_enum);
	
	connect(editor, SIGNAL(currentIndexChanged(const QString)), 
		this, SLOT(valueChanged(const QString)));
	return editor;
}

bool EnumProperty::setEditorData(QWidget *editor, const QVariant &data)
{
	QComboBox* combo = 0;
    if(combo = qobject_cast<QComboBox*>(editor))
    {
		int value = data.toInt();
		const QMetaObject* meta = m_propertyObject->metaObject();
		QMetaProperty prop = meta->property(meta->indexOfProperty(qPrintable(objectName())));
		
		int index = combo->findText(prop.enumerator().valueToKey(value));
		if(index == -1)
        {
            return false;
        }

		combo->setCurrentIndex(index);
    }
    else
    {
		return false;
	}

	return true;
}

QVariant EnumProperty::editorData(QWidget *editor)
{
	QComboBox* combo = 0;

    if(combo = qobject_cast<QComboBox*>(editor))
    {
		return QVariant(combo->currentText());
    }
    else
    {
		return QVariant();
	}
}

void EnumProperty::valueChanged(const QString item)
{
	setValue(QVariant(item));
}
