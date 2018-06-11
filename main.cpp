/*
Developed by Giovanni Mounir
W: giovannimounir.net
E: gmounir@giovannimounir.net
---
Copyright (c) 2017 giovannimounir.net

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Sofwtare is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.

IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <iostream>
#include <string>
#include <regex>
using namespace std;
//prototypes
class Point;
class Polygon;
int rc(Polygon polygon, Point p, bool checkintersect); 
bool seg_intersect(Point A, Point B, Point C, Point D);
Point& min_dist(Point& start, Point& p1, Point&p2);
//
string tolower(string str)
{
	//97: a
	//65: A
	//32 gap
    for (int i = 0; i < str.length(); i++)
	{
        if (str[i] > 64 && str[i] < 91)
            str[i] += 32;
	}
    return str;
}
void op_cleanup(bool &remove)
{
	if (remove) cout << '\b' << " "; //Go backwards (backspace), replace with space
	else cout << "none";
}
bool inf(float x, float y)
{
	if (abs(x) == 0 && abs(y) == INFINITY || abs(y) == 0 && abs(x) == INFINITY) return true;
	return false;
}
class Helper
{
public : 
	static void Exit(int error)
{
	switch (error)
	{
	case 1:
		cout << "WARNING!!! Incorrect format entered, please double-check your input. The program will exit.";
		break;
	case 2:
		cout << "ERROR: Empty sets provided. The program will exit.";
		break;
	case 3:
		cout << "NOTICE: Received abort request. The program will exit.";
		break;
		case 4 :
			cout << "ERROR: Bad syntax. Probably missing parentheses?";
		break;
		case 5 :
			cout << "ERROR: Nothing supplied. The program will terminate.";
			break;
	default:
		cout << "FATAL: The program has encountered an unknown critical error and will now exit." ;
		break;
	}
	cout << endl;
	exit(1);
}
static bool is_digit(string s){
	return regex_match(s, std::regex("^[ ]{0,1}[-+]{0,1}[0-9]+[\\.\\d+]{0,}[ ]{0,1}$"));
}
};

class Point{
private:

	int label;
	bool redundant;
	bool mark;
	int tag;
public:
	float X;
	float Y;
	Point()
	{
		this->tag = 0;
	}
	Point(float X, float Y)
	{
		this->tag = 0;
		this->X = X;
		this->Y = Y;
		this->redundant = false;
	}
	float Slope(Point p2)
	{
		return ((p2.Y - this->Y) / ((float)(p2.X - this->X)));
	}
	int getTag()
	{
		return tag;
	}
	void setTag(int tag)
	{
		this->tag = tag;
	}
	bool Inside(Polygon _P, bool checkintersect); //Prototype
	void setLabel(int label)
	{
		this->label = label;
	}
	int getLabel() { return this->label; }
	float distance(Point p2)
	{
		return sqrt(pow(p2.X-this->X,2) + pow(p2.Y-this->Y,2));
	}
	bool isRedundant(Point p1, Point p2)
	{
		if (*this != p1 && *this != p2 && p1 != p2) //Avoid comparing the same points
		{
			if (p1.X - p2.X == 0 && this->X - p2.X == 0) return true;
			return (this->Slope(p1) == p1.Slope(p2));
		}
		else return false;
	}
	friend ostream& operator<<(ostream& os, Point& p)  
	{  
		os << "(" << p.X << "," << p.Y << ")";  
		return os;  
	}  
	bool Point::operator!=(Point& p)
	{
		return !(p.X == this->X && p.Y == this->Y);
	}
	bool Point::operator==(Point& p)
	{
		return (p.X == this->X && p.Y == this->Y);
	}
	void setRedundant(bool redundancy)
	{
		this->redundant = redundancy;
	}
	bool isRedundant()
	{
		return this->redundant;
	}
};
Point GetMidPoint(Point p1, Point p2)
{
	//Gets the midpoint between 2 points
	return Point((p1.X + p2.X) / 2, (p1.Y + p2.Y) / 2);
}
Point& GetMidPoint(Point &p1, Point &p2, Point &p3)
{
	//Determines which point lies in the middle from 3 points.
	float max = 0;
	int index = 0;
	float _x[3];
	_x[0] = p1.distance(p2);
	_x[1] = p2.distance(p3);
	_x[2] = p1.distance(p3);
	for (int i = 0; i < 3; i++)
	{
		if (max < _x[i])
		{
			max = _x[i];
			index = i;
		}
	}
	switch (index)
	{
		case 0:
			return p3;
		
		case 1:
			return p1;
		
		case 2:
			return p2;
	}

}
class Polygon {
private:
	int totalPoints;
	int redundantPoints;
	int tag;
	int nonRedundantPointsNum;
public:
	Point * points;
	Point * redundant;
	Point * nonredundantpoints;
	Polygon()
	{
		this->totalPoints = 0;
		this->redundantPoints = 0;
		this->nonRedundantPointsNum = 0;
		this->tag = -1;
	}
	Polygon(Point * points)
	{
		this->points = points;
		this->totalPoints = 0;
		this->redundantPoints = 0;
		this->nonRedundantPointsNum = 0;
		this->tag = -1;
	}
	int getTag() {return tag;
}
	void setTag(int tag) { this->tag = tag; }
	float get(string operation)
	{
		operation = tolower(operation);
		bool _first = true;
		float number;
		for (int i = 0; i < getTotalPoints(true); i++)
		{
			if (operation == "minimum_x" && (_first || points[i].X < number))
			{
				_first = false;
				number = points[i].X;
			}
			else if (operation == "maximum_x" && (_first || points[i].X > number))
			{
				_first = false;
				number = points[i].X;
			}
			else if (operation == "minimum_y" && (_first || points[i].Y < number))
			{
				_first = false;
				number = points[i].Y;
			}
			else if (operation == "maximum_y" && (_first || points[i].Y > number))
			{
				_first = false;
				number = points[i].Y;
			}
		}
		return number;
	}
	bool Polygon::operator==(Polygon& p)
	{
		if (p.getTotalPoints(true) != getTotalPoints(true)) return false;
		for (int i = 0; i < p.getTotalPoints(true); i++)
		{
			if (p.points[i] != points[i]) return false;
		}
		return true;
	}
	bool Intersects(Polygon p)
	{
		/*
		if (p == *this) return true;
		for (int i = 0; i < getTotalPoints(true); i++)
		{
			if (points[i].Inside(p, true)) return true;
		}
		for (int i = 0; i < p.getTotalPoints(true); i++)
		{
			if (p.points[i].Inside(*this, true)) return true;
		}
		^This will work only when the point is inside the polygon. A more efficient solution below.
		*/
		for (int i = 0; i < getTotalPoints(true); i++)
		{
			for (int j = 0; j < p.getTotalPoints(true); j++)
			{
				if (seg_intersect(points[i], points[i + 1 >= getTotalPoints(true) ? 0 : i + 1], p.points[j], p.points[j + 1 >= p.getTotalPoints(true) ? 0 : j + 1])) return true;
			}
		}
		return false;
	}
	void Print(bool redundant = false)
	{
		for (int i = 0; i < getTotalPoints(true); i++)	
		{
			if (!points[i].isRedundant() && !redundant || redundant)
			{
				cout << "(" << points[i].X << "," << points[i].Y << "),";
			}
		}
		cout << "\b ";
	}
	float Area()
	{
		float area = 0;
		for (int i = 0; i < totalPoints; i++)
			area += points[i].X * points[i + 1 >= totalPoints ? 0 : i +1].Y - points[i].Y * points[i + 1 >= totalPoints ? 0 : i + 1].X;
		return abs(area/2);
		//TODO: replace with Green's theorem for CLOSED surfaces to save computational power
	}
	float Length()
	{
		float length = 0;
		for (int i=0; i < totalPoints; i++)
		{
			length += points[i].distance(points[i+1 >= totalPoints? 0 : i+1]);
		}
		return length;
	}
	int getTotalPoints(bool redundant = false)
	{
		return this->totalPoints - (redundant? 0 : this->redundantPoints);
	}
	bool isTrapezoid()
	{
		if (getTotalPoints() != 4) return false;
		float slopes[4];
		int counter = 0;
		int index = 0;
		for (int i = 0; i < this->getTotalPoints(true); i++)
		{
			if (!points[i].isRedundant())
			{
				slopes[index] = points[i].Slope(points[index ==3? 0 : i + 1]);
				index++;
			}
		}
		for (int i =0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (slopes[i] == slopes[j] || abs(slopes[i]) == abs(slopes[j]) && (slopes[i] == INFINITY || slopes[j] == INFINITY))
				{
					counter++;
					break;
				}
			}
			if (counter > 0) break;
		};
		return (counter >= 1);
	
	}
	bool isRectangle()
	{
		if (getTotalPoints(false) != 4) return false;
		int index = 0;
		float slopes[4];
		for (int i =0; i < this->getTotalPoints(true); i++)
		{
			int x = 1;
			int y = 1;
			if (!points[i].isRedundant())
			{
				slopes[index] = points[i].Slope(points[index == 3? 0 : i+1]);
				index++;
			}
		}
		
//		if ((floor((slopes[0] * slopes[1]) + 0.1)) == -1 || inf(slopes[0], slopes[1]) && (floor(slopes[2] * slopes[3]) + 0.1) == -1 || inf(slopes[2], slopes[3]))return true;
//		^ Uncomment and comment below line for lower accuracy [slope error rate: -+ 0.1)(i.e slopes that are 0.9 and -0.9 will be considered as a rectangle)
		if ((slopes[0] * slopes[1] == -1 || inf(slopes[0], slopes[1])) && (slopes[2] * slopes[3] == -1 || inf(slopes[2], slopes[3])))return true;
		return false;
	}
	bool Inside(Polygon P)
	{
		for (int i = 0; i < getTotalPoints(true); i++)
		{
			if (!points[i].isRedundant())
			{
				if (!points[i].Inside(P, false)) return false;
			}
		}
		return true;
	}
	int getRedundantPoints()
	{
		return this->redundantPoints;
	}
	void RedundancyChecks()
	{
		bool recheck = false;
		if (this->totalPoints > 0)
		{
			if (points[0] == points[this->totalPoints - 1] && !points[this->totalPoints - 1].isRedundant())
			{
				this->addRedundantPoint(points[this->totalPoints - 1]);
				recheck = true;
			}
		}
		for (int i =0; i < totalPoints; i++)
		{
			if (!this->points[i].isRedundant()) { this->addNonRedundantPoint(this->points[i], i); }
		}
		if (this->nonRedundantPointsNum >= 2)
		{
			if (nonredundantpoints[nonRedundantPointsNum -1].isRedundant(this->nonredundantpoints[0], this->nonredundantpoints[1])  )
			{
				if (!GetMidPoint(nonredundantpoints[nonRedundantPointsNum -1],this->nonredundantpoints[0], this->nonredundantpoints[1]).isRedundant())
				{	
					this->addRedundantPoint(this->points[GetMidPoint(nonredundantpoints[nonRedundantPointsNum -1],this->nonredundantpoints[0], this->nonredundantpoints[1]).getTag()]);
					recheck = true;
				}
			}
			if (nonredundantpoints[nonRedundantPointsNum -1].isRedundant(this->nonredundantpoints[nonRedundantPointsNum -2], this->nonredundantpoints[0]))
			{
				if (!GetMidPoint(nonredundantpoints[nonRedundantPointsNum -1],this->nonredundantpoints[nonRedundantPointsNum -2], this->nonredundantpoints[0]).isRedundant())
				{	
					this->addRedundantPoint(this->points[GetMidPoint(nonredundantpoints[nonRedundantPointsNum -1],this->nonredundantpoints[nonRedundantPointsNum -2], this->nonredundantpoints[0]).getTag()]);
					recheck = true;
				}
				
			}
		}
			for (int i =0; i <nonRedundantPointsNum; i++)
			{
				if (i > 0 && this->nonredundantpoints[i - 1] == this->nonredundantpoints[i])
				{
					this->addRedundantPoint(this->points[this->nonredundantpoints[i].getTag()]);
					recheck = true;
				}
				else if (i >= 2 && this->nonredundantpoints[i].isRedundant(this->nonredundantpoints[i - 1], this->nonredundantpoints[i - 2]))
				{
					this->addRedundantPoint(min_dist(this->nonredundantpoints[i], this->points[this->nonredundantpoints[i - 1].getTag()], this->points[this->nonredundantpoints[i - 2].getTag()]));
					recheck = true;
				}
				else if (i == nonRedundantPointsNum - 1 && this->points[0] == this->nonredundantpoints[i])
				{
					this->addRedundantPoint(this->points[this->nonredundantpoints[i].getTag()]);
					recheck = true;
				}
			}
		if (this->nonRedundantPointsNum > 0)
		{
			delete[] nonredundantpoints;
			this->nonRedundantPointsNum= 0;
		}
		if (recheck)
		{
			this->RedundancyChecks();
		}
	}
	void addPoint(Point &P, int polyid, bool noduplicates = false)
	{
		P.setLabel(polyid);
		Point * _array = new Point[this->totalPoints+1];
		if (this->totalPoints > 0)
		{
			for (int i =0; i < this->totalPoints; i++)
			{
				_array[i] = this->points[i];
				if (noduplicates && P == this->points[i]){
					delete[] _array;
					return;
				}
			}
		}

		if (this->totalPoints > 0)
		delete[] this->points;
		
		this->points = _array;
		
		_array[this->totalPoints] = P;
		this->totalPoints++;
		
	}
	void addNonRedundantPoint(Point& P, int tag)
	{
		if (!P.isRedundant())
		{
			Point * _array = new Point[this->nonRedundantPointsNum+2];
			P.setRedundant(false);
			P.setTag(tag);
			for (int i =0; i < this->nonRedundantPointsNum; i++)
			_array[i] = this->nonredundantpoints[i];
			_array[this->nonRedundantPointsNum] = P;
			if (this->nonRedundantPointsNum > 0)
			delete[] nonredundantpoints;
			this->nonredundantpoints = _array;
			this->nonRedundantPointsNum++;
		}
	}
	void addRedundantPoint(Point& P)
	{
		if (!P.isRedundant())
		{
			Point * _array = new Point[this->redundantPoints+2];
			P.setRedundant(true);
			cout << P << endl;
			for (int i =0; i < this->redundantPoints; i++)
			_array[i] = this->redundant[i];
			_array[this->redundantPoints] = P;
			if (this->redundantPoints > 0)
			delete[] redundant;
			this->redundant = _array;
			this->redundantPoints++;
		}
	}

};
bool Point::Inside(Polygon _P, bool checkintersect = false)
{
	float Xmax = _P.get("maximum_x");
	float Xmin = _P.get("minimum_x");
	float Ymax = _P.get("maximum_y");
	float Ymin = _P.get("minimum_y");
	if (!checkintersect && (X < Xmin || X > Xmax || Y < Ymin || Y > Ymax)) return false; //This is a quicker check, works best with shapes parallel to the axes
	else if (rc(_P, *this, checkintersect) == 0) return false; //A more thorough test: simulates a ray outside the polygon to the point; returns 0 on even intersections (point is outside) and 1 when it intersects an odd number of segments (point is inside).
	return true;
}
bool seg_overlap(Point A, Point B, Point C)
{
	return (C.Y - A.Y) * (B.X - A.X) > (B.Y - A.Y) * (C.X - A.X);
}
bool seg_intersect(Point A, Point B, Point C, Point D)
{
	return (seg_overlap(A, C, D) != seg_overlap(B, C, D) && seg_overlap(A, B, C) != seg_overlap(A, B, D));
}
int rc(Polygon polygon, Point p, bool checkintersect = false)
{
	//Ray casting function
	int i, j, c = 0;
	for (i = 0, j = polygon.getTotalPoints(true) - 1; i < polygon.getTotalPoints(true); j = i++) {
		if (!polygon.points[i].isRedundant() && !polygon.points[j].isRedundant())
		{
			if (((polygon.points[i].Y > p.Y) != (polygon.points[j].Y > p.Y)) &&
				(p.X < (polygon.points[j].X - polygon.points[i].X) * (p.Y - polygon.points[i].Y) / (polygon.points[j].Y - polygon.points[i].Y) + polygon.points[i].X))
			{
				c = !c;
			}
		}
	}
	return c;
	// 0 = even, 1 = odd
}
class Polygon_Parser{
private:
int count;
void populateArray(char * polygons, Polygon * _polygons, int n )
{	
	char *ptr1, * splits = strtok_s(strdup(polygons), ",", &ptr1);
	int i = 0;
	float x = NULL , y = NULL;
	bool _x = false, _y = false;
	while(splits != NULL)
	{
		if (splits[strlen(splits) - 1] == ')' || splits[strlen(splits) - 1] == ';' && splits[strlen(splits) - 2] == ')')
		{
			splits[strlen(splits) - 1] = ' ';
			if (splits[strlen(splits) - 2] == ')')
			{
				splits[strlen(splits) - 2] == ' ';
				splits[strlen(splits) - 1] == '\0';
			}
			if (!Helper::is_digit(splits)) Helper::Exit(1);
			y = atof(splits);
			_y = true;
		}
		else
		{
			splits[0] = ' ';
			if (!Helper::is_digit(splits)) Helper::Exit(1); 
			x = atof(splits);
			_x = true;

		}
		if (_x && _y)
		{
			_polygons[n].addPoint(Point(x,y),n );
			_x = false; _y = false;
		}
		splits = strtok_s(NULL, ",", &ptr1);
	}
	
	_polygons[n].RedundancyChecks();
	delete[] splits;
}
void buildArray(char *  polygons)
{
	int n = 0;
	char * splits = strtok(strdup(polygons), ";");
	while(splits != NULL)
	{
		if (polygons[strlen(polygons) - 1] == ')')
		{
		this->populateArray(splits, this->polygons, n);
		n++;
		splits = strtok(NULL, ";");
		}
		else
		{
			Helper::Exit(4);
		}
	}
	delete[] splits;
	if (n == 0) Helper::Exit(2);
}
int getCount(char *  polygons)
{
	int n = 0;
	char * splits = strtok(strdup(polygons), ";");
	while(splits != NULL)
	{
		n++;
		splits = strtok(NULL, ";");
	}
	delete[] splits;
	if (n == 0) Helper::Exit(2);
	return n;
}
public:
Polygon * polygons;
Polygon_Parser(char *  input)
{
	this->count = this->getCount(input);
	polygons = new Polygon[this->count];
	this->buildArray(input);
}

int getCount()
{
	return this->count;
}
Polygon at(int index)
{
	return polygons[index];
}
float get(string operation)
{
	operation = tolower(operation);
	bool _first = true;
	float number;
	float p_number;
	for (int i =0; i < this->getCount(); i++)
	{
		p_number = at(i).get(operation);


		if (operation == "minimum_x" && (_first || p_number < number))
		{
			_first = false;
			number = p_number;
		}
		else if (operation == "maximum_x" && (_first || p_number > number))
		{
			_first = false;
			number = p_number;
		}
		else if (operation == "minimum_y" && (_first || p_number < number))
		{
			_first = false;
			number = p_number;
		}
		else if (operation == "maximum_y" && (_first || p_number > number))
		{
			_first = false;
			number = p_number;
		}
	}
	return number;
}
};
bool Connected(Polygon pol1, Polygon pol2, Polygon_Parser P)
{
	for (int i =0; i < P.getCount(); i++)
	{
		if (pol1.Intersects(P.at(i)) && !(pol1 == P.at(i)))
		{
			if (P.at(i) == pol2) return true;
			else return Connected(pol2, P.at(i), P);
		}
	}
	return false;
}

