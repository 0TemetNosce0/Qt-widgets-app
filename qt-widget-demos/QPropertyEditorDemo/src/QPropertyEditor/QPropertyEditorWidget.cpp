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

#include "QPropertyEditorWidget.h"
#include "QPropertyModel.h"
#include "QVariantDelegate.h"
#include "Property.h"

QPropertyEditorWidget::QPropertyEditorWidget(QWidget* parent /*= 0*/)
    : QTreeView(parent)
{
	m_model = new QPropertyModel(this);		
	setModel(m_model);
	setItemDelegate(new QVariantDelegate(this));
}


QPropertyEditorWidget::~QPropertyEditorWidget()
{
}

void QPropertyEditorWidget::addObject(QObject* propertyObject)
{
	m_model->addItem(propertyObject);
	expandToDepth(0);
}

void QPropertyEditorWidget::setObject(QObject* propertyObject)
{
	m_model->clear();
	if (propertyObject)
    {
        addObject(propertyObject);
    }
}

void QPropertyEditorWidget::updateObject(QObject* propertyObject)
{
	if (propertyObject)
    {
        m_model->updateItem(propertyObject);
    }
}

void QPropertyEditorWidget::registerCustomPropertyCB(UserTypeCB callback)
{
	m_model->registerCustomPropertyCB(callback);
}

void QPropertyEditorWidget::unregisterCustomPropertyCB(UserTypeCB callback)
{
	m_model->unregisterCustomPropertyCB(callback);
}

