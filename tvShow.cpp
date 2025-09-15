/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#include "tvShow.h"

namespace seneca {

	TvShow::TvShow(const std::string& id, const std::string& title, unsigned short year, const std::string& summary)
		: MediaItem(title, summary, year), m_id(id) {}

	void TvShow::display(std::ostream& out) const {
		if (g_settings.m_tableView)
		{
			out << "S | ";
			out << std::left << std::setfill('.') << std::setw(50) << getTitle() << " | ";
			out << std::right << std::setfill(' ') << std::setw(2) << m_episodes.size() << " | ";
			out << std::setw(4) << getYear() << " | ";
			out << std::left;
			if (g_settings.m_maxSummaryWidth > -1)
			{
				if (static_cast<short>(getSummary().size()) <= g_settings.m_maxSummaryWidth)
					out << getSummary();
				else
					out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
			}
			else
				out << getSummary();
			out << std::endl;
		}
		else
		{
			size_t pos = 0;
			out << getTitle() << " [" << getYear() << "]\n";
			out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << '\n';
			while (pos < getSummary().size()) {
				out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
				pos += g_settings.m_maxSummaryWidth;
			}
			for (auto& item : m_episodes) {
				out << std::setfill('0') << std::right;
				out << "    S" << std::setw(2) << item.m_season << "E" << std::setw(2) << item.m_numberInSeason << ' ';
				if (!item.m_title.empty())
					out << item.m_title << '\n';
				else
					out << "Episode " << item.m_numberOverall << '\n';
				pos = 0;
				while (pos < item.m_summary.size()) {
					out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
					pos += g_settings.m_maxSummaryWidth - 8;
				}
			}
			out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n';
		}
	}

	TvShow* TvShow::createItem(const std::string& strShow) {
		if (strShow.empty() || strShow[0] == '#') {
			throw "Not a valid show.";
		}

		std::stringstream line(strShow);
		std::string id, title, tempYear, summary;
		getline(line, id, ',');
		getline(line, title, ',');
		getline(line, tempYear, ',');
		getline(line, summary);

		MediaItem::trim(id);
		MediaItem::trim(title);
		MediaItem::trim(tempYear);
		MediaItem::trim(summary);

		if (id.empty() || title.empty() || tempYear.empty()) {
			throw "Not a valid show.";
		}

		unsigned short year = static_cast<unsigned short>(std::stoi(tempYear));
		return new TvShow(id, title, year, summary);
	}

	double TvShow::getEpisodeAverageLength() const {
		
		if (m_episodes.empty()) {
			return 0.0;
		}
		unsigned int totalLen = std::accumulate(m_episodes.begin(), m_episodes.end(), 0u,
			[](unsigned int sum, const TvEpisode& ep) {
				return sum + ep.m_length;
			});
		return static_cast<double>(totalLen) / m_episodes.size();
	}

	std::list<std::string> TvShow::getLongEpisodes() const {
		std::list<std::string> result;

		std::transform(m_episodes.begin(), m_episodes.end(), std::back_inserter(result),
			[](const TvEpisode& ep) -> std::string {
				return (ep.m_length >= 3600 && !ep.m_title.empty()) ? ep.m_title : "";
			});

		result.remove_if([](const std::string& str) { 
			return str.empty();
			});

		return result;
	}


} 