Point& min_dist(Point& start, Point& p1, Point& p2)
{
	if (p1.distance(start) < p2.distance(start)) return p1;
	else return p2;
}
void doOperation(Polygon_Parser P, string operation)
{
	operation = tolower(operation);
	if (operation == "number_polygons")
	{
		//cout << "Number of polygons provided: " << P.getCount();
		cout << P.getCount();
	}
	else if (operation == "total_number_points")
	{
		int n =0;
		for (int i = 0; i < P.getCount(); i++)
		{
			n += P.polygons[i].getTotalPoints(true);
		}
		//cout << "Number of points provided: " << n;
		cout << n;
	}
	else if (operation == "enclosing_rectangle")
	{
		cout << "(" << P.get("minimum_x") << "," << P.get("minimum_y") << "),(" << P.get("minimum_x") << "," << P.get("maximum_y") << "),(" << P.get("maximum_x") << "," << P.get("maximum_y") << "),(" << P.get("maximum_x") << "," << P.get("minimum_y") << ")" ;
	}
	else if (operation == "minimum_x" || operation == "minimum_y" || operation == "maximum_x" || operation == "maximum_y")
	{	
		cout << P.get(operation);
		//cout << operation << ": " << number;
	}
	else if (operation == "total_redundant_points")
	{
		int n = 0;
		for (int i =0; i < P.getCount(); i++)
		{
			n+= P.polygons[i].getRedundantPoints();
		}
		cout << n;
	}
	else if (regex_match(operation, regex("^polygon_points \\d+$")))
	{
		smatch match;
		regex_search(operation, match, regex("\\d+$"));
		int _index = stoi(match.str(0).c_str());
		if (_index <= P.getCount())
		{
			P.at(_index-1).Print(false);
		}
		else
		{
			cout << "FAIL: Provided polygon index does not exist.";
			cout << "none";
		}
	}
	else if (regex_match(operation, regex("^point_polygons \\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\)$")))
	{
		smatch match;
		char * output;
		regex_search(operation, match, regex("\\([\-]{0,}\\d+[\\.\\d+]{0,},"));
		output = new char[match.str(0).length()];
		strcpy(output, match.str(0).c_str());
		output[0] = ' ';
		output[strlen(output) - 1] = ' ';
		float x = atof(output);
		regex_search(operation, match, regex(",[\-]{0,}\\d+[\\.\\d+]{0,}\\)$"));
		output = new char[match.str(0).length()];
		strcpy(output, match.str(0).c_str());
		output[0] = ' ';
		output[strlen(output) - 1] = ' ';
		float y = atof(output);
		bool remove = false;
		for (int i =0; i < P.getCount(); i++)
		{
			for (int j =0; j < P.polygons[i].getTotalPoints(true); j++)
			{
				if (P.polygons[i].points[j].X == x && P.polygons[i].points[j].Y == y)
				{
					cout << i+1 << ",";
					remove = true;
					break;
				}
			}
		}
		op_cleanup(remove);
	}
	else if (regex_match(operation, regex("^list_polygons_points (less|more|equal) \\d+$")))
	{
		smatch match;
		bool remove = false;
		regex_search(operation, match, regex("\\d+"));
		int digits = atoi(match[0].str().c_str());
		if (regex_match(operation, regex("^list_polygons_points less \\d+")))
		{
			for (int i = 0; i < P.getCount(); i++)
			{
				if (P.polygons[i].getTotalPoints() < digits)
				{	
					cout << i+1 << ",";
					remove = true;
				}
			}
		}
		else if (regex_match(operation, regex("^list_polygons_points more \\d+")))
		{	
			for (int i = 0; i < P.getCount(); i++)
			{
				if (P.polygons[i].getTotalPoints() > digits)
				{	
					cout << i+1 << ",";
					remove = true;
				}
			}
		}
		else if (regex_match(operation, regex("^list_polygons_points equal \\d+")))
		{
			for (int i = 0; i < P.getCount(); i++)
			{
				if (P.polygons[i].getTotalPoints() == digits)
				{	
					cout << i+1 << ",";
					remove = true;
				}
			}
		}
		op_cleanup(remove);
	}
	else if (regex_match(operation, regex("^list_points_polygons (less|more|equal) \\d+$")))
	{
		smatch match;
		bool remove = false;
		regex_search(operation, match, regex("\\d+"));
		int digits = atoi(match[0].str().c_str());
		int n = 0;
		for (int i = 0; i < P.getCount(); i++)
		{
			n+= P.polygons[i].getTotalPoints(true);
		}
		string _operation = "less";
		if (regex_match(operation, regex("^list_points_polygons more \\d+")))
		{
			_operation = "more";
		}
		else if (regex_match(operation, regex("^list_points_polygons equal \\d+")))
		{
			_operation = "equal";
		}
		Point * allPoints = new Point[n];
		int index = 0;
		for (int i = 0; i < P.getCount(); i++)
		{
			for (int j =0; j < P.at(i).getTotalPoints(true); j++)
			{
				allPoints[index] = P.at(i).points[j];
				index++;
			}
		}
		int occurence= n? 1: 0;
		Polygon Output;
		for (int i =0; i < n; i++)
		{
			for (int j =0; j <n; j++)
			{
				if (allPoints[j] == allPoints[i] && allPoints[j].getLabel() != allPoints[i].getLabel())
				{
					occurence++;
				}
			}
			if (occurence == digits && _operation == "equal" || occurence > digits && _operation == "more" || occurence < digits && _operation == "less")
			{
				Output.addPoint(allPoints[i], 0, true);
			}
			occurence = 1;
		}
		for (int i =0; i < Output.getTotalPoints(true); i++)
		{
			cout << Output.points[i] << ",";
			remove = true;
		}
		op_cleanup(remove);
	}
	else if (regex_match(operation, regex("^polygon_perimeter \\d+$")))
	{
		smatch match;
		regex_search(operation, match, regex("\\d+$"));
		int _index = stoi(match.str(0).c_str());
		if (_index <= P.getCount())
		{
			cout << P.at(_index-1).Length();
		}
		else
		{
			//cout << "FAIL: Provided polygon index does not exist.";
			cout << "none";
		}
	}
	else if (operation == "list_triangles") //Based on benchmarks, comparison is faster than regex matching, so we will use it when possible
	{
		bool remove = false;
		for (int i =0; i < P.getCount(); i++)
		{
			if (P.at(i).getTotalPoints() == 3)
			{
				cout << i+1 << ",";
				remove = true;
			}
		}
		op_cleanup(remove);
	}
	else if (operation == "list_rectangles") 
	{
		bool remove = false;
		for (int i =0; i < P.getCount(); i++)
		{
			if (P.at(i).isRectangle())
			{
				cout << i + 1 << ",";
				remove = true;
			}
		}
		op_cleanup(remove);
	}
	else if (operation == "list_trapezoid")
	{
		bool remove = false;
		for (int i = 0; i < P.getCount(); i++)
		{
			if (P.at(i).isTrapezoid())
			{
				cout << i + 1 << ",";
				remove = true;
			}

		}
		op_cleanup(remove);
	}
	else if (regex_match(operation, regex("^inside_rectangle \\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\),\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\),\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\),\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\)")))
	{
		smatch match;
		regex_search(operation, match, regex("\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\),\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\),\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\),\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\)"));
		char * _polygons = new char[match[0].str().length()];
		strcpy(_polygons, match[0].str().c_str());
		Polygon_Parser _P(_polygons);
		bool in_rect = true;
		bool remove = false;
		if (_P.at(0).isRectangle())
		{
			for (int i = 0; i < P.getCount(); i++)
			{
				if (P.at(i).Inside(_P.at(0)))
				{
					cout << i + 1 << ",";
					remove = true;
				}
			}
			op_cleanup(remove);
		}
		else
		{
			cout << "ERROR: Provided coordinates do not resemble a rectangle. Please retry.";
		}
	}
	else if (regex_match(operation, regex("^inside_circle \\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\),[\-]{0,}\\d+[\\.\\d+]{0,}")))
	{
		smatch match;
		regex_search(operation, match, regex("\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\)"));
		char * _polygons = new char[match[0].str().length()];
		strcpy(_polygons, match[0].str().c_str());
		Polygon_Parser _P(_polygons);
		float r = atof(operation.substr(operation.find("),") + 2).c_str());
		bool in_circle = true;
		bool remove = false;
		for (int i = 0; i < P.getCount(); i++)
		{
			for (int j = 0; j < P.at(i).getTotalPoints(true); j++)
			{
				if (!P.at(i).points[j].isRedundant())
				{
					if (!(P.at(i).points[j].distance(_P.at(0).points[0]) <= r))
					{
						in_circle = false;
						break;
					}

				}
			}

			if (in_circle)
			{
				cout << i + 1 << ",";
				remove = true;
			}
			in_circle = true;
		}
		op_cleanup(remove);
	}
	else if (regex_match(operation, regex("^polygon_area \\d+$")))
	{
		smatch match;
		regex_search(operation, match, regex("\\d+$"));
		int _index = stoi(match.str(0).c_str());
		if (_index <= P.getCount())
		{
			cout << P.at(_index - 1).Area();
		}
		else
		{
			//cout << "FAIL: Provided polygon index does not exist.";
			cout << "none";
		}
	}
	else if (regex_match(operation, regex("^polygons_area_range [\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}$")))
	{
		smatch match;
		regex_search(operation, match, regex("[\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}"));
		float minArea = atof(match[0].str().substr(0, match[0].str().find(',') + 1).c_str());
		float maxArea = atof(match[0].str().substr(match[0].str().find(',') + 1).c_str());
		if (minArea > maxArea)
		{
			swap(minArea, maxArea);
			cout << "WARNING: Invalid format. Minimum area is larger than maximum area. Swapping parameters..";
		}
		bool remove = false;
		for (int i = 0; i < P.getCount(); i++)
		{
			if (P.at(i).Area() >= minArea && P.at(i).Area() <= maxArea)
			{
				cout << i + 1 << ",";
				remove = true;
			}
		}
		op_cleanup(remove);
	}
	else if (regex_match(operation, regex("^polygons_enclosing_point \\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\)")))
	{
		bool remove = false;
		smatch match;
		regex_search(operation, match, regex("\\([\-]{0,}\\d+[\\.\\d+]{0,},[\-]{0,}\\d+[\\.\\d+]{0,}\\)"));
		char * _polygons = new char[match[0].str().length()+1];
		strcpy(_polygons, match[0].str().c_str());
		Polygon_Parser _P(_polygons);
		for (int i = 0; i < P.getCount(); i++)
		{
			if (_P.at(0).points[0].Inside(P.at(i)))
			{
				cout << i + 1 << ",";
				remove = true;
			}
		}
		op_cleanup(remove);
		delete[] _polygons;
	}
	else if (regex_match(operation, regex("^is_intersecting \\d+,\\d+")))
	{
		smatch match;
		regex_search(operation, match, regex("\\d+,\\d+"));
		int i = stoi(match[0].str().substr(0, match[0].str().find(",")));
		int j = stoi(match[0].str().substr(match[0].str().find(",") + 1));
		if (i <= P.getCount() && j <= P.getCount() && i > 0 && j > 0)
		{
			if (P.at(i - 1).Intersects(P.at(j - 1))) cout << "TRUE";
			else cout << "FALSE";
		}
		else
		{
			//cout << "FAIL: Provided polygon index does not exist.";
			cout << "none";
		}
	}
	else if (regex_match(operation, regex("^intersecting_group \\d+(,\\d+)+")))
	{
		smatch match;
		regex_search(operation, match, regex("\\d+(,\\d+)+"));
		string buffer = "";
		int count = 1;
		for (int i = 0; i < match[0].str().length(); i++)
		{
			if (match[0].str()[i] != ',')
			buffer += match[0].str()[i];
			else
			{
				int i = stoi(buffer);
				if (i <= P.getCount() && i > 0)
				{
					count++;
				}
				else
				{
					cout << "ERROR: '" << buffer << "' is an unrecognized polygon. Skipping..." << endl;
				}
				buffer = "";
			}
		}
		{
			int i = stoi(buffer);
			if (i <= P.getCount() && i > 0)
			{
				count++;
			}
			else
			{
				cout << "ERROR: '" << buffer << "' is an unrecognized polygon. Skipping..." << endl;
			}
		}
		buffer = "";
		int * polygons = new int[count + 1];
		count = 0;
		for (int i = 0; i < match[0].str().length(); i++)
		{
			if (match[0].str()[i] != ',')
				buffer += match[0].str()[i];
			else
			{
				int i = stoi(buffer);
				if (i <= P.getCount() && i > 0)
				{
					polygons[count] = i;
						count++;
				}
				buffer = "";
			}

		}
		{
			int i = stoi(buffer);
			if (i <= P.getCount() && i > 0)
			{
				polygons[count] = i;
				count++;
			}
		}
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count; j++)
			{
				if (j != i)
				{
					if (!P.at(polygons[i] - 1).Intersects(P.at(polygons[j] - 1))) {
						cout << "FALSE";
						count = -1;
						break;
					}
				}
			}
		}
		if (count > -1) cout << "TRUE";
		delete[] polygons;
			
	}
	else if (operation == "largest_intersecting_pair")
	{
		Polygon * max_areas = new Polygon[P.getCount() + 1];
		int index = 0;
		for (int i = 0; i < P.getCount(); i++)
		{
			max_areas[i] = P.at(i);
			max_areas[i].setTag(i);
		}
		for (int i = 0; i < P.getCount(); i++)
		{
			for (int j = i+1; j < P.getCount(); j++)
			{
				if (max_areas[i].Area() < max_areas[j].Area()){
					swap(max_areas[i],max_areas[j]);
				}
			}
		}
		bool remove = false;
		for (int i = 0; i < P.getCount(); i++)
		{
			for (int j = i + 1; j < P.getCount(); j++)
			{
				if (max_areas[i].Intersects(max_areas[j])) { cout << max_areas[i].getTag() +1 << "," << max_areas[j].getTag() + 1; remove = true; break; }
			}
			if (remove) break;
		}
		delete[] max_areas;
	}
	else if (regex_match(operation, regex("^is_connected \\d+,\\d+")))
	{
		smatch match;
		regex_search(operation, match, regex("\\d+,\\d+"));
		int i = stoi(match[0].str().substr(0, match[0].str().find(",")));
		int j = stoi(match[0].str().substr(match[0].str().find(",") + 1));
		if (i <= P.getCount() && j <= P.getCount() && i > 0 && j > 0)
		{
			if (Connected(P.at(i - 1), P.at(j - 1), P)) cout << "TRUE";
			else cout << "FALSE";
		}
		else
		{
			//cout << "FAIL: Provided polygon index does not exist.";
			cout << "none";
		}
	}
	else if (regex_match(operation, regex("^is_connected_group \\d+(,\\d+)+")))
	{
		smatch match;
		regex_search(operation, match, regex("\\d+(,\\d+)+"));
		string buffer = "";
		int count = 1;
		for (int i = 0; i < match[0].str().length(); i++)
		{
			if (match[0].str()[i] != ',')
				buffer += match[0].str()[i];
			else
			{
				int i = stoi(buffer);
				if (i <= P.getCount() && i > 0)
				{
					count++;
				}
				else
				{
					cout << "ERROR: '" << buffer << "' is an unrecognized polygon. Skipping..." << endl;
				}
				buffer = "";
			}
		}
		{
			int i = stoi(buffer);
			if (i <= P.getCount() && i > 0)
			{
				count++;
			}
			else
			{
				cout << "ERROR: '" << buffer << "' is an unrecognized polygon. Skipping..." << endl;
			}
		}
		buffer = "";
		int * polygons = new int[count + 1];
		count = 0;
		for (int i = 0; i < match[0].str().length(); i++)
		{
			if (match[0].str()[i] != ',')
				buffer += match[0].str()[i];
			else
			{
				int i = stoi(buffer);
				if (i <= P.getCount() && i > 0)
				{
					polygons[count] = i;
					count++;
				}
				buffer = "";
			}

		}
		{
			int i = stoi(buffer);
			if (i <= P.getCount() && i > 0)
			{
				polygons[count] = i;
				count++;
			}
		}
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count; j++)
			{
				if (j != i)
				{
					if (!Connected(P.at(polygons[i] - 1), P.at(polygons[j] - 1), P)) {
						cout << "FALSE";
						count = -1;
						break;
					}
				}
			}
		}
		if (count > -1) cout << "TRUE";
		delete[] polygons;
	}
	else if (operation == "maximum_intersecting_group")
	{
		int count = 0;
		int max_count = 0;
		string buffer = "";
		string max_buffer = "";
		int * _array = new int[P.getCount() + 1];
		int n = 0;
		for (int i = 0; i < P.getCount(); i++)
		{
			n = 0;
			buffer = to_string(i +1) + ",";
			for (int j = 0; j < P.getCount(); j++)
			{
				if (P.at(i).Intersects(P.at(j)) && j != i)
				{
					bool _continue = true;
					for (int k = 0; k < n; k++)
					{
						if (!P.at(j).Intersects(P.at(_array[k])))
						{
							_continue = false;
							break;
						}
					}
					if (_continue)
					{
						_array[n] = j;
						buffer += to_string(j + 1) + ",";
						count++;
						n++;
					}
				}
			}
			if (count > max_count) { max_count = count; max_buffer = buffer; }

		}
		max_buffer = max_buffer.substr(0, max_buffer.length() - 1);
		if ( max_buffer.length() > 0)
		cout << max_buffer;
		else cout << "none";
		delete[] _array;
	}
	else if (operation == "maximum_connected_group")
	{
		int count = 0;
		int max_count = 0;
		string buffer = "";
		string max_buffer = "";
		int * _array = new int[P.getCount() + 1];
		int n = 0;
		for (int i = 0; i < P.getCount(); i++)
		{
			n = 0;
			buffer = to_string(i + 1) + ",";
			for (int j = 0; j < P.getCount(); j++)
			{
				if (Connected(P.at(i),P.at(j), P) && j != i)
				{
					bool _continue = true;
					for (int k = 0; k < n; k++)
					{
						if (!Connected(P.at(j),P.at(_array[k]), P))
						{
							_continue = false;
							break;
						}
					}
					if (_continue)
					{
						_array[n] = j;
						buffer += to_string(j + 1) + ",";
						count++;
						n++;
					}
				}
			}
			if (count > max_count) { max_count = count; max_buffer = buffer; }

		}
		max_buffer = max_buffer.substr(0, max_buffer.length() - 1);
		if (max_buffer.length() > 0)
			cout << max_buffer;
		else cout << "none";
		delete[] _array;
	}
	else if (operation == "quit")
	{
		Helper::Exit(3);
	}
	else
	{
		cout << "Unknown operation. Please double-check the spelling (case insensitive)";
	}
	cout << endl;
}
void ReadInput(char* message, string &input)
{
	cout << message;
	getline(cin, input);
}
int main()
{
	try
	{
		string input;
		ReadInput("", input);
		if (input.find("[") != string::npos)
			input.erase(0, input.find("[")); //Erase everything before [ 
		if (input.length() > 0)
		{
			if (input[input.length() - 1] == ']')
			{
				input = input.substr(0, input.length() - 1);
			}
			if (input[0] == '[')
			{
				input = input.substr(1, input.length() - 1);
			}
		}
		if (input.length() > 0)
		{
			char * polygons = new char[input.length() + 1];
			strcpy(polygons, input.c_str());
			Polygon_Parser P(polygons);
			do
			{
				ReadInput("", input);
				doOperation(P, input);
			} while (true);
			delete[] polygons;
		}
		else
		{
			Helper::Exit(5);
		}
	}
	catch (exception) { Helper::Exit(10); }
	return 0;
}
