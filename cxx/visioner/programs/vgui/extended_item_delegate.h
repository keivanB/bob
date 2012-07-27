/**
 * @file visioner/programs/vgui/extended_item_delegate.h
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2012 Idiap Research Institute, Martigny, Switzerland
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EXTENDED_ITEM_DELEGATE_H 
#define EXTENDED_ITEM_DELEGATE_H

#include <QtGui>

/**
 * Qt item delegate to be used within an ExtendedTable object. Mainly because
 * there might be elements in a table that need to be drawn different.
 */

class ExtendedItemDelegate : public QItemDelegate {

  Q_OBJECT

  public:

    // Constructor
    ExtendedItemDelegate(QWidget* parent)
      :	QItemDelegate(parent)
    {
    }

    // Overriden - paint the cell accordingly with the stored data type
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

};

#endif
