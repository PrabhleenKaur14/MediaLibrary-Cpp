/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace seneca {

	class Movie : public MediaItem {
	
		Movie(const std::string& title, unsigned short year, const std::string& summary);

	public:
		void display(std::ostream& out) const override;
		static Movie* createItem(const std::string& strMovie);
	};

}

#endif 

