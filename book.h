#pragma once
/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student 
or 3rd party content provider.
*/
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include "mediaItem.h"
#include "settings.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>



namespace seneca {

	class Book : public MediaItem {
		std::string m_author;
		std::string m_country;
		double m_price = 0.0;

		Book(const std::string& author, const std::string& title, const std::string& country,
			double price, unsigned short year, const std::string& summary);

	public:
		
		void display(std::ostream& out)const override;
		static Book* createItem(const std::string& strBook);
	};

} 

#endif 
