/*
 * Stellarium
 * Copyright (C) 2008 Fabien Chereau
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef _STELGUI_HPP_
#define _STELGUI_HPP_

#ifndef NO_GUI

#include "StelModule.hpp"
#include "StelObject.hpp"
#include "StelGuiBase.hpp"
#include "StelStyle.hpp"

#include <QGraphicsTextItem>

class QGraphicsSceneMouseEvent;
class QTimeLine;
class StelButton;
class BottomStelBar;
class InfoPanel;
class ConfigurationDialog;
class DateTimeDialog;
class HelpDialog;
class LocationDialog;
class SearchDialog;
class ViewDialog;
class ShortcutsDialog;
class AstroCalcDialog;
class BookmarksDialog;
#ifdef ENABLE_SCRIPT_CONSOLE
class ScriptConsole;
#endif

//! @class StelGui
//! Main class for the GUI based on QGraphicView.
//! It manages the various qt configuration windows, the buttons bars, the list of shortcuts.
class StelGui : public QObject, public StelGuiBase
{
	Q_OBJECT
	Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged)
	Q_PROPERTY(bool autoHideHorizontalButtonBar READ getAutoHideHorizontalButtonBar WRITE setAutoHideHorizontalButtonBar NOTIFY autoHideHorizontalButtonBarChanged)
	Q_PROPERTY(bool autoHideVerticalButtonBar READ getAutoHideVerticalButtonBar WRITE setAutoHideVerticalButtonBar NOTIFY autoHideVerticalButtonBarChanged)
	Q_PROPERTY(bool flagShowFlipButtons READ getFlagShowFlipButtons WRITE setFlagShowFlipButtons NOTIFY flagShowFlipButtonsChanged)
	Q_PROPERTY(bool flagShowNebulaBackgroundButton READ getFlagShowNebulaBackgroundButton WRITE setFlagShowNebulaBackgroundButton NOTIFY flagShowNebulaBackgroundButtonChanged)
	Q_PROPERTY(bool flagShowDSSButton READ getFlagShowDSSButton WRITE setFlagShowDSSButton NOTIFY  flagShowDSSButtonChanged)
	Q_PROPERTY(bool flagShowBookmarksButton READ getFlagShowBookmarksButton WRITE setFlagShowBookmarksButton NOTIFY flagShowBookmarksButtonChanged)
	Q_PROPERTY(bool flagShowICRSGridButton READ getFlagShowICRSGridButton WRITE setFlagShowICRSGridButton NOTIFY flagShowICRSGridButtonChanged)
	Q_PROPERTY(bool flagShowGalacticGridButton READ getFlagShowGalacticGridButton WRITE setFlagShowGalacticGridButton NOTIFY flagShowGalacticGridButtonChanged )
	Q_PROPERTY(bool flagShowEclipticGridButton READ getFlagShowEclipticGridButton WRITE setFlagShowEclipticGridButton NOTIFY flagShowEclipticGridButtonChanged )
	Q_PROPERTY(bool flagShowConstellationBoundariesButton READ getFlagShowConstellationBoundariesButton WRITE setFlagShowConstellationBoundariesButton NOTIFY flagShowConstellationBoundariesButtonChanged )

public:
	friend class ViewDialog;
	
	StelGui();
	virtual ~StelGui();

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class
	//! Initialize the StelGui object.
	virtual void init(QGraphicsWidget* topLevelGraphicsWidget);
	void update();

	StelStyle getStelStyle() const {return currentStelStyle;}
	
	///////////////////////////////////////////////////////////////////////////
	// Methods specific to the StelGui class
	//! Load a Qt style sheet to define the widgets style
	void loadStyle(const QString& fileName);
	
	//! Get the button bar at the bottom of the screen
	BottomStelBar* getButtonBar() const;
	
	//! Get the button bar of the left of the screen
	class LeftStelBar* getWindowsButtonBar() const;

	//! Get the SkyGui instance (useful for adding other interface elements).
	//! It will return a valid object only if called after init().
	class SkyGui* getSkyGui() const;

	//! returns true if the gui has completed init process.
	bool initComplete(void) const;

#ifdef ENABLE_SCRIPT_CONSOLE
	ScriptConsole* getScriptConsole() {return scriptConsole;}
#endif

	//! Used to force a refreshing of the GUI elements such as the button bars.
	virtual void forceRefreshGui();
	
	virtual void setVisible(bool b);

	virtual bool getVisible() const;

	virtual bool getAstroCalcVisible();

	virtual bool isCurrentlyUsed() const;
	
	virtual void setInfoTextFilters(const StelObject::InfoStringGroup& aflags);
	virtual const StelObject::InfoStringGroup& getInfoTextFilters() const;

public slots:
	//! Define whether the buttons toggling image flip should be visible
	void setFlagShowFlipButtons(bool b);
	//! Get whether the buttons toggling image flip are visible
	bool getFlagShowFlipButtons() const;

	//! Define whether the button toggling nebulae background should be visible
	void setFlagShowNebulaBackgroundButton(bool b);
	//! Get whether the button toggling nebulae background is visible
	bool getFlagShowNebulaBackgroundButton() const;

	//! Define whether the button toggling DSS survey should be visible
	void setFlagShowDSSButton(bool b);
	//! Get whether the button toggling DSS survey is visible
	bool getFlagShowDSSButton() const;

	//! Define whether the button toggling bookmarks should be visible
	void setFlagShowBookmarksButton(bool b);
	//! Get whether the button toggling bookmarks is visible
	bool getFlagShowBookmarksButton() const;

	//! Define whether the button toggling ICRS grid should be visible
	void setFlagShowICRSGridButton(bool b);
	//! Get whether the button toggling ICRS grid is visible
	bool getFlagShowICRSGridButton() const;

	//! Define whether the button toggling galactic grid should be visible
	void setFlagShowGalacticGridButton(bool b);
	//! Get whether the button toggling galactic grid is visible
	bool getFlagShowGalacticGridButton() const;

	//! Define whether the button toggling ecliptic grid should be visible
	void setFlagShowEclipticGridButton(bool b);
	//! Get whether the button toggling ecliptic grid is visible
	bool getFlagShowEclipticGridButton() const;

	//! Define whether the button toggling constellation boundaries should be visible
	void setFlagShowConstellationBoundariesButton(bool b);
	//! Get whether the button toggling constellation boundaries is visible
	bool getFlagShowConstellationBoundariesButton() const;

	//! Get the auto-hide status of the horizontal toolbar.
	bool getAutoHideHorizontalButtonBar() const;
	//! Set the auto-hide status of the horizontal toolbar.
	//! When set to true, the horizontal toolbar will auto-hide itself, only
	//! making an appearance when the mouse is nearby.  When false, it will
	//! remain on screen.
	//! @param b to hide or not to hide
	void setAutoHideHorizontalButtonBar(bool b);
	
	//! Get the auto-hide status of the vertical toolbar.
	bool getAutoHideVerticalButtonBar() const;
	//! Set the auto-hide status of the vertical toolbar.
	//! When set to true, the vertical toolbar will auto-hide itself, only
	//! making an appearance when the mouse is nearby.  When false, it will
	//! remain on screen.
	//! @param b to hide or not to hide
	void setAutoHideVerticalButtonBar(bool b);

#ifndef DISABLE_SCRIPTING
	//! change keys when a script is running / not running
	void setScriptKeys(bool b);
	void increaseScriptSpeed();
	void decreaseScriptSpeed();
	void setRealScriptSpeed();
	void stopScript();
	void pauseScript();
	void resumeScript();
#endif

	//! Hide or show the GUI.  Public so it can be called from scripts.
	void setGuiVisible(bool);	

signals:
	void visibleChanged(bool b);
	void autoHideHorizontalButtonBarChanged(bool b);
	void autoHideVerticalButtonBarChanged(bool b);
	void flagShowFlipButtonsChanged(bool b);
	void flagShowNebulaBackgroundButtonChanged(bool b);
	void flagShowDSSButtonChanged(bool b);
	void flagShowBookmarksButtonChanged(bool b);
	void flagShowICRSGridButtonChanged(bool b);
	void flagShowGalacticGridButtonChanged(bool b);
	void flagShowEclipticGridButtonChanged(bool b);
	void flagShowConstellationBoundariesButtonChanged(bool b);

private slots:
	void reloadStyle();
#ifndef DISABLE_SCRIPTING
	void scriptStarted();
	void scriptStopped();
#endif
	//! Load color scheme from the given ini file and section name
	void setStelStyle(const QString& section);
	void quit();	
	void updateI18n();
	void copySelectedObjectInfo(void);

private:
	//! convenience method to find an action in the StelActionMgr.
	StelAction* getAction(const QString& actionName);

	QGraphicsWidget* topLevelGraphicsWidget;

	class SkyGui* skyGui;

	StelButton* buttonTimeRewind;
	StelButton* buttonTimeRealTimeSpeed;
	StelButton* buttonTimeCurrent;
	StelButton* buttonTimeForward;

	StelButton* buttonGotoSelectedObject;

	LocationDialog* locationDialog;
	HelpDialog* helpDialog;
	DateTimeDialog* dateTimeDialog;
	SearchDialog* searchDialog;
	ViewDialog* viewDialog;
	ShortcutsDialog* shortcutsDialog;
	ConfigurationDialog* configurationDialog;
#ifdef ENABLE_SCRIPT_CONSOLE
	ScriptConsole* scriptConsole;
#endif
	AstroCalcDialog* astroCalcDialog;
	BookmarksDialog* bookmarksDialog;

	bool flagShowFlipButtons;
	StelButton* flipVert;
	StelButton* flipHoriz;

	bool flagShowNebulaBackgroundButton;
	StelButton* btShowNebulaeBackground;

	bool flagShowDSSButton;
	StelButton* btShowDSS;

	bool flagShowBookmarksButton;
	StelButton* btShowBookmarks;

	bool flagShowICRSGridButton;
	StelButton* btShowICRSGrid;

	bool flagShowGalacticGridButton;
	StelButton* btShowGalacticGrid;

	bool flagShowEclipticGridButton;
	StelButton* btShowEclipticGrid;

	bool flagShowConstellationBoundariesButton;
	StelButton* btShowConstellationBoundaries;

	bool initDone;

	QSizeF savedProgressBarSize;

	// Currently used StelStyle
	StelStyle currentStelStyle;

#ifndef DISABLE_SCRIPTING
	// We use a QStringList to save the user-configured buttons while script is running, and restore them later.
	QStringList scriptSaveSpeedbuttons;
#endif
};

#else // NO_GUI

#include "StelGuiBase.hpp"
#include <QProgressBar>

class StelGui : public StelGuiBase
{
public:
	StelGui() {;}
	~StelGui() {;}
	virtual void init(QGraphicsWidget* topLevelGraphicsWidget, class StelAppGraphicsWidget* stelAppGraphicsWidget) {;}
	virtual void updateI18n() {;}
	virtual void setStelStyle(const QString& section) {;}
	virtual void setInfoTextFilters(const StelObject::InfoStringGroup& aflags) {dummyInfoTextFilter=aflags;}
	virtual const StelObject::InfoStringGroup& getInfoTextFilters() const {return dummyInfoTextFilter;}
	virtual QProgressBar* addProgressBar() {return new QProgressBar;}
	virtual QAction* addGuiActions(const QString& actionName, const QString& text, const QString& shortCut, const QString& helpGroup, bool checkable=true, bool autoRepeat=false) {return Q_NULLPTR;}
	virtual void forceRefreshGui() {;}
	virtual void setVisible(bool b) {visible=b;}
	virtual bool getVisible() const {return visible;}
	virtual bool isCurrentlyUsed() const {return false;}
private:
	StelObject::InfoStringGroup dummyInfoTextFilter;
	bool visible;
};

#endif

#endif // _STELGUI_HPP_
