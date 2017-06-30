#pragma once

enum InitReturnVal_t
{
	INIT_FAILED = 0,
	INIT_OK,

	INIT_LAST_VAL,
};

class IAppSystem
{
	virtual bool Connect(CreateInterfaceFn factory) = 0;
	virtual void Disconnect() = 0;
	virtual void *QueryInterface(const char *pInterfaceName) = 0;
	virtual InitReturnVal_t Init() = 0;
	virtual void Shutdown() = 0;
};