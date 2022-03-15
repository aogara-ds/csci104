#include "searcheng.h"

using namespace std;

#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>



// Helper function that will extract the extension of a filename
std::string extract_extension(const std::string& filename);

std::string extract_extension(const std::string& filename)
{
	size_t idx = filename.rfind(".");
	if (idx == std::string::npos) {
		return std::string();
	}
	return filename.substr(idx + 1);
}


// To be updated as needed 
SearchEng::SearchEng()
{
	
}

// To be completed
SearchEng::~SearchEng()
{

}

// Complete
void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
	if (parsers_.find(extension) != parsers_.end())
	{
		throw std::invalid_argument("parser for provided extension already exists");
	}
	parsers_.insert(make_pair(extension, parser));
}

// Complete
void SearchEng::read_pages_from_index(const std::string& index_file)
{
	ifstream ifile(index_file.c_str());
	if(ifile.fail()) {
		cerr << "Unable to open index file: " << index_file << endl;
	}

	else
	{
		std::cout << "index file opened!" << std::endl;
	}

	// Parse all the files
	string filename;
	while(ifile >> filename) {
#ifdef DEBUG
		cout << "Reading " << filename << endl;
#endif
		read_page(filename);
	}
	ifile.close();
}

// To be completed
void SearchEng::read_page(const string& filename)
{
	std::cout << "read_page(): " << filename << std::endl;

	// Parse extension from filename
	string ext = extract_extension(filename);

	// Check if parser is registered
	if (!parsers_.count(ext))
	{
		std::cout << "No parser for extension: " << ext << std::endl;
		throw std::logic_error("Cannot read the page.");
	}

	// Read contents of filename into stringstream
	ifstream ifile(filename.c_str());
	if(ifile.fail()) 
	{
		cerr << "Unable to open filename: " << filename << endl;
		throw std::invalid_argument("Unable to open filename.");
	}
	
	// Initialize sets to be parsed
	std::set<std::string> terms = {};  
	std::set<std::string> outgoing = {};

	// Find your parser
	PageParser* pp = parsers_.find(ext)->second;

	// Parse the page
	pp->parse(ifile, terms, outgoing);

	// FIRST PART OF READ_PAGE(): Generate filename-webpage pair
	// If filename does not exist, 
	if (webpages_map.find(filename) == webpages_map.end())
	{
		// Print statement
		std::cout << "Generating new entry for F1" << std::endl;

		// Dynamically allocate a new WebPage object
		WebPage* wp1 = new WebPage(filename);

		// Make terms a StringSet
		// TODO: make this dynamic?
		StringSet terms_ss = terms;

		// Load terms
		wp1->all_terms(terms_ss);

		// Load outgoing links
		// For each filename in outgoing
		for (std::set<std::string>::iterator lit = outgoing.begin(); lit != outgoing.end(); lit++)
		{
			// Print statement
			std::cout << "Iterating through outgoing links" << std::endl;
			std::cout << "Trying to link to: " << *lit << std::endl;

			// If the filename-WebPage pair exists
			if (webpages_map.find(*lit) != webpages_map.end())
			{
				// Print statement
				std::cout << "Outgoing link WebPage exists" << std::endl;

				// Store the destination WebPage
				// TODO: make this dynamic?
				WebPage* wp2 = webpages_map.find(*lit)->second; 
				std::cout << "Destination WP filename: " << wp2->filename() << std::endl;

				// Add wp2 pointer to wp1 outgoing
				wp1->add_outgoing_link(wp2);

				// Add wp1 pointer to wp2 incoming
				wp2->add_incoming_link(wp1);

				// Clear wp2 pointer for safety
				wp2 = nullptr;
			}
			
			// If the filename-WebPage pair does NOT exist
			else
			{
				// Print statement
				std::cout << "Outgoing link WebPage does NOT exist" << std::endl;

				// Dynamically allocate a new WebPage
				WebPage* wp2 = new WebPage(*lit);
				std::cout << "Destination WP filename: " << wp2->filename() << std::endl;

				// Add wp2 pointer to wp1 outgoing
				wp1->add_outgoing_link(wp2);

				// Add wp1 pointer to wp2 incoming
				wp2->add_incoming_link(wp1);

				// Add new WebPage to webpages_map
				webpages_map.insert(make_pair(*lit, wp2));

				// Clear wp2 pointer for safety
				wp2 = nullptr;
			}

		}
		
		// Insert pointer into map
		webpages_map.insert(make_pair(filename, wp1));
	}

	// If filename and webpage already exist, 
	else
	{
		// Print statement
		std::cout << "Updating an existing entry for F1" << std::endl;

		// Store pointer to existing page
		WebPage* wp1 = webpages_map.find(filename)->second;

		// Overwrite terms in existing page
		wp1->all_terms(terms);


		// Clear outgoing links in existing page
		// NOTE TO GRADER: The assignment misses an edge case here. 
		// If a webpage already exists with one set of outgoing links,
		// but the webpage is then edited to remove a link, and the 
		// webpage is read again by the search engine, the search engine
		// should remove that link from the outgoing links. But the 
		// provided WebPage class does not provide that functionality. 
		// TODO: Fix this edge case. Not finished here. 
		
		// Add new outgoing links to existing webpage
		// TODO: Check the variables being input here
		// For each filename in outgoing
		for (std::set<std::string>::iterator lit = outgoing.begin(); lit != outgoing.end(); lit++)
		{
			// Print statement
			std::cout << "Iterating through outgoing links" << std::endl;

			// If the filename-WebPage pair exists
			if (webpages_map.find(*lit) != webpages_map.end())
			{
				// Print statement
				std::cout << "Outgoing link WebPage exists" << std::endl;

				// Store the destination WebPage
				WebPage* wp2 = webpages_map.find(*lit)->second; 
				std::cout << "Destination WP filename: " << wp2->filename() << std::endl;

				// Add wp2 pointer to wp1 outgoing
				wp1->add_outgoing_link(wp2);

				// Add wp1 pointer to wp2 incoming
				wp2->add_incoming_link(wp1);

				// Clear wp2 pointer for safety
				wp2 = nullptr;
			}
			
			// If the filename-WebPage pair does NOT exist
			else
			{
				// Print statement
				std::cout << "Outgoing link WebPage does NOT exist" << std::endl;

				// Dynamically allocate a new WebPage
				WebPage* wp2 = new WebPage(*lit);
				std::cout << "Destination WP filename: " << wp2->filename() << std::endl;

				// Add wp2 pointer to wp1 outgoing
				wp1->add_outgoing_link(wp2);

				// Add wp1 pointer to wp2 incoming
				wp2->add_incoming_link(wp1);

				// Add new WebPage to webpages_map
				webpages_map.insert(make_pair(*lit, wp2));

				// Clear wp2 pointer for safety
				wp2 = nullptr;
			}
		}
	}
	

	// SECOND PART OF READ_PAGE()
	// Fill the term - WebPageSet map

	// Retrieve the pointer to F1
	WebPage* wp1 = webpages_map.find(filename)->second;

	// For each term in terms
	for (auto tit = terms.begin(); tit != terms.end(); tit++)
	{
		// If terms_map does not have the term
		if (terms_map.find(*tit) == terms_map.end())
		{
			// Print statement
			std::cout << "Generating new pair in terms_map" << std::endl;

			// Dynamically allocate a new WebPageSet
			WebPageSet* new_wp_set = new WebPageSet {wp1};

			// Insert the term-WebPageSet pair into terms_map
			std::pair<std::string, WebPageSet*> tpair = make_pair(*tit, new_wp_set);
			terms_map.insert(tpair);
		}

		// if terms_map has the term
		else
		{
			// Print statement
			std::cout << "Adding WebPage to existing set in terms_map" << std::endl;

			// Insert the webpage pointer into the set in the dict for the term
			terms_map.find(*tit)->second->insert(wp1); //TODO: Double check
		}
	}
}

