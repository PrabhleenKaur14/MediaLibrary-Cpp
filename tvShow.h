/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#pragma once
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include "mediaItem.h"
#include "settings.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>

namespace seneca {

	struct TvEpisode {
		const class TvShow* m_show{};
		unsigned short m_numberOverall{};
		unsigned short m_season{ 1 };
		unsigned short m_numberInSeason{};
		std::string m_airDate{};
		unsigned int m_length{};
		std::string m_title{};
		std::string m_summary{};
	};

	class TvShow : public MediaItem {

		std::string m_id;
		std::vector<TvEpisode> m_episodes;

		TvShow(const std::string& id, const std::string& title,
			unsigned short year, const std::string& summary);

	public:
		void display(std::ostream& out) const override;
		static TvShow* createItem(const std::string& strShow);

		template <typename Collection_t>
		static void addEpisode(Collection_t& col, const std::string& strEpisode) {

			if (strEpisode.empty() || strEpisode[0] == '#') {
				throw "Not a valid episode.";
			}

			std::stringstream line(strEpisode);
			std::string id, tempEpNum, tempSeasonNum, tempEpInSeason, airDate,
				tempLen, title, summary;

			getline(line, id, ',');
			getline(line, tempEpNum, ',');
			getline(line, tempSeasonNum, ',');
			getline(line , tempEpInSeason, ',');
			getline(line, airDate, ',');
			getline(line, tempLen, ',');
			getline(line, title, ',');
			getline(line, summary);

			MediaItem::trim(id);
			MediaItem::trim(tempEpNum);
			MediaItem::trim(tempSeasonNum);
			MediaItem::trim(tempEpInSeason);
			MediaItem::trim(airDate);
			MediaItem::trim(tempLen);
			MediaItem::trim(title);
			MediaItem::trim(summary);

			if (id.empty() || tempEpNum.empty() || tempEpInSeason.empty() || tempLen.empty()) {
				throw "Not a valid episode.";
			}


			TvShow* show = nullptr;
			for (size_t i = 0; i < col.size(); i++) {
				const TvShow* temp = dynamic_cast<const TvShow*>(col[i]);
				if (temp && temp->m_id == id) {
					show = const_cast<TvShow*>(temp);
					break;
				}
			}if (!show) {
				throw std::string("No show with ID [" + id + "] found.");
			}

			TvEpisode e;
			e.m_show = show;
			e.m_numberOverall = static_cast<unsigned short>(std::stoi(tempEpNum));
			e.m_season = tempSeasonNum.empty() ? 1 : static_cast<unsigned short>(std::stoi(tempSeasonNum));
			e.m_numberInSeason = static_cast<unsigned short>(std::stoi(tempEpInSeason));
			e.m_airDate = airDate;
			unsigned int hour = 0, min = 0, sec = 0;
			try {
				std::stringstream timeStream(tempLen);
				std::string colon;
				if (std::getline(timeStream, colon, ':')) hour = std::stoul(colon);
				if (std::getline(timeStream, colon, ':')) min = std::stoul(colon);
				if (std::getline(timeStream, colon, ':')) sec = std::stoul(colon);
				e.m_length = hour * 3600 + min * 60 + sec;
			}
			catch (...) {
				e.m_length = 0;
			}


			e.m_title = title;
			e.m_summary = summary;

			show->m_episodes.push_back(e);
		}

		double getEpisodeAverageLength() const;
		std::list<std::string> getLongEpisodes() const;
	};
}

#endif 
