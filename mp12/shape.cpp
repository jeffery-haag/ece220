#include "shape.hpp"
int num_shapes;
const double PI = 3.14159265358979323846;
//partners jrhaag2,briants2

//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 
Shape::Shape(string name)
{
  name_ = name;
}

string Shape::getName()
{
  return name_;
}

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double width, double height):Shape("Rectangle")
{
  width_ = width;
  length_ = height;
};

double Rectangle::getArea()const
{
  double area;
  area = width_ * length_;
  return area;
}

double Rectangle::getVolume()const{return 0;}
double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}

Rectangle Rectangle :: operator + (const Rectangle& recB)
{
	
	Rectangle recC(  (recB.getWidth()+width_), (recB.getLength()+length_) ) ;
	//recC.width=(recB->width_+recA->width_);
	//recC.length=(recB.length_+recA.length_)
	
	return recC;
}

Rectangle Rectangle::operator-(const Rectangle& recA)
{
	double width=(width_-recA.getWidth());
	double length=(length_-recA.getLength()) ;
	if (width<0)width=0;
	if (length<0)length=0;

	Rectangle recC( width , length );
	//recC.width_=(recB.width_-recA.width_);
	//recC.length_=(recB.length_-recA.length_)
	
	return recC;
}

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle")
{
  radius_ = radius;
};

double Circle::getArea()const
 {
   double area;
   area = (PI * (radius_ * radius_));
   return area;
 }

double Circle::getVolume()const{return 0;}
double Circle::getRadius()const{return radius_;}

Circle Circle::operator+(const Circle& cirB)
{
	Circle cirC( (cirB.getRadius()+radius_)  );
	//recC.radius_=(cirB.radius_+recA.radius_);
	
	return cirC;
}
Circle Circle::operator-(const Circle& cirA)
{
	double rad=(radius_-cirA.getRadius()) ;
	if (rad<0)rad=0; 
	Circle cirC( rad);
	//recC.radius_=(cirB.radius_-recA.radius_);
	
	return cirC;
}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius):Shape("Sphere")
{
  radius_ = radius;
};

double Sphere::getVolume()const
{
  double vol;
  vol = ((4.0/3.0) * PI * (radius_ * radius_ * radius_));
  return vol;
}

double Sphere::getArea()const
{
  double area;
  area = (4.0 * PI * (radius_ * radius_));
  return area;
}
double Sphere::getRadius()const{return radius_;}

Sphere Sphere::operator+(const Sphere& sphB)
{
	Sphere sphC(  (sphB.getRadius()+radius_)  );
	//sphC.radius_=(sphB.radius_+recA.radius_);
	
	return sphC;
}
Sphere Sphere:: operator-(const Sphere& sphA)
{
	int rad=(radius_-sphA.getRadius());
	if(rad<0)rad=0;
	Sphere sphC(  rad);
	//sphC.radius_=(sphB.radius_-recA.radius_);
	
	return sphC;
}




//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism")
{
  width_ = width;
  length_ = length;
  height_ = height;
};

double RectPrism::getVolume()const
{
  double vol;
  vol = (width_ * length_ * height_);
  return vol;
}
  
double RectPrism::getArea()const
{
  double area;
  area = (2*((length_*height_) + (length_ * width_) + (width_ * height_)));
  return area;
}


double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}



RectPrism RectPrism::operator+(const RectPrism& priA)
{
	double width=(width_+priA.getWidth());
	double length=(length_+priA.getLength());
	double height=(height_+priA.getHeight());


	RectPrism priC( width, length, height);
	
	return priC;
}

RectPrism RectPrism::operator-(const RectPrism& priA)
{
	double width=(width_-priA.getWidth());
	double length=(length_-priA.getLength());
	double height=(height_-priA.getHeight());
	if(width<0)width=0;
	if(length<0)length=0;
	if(height<0)height=0;

	RectPrism priC( width, length, height);
	
	return priC;
}




 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
	
	vector<Shape*> vect;
	string name;
  string extra;
  int num;
  double rw, rl, cr, sr, rph, rpw, rpl;
  ifstream ifs (file_name, ifstream::in);
  ifs >> num;
  num_shapes = num;
  cout << num << endl;
  cerr << extra << endl;
  vect.reserve(num);
  
  while (true) //EDGY!!
  {
    ifs >> name;
    if (ifs.eof()) break; //Quit if end of text file.
    cout << name << endl; //Testing
    
    if (name == "Rectangle") //Create rectangle object
    {
      cerr << extra << endl;
      ifs >> rw;
      cerr << extra << endl;
      ifs >> rl;
      Shape* shape_ptrR = new Rectangle(rw, rl);
      vect.push_back(shape_ptrR);
    }
    else if (name == "Circle") //Create circle object
    {
      cerr << extra << endl;
      ifs >> cr;
      Shape* shape_ptrC = new Circle(cr);
      vect.push_back(shape_ptrC);
    }
    else if (name == "Sphere") //Create sphere object
    {
      cerr << extra << endl;
      ifs >> sr;
      Shape* shape_ptrS = new Sphere(sr);
      vect.push_back(shape_ptrS);
    }
    else if (name == "RectPrism") //Create Rectangular Prism Object
    {
      cerr << extra << endl;
      ifs >> rpw;
      cerr << extra << endl;
      ifs >> rpl;
      cerr << extra << endl;
      ifs >> rph;
      Shape* shape_ptrRP = new RectPrism(rpw, rpl, rph);
      vect.push_back(shape_ptrRP);
    }
    
    cerr << extra << endl; //Go to next item in file
  }
	
	ifs.close();
	return vector<Shape*>(vect.begin(), vect.end()); // please remeber to modify this line to return the correct value
}

// call getArea() of each object 


// return the max area
double MaxArea(vector<Shape*> shapes)
{
	if (shapes.empty())return 0;
	int counter=shapes.size();

	double max_area = 0;

	for (int i=0;i<counter;i++)
	{
		if (shapes[i]->getArea()>max_area)max_area=shapes[i]->getArea();
	}

	
	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	if (shapes.empty())return 0;
	int counter=shapes.size();

	

	for (int i=0;i<counter;i++)
	{
		if (shapes[i]->getVolume()>max_volume)max_volume=shapes[i]->getVolume();
	}

	
	return max_volume;
}


