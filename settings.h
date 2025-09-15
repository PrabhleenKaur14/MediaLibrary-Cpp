/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#pragma once
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <cstdint>

namespace seneca {

	struct Settings {
		int m_maxSummaryWidth{ 80 };
		bool m_tableView{ false };
	};
	extern Settings g_settings;
} 

#endif 
