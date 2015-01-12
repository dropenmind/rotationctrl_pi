/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  rotation control Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2015 by Sean D'Epagnier                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#ifndef _WATCHMANPI_H_
#define _WATCHMANPI_H_

#include "wx/wx.h"

#include <wx/fileconf.h>

#include "version.h"

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    13

#define ABOUT_AUTHOR_URL "http://seandepagnier.users.sourceforge.net"

#include "ocpn_plugin.h"

#ifdef __MSVC__
#include <float.h>
#include <iostream>
#include <limits>

# if !defined(M_PI)
# define M_PI		3.14159265358979323846	/* pi */
# endif

# if !defined(NAN)
# define NAN std::numeric_limits<double>::quiet_NaN ()
# endif

# if !defined(INFINITY)
# define INFINITY std::numeric_limits<double>::infinity ()
# endif

#define isnan _isnan
#define isinf(x) (!_finite(x) && !_isnan(x))

inline double trunc(double d){ return (d>0) ? floor(d) : ceil(d) ; }
inline double round(double n) { return n < 0.0 ? ceil(n - 0.5) : floor(n + 0.5); }

# if !defined(snprintf)
# define snprintf _snprintf
# endif
#define vsnprintf _vsnprintf
#define strcasecmp _stricmp
#define strncasecmp _strnicmp

#endif

double heading_resolve(double degrees);

//----------------------------------
//    The PlugIn Class Definition
//----------------------------------

#define TOOL_POSITION    -1          // Request default positioning of toolbar tool

enum RotationTools {MANUAL_CCW, MANUAL_CW, NORTH_UP, SOUTH_UP, COURSE_UP,
                    HEADING_UP, ROUTE_UP, WIND_UP, NUM_ROTATION_TOOLS};

class rotationctrl_pi : public wxEvtHandler, public opencpn_plugin_113
{
public:

    rotationctrl_pi(void *ppimgr);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

      int GetToolbarToolCount(void);

      void OnToolbarToolCallback(int id);

      void OnTimer( wxTimerEvent & );

//    Optional plugin overrides
      void SetColorScheme(PI_ColorScheme cs);

      void    ShowPreferencesDialog( wxWindow* );

      PlugIn_Position_Fix_Ex &LastFix() { return m_lastfix; }

      wxDateTime m_LastFixTime;

      double m_sog, m_cog;

      int m_filter_msecs;
      double m_filter_lp;

      int               m_leftclick_tool_ids[NUM_ROTATION_TOOLS];

protected:

      PlugIn_Position_Fix_Ex m_lastfix, m_lasttimerfix;

private:
      bool    LoadConfig(void);
      bool    SaveConfig(void);

      void SetCurrentViewPort(PlugIn_ViewPort &vp) { m_vp = vp; }
      void    SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);

      wxTimer m_Timer;

      PlugIn_ViewPort m_vp;
      int m_currenttool;
};

#endif