// To be completed
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
	std::cout << "retrieve_page()" << std::endl;

	WebPage* result = webpages_map.find(page_name)->second;

	if (webpages_map.find(page_name) == webpages_map.end())
	{
		return nullptr;
	}
	
	return result;
}

// To be completed
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
	std::cout << "Doing: display_page()" << std::endl;

	// Parse extension from filename
	string ext = extract_extension(page_name);

	// Check if parser is registered
	if (!parsers_.count(ext))
	{
		throw std::logic_error("Cannot read the page.");
	}

	// Find your parser
	PageParser* pp = parsers_.find(ext)->second;

	// Read contents of filename into stringstream
	ifstream ifile(page_name.c_str());
	if(ifile.fail()) 
	{
		cerr << "Unable to open filename: " << page_name << endl;
		throw std::invalid_argument("Unable to open filename.");
	}

	std::string output_string = pp->display_text(ifile);
	std::cout << output_string << std::endl;
	ostr << output_string;
}

// To be completed
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
	// Print statement
	std::cout << "search()" << std::endl;

	// Initialize a special condition for the first loop run
	bool first_loop = true;

	// Initialize sets A and B
	WebPageSet* setA = new WebPageSet;
	WebPageSet* setB = new WebPageSet;

	// For each term
	for (auto tit = terms.begin(); tit != terms.end(); tit++)
	{
		// If it's the first loop
		if (first_loop == true)
		{
			// Initialize the result set with the first lookup
			if (terms_map.find(*tit) != terms_map.end())
			{
				// setA = terms_map.find(*tit)->second;

				setA->insert(terms_map.find(*tit)->second->begin(),
						terms_map.find(*tit)->second->end());
			}

			// Turn off the first loop condition
			first_loop = false;
		}

		// If it's any other loop
		else
		{
			// Grab the second set
			setB->insert(terms_map.find(*tit)->second->begin(),
						terms_map.find(*tit)->second->end());

			// Combine the result set and the second set using the combiner
			*setA = combiner->combine(*setA, *setB);
		}

	}
	return *setA;
}