/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#include "movie.h"

namespace seneca {

	Movie::Movie(const std::string& title, unsigned short year, const std::string& summary)
		: MediaItem(title, summary, year) {}

	void Movie::display(std::ostream& out) const {
		if (g_settings.m_tableView)
		{
			out << "M | ";
			out << std::left << std::setfill('.') << std::setw(50) << this->getTitle() << " | ";
			out << std::right << std::setfill(' ') << std::setw(9) << this->getYear() << " | ";
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
			out << this->getTitle() << " [" << this->getYear() << "]\n";
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
			while (pos < this->getSummary().size())
			{
				out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
				pos += g_settings.m_maxSummaryWidth;
			}
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n';
		}
	}

	Movie* Movie::createItem(const std::string& strMovie) {
		unsigned short year;

		if (strMovie.empty() || strMovie[0] == '#') {
			throw "Not a valid movie.";
		}

		std::stringstream str(strMovie);
		std::string title,tempYear, summary;

		getline(str, title, ',');
		getline(str, tempYear, ',');
		getline(str, summary);

		trim(title);
		trim(tempYear);
		trim(summary);

		if (tempYear.empty() || title.empty() ) {
			throw "Not a valid movie.";
		}

		year = static_cast<unsigned short>(std::stoi(tempYear));
		return new Movie(title, year, summary);
	}

} 
