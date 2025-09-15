/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#include "collection.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace seneca {

	Collection::Collection(const std::string& name) : col_name(name) {}

	Collection::~Collection() {
		for (auto i : media_items) {
			delete i;
		}
	}

	const std::string& Collection::name() const {
		return col_name;
	}

	size_t Collection::size() const {
		return media_items.size();
	}

	void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
		m_observer = observer;
	}

	Collection& Collection::operator+=(MediaItem* item) {
		if (!item) return *this;
		for (size_t i = 0; i < media_items.size(); ++i) {
			if (media_items[i] && media_items[i]->getTitle() == item->getTitle()) {
				delete item;
				return *this;
			}
		}
		media_items.push_back(item);
		if (m_observer) {
			m_observer(*this, *item);
		}
		return *this;
	}



	MediaItem* Collection::operator[](size_t idx) const {
		if (idx >= media_items.size()) {
			throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" +
				std::to_string(media_items.size()) + "] items.");
		}
		return media_items[idx];
	}

	MediaItem* Collection::operator[](const std::string& title) const {
		auto it = std::find_if(media_items.begin(), media_items.end(), [title](const MediaItem* item) {
			return item->getTitle() == title;
			});
		return it != media_items.end() ? *it : nullptr;
	}

	void Collection::removeQuotes() {

		std::for_each(media_items.begin(), media_items.end(), [](MediaItem* item) {
			auto trim = [](std::string& str) {
				if (!str.empty() && str.front() == '\"') {
					str.erase(0, 1);
				}
				if (!str.empty() && str.back() == '\"') {
					str.pop_back();
				}
				};
			std::string title = item->getTitle();
			std::string summary = item->getSummary();
			trim(title);
			trim(summary);
			item->setTitle(title);
			item->setSummary(summary);
			});
	}

	void Collection::sort(const std::string& field) {

		if (field == "title") {
			std::sort(media_items.begin(), media_items.end(), [](const MediaItem* item1, const MediaItem* item2) {
				return item1->getTitle() < item2->getTitle();
				});
		}
		else {
			if (field == "year") {
				std::sort(media_items.begin(), media_items.end(), [](const MediaItem* item1, const MediaItem* item2) {
					return item1->getYear() < item2->getYear();
					});
			}
		}
	}

	std::ostream& operator<<(std::ostream& os, const seneca::Collection& col) {
		for (size_t i = 0; i < col.size(); ++i) {
			os << *col[i];
		}
		return os;
	}
}
