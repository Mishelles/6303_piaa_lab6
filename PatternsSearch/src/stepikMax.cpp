#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <algorithm>
#include <utility>

#include <cstring>

typedef std::pair<int, int> res_pair;

// void strToAlphabet(std::string &str);
bool compareForSort(res_pair el1, res_pair el2);

std::vector<res_pair > Aho_Corasick(std::string text,
									std::vector<std::string> patterns,
									size_t number_of_patterns);

struct Bohr_vertex_AC
{
	 Bohr_vertex_AC(char symbol, int parrent_link = -1);

	 //data
	std::map<char,int> next_vertices;
	std::map<char,int> moves;
	int pattern_number;
	int suffix_link ;
	int correct_suffix_link;
	int parrent_link;
	bool is_end_of_pattern;
	char symbol;

};

struct BohrTree_AC
{
	BohrTree_AC();
	void addStrToBohr(const std::string &pattern, int numberOfPattern);
	int getSuffixLink(int vertexNum);
	int getAutoMove(int vertexNum, char symbol);
	int getCorrectSuffixLink(int vertexNum);
	void check(int vertexNum, int i, std::vector <std::string> &patterns, std::vector<res_pair > &results);
	std::vector<res_pair > findIn(const std::string &text, std::vector <std::string> &patterns);

	//data
	std::vector<Bohr_vertex_AC> bohr;
};

std::vector<res_pair > Aho_Corasick(std::string text,
									std::vector<std::string> patterns,
									size_t number_of_patterns) // typedef in Aho_Corasick_hdr
{
	BohrTree_AC bohr;
	for (size_t i = 0; i<number_of_patterns; i++)
		bohr.addStrToBohr(patterns[i], i);
	std::vector<res_pair> results = bohr.findIn(text, patterns);
	std::sort(results.begin(), results.end(), compareForSort);
	return results;
}

bool compareForSort( res_pair el1, res_pair el2)
{
	if (el1.first == el2.first)
		return el1.second < el2.second;
	else
		return el1.first < el2.first;
}

Bohr_vertex_AC::Bohr_vertex_AC(char symbol, int parrent_link) :
	parrent_link(parrent_link),
	symbol(symbol),
	is_end_of_pattern(false),
	suffix_link(-1),
	correct_suffix_link(-1)
{
	next_vertices[symbol] = -1;
	moves[symbol] = -1;
}

BohrTree_AC::BohrTree_AC()
{
	bohr.push_back(Bohr_vertex_AC('$'));
}

void BohrTree_AC::addStrToBohr(const std::string &pattern, int numberOfPattern)
{
	int vertexNum = 0;

	for (size_t i = 0; i < pattern.size(); i++)
	{
		char symb = pattern[i];
		if (bohr[vertexNum].next_vertices.find(symb) == bohr[vertexNum].next_vertices.end() || bohr[vertexNum].next_vertices[symb] == -1)
		{
			bohr.push_back(Bohr_vertex_AC(symb, vertexNum));
			bohr[vertexNum].next_vertices[symb] = bohr.size() - 1;
		}

		vertexNum = bohr[vertexNum].next_vertices[symb];
	}

	bohr[vertexNum].pattern_number = numberOfPattern;
	bohr[vertexNum].is_end_of_pattern = true;
}

int BohrTree_AC::getSuffixLink(int vertexNum)
{
	if (bohr[vertexNum].suffix_link == -1)
	{
		if (vertexNum == 0 || bohr[vertexNum].parrent_link == 0)
			bohr[vertexNum].suffix_link = 0;
		else
			bohr[vertexNum].suffix_link = getAutoMove(getSuffixLink(bohr[vertexNum].parrent_link),
													  bohr[vertexNum].symbol);
	}

	return bohr[vertexNum].suffix_link;
}

int BohrTree_AC::getAutoMove(int vertexNum, char symbol)
{
	if (bohr[vertexNum].moves.find(symbol) == bohr[vertexNum].moves.end() || bohr[vertexNum].moves[symbol] == -1)
	{
		if (bohr[vertexNum].next_vertices.find(symbol) != bohr[vertexNum].next_vertices.end() && bohr[vertexNum].next_vertices[symbol] != -1)
			bohr[vertexNum].moves[symbol] = bohr[vertexNum].next_vertices[symbol];
		else
		{
			if (vertexNum == 0)
				bohr[vertexNum].moves[symbol] = 0;
			else
				bohr[vertexNum].moves[symbol] = getAutoMove(getSuffixLink(vertexNum), symbol);
		}
	}
	return bohr[vertexNum].moves[symbol];
}

int BohrTree_AC::getCorrectSuffixLink(int vertexNum)
{
	if (bohr[vertexNum].correct_suffix_link == -1)
	{
		int tmpLink = getSuffixLink(vertexNum);
		if (tmpLink == 0)
			bohr[vertexNum].correct_suffix_link = 0;
		else
		{
			if (bohr[tmpLink].is_end_of_pattern == true)
				bohr[vertexNum].correct_suffix_link = tmpLink;
			else
				bohr[vertexNum].correct_suffix_link = getCorrectSuffixLink(tmpLink);
		}
	}
	return bohr[vertexNum].correct_suffix_link;
}

void BohrTree_AC::check(int vertexNum, int i,
					 std::vector <std::string> &patterns,
					 std::vector<res_pair > &results)
{
	for (int nextVertex = vertexNum; nextVertex != 0; nextVertex = getCorrectSuffixLink(nextVertex))
	{
		if (bohr[nextVertex].is_end_of_pattern)
		{
			res_pair tmp(i - patterns[bohr[nextVertex].pattern_number].size() + 1,
						 bohr[nextVertex].pattern_number + 1);
			results.push_back(tmp);
		}
	}
}

std::vector<res_pair > BohrTree_AC::findIn(const std::string &text, std::vector <std::string> &patterns)
{
	std::vector<res_pair > results;
	int vertexNum = 0;
	for (size_t i = 0; i < text.size(); i++)
	{
		vertexNum = getAutoMove(vertexNum, text[i]);
		check(vertexNum, i + 1, patterns, results);
	}

	return results;
}

int main()
{
	std::string text;
	size_t number_of_patterns;
	std::cin >> text;
	std::cin >> number_of_patterns;
	std::vector<std::string> patterns(number_of_patterns);
	for (size_t i = 0; i < number_of_patterns; i++)
	{
		std::cin >> patterns[i];
	}
	std::vector<res_pair > results = Aho_Corasick(text, patterns, number_of_patterns); // typedef in Aho_Corasick_hdr
	for (size_t i = 0; i < results.size(); i++)
		std::cout << results[i].first << " " << results[i].second << std::endl;
	return 0;
}
