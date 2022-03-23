// main.cpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include "InputReader.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"
#include "RoadMap.hpp"
#include <iostream>
#include <vector>
#include "Trip.hpp"
#include "TripMetric.hpp"
#include "RoadSegment.hpp"
#include <stack>
#include <iomanip>

void displaytime(double time){
	int hour = time;
	//std::cout<< hour << "hrs ";
	if (hour != 0){std::cout<< " "<< hour << " hours";}
	int mins = (time - hour) * 60;
	//std::cout<< mins << "mins ";
	if (mins != 0){std::cout<< " "<< mins << " minutes";}
	double sec = ((time - hour) * 60 - mins)*60;
	//std::cout<< sec << "sec ";
	//if (mins != 0){std::cout<< mins - sec << "mins ";}
	if (sec != 0){std::cout << " "<< sec << " seconds";}
}

int main()
{
	InputReader iReader(std::cin);//init reader
	RoadMap roadMap;//init RoadMap
	RoadMapReader rReader;//init roadmapreader
	TripReader rTripReader;//init tripreader
	roadMap = rReader.readRoadMap(iReader);
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed);
	//RoadMapWriter rWriter;
	//rWriter.writeRoadMap(std::cout,roadMap);// write out the graph
	
	//whether strong connected
	if (!roadMap.isStronglyConnected()){return 0;}

	
	std::vector<Trip> mTrip = rTripReader.readTrips(iReader);

	//short path part
	for (auto &k : mTrip){
		std::stack<int> printpath;
		if (k.metric == TripMetric::Distance)
		{
			std::cout<< "Shortest distance from " << roadMap.vertexInfo(k.startVertex) <<" to " << roadMap.vertexInfo(k.endVertex) << ":"<<std::endl;
			std::map<int, int> shortestpaths = roadMap.findShortestPaths(k.startVertex,[](RoadSegment rs){return rs.miles;});
			int temp = k.endVertex;
			while(temp != k.startVertex){
				printpath.push(temp);
				temp = shortestpaths[temp];
			}
			printpath.push(k.startVertex);
		
			std::cout<< "	Begin at " << roadMap.vertexInfo(printpath.top())<<std::endl; 
			float totaldis = 0; 
			int last = printpath.top(); 
			printpath.pop();
			
			while(!printpath.empty()){
				std::cout<< "	Continue to " << roadMap.vertexInfo(printpath.top())<< "(" <<roadMap.edgeInfo(last,printpath.top()).miles << " miles)" <<std::endl;
				totaldis+= roadMap.edgeInfo(last,printpath.top()).miles;
				last = printpath.top(); 
				printpath.pop();
			}
			std::cout<< "Total distance: " << totaldis << " miles"<< std::endl<< std::endl; 
			
		}
		else if (k.metric == TripMetric::Time)
		{
			std::cout<< "Shortest driving time from " << roadMap.vertexInfo(k.startVertex) <<" to " << roadMap.vertexInfo(k.endVertex) << ":"<<std::endl;
			std::map<int, int> shortestpaths = roadMap.findShortestPaths(k.startVertex,[](RoadSegment rs){return rs.miles/rs.milesPerHour;});
			int temp = k.endVertex;
			while(temp != k.startVertex){
				printpath.push(temp);
				temp = shortestpaths[temp];
			}
			printpath.push(k.startVertex);
		
			std::cout<< "	Begin at " << roadMap.vertexInfo(printpath.top())<<std::endl; 
			double time = 0; 
			int last = printpath.top(); 
			printpath.pop();
			
			while(!printpath.empty()){
				double d = roadMap.edgeInfo(last,printpath.top()).miles;
				double s = roadMap.edgeInfo(last,printpath.top()).milesPerHour;
				std::cout<< "	Continue to " << roadMap.vertexInfo(printpath.top())<< "(" << d << " miles & "<<  s << "mph =";
				displaytime(d/s);
				std::cout<< ")";
				std::cout<< std::endl;
				time += d/s;
				//time+= roadMap.edgeInfo(last,printpath.top()).miles;
				last = printpath.top(); 
				printpath.pop();
			}
			std::cout<< "Total time:";
			displaytime(time);

			std::cout<<std::endl<< std::endl; 

		}
	}
	

	//


    return 0;
}

	// std::cout<< "LOCATIONS"<<std::endl;
	
	// int Vertex_num = iReader.readIntLine();
	// std::vector<std::pair<int,std::string>> Vertexs;// vector made of pari<int,string>

	// for (int i = 0;i<Vertex_num;++i){
	// 	std::string newline = iReader.readLine();
	// 	Vertexs.push_back(std::pair<int,std::string>(i,newline));
	// }

	// std::cout<< std::endl <<"ROAD SEGMENTS"<<std::endl;
	// int Road_num = iReader.readIntLine();


	// for (int i = 0;i<Road_num;++i){
	// 	std::string newline = iReader.readLine();
	// 	Vertexs.push_back(std::pair<int,std::string>(i,newline));
	// }
