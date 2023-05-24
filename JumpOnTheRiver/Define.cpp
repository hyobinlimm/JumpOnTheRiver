#include "Define.h"

std::string ConvertState(CHARACTER_STATE state)
{
	switch (state)
	{
		case CHARACTER_STATE::NORMAL:	return "NORMAL";
		case CHARACTER_STATE::DIE:		return "DIE";
		case CHARACTER_STATE::SIT:		return "SIT";
		default:
			break;
	}

	return "NORMAL";
}

std::string ConvertState(MOVE_STATE state)
{
	switch (state)
	{
		case MOVE_STATE::GROUND:	return "GROUND";
		case MOVE_STATE::AIR:		return "AIR";
		case MOVE_STATE::WALLMOVE:	return "WALLMOVE";
		default:
			break;
	}

	return "GROUND";
}

std::string ConvertState(PLAYER_TYPE state)
{
	switch (state)
	{
		case PLAYER_TYPE::GIRL:		return "GIRL";
		case PLAYER_TYPE::SHADOW:	return "SHADOW";
		default:
			break;
	}

	return "GIRL";
}
