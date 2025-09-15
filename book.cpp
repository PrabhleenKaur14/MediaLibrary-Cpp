/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#include "book.h"

namespace seneca {

	Book::Book(const std::string& author, const std::string& title, const std::string& country,
		double price, unsigned short year, const std::string& summary)
		: MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {}

	void Book::display(std::ostream& out) const {
		if (g_settings.m_tableView)
		{
			out << "B | ";
			out << std::left << std::setfill('.') << std::setw(50) << this->getTitle() << " | ";
			out << std::right << std::setfill(' ') << std::setw(2) << this->m_country << " | ";
			out << std::setw(4) << this->getYear() << " | ";
			out << std::left;
			if (g_settings.m_maxSummaryWidth > -1)
			{
				if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
					out << this->getSummary();
				else
					out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
			}
			else
				out << this->getSummary();
			out << std::endl;
		}
		else
		{
			size_t pos = 0;
			out << this->getTitle() << " [" << this->getYear() << "] ["
				<< m_author << "] [" << m_country << "] [" << m_price << "]\n";
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
			while (pos < this->getSummary().size())
			{
				out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
				pos += g_settings.m_maxSummaryWidth;
			}
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n';
		}
	}

	Book* Book::createItem(const std::string& strBook) {
		if (strBook.empty() || strBook[0] == '#') {
			throw "Not a valid book.";
		}

		std::stringstream ss(strBook);
		std::string author, title, country, tempPrice, tempYear, summary;
		double price = 0.0;
		unsigned short year;
		getline(ss, author, ',');
		getline(ss, title, ',');
		getline(ss, country, ',');
		getline(ss, tempPrice, ',');
		getline(ss, tempYear, ',');
		getline(ss, summary);

		trim(author);
		trim(title);
		trim(country);
		trim(tempPrice);
		trim(tempYear);
		trim(summary);

		if (author.empty() || title.empty() || country.empty() || tempPrice.empty() || tempYear.empty()) {
			throw "Not a valid book.";
		}

		price = std::stod(tempPrice);
		year = static_cast<unsigned short>(std::stoi(tempYear));

		return new Book(author, title, country, price, year, summary);
	}

} 