// *************************************************************************************************
//
// This code is part of the Sample Application to demonstrate the use of the QPropertyEditor library.
// It is distributed as public domain and can be modified and used by you without any limitations.
// 
// Your feedback is welcome!
//
// Author: Volker Wiendl
// Enum enhancement by Roman alias banal from qt-apps.org
// *************************************************************************************************


#include "Vec3fProperty.h"
#include "CustomTypes.h"

#include <qregexp.h>

Vec3fProperty::Vec3fProperty(const QString& name /*= QString()*/, QObject* propertyObject /*= 0*/, QObject* parent /*= 0*/) : Property(name, propertyObject, parent)
{
	m_x = new Property("x", this, this);
	m_y = new Property("y", this, this);
	m_z = new Property("z", this, this);
	setEditorHints("minimumX=-2147483647;maximumX=2147483647;minimumY=-2147483647;maximumY=2147483647;minimumZ=-2147483647;maximumZ=2147483647;");
}

QVariant Vec3fProperty::value(int role) const
{
	QVariant data = Property::value();
	if (data.isValid() && role != Qt::UserRole)
	{
		switch (role)
		{
		case Qt::DisplayRole:
			return tr("[ %1, %2, %3]").arg(data.value<Vec3f>().X).arg(data.value<Vec3f>().Y).arg(data.value<Vec3f>().Z);
		case Qt::EditRole:
			return tr("%1, %2, %3").arg(data.value<Vec3f>().X).arg(data.value<Vec3f>().Y).arg(data.value<Vec3f>().Z);
		};
	}
	return data;
}

void Vec3fProperty::setValue(const QVariant& value)
{
	if (value.type() == QVariant::String)
	{
		QString v = value.toString();				
		QRegExp rx("([+-]?([0-9]*[\\.,])?[0-9]+(e[+-]?[0-9]+)?)");
		rx.setCaseSensitivity(Qt::CaseInsensitive);
		int count = 0;
		int pos = 0;
		float x = 0.0f, y = 0.0f, z = 0.0f;
		while ((pos = rx.indexIn(v, pos)) != -1) 
		{
			if (count == 0)
				x = rx.cap(1).toDouble();
			else if (count == 1)
				y = rx.cap(1).toDouble();
			else if (count == 2)
				z = rx.cap(1).toDouble();
			else if (count > 2)
				break;
			++count;
			pos += rx.matchedLength();
		}
		m_x->setProperty("x", x);
		m_y->setProperty("y", y);
		m_z->setProperty("z", z);
		Property::setValue(QVariant::fromValue(Vec3f(x, y, z)));
	}
	else
		Property::setValue(value);
}

void Vec3fProperty::setEditorHints(const QString& hints)
{
	m_x->setEditorHints(parseHints(hints, 'X'));
	m_y->setEditorHints(parseHints(hints, 'Y'));
	m_z->setEditorHints(parseHints(hints, 'Z'));
}

float Vec3fProperty::x() const
{
	return value().value<Vec3f>().X;
}

void Vec3fProperty::setX(float x)
{
	Property::setValue(QVariant::fromValue(Vec3f(x, y(), z())));
}

float Vec3fProperty::y() const
{
	return value().value<Vec3f>().Y;
}

void Vec3fProperty::setY(float y)
{
	Property::setValue(QVariant::fromValue(Vec3f(x(), y, z())));
}

float Vec3fProperty::z() const
{
	return value().value<Vec3f>().Z;
}

void Vec3fProperty::setZ(float z)
{
	Property::setValue(QVariant::fromValue(Vec3f(x(), y(), z)));
}

QString Vec3fProperty::parseHints(const QString& hints, const QChar component )
{
	QRegExp rx(QString("(.*)(")+component+QString("{1})(=\\s*)(.*)(;{1})"));
	rx.setMinimal(true);
	int pos = 0;
	QString componentHints;
	while ((pos = rx.indexIn(hints, pos)) != -1) 
	{
		// cut off additional front settings (TODO create correct RegExp for that)
		if (rx.cap(1).lastIndexOf(';') != -1)			
			componentHints += QString("%1=%2;").arg(rx.cap(1).remove(0, rx.cap(1).lastIndexOf(';')+1)).arg(rx.cap(4));
		else
			componentHints += QString("%1=%2;").arg(rx.cap(1)).arg(rx.cap(4));
		pos += rx.matchedLength();
	}
	return componentHints;
}
