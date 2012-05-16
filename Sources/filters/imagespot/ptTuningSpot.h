/*******************************************************************************
**
** Photivo
**
** Copyright (C) 2012 Bernd Schoeler <brjohn@brother-john.net>
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

#ifndef PTLOCALSPOT_H
#define PTLOCALSPOT_H

#include <memory>

#include "ptImageSpot.h"
#include <ptCurve.h>

class ptCfgItem;

//==============================================================================

const QString CSpotHasMaxRadiusId  ="HasMaxRadius";
const QString CSpotMaxRadiusId     ="MaxRadius";
const QString CSpotChromaWeightId  ="ChromaWeight";
const QString CSpotThresholdId     ="Threshold";
const QString CSpotLumaCurveId     ="LumaCurve";
const QString CSpotSaturationId    ="Saturation";
const QString CSpotIsAdaptiveSatId ="IsAdaptiveSat";
const QString CSpotColorShiftId    ="ColorShift";

//==============================================================================

class ptTuningSpot: public ptImageSpot {
public:
  explicit ptTuningSpot(const QList<ptCfgItem> *ADefaults);
  ~ptTuningSpot();
  ptCurve *curve() { return FCurve.get(); }


protected:
  TConfigStore  doStoreConfig(const QString &APrefix) const;
  void          doLoadConfig(const TConfigStore &AConfig, const QString &APrefix);
  QVariant      doGetValue(const QString &AKey) const;
  bool          doSetValue(const QString &AKey, const QVariant AValue);


private:
  std::shared_ptr<ptCurve>  FCurve;
  ptCfgItem                *FDefaults;

};

#endif // PTLOCALSPOT_H
