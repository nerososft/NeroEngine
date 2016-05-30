#pragma once
namespace NeroEngine{
	class MqttClient{};
	class HttpClient{};
	class SocketClient{};
	class Network
	{
	public:
		Network();
		~Network();
	private:
		MqttClient _mqttClient;
		HttpClient _httpClient;
		SocketClient _socketClient;
	};
}

