/*******************************************************************************
**
** Photivo
**
** Copyright (C) 2011 Bernd Schoeler <brjohn@brother-john.net>
**
** This file is part of Photivo.
**
** Photivo is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License version 3
** as published by the Free Software Foundation.
**
** Photivo is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Photivo.  If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************/
/*
** Management class for spot repair image spots, based on QList.
**
** IMPORTANT! The caller is responsible for creating ptImageSpot instances that
** should appear in the list, use "new". DO NOT delete them yourself, the list
** takes care of that. Exception: the take...() functions that remove the object
** return from the list and return the object itself.
**
*******************************************************************************/

#include "ptImageSpotList.h"
#include "../ptSettings.h"

extern ptSettings* Settings;


////////////////////////////////////////////////////////////////////////////////
//
// constructor and destructor.
//
////////////////////////////////////////////////////////////////////////////////
ptImageSpotList::ptImageSpotList(const QString IniPrefix /*= ""*/)
: QList<ptImageSpot*>()
{
  m_IniName = IniPrefix + "Spot";
}

ptImageSpotList::~ptImageSpotList() {
  while (!isEmpty()) {
    delete takeFirst();
  }
}


////////////////////////////////////////////////////////////////////////////////
//
// overwritten methods from QList
//
////////////////////////////////////////////////////////////////////////////////
void ptImageSpotList::clear() {
  while (!isEmpty()) {
    delete takeFirst();
  }
}

void ptImageSpotList::removeAt(int i) {
  delete takeAt(i);
}

void ptImageSpotList::removeFirst() {
  delete takeFirst();
}

void ptImageSpotList::removeLast() {
  delete takeLast();
}

void ptImageSpotList::replace(int i, ptImageSpot *const& NewSpot) {
  delete at(i);
  QList::replace(i, NewSpot);
}


////////////////////////////////////////////////////////////////////////////////
//
// WriteToIni()
//
////////////////////////////////////////////////////////////////////////////////
void ptImageSpotList::WriteToIni() {
  // Clear old stored spots
  Settings->m_IniSettings->beginGroup(m_IniName);
  Settings->m_IniSettings->remove("");
  Settings->m_IniSettings->endGroup();

  // Save the new ones
  Settings->m_IniSettings->beginWriteArray(m_IniName);
  for (int i = 0; i < this->count(); i++) {
    Settings->m_IniSettings->setArrayIndex(i);
    at(i)->WriteToIni();
  }
  Settings->m_IniSettings->endArray();
}
