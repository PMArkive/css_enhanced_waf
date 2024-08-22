#ifndef BASETOGGLE_H
#define BASETOGGLE_H
#pragma once

#include "c_baseentity.h"

//-----------------------------------------------------------------------------
// Things that toggle (buttons/triggers/doors) need this
//-----------------------------------------------------------------------------
enum TOGGLE_STATE
{
	TS_AT_TOP,
	TS_AT_BOTTOM,
	TS_GOING_UP,
	TS_GOING_DOWN
};

// doors
#define SF_DOOR_ROTATE_YAW			0		// yaw by default
#define	SF_DOOR_START_OPEN_OBSOLETE	1
#define SF_DOOR_ROTATE_BACKWARDS	2
#define SF_DOOR_NONSOLID_TO_PLAYER	4
#define SF_DOOR_PASSABLE			8
#define SF_DOOR_ONEWAY				16
#define	SF_DOOR_NO_AUTO_RETURN		32
#define SF_DOOR_ROTATE_ROLL			64
#define SF_DOOR_ROTATE_PITCH		128
#define SF_DOOR_PUSE				256	// door can be opened by player's use button.
#define SF_DOOR_NONPCS				512	// NPC can't open
#define SF_DOOR_PTOUCH				1024 // player touch opens
#define SF_DOOR_LOCKED				2048	// Door is initially locked
#define SF_DOOR_SILENT				4096	// Door plays no audible sound, and does not alert NPCs when opened
#define	SF_DOOR_USE_CLOSES			8192	// Door can be +used to close before its autoreturn delay has expired.
#define SF_DOOR_SILENT_TO_NPCS		16384	// Does not alert NPC's when opened.
#define SF_DOOR_IGNORE_USE			32768	// Completely ignores player +use commands.
#define SF_DOOR_NEW_USE_RULES		65536	// For func_door entities, behave more like prop_door_rotating with respect to +USE (changelist 242482)

class C_BaseToggle : public C_BaseEntity
{
	DECLARE_CLASS(C_BaseToggle, C_BaseEntity);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
public:
	C_BaseToggle();

	virtual bool		KeyValue( const char *szKeyName, const char *szValue );
	virtual bool		KeyValue( const char *szKeyName, Vector vec ) { return BaseClass::KeyValue( szKeyName, vec ); };
	virtual bool		KeyValue( const char *szKeyName, float flValue ) { return BaseClass::KeyValue( szKeyName, flValue ); };

	TOGGLE_STATE		m_toggle_state;
	float				m_flMoveDistance;// how far a door should slide or rotate
	float				m_flWait;
	float				m_flLip;

	Vector				m_vecPosition1;
	Vector				m_vecPosition2;

	QAngle				m_vecMoveAng;
	QAngle				m_vecAngle1;
	QAngle				m_vecAngle2;

	float				m_flHeight;
	EHANDLE				m_hActivator;
	Vector				m_vecFinalDest;
	QAngle				m_vecFinalAngle;

	int					m_movementType;

	virtual float	GetDelay( void ) { return m_flWait; }

	// common member functions
	void LinearMove( const Vector &vecDest, float flSpeed );
	void LinearMoveDone( void );
	void AngularMove( const QAngle &vecDestAngle, float flSpeed );
	void AngularMoveDone( void );
	bool IsLockedByMaster( void );
	virtual void MoveDone( void );

	static float AxisValue( int flags, const QAngle &angles );
	void AxisDir( void );
	static float AxisDelta( int flags, const QAngle &angle1, const QAngle &angle2 );

	string_t m_sMaster;		// If this button has a master switch, this is the targetname.
							// A master switch must be of the multisource type. If all
							// of the switches in the multisource have been triggered, then
							// the button will be allowed to operate. Otherwise, it will be
							// deactivated.
};



#endif // BASETOGGLE_H
