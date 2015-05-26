#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>

#define DEFAULT			0
#define FALSE			1
#define TRUE 			2

using namespace std;

	int main() {

 		int n = 0;
 		int i; 
 		int j;
 		int x;
 		int flag = 0;

		string line;
	 	string subject;
		string negative;
		string predicate;
		string object;
		string type;



		map<string, map<string, map<string, int> > > statement;
		vector<string> subjectv;
		vector<string> predicatev;
		vector<string> objectv;

		vector<string> people;
		vector<int> subjects;
		vector<int> subjectswithdupe;

		vector<pair<string, string> > seen;

 		scanf("%d\n", &n);
 		//cout << n << " number of dialogues to follow\n";
		//istringstream iss(line);
		printf("Dialogue #1:\n");
		i = 0;
		while (i < n) {
			line = "";
			subject = "";
			negative = "";
			predicate = "";
			object = "";


			getline(cin, line);

			if (line[line.length() - 1] == '!') {
				i++;
				statement.clear();
				subjectv.clear();
				predicatev.clear();
				objectv.clear();
				flag = 0;
				cout << line << "\n";
				cout << "\n";
				if (i < n) {
					printf("Dialogue #%d:\n", i+1);
				}
			}

			if (line[line.length() - 1] == '.' && flag == 0) {
				//cout << "#S\n";

				line.resize(line.size() - 1);

				int result = TRUE;
				istringstream iss(line);
				iss >> subject;
				//cout << "subject = " << subject << "\n";
				iss >> negative;
				if (negative.compare("don't") == 0 || negative.compare("doesn't") == 0) {
				//	cout << "negative = " << negative << "\n";
					result = FALSE;
					iss >> predicate;

					//remove trailing s
					if (predicate[predicate.length() - 1] == 's') {
						predicate.resize(predicate.size() - 1);
					}

				//	cout << "predicate = " << predicate << "\n";
				} else {
					predicate = negative;

					//remove trailing s
					if (predicate[predicate.length() - 1] == 's') {
						predicate.resize(predicate.size() - 1);
					}

				//	cout << "predicate = " << predicate << "\n";
				}
				getline(iss, object);
				//cout << "object = " << object << "\n";

				if (subject.compare("nobody") == 0) {
					subject = "everybody";
					result = FALSE;
				}

				//checks
				int check1 = statement[object][predicate][subject];
				int check2 = statement[object][predicate]["everybody"];

				
				if (check1 != DEFAULT && check1 != result) { //something contradicts directly
					flag = 1;
				//	cout << "ZING1";
				} else if (check2 != DEFAULT && result != check2) { //something contradicts with everybody statement
					flag = 1;
				//	cout << "ZING2";
				} else if (subject.compare("everybody") == 0) { //check if new everybody statement contradicts
					for (std::map<string, int>::iterator iter = statement[object][predicate].begin(); iter != statement[object][predicate].end() ; iter++) {
						int check3 = iter->second;
						if (check3 != DEFAULT && check3 != result) {
							flag = 1;
				//			cout << "ZING3";
						}	
					}
				}

				if (flag == 0) {
					if (statement[object][predicate][subject] == DEFAULT) {
						objectv.push_back(object);
						predicatev.push_back(predicate);
						subjectv.push_back(subject);
					}
					statement[object][predicate][subject] = result;

				//	cout << statement[object][predicate][subject] << "\n";
				//	cout << statement[object][predicate]["everybody"] << "\n";
				}
			}

			if (line[line.length() - 1] == '?') {

				cout << line << "\n";
				if (flag == 1) {
					cout << "I am abroad.\n";
				} else {

					//cout << "#Q\n";
					type = "";


					line.resize(line.size() - 1);

					istringstream iss(line);
					iss >> type;
					//cout << "type = " << type << "\n";
					if (type.compare("do") == 0) {
						iss >> subject;

						//cout << "subject = " << subject << "\n";
						iss >> predicate;
						//cout << "predicate = " << predicate << "\n";
						getline(iss, object);
						//cout << "object = " << object << "\n";

						//check if everybody or subject does X.

						int everybodycheck = statement[object][predicate]["everybody"];
						int result = statement[object][predicate][subject];
						

						if (subject.compare("I") == 0) {
							subject = "you";
						} else {
							subject = "I";
						}

						//cout << "#A " << result << everybodycheck << "\n";
						if (result == DEFAULT && everybodycheck == DEFAULT) {
							cout << "maybe.\n";
						} else if (	everybodycheck 		!= FALSE 
									&& result 			!= FALSE) {
							printf("yes, %s %s%s.\n", subject.c_str(), predicate.c_str(), object.c_str());
			
						} else if (	everybodycheck 		!= TRUE
									&& result 			!= TRUE) {
							printf("no, %s don't %s%s.\n", subject.c_str(), predicate.c_str(), object.c_str());
						}
					} else if (type.compare("does") == 0) {
						iss >> subject;

						//cout << "subject = " << subject << "\n";
						iss >> predicate;
						//cout << "predicate = " << predicate << "\n";
						getline(iss, object);
						//cout << "object = " << object << "\n";

						//check if everybody or subject does X.

						int everybodycheck = statement[object][predicate]["everybody"];
						int result = statement[object][predicate][subject];
						
						//cout << "#A " << result << everybodycheck << "\n";
						if (result == DEFAULT && everybodycheck == DEFAULT) {
							cout << "maybe.\n";
						} else if (	everybodycheck 		== TRUE 
									|| result			== TRUE) {
							printf("yes, %s %ss%s.\n", subject.c_str(), predicate.c_str(), object.c_str());
			
						} else if (	everybodycheck 		== FALSE
									|| result 			== FALSE) {
							printf("no, %s doesn't %s%s.\n", subject.c_str(), predicate.c_str(), object.c_str());
						}
					} else if (type.compare("who") == 0) {
						iss >> predicate;
						predicate.resize(predicate.size() - 1);
						//cout << "predicate = " << predicate << "\n";
						getline(iss, object);
						//cout << "object = " << object << "\n";

						int everybodycheck = statement[object][predicate]["everybody"];

						if (everybodycheck == TRUE) {
							printf("everybody %ss%s.\n", predicate.c_str(), object.c_str());
						} else if (everybodycheck == FALSE) {
							printf("nobody %ss%s.\n", predicate.c_str(), object.c_str());
						} else {
							people.clear();
							int x;
							for (x = 0; x < objectv.size(); x++) {
								if (objectv[x].compare(object) == 0) {
									if (predicatev[x].compare(predicate) == 0) {
										if (statement[objectv[x]][predicatev[x]][subjectv[x]] == TRUE) {
											people.push_back(subjectv[x]);
										}
									}
								}
							}
							for (j = 0; j < people.size(); j++) {
								if (people[j].compare("I") == 0) {
									people[j] = "you";
								} else if (people[j].compare("you") == 0) {
									people[j] = "I";
								}
								printf("%s", people[j].c_str());
								if (j == people.size() - 2) {
									printf(" and ");
								} else if (j < people.size() - 2 && people.size() > 2) {
									printf(", ");
								} else if (people.size() > 1) {
									printf(" %s%s.\n", predicate.c_str(), object.c_str());
								} else {
									if (people[j].compare("I") == 0 || people[j].compare("you") == 0) {
										printf(" %s%s.\n", predicate.c_str(), object.c_str());
									} else {
										printf(" %ss%s.\n", predicate.c_str(), object.c_str());
									}
								}
							}
							if (people.size() == 0) {
								cout << "I don't know.\n";
							}
						}
					} else if (type.compare("what") == 0) {

						iss >> subject;
						iss >> subject;
						//cout << "subject = " << subject << "\n";
						subjectswithdupe.clear();
						subjects.clear();
						seen.clear();
						for (x = 0; x < subjectv.size(); x++) {
							if (subjectv[x].compare(subject) == 0 || subjectv[x].compare("everybody") == 0) {
								subjectswithdupe.push_back(x);
							}
						}

						for (j = 0; j < subjectswithdupe.size(); j++) {

							pair<string, string> p = make_pair(predicatev[subjectswithdupe[j]],objectv[subjectswithdupe[j]]);

							if (find(seen.begin(), seen.end(), p) != seen.end()) {
								continue;
							} else {
								seen.push_back(p);
								subjects.push_back(subjectswithdupe[j]);
							}
						}

						if (subject.compare("I") == 0) {
							subject = "you";
						} else if (subject.compare("you") == 0) {
							subject = "I";
						}

						if (subjects.size() == 0) {
							cout << "I don't know.\n";
						} else {

							printf("%s", subject.c_str());
							for (j = 0; j < subjects.size(); j++) {
								int check1 = statement[objectv[subjects[j]]][predicatev[subjects[j]]][subjectv[subjects[j]]];
								int check2 = statement[objectv[subjects[j]]][predicatev[subjects[j]]]["everybody"];
	     	

								if ( check1 == TRUE || check2 == TRUE) {
									if (subject.compare("I") == 0 || subject.compare("you") == 0) {
										printf(" %s%s", predicatev[subjects[j]].c_str(), objectv[subjects[j]].c_str());
									} else {
										printf(" %ss%s", predicatev[subjects[j]].c_str(), objectv[subjects[j]].c_str());	
									}
								} else if ( check1 == FALSE || check2 == FALSE) {
									if (subject.compare("I") == 0 || subject.compare("you") == 0) {
										printf(" don't %s%s", predicatev[subjects[j]].c_str(), objectv[subjects[j]].c_str());
									} else {
										printf(" doesn't %s%s", predicatev[subjects[j]].c_str(), objectv[subjects[j]].c_str());	
									}
								}
								if (j == subjects.size() - 2) {
									printf(", and");
								} else if (j < subjects.size() - 2 && subjects.size() > 2) {
									printf(",");
								} else {
									printf(".\n");
								}
							}
						}

					}
				}
				cout << "\n";
			}
    	}
 	return 0;
} 