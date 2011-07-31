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
/*!
  \class ptImageSpot

  \brief Base class for storing image spot data.

  This class stores the data for a single image spot. Values you pass to a
  ptImageSpot object must always be in current pipe size scale. Similarly
  ptImageSpot always return values in current pipe size scale.

  Internally (and in the ini file) everything is stored in 1:1 pipe size scale.
*/

#ifndef PTIMAGESPOT_H
#define PTIMAGESPOT_H

#include <QtGlobal>
#include <QPoint>
#include <stdint.h>

#include "../ptSettings.h"


class ptImageSpot {
////////////////////////////////////////////////////////////////////////////////
//
// PUBLIC members
//
////////////////////////////////////////////////////////////////////////////////
public:
  /*! Creates an empty and disabled image spot or loads a spot from the current ini file.
    \param CreateFromIni
      Optional flag for creation from ini file. Set to \\1 to create the spot
      from the currently opened ini file. Default is \\0 (no load from ini). The ini’s
      \\ReadArray() must be set appropriately before you can use this.
  */
  ptImageSpot(const short CreateFromIni = 0);

  /*! Create an image spot with specific values. */
  ptImageSpot(const short isEnabled,
              const uint spotX,
              const uint spotY,
              const uint radiusW,
              const uint radiusH,
              const float angle,
              const uint edgeRadius,
              const float edgeBlur,
              const float opacity);

  /*! Returns the spot's rotation angle in degrees clockwise. */
  inline float angle() const { return m_Angle * (1 >> Settings->GetInt("PipeSize")); }

  /*! Returns the edge blur value. */
  inline float edgeBlur() const { return m_EdgeBlur; }

  /*! Returns the radius of the blurred outer edge. */
  inline uint edgeRadius() const { return m_EdgeRadius * (1 >> Settings->GetInt("PipeSize")); }

  /*! Returns the spot's enabled status. */
  inline short isEnabled() const { return m_IsEnabled; }

  /*! Returns the global opacity. \\0.0 is fully transparent and
      \\1.0 is fully opaque.
  */
  inline float opactiy() const { return m_Opacity; }

  /*! Returns the horizontal radius. */
  inline uint radiusH() const { return m_RadiusH * (1 >> Settings->GetInt("PipeSize")); }

  /*! Returns the vertical radius. */
  inline uint radiusW() const { return m_RadiusW * (1 >> Settings->GetInt("PipeSize")); }

  /*! Returns the spot's center position. */
  QPoint pos() const;

  /*! Sets the spot's rotation angle in degrees clockwise. */
  void setAngle(float angle);

  /*! Sets edge blur. */
  void setEdgeBlur(const float blur);

  /*! Sets the size of the blurred edge. */
  void setEdgeRadius(uint radius);

  /*! Enables or disables the spot. Disabled spots are ignored when running
      the pipe.
  */
  inline void setEnabled(const short state) { m_IsEnabled = state; }

  /*! Sets the spot's global opacity.
      \param opacity
        Opacity in the range from \\0.0 (fully transparent) to \\1.0
        (fully opaque).
  */
  void setOpacity(const float opacity);

  /*! Moves the spot to a new position.

      Derived classes should re-implement \\setPos() to move the complete spot including repairers
      or any other additional elements. The default ptImageSpot implementation moves only spot
      itself.
  */
  virtual void setPos(uint x, uint y);

  /*! Sets the horizontal radius in pixels. */
  void setRadiusH(uint radius);

  /*! Sets the vertical radius in pixels. */
  void setRadiusW(uint radius);

  /*! Writes the spot’s data to the currently opened ini file.
    The ini’s \\WriteArray() must be set appropriately before you use this.
  */
  virtual void WriteToIni();


////////////////////////////////////////////////////////////////////////////////
//
// PROTECTED members
//
////////////////////////////////////////////////////////////////////////////////
protected:
  float m_Angle;
  float m_EdgeBlur;
  uint m_EdgeRadius;
  short m_IsEnabled;
  float m_Opacity;  // global transparency percentage
  uint m_RadiusW;
  uint m_RadiusH;
  QPoint m_Pos;  // Position is the center of the spot
  uint16_t* m_WeightMatrix;

  void UpdateWeight();


////////////////////////////////////////////////////////////////////////////////
//
// PRIVATE members
//
////////////////////////////////////////////////////////////////////////////////
private:
  short m_init;

};

#endif
