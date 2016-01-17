#include "Pch.h"


#include "Room.h"
#include "WorldState.h"


namespace Game {

Room::Room (unsigned roomToken, ScriptWorld * world, WorldState * worldState)
	: m_world(world),
	  m_worldState(worldState),
	  m_roomToken(roomToken)
{
	m_scriptable = world->InstantiateArchetype(roomToken, world->GetTokenPool().AddToken("Room"), nullptr);
}


void Room::AddConnection (unsigned directionToken, Room * otherRoom) {
	m_connections[directionToken] = otherRoom;
}

Room * Room::FindConnection (unsigned directionToken) {
	auto iter = m_connections.find(directionToken);
	if (iter == m_connections.end())
		return nullptr;

	return iter->second;
}

void Room::SetDescription (const std::string & description) {
	m_description = description;
}



RoomNetwork::RoomNetwork (const char * jsonFileName, TokenPool * tokens, ScriptWorld * world, WorldState * worldState) {
	picojson::value outvalue;

	{
		std::ifstream stream(jsonFileName, std::ios::in);
		picojson::parse(outvalue, stream);
	}

	if(!outvalue.is<picojson::object>())
		return;

	const auto & obj = outvalue.get<picojson::object>();

	auto roomiter = obj.find("rooms");
	if (roomiter == obj.end())
		return;

	FormulaParser parser;

	const auto & rooms = roomiter->second.get<picojson::array>();
	for (const auto & room : rooms) {
		if (!room.is<picojson::object>())
			continue;

		const auto & roomobj = room.get<picojson::object>();

		auto nameiter = roomobj.find("name");
		if (nameiter == roomobj.end() || !nameiter->second.is<std::string>())
			continue;

		unsigned nameToken = tokens->AddToken(nameiter->second.get<std::string>());

		m_rooms[nameToken] = Room(nameToken, world, worldState);

		auto desciter = roomobj.find("description");
		if (desciter != roomobj.end() && desciter->second.is<std::string>())
			m_rooms[nameToken].SetDescription(desciter->second.get<std::string>());

		auto eventiter = roomobj.find("events");
		if (eventiter != roomobj.end() && eventiter->second.is<picojson::array>())
			DeserializerFactory::LoadArrayOfEvents(eventiter->second, world, &parser, m_rooms[nameToken].GetScriptable());

		auto listsiter = roomobj.find("lists");
		if (listsiter != roomobj.end() && listsiter->second.is<picojson::array>())
			DeserializerFactory::LoadArrayOfLists(listsiter->second.get<picojson::array>(), world, m_rooms[nameToken].GetScriptable());
	}

	for (const auto & room : rooms) {
		if (!room.is<picojson::object>())
			continue;

		const auto & roomobj = room.get<picojson::object>();

		auto nameiter = roomobj.find("name");
		if (nameiter == roomobj.end() || !nameiter->second.is<std::string>())
			continue;

		unsigned nameToken = tokens->AddToken(nameiter->second.get<std::string>());
		auto conniter = roomobj.find("connections");
		if (conniter == roomobj.end() || !conniter->second.is<picojson::object>())
			continue;

		Room * room = FindRoom(tokens->AddToken(nameiter->second.get<std::string>()));
		assert(room != nullptr);

		for (const auto & conn : conniter->second.get<picojson::object>()) {
			unsigned dirToken = tokens->AddToken(conn.first);
			unsigned targetToken = tokens->AddToken(conn.second.get<std::string>());

			Room * otherRoom = FindRoom(targetToken);
			if (!otherRoom)
				continue;

			room->AddConnection(dirToken, otherRoom);
		}
	}
}


Room * RoomNetwork::FindRoom (unsigned roomIdToken) {
	auto iter = m_rooms.find(roomIdToken);
	if (iter == m_rooms.end())
		return nullptr;

	return &iter->second;
}


}


