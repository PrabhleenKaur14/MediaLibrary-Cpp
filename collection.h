#pragma once
/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include "mediaItem.h"
#include <string>
#include <iostream>
#include <vector>
#include<iomanip>
#include <algorithm>
#include <stdexcept>

namespace seneca {

	class Collection {
		std::string col_name;
		std::vector<MediaItem*> media_items;
		void (*m_observer)(const Collection&, const MediaItem&) = nullptr;
		//pointer to a function

	public:
		Collection(const std::string& name);
		~Collection();

		Collection(const Collection&) = delete;
		Collection(Collection&&) = delete;
		Collection& operator=(const Collection&) = delete;
		Collection& operator=(Collection&&) = delete;

		const std::string& name() const;
		size_t size() const;
		void setObserver(void (*observer)(const Collection&, const MediaItem&));
		Collection& operator+=(MediaItem* item);
		MediaItem* operator[](size_t idx) const;
		MediaItem* operator[](const std::string& title) const;
		void removeQuotes();
		void sort(const std::string& field);
		auto begin() const { return media_items.begin(); }
		auto end() const { return media_items.end(); }
	};

	std::ostream& operator<<(std::ostream& os, const Collection& col);

} 
#endif 