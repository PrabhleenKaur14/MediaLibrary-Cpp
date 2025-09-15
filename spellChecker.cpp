/*NAME:PRABHLEEN KAUR
* EMAIL:pkaur526@myseneca.ca
* STUDENT ID:151653227
* DATE: 2025-03-23
* I declare that this submission is the result of my own work and I only copied the code that my professor
provided to complete my assignments. This submitted piece of work has not been shared with any other student
or 3rd party content provider.
*/
#include "spellChecker.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

namespace seneca {

	SpellChecker::SpellChecker(const char* filename) {
		int num = 6;
		int idx = 0;
		std::string line, badWord, goodWord;
		std::ifstream file(filename);
		if (!file) {
			throw "Bad file name!";
		}

		while (std::getline(file, line) && idx < num) {
			std::istringstream iss(line);
			iss >> badWord >> goodWord;
			m_badWords[idx] = badWord;
			m_goodWords[idx] = goodWord;
			m_counts[idx] = 0;
			++idx;
		}
	}

	void SpellChecker::operator()(std::string& text) {
		for (size_t i = 0; i < 6; i++) {
			size_t position = text.find(m_badWords[i]);
			while (position != std::string::npos) {
				text.replace(position, m_badWords[i].length(), m_goodWords[i]);
				++m_counts[i];
				position = text.find(m_badWords[i], position + m_goodWords[i].length());
			}
		}
	}

	void SpellChecker::showStatistics(std::ostream& out) const {
		out << "Spellchecker Statistics" << std::endl;
		for (size_t i = 0; i < 6; ++i) {
			
			out << std::left << std::setw(15) << m_badWords[i] << ": "
				<< m_counts[i] << " replacements" << std::endl;
		}
	}

} 
