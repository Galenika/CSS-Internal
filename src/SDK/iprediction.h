#pragma once

#include "Vector.h"

class C_BasePlayer;
class IMoveHelper;
class IPrediction
{
public:
	virtual			~IPrediction(void) {};

	virtual void	Init(void) = 0;
	virtual void	Shutdown(void) = 0;

	// Run prediction
	virtual void	Update
	(
		int startframe,				// World update ( un-modded ) most recently received
		bool validframe,			// Is frame data valid
		int incoming_acknowledged,	// Last command acknowledged to have been run by server (un-modded)
		int outgoing_command		// Last command (most recent) sent to server (un-modded)
	) = 0;

	// We are about to get a network update from the server.  We know the update #, so we can pull any
	//  data purely predicted on the client side and transfer it to the new from data state.
	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
	virtual void	PostEntityPacketReceived(void) = 0;
	virtual void	PostNetworkDataReceived(int commands_acknowledged) = 0;

	virtual void	OnReceivedUncompressedPacket(void) = 0;

	// The engine needs to be able to access a few predicted values
	virtual void	GetViewOrigin(Vector& org) = 0;
	virtual void	SetViewOrigin(Vector& org) = 0;
	virtual void	GetViewAngles(QAngle& ang) = 0;
	virtual void	SetViewAngles(QAngle& ang) = 0;
	virtual void	GetLocalViewAngles(QAngle& ang) = 0;
	virtual void	SetLocalViewAngles(QAngle& ang) = 0;

	virtual bool	InPrediction(void) const = 0;
	virtual bool	IsFirstTimePredicted(void) const = 0;
	virtual int		GetIncomingPacketNumber(void) const = 0;
	virtual void	RunCommand(C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *moveHelper) = 0;
	virtual void	SetupMove(C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move) = 0;
	virtual void	FinishMove(C_BasePlayer *player, CUserCmd *ucmd, CMoveData *move) = 0;
	virtual void	SetIdealPitch(C_BasePlayer *player, const Vector& origin, const QAngle& angles, const Vector& viewheight) = 0;
};