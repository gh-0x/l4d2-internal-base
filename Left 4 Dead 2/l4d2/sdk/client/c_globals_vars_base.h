#pragma once

class global_vars_base {
public:
	float     realtime;
	int       framecount;
	float     absoluteframetime;
	float     curtime;
	float     frametime;
	int       max_clients;
	int       tickcount;
	float     interval_per_tick;
	float     interpolation_amount;
	int       sim_ticks_this_frame;
	int       network_protocol;
	void*     save_data;
	bool      m_bclient;
	bool      m_bremoteclient;
private:
	int       nTimestampNetworkingBase;
	int       nTimestampRandomizeWindow;
};