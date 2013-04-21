/*


Test file by Derrick Ho
*/
/*
pathfinding algorithm file by Derrick Ho

How to use this file:

initialize using the contructor.
Pathfind ();

load map

loadPath("filename");

use function called

std::vector<Ogre::Vector3> startToTarget(Ogre::Vector3 start, Ogre::Vector3 target, bool Simple_spline = False);

This function returns a std vector full of Ogre::Vector3's.  it takes in
as arguments two Ogre::Vector3's.  The Ogre::Vector3's are the positions in
space.  The third toggles whether to use the simple spline or not
it will create a vector of Ogre::Vector3 from a starting position to an ending position

example:
Pathfind floor;
floor.loadPath(filename);//initialization
Ogre::Vector3 s(sx, 0,sz); //start position
Ogre::Vector3 t(tx, 0,tz); //target position
std::vector<Ogre::Vector3> pass(  floor.startToTarget(s,t)  );

note may 29,2011
using centroid distances to calculate the G score did not appear
to have differing results from using the midHypotenuse to calculate
the the G score.  you may have to try a different map to actually see
if there is a difference.
*/

#ifndef __PATHFIND_H__
#define __PATHFIND_H__

#include <iostream>
#include <cassert>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <deque>
#include <cstring>
#include <fstream>
#include <sstream>
//#include <cmath>
//#include <algorithm>
#include <cfloat>
#include <Ogre.h>
#include <OgreVector3.h>
#include <OgreSimpleSpline.h>
//#define foreach(I)							\
//	for(typeof((I).begin()) it = (I).begin(); it != (I).end()  ;++it)


using namespace std;

//obj class was given to us in CS130
class obj
{
public:
	// Faces maintain indices to the data for efficiency, rather
	// than duplicating the data. Provided the indices, you can call
	// get_vertex and get_normal in obj:: to get the data.
	struct face
	{
		std::string mat;
		std::string group;
		std::vector<int> vind; // vertex indices
		std::vector<int> nind; // normal indices
		std::vector<int> tex;  // texture indices
	};

	struct material
	{
		material();

		float ka[3], ks[3], kd[3];
		float ns;
		int illum;
		std::string map_ka, map_kd, map_ks;
	};

	typedef std::map<std::string, material> string_to_material_map;

	obj();
	~obj();

	bool load(const std::string& filename);

	inline size_t get_vertex_count() const;
	inline size_t get_normal_count() const;
	inline size_t get_texture_indices_count() const;

	// returns the vertex with vertex index i
	inline const float* get_vertex(size_t i) const;

	// returns the normal with normal index i
	inline const float* get_normal(size_t i) const;

	// returns the texture with texture index i
	inline const float* get_texture_indices(size_t i) const;

	inline size_t get_face_count() const;
	inline const face& get_face(size_t i) const;
	inline const material* get_material(
		const std::string& name
		) const;
	inline const string_to_material_map& get_materials() const;

private:
	bool load_material(const std::string& filename);

	std::vector<float> verts;
	std::vector<float> norms;
	std::vector<float> tex;
	std::vector<face> faces;
	string_to_material_map mats;
};

size_t obj::get_face_count() const
{
	return faces.size();
}

const obj::face& obj::get_face(size_t i) const
{
	assert(i < faces.size());
	return faces[i];
}

size_t obj::get_vertex_count() const
{
	return verts.size() / 3;
}

const float* obj::get_vertex(size_t i) const
{
	return &verts[3*i];
}

size_t obj::get_normal_count() const
{
	return norms.size() / 3;
}

const float* obj::get_normal(size_t i) const
{
	return &norms[3*i];
}

size_t obj::get_texture_indices_count() const
{
	return tex.size() / 2;
}

const float* obj::get_texture_indices(size_t i) const
{
	return &tex[2*i];
}

const obj::material* obj::get_material(
	const std::string& name
	) const
{
	std::map<std::string, material>::const_iterator i =
		mats.find(name);

	if (i == mats.end()) {
		return NULL;
	} else {
		return &(i->second);
	}
}

const obj::string_to_material_map& obj::get_materials() const
{
	return mats;
}

obj::material::material()
{
	memset(ka, 0, 3*sizeof(float));
	memset(kd, 0, 3*sizeof(float));
	memset(ks, 0, 3*sizeof(float));
	ns = 0;
	illum = 0;
}

obj::obj()
{
}

obj::~obj()
{
}

bool obj::load_material(const string& filename)
{
	ifstream istr(filename.c_str());
	if (!istr) return false;

	string line, tok;
	string sval;

	string matact;
	while (getline(istr, line))
	{
		stringstream ss(line);
		ss >> sval;

		if (sval == "newmtl")
		{
			ss >> matact;
			mats.insert(
				std::pair<std::string,material>(matact, material())
				);
		}
		else if (sval == "Ka")
		{
			for (int i = 0; i < 3; ++i)
				ss >> mats[matact].ka[i];
		}
		else if (sval == "Kd")
		{
			for (int i = 0; i < 3; ++i)
				ss >> mats[matact].kd[i];
		}
		else if (sval == "Ks")
		{
			for (int i = 0; i < 3; ++i)
				ss >> mats[matact].ks[i];
		}
		else if (sval == "Ns")
		{
			ss >> mats[matact].ns;
		}
		else if (sval == "illum")
		{
			ss >> mats[matact].illum;
		}
		else if (sval == "map_Ka")
		{
			ss >> mats[matact].map_ka;
		}
		else if (sval == "map_Kd")
		{
			ss >> mats[matact].map_kd;
		}
		else if (sval == "map_Ks")
		{
			ss >> mats[matact].map_ks;
		}
	}

	istr.close();
	return true;
}

bool obj::load(const std::string& filename)
{
	ifstream istr(filename.c_str());
	if (!istr) return false;

	string line, tok;
	int ival;
	float fval;
	char cval;
	string sval;

	string matact("none");

	while (getline(istr, line))
	{
		stringstream ss;
		ss << line;

		ss >> tok;
		if (tok == "v") {
			for (int i = 0; i < 3; ++i)
			{
				ss >> fval;
				verts.push_back(fval);
			}
		}
		else if (tok == "vn")
		{
			for (int i = 0; i < 3; ++i)
			{
				ss >> fval;
				norms.push_back(fval);
			}
		}
		else if (tok == "vt")
		{
			for (int i = 0; i < 2; ++i)
			{
				ss >> fval;
				tex.push_back(fval);
			}
		}
		else if (tok == "f")
		{
			string ftok;
			face f;
			while (ss >> ftok) {
				stringstream ss2;

				ss2 << ftok;
				//cout << ftok << endl;

				ss2 >> ival;
				f.vind.push_back(ival-1);
				//cout << ival << endl;

				if (ss2 && ss2.peek() == '/')
				{
					ss2 >> cval;

					// texture coordinates
					if (ss2.peek() != '/')
					{
						ss2 >> ival;
						f.tex.push_back(ival-1);
						//cout << fval << endl;
					}
				}

				// normal indices
				if (ss2 && ss2.peek() == '/')
				{
					ss2 >> cval;
					ss2 >> ival;
					f.nind.push_back(ival-1);
					//cout << ival << endl;
				}

			};

			//cout << matact << endl;
			f.mat = matact;
			faces.push_back(f);
		}
		else if(tok == "mtllib")
		{
			ss >> sval;
			if (!load_material(sval)) {
				cout << "(warning) could not load material file: " << sval << endl;
			}
		}
		else if (tok == "usemtl")
		{
			ss >> matact;
			//cout << matact<< endl;
		}
	}

	istr.close();
	return true;
}




class Fnode//it is the face class and its verteices
{
 public:
  Ogre::Vector3 v1,v2,v3;
  std::pair<float,std::pair<Ogre::Vector3,Ogre::Vector3> > l1,l2,l3; //pair<va.squareddistance(vb), pair<va,vb>>
  float F,G,H;//weights for heuristics
  Ogre::Vector3 centroid;
  Ogre::Vector3 midHyp;//mid point of hypotenuse
  //Fnode *parent;
  size_t parent;
  size_t index;//index that corresponds to its location in the VFaces.
  Fnode(Ogre::Vector3 v1,Ogre::Vector3 v2,Ogre::Vector3 v3)
    :v1(v1), v2(v2), v3(v3), parent(0), F(0), G(0), H(0)
    {
      this->centroid = Ogre::Vector3((1.0/3.0)*(v1[0] + v2[0] + v3[0]),
				     (1.0/3.0)*(v1[1] + v2[1] + v3[1]),
				     (1.0/3.0)*(v1[2] + v2[2] + v3[2]));
      
      l1=	std::pair<float,std::pair<Ogre::Vector3,Ogre::Vector3> >
	(this->v1.squaredDistance(this->v2),
	 std::pair<Ogre::Vector3,Ogre::Vector3>(this->v1,this->v2));
      l2=	std::pair<float,std::pair<Ogre::Vector3,Ogre::Vector3> >
	(this->v2.squaredDistance(this->v3),
	 std::pair<Ogre::Vector3,Ogre::Vector3>(this->v2,this->v3));
      l3=	std::pair<float,std::pair<Ogre::Vector3,Ogre::Vector3> >
	(this->v3.squaredDistance(this->v1),
	 std::pair<Ogre::Vector3,Ogre::Vector3>(this->v3,this->v1));
      
      this->midHyp= l1.second.first.midPoint(l1.second.second);
      //find the hypotenuse
      if(l2.first > l1.first) {
	if(l2.first > l3.first)
	  this->midHyp= l2.second.first.midPoint(l2.second.second);
	//this->midHyp = l2.first;
	else
	  this->midHyp= l3.second.first.midPoint(l3.second.second);
	//this->midHyp = l3.first;
      }
      if(l3.first > l1.first){
	if(l3.first > l2.first)
	  this->midHyp= l3.second.first.midPoint(l3.second.second);
	//this->midHyp = l3.first;
	else
	  this->midHyp= l2.second.first.midPoint(l2.second.second);
	//this->midHyp = l2.first;
	
      }
      
      
    }
    friend std::ostream& operator<<(std::ostream&s, Fnode f)
    {
      s << "( " << f.v1 << " ), "
	<< "( " << f.v2 << " ), "
	<< "( " << f.v3 << " ) "
	<< f.centroid
	<< " "
	<< f.midHyp;
      
      return s;
    }
 private:
};

bool isAdjTo(Fnode& lhs, Fnode& rhs)
{
  std::vector<Ogre::Vector3> set;
  set.push_back(lhs.v1);
  set.push_back(lhs.v2);
  set.push_back(lhs.v3);
  
  size_t adjflag=0; //if reaches 2 then the triangles are adj
  for (size_t i=0; i < 3 ; ++i) {
    if((set[i] == rhs.v1)) ++adjflag;
    if((set[i] == rhs.v2)) ++adjflag;
    if((set[i] == rhs.v3)) ++adjflag;
  }
  return (adjflag==2? true: false);
}

typedef Ogre::Vector3 V3;
std::pair<V3,V3> getAdjNodes(Fnode& lhs, Fnode& rhs )
{
  if(isAdjTo(lhs,rhs)){
    std::vector<V3> set;
    std::vector<V3> adjSet;
    set.push_back(lhs.v1);
    set.push_back(lhs.v2);
    set.push_back(lhs.v3);
    
    size_t adjflag=0; //if reaches 2 then the triangles are adj
    for (size_t i=0; i < 3 ; ++i) {
      if((set[i] == rhs.v1)){ ++adjflag; adjSet.push_back(set[i]);}
      if((set[i] == rhs.v2)){ ++adjflag; adjSet.push_back(set[i]);}
      if((set[i] == rhs.v3)){ ++adjflag; adjSet.push_back(set[i]);}
    }
    return std::pair<V3,V3> (adjSet[0],adjSet[1]);
  }
  else return std::pair<V3,V3>();
  
}

class Vnode
{
 public:
  Vnode(Ogre::Vector3 v){
    this->value=v;
    setId();
  }
  void setId(){
    stringstream ss;
    ss << value[0] << "-" << value[1] << "-" << value[2];
    identity = ss.str();
  }
  string getId(){
    return identity;
  }
 private:
  string identity;//string used to identify it as unique
  size_t index;// number given to it to destiguish it from the others
  Ogre::Vector3 value;
  std::vector<Vnode*> adj;//pointer to adj nodes.
};

class Pathfind
{
 public:
  Pathfind(){}
  Pathfind(string a );
  void loadPath (string a);
  ~Pathfind();
  deque<Ogre::Vector3>startToTarget(Ogre::Vector3 start,
					  Ogre::Vector3 target,
					  bool ss = 0);
 private:
  void  printAllFaces();
  void createFaceVector();
  deque<int> a_star(int start, int end, Ogre::Vector3, Ogre::Vector3);
  
  void makeFaceAdjMat(std::vector<bool>& a,std::vector<Fnode>& f)//1 means adj 0 means not
  {
    for (size_t i=0; i < f.size(); ++i) {
      for (size_t j=0; j < f.size(); ++j) {
	if(isAdjTo(f[i],f[j])) a[i + f.size()*j]=1;
      }
    }
  }
  
  int get_num_faces(){
    return Vfaces.size();
  } 
  
  bool vec2LinesIntersect ( Ogre::Vector2 l1s, Ogre::Vector2 l1f, Ogre::Vector2 l2s, Ogre::Vector2 l2f ){
    
    Ogre::Vector2 v1 = l1f - l1s;
    
    Ogre::Vector2 v2 = l2s - l1s;
    Ogre::Vector2 v3 = l2f - l1s;
    
    Ogre::Real crossProd1 = v1.crossProduct(v2);
    Ogre::Real crossProd2 = v1.crossProduct(v3);
    
    if ((crossProd1 >= 0 && crossProd2 <= 0) || (crossProd1 <= 0 && crossProd2 >= 0) || (crossProd1 == 0 && crossProd2 == 0))
      {
	v1 = l2s - l2f;
	
	v2 = l1s - l2f;
	v3 = l1f - l2f;
	
	crossProd1 = v1.crossProduct(v2);
	crossProd2 = v1.crossProduct(v3);
	
	if ((crossProd1 >= 0 && crossProd2 <= 0) || (crossProd1 <= 0 && crossProd2 >= 0) || (crossProd1 == 0 && crossProd2 == 0))
	  {
	    return true;
	  }
      }
    return false;
  }
  void makeFaceAdjNodeList(deque<int>& path_of_faces, deque<std::pair<V3,V3> >& pair_adj ){
    for(size_t i = 1; i < path_of_faces.size(); ++i){
      pair_adj.push_back(getAdjNodes(Vfaces[path_of_faces[i-1]],Vfaces[path_of_faces[i]]));
    }
  }
  
 private:
  obj o;
  vector<Fnode> Vfaces;
  std::vector<bool> faceAdjMat;
};


Pathfind::Pathfind(string filename){
  
  
  o.load(filename);
  createFaceVector();

  
  faceAdjMat.resize(Vfaces.size()*Vfaces.size(),0);
  makeFaceAdjMat(faceAdjMat, Vfaces);
  
}

Pathfind::~Pathfind(){
}

void Pathfind::loadPath(string filename){ 
  o.load(filename);
  createFaceVector();
  faceAdjMat.resize(Vfaces.size()*Vfaces.size(),0);
  makeFaceAdjMat(faceAdjMat, Vfaces);
}

deque<Ogre::Vector3> Pathfind::startToTarget(Ogre::Vector3 start,
						   Ogre::Vector3 target,
						   bool ss)
{
 deque<Ogre::Vector3> t;//vector that holds a path to follow
  
  //find which face the start is on
  int start_face, target_face;
  bool found_s = false;
  bool found_t= false;
  
  
  for (vector<Fnode>::iterator it = Vfaces.begin(); it != Vfaces.end(); ++it)
    {
      if(found_s && found_t) break;
      if(!found_s){
	if( Ogre::Math::pointInTri2D( Ogre::Vector2 (start[0], start[2]),
				      Ogre::Vector2 (it->v1[0], it->v1[2]),
				      Ogre::Vector2 (it->v2[0], it->v2[2]),
				      Ogre::Vector2 (it->v3[0], it->v3[2])
				      ))
	  {
	    start_face = it->index;
	    found_s = true;
	  }
      }
      if(!found_t){
	if( Ogre::Math::pointInTri2D( Ogre::Vector2 (target[0], target[2]),
				      Ogre::Vector2 (it->v1[0], it->v1[2]),
				      Ogre::Vector2 (it->v2[0], it->v2[2]),
				      Ogre::Vector2 (it->v3[0], it->v3[2])
				      ))
	  {
	    target_face = it->index;
	    found_t = true;
	    
	  }
      }
      
    }
  //=========
  if (!found_t) {
    // cout << " target not on any valid face"<< endl;
    // return deque<V3>();

    t.push_back(start);
    std::vector<V3> try_tar;
    for(float k = 0.1; k < 5.0; k+=0.1){ 
      try_tar.push_back(V3(target[0],target[1],target[2]+k));
      try_tar.push_back(V3(target[0],target[1],target[2]-k));
      try_tar.push_back(V3(target[0]-k,target[1],target[2]));
      try_tar.push_back(V3(target[0]+k,target[1],target[2]));
    }
    for(size_t itt = 0; itt < try_tar.size();++itt)
      {
	V3 tar( try_tar[itt]);
	for (vector<Fnode>::iterator it = Vfaces.begin(); it != Vfaces.end(); ++it)
	  {
	    
	    
	    if( Ogre::Math::pointInTri2D( Ogre::Vector2 (tar[0], tar[2]),
					  Ogre::Vector2 (it->v1[0], it->v1[2]),
					  Ogre::Vector2 (it->v2[0], it->v2[2]),
					  Ogre::Vector2 (it->v3[0], it->v3[2])
					  ))
	      {
		
		t.push_back(tar);
		return startToTarget(t[0],t[1] );
	      }
	  }
	
      }
    
    //if all else fails
    
    //t.push_back(target);
    return t;
  }//not on a valid face
  if (!found_s) {//npc is not on nav mesh but target is
    t.push_back(start);
    std::vector<V3> try_tar;
    for(float k = 0.0; k < 5.0; k+=0.1){
      try_tar.push_back(V3(start[0],start[1],start[2]+k));
      try_tar.push_back(V3(start[0],start[1],start[2]-k));
      try_tar.push_back(V3(start[0]-k,start[1],start[2]));
      try_tar.push_back(V3(start[0]+k,start[1],start[2]));
    }
    for(size_t itt = 0; itt < try_tar.size();++itt)
      {
	V3 tar( try_tar[itt]);
	for (vector<Fnode>::iterator it = Vfaces.begin(); it != Vfaces.end(); ++it)
	  {
	    
	    
	     if( Ogre::Math::pointInTri2D( Ogre::Vector2 (tar[0], tar[2]),
	    				Ogre::Vector2 (it->v1[0], it->v1[2]),
	    				Ogre::Vector2 (it->v2[0], it->v2[2]),
	    				Ogre::Vector2 (it->v3[0], it->v3[2])
	    				))
	    {
	      
	      t.push_back(tar);
	      return t;
	    }
	  }
	
      }
    
    //if all else fails push target on it and hopefully
    //chasing him will move the npc enough to get out of
    //the trap
    
    t.push_back(target);
    return t;
    
  }  
  t.push_back(start);

  //if target and start are on the same face then  
  if(start_face == target_face)
    {
      // t.push_back(start );
      t.push_back(target);
    }
  
  //if target and start are in adj faces
  else if(isAdjTo(Vfaces[start_face], Vfaces[target_face]))
    {
      //cout << "bleh" <<endl;
      
      std::pair<V3,V3> pr = getAdjNodes(Vfaces[start_face], Vfaces[target_face]);
      if( vec2LinesIntersect ( Ogre::Vector2 (pr.first[0],pr.first[2]), Ogre::Vector2 (pr.second[0],pr.second[2]),
			       Ogre::Vector2 (start[0], start[2]), Ogre::Vector2(target[0], target[2]))){
	//	t.push_back(start);
	t.push_back(target);
      }
      //else go to the adj node that is closer to the target then when you get then go to the target
      else{
	float dist1 , dist2;
	dist1 = (pr.first).squaredDistance(target);
	dist2 = (pr.second).squaredDistance(target);
	//t.push_back(start);
	if(dist1 >= dist2) //start to pr.second to target is shorter
	  t.push_back(pr.second);
	else
	  t.push_back(pr.first);
	t.push_back(target);
      }
      
    }
  //if farther away
  // use a_star(int, int) to return a vector of
  // faces that lead up to the target.
  // make a vector of pairs that contain the adjnodes between
  //each face and use that as a line.  then check if
  //a line from your start to a certain adjnodes line's center intersect
  
  else
    {
      deque<int> path_nums(a_star(start_face, target_face, start,target ));
      
      int path_num_count = path_nums.size();
      
      deque<std::pair<V3,V3> > v_of_adj_nodes;
      makeFaceAdjNodeList(path_nums, v_of_adj_nodes);
      //=================
      //for use with simple spline method 
      if(ss){
	//t.push_back(start);
	for(int i = 0; i < v_of_adj_nodes.size(); ++i)
	  t.push_back(v_of_adj_nodes[i].first.midPoint(v_of_adj_nodes[i].second));
	{//make the vector into a SimpleSpline
	  Ogre::SimpleSpline s_Spline;
	  s_Spline.setAutoCalculate(0);
	  for (deque<Ogre::Vector3>::iterator it = t.begin(); it != t.end(); ++it)
	    s_Spline.addPoint(*it);
	  s_Spline.recalcTangents();
	  deque<Ogre::Vector3> Simple_spline_vector;
	  
	  for(float i = 0; i <= 1.0001 ; i+= 0.50/(path_num_count))
	    Simple_spline_vector.push_back(s_Spline.interpolate(i));
	  
	  Simple_spline_vector.push_back(target);//put target at end of vector
	  return Simple_spline_vector;
	}//finish simple spline
      }
      //=============================
      //use below code if you want a minimum number of control points
      //------
      else
	{
	  //t.push_back(start);
	  V3 cur_V3 = start;
	  int cur_V3num =0;
	  for(size_t i = 0; i < v_of_adj_nodes.size() ; ++i){
	    //V3 temp_d = v_of_adj_nodes[i].first.midPoint(v_of_adj_nodes[i].second);
	    std::pair<V3,V3> furthest_line_visible(v_of_adj_nodes[i]);
	    for(size_t j = cur_V3num; j < i ; ++j){
	      std::pair<V3,V3> temp_mid = v_of_adj_nodes[j];
	      //	     if( vec2LinesIntersect(Ogre::Vector2 (temp_mid.first[0],temp_mid.first[2]),
	      //			    Ogre::Vector2 (temp_mid.second[0],temp_mid.second[2]),
	      //			    Ogre::Vector2 (cur_V3[0], cur_V3[2]), Ogre::Vector2(temp_d[0], temp_d[2]))){
	      
	      //  continue;
	      // }
	      if(( vec2LinesIntersect(Ogre::Vector2 (temp_mid.first[0],temp_mid.first[2]),
				      Ogre::Vector2 (temp_mid.second[0],temp_mid.second[2]),
				      Ogre::Vector2 (cur_V3[0], cur_V3[2]), 
				      Ogre::Vector2(furthest_line_visible.first[0],furthest_line_visible.first[2]))  ) 
		 && 
		 ( vec2LinesIntersect(Ogre::Vector2 (temp_mid.first[0],temp_mid.first[2]),
				      Ogre::Vector2 (temp_mid.second[0],temp_mid.second[2]),
				      Ogre::Vector2 (cur_V3[0], cur_V3[2]), 
				      Ogre::Vector2(furthest_line_visible.second[0],furthest_line_visible.second[2]))  ))
		{
		  continue; 
		}
	      else{
		float dist1 , dist2;
		
		std::pair<V3,V3> last (v_of_adj_nodes[i].first,v_of_adj_nodes[i].second);
		if(i-1 < 0) {cout << "err" << endl; exit(0);}//debug
		std::pair<V3,V3> mid (v_of_adj_nodes[i-1].first,v_of_adj_nodes[i-1].second);
		dist1 = (cur_V3).distance(mid.first) + (mid.first).distance((last.first).midPoint(last.second));
		dist2 = (cur_V3).distance(mid.second)+ (mid.second).distance((last.first).midPoint(last.second));
		if(dist1 > dist2) //start to pr.second to target is shorter
		  t.push_back(mid.second);
		else if (dist1 <dist2)
		  t.push_back(mid.first);
		else
		  t.push_back((mid.first).midPoint(mid.second));
		
		cur_V3num = i; //increment
		
		cur_V3= t[t.size()-1];//mid is the new cur_V3
		break;
	      }
	    }
	  }
	  int temp_size = v_of_adj_nodes.size()-1;
	  
	  if( vec2LinesIntersect(Ogre::Vector2 (v_of_adj_nodes[temp_size].first[0],v_of_adj_nodes[temp_size].first[2]),
				 Ogre::Vector2 (v_of_adj_nodes[temp_size].second[0],v_of_adj_nodes[temp_size].second[2]),
				 Ogre::Vector2 (cur_V3[0], cur_V3[2]),
				 Ogre::Vector2 (target[0], target[2]))){
	    t.push_back(target);
	  }
	  else
	    {
	      float dist1 , dist2;
	      std::pair<V3,V3> pr (v_of_adj_nodes[temp_size]);
	      V3 cur = t[t.size()-1];
	      dist1 =(cur).distance(pr.first) + (pr.first).distance(target);
	      dist2 = (cur).distance(pr.second) + (pr.second).distance(target);
	      if(dist1 > dist2) //start to pr.second to target is shorter
		t.push_back(pr.second);
	      else if(dist1 < dist2)
		t.push_back(pr.first);
	      else
	  	t.push_back(pr.first.midPoint(pr.second));
	      
	      t.push_back(target);
	    }
	}//end min control points code
    }
  return t;
}
//==========================

/*Start is the index of the face that the */
deque<int> Pathfind::a_star(int start, int end ,Ogre::Vector3 st, Ogre::Vector3 en){

	std::set<int> open;
	std:: set<int> closed;
	Fnode* cur_node=NULL;
	//add start to open list
	open.insert(start);
	float G,H;
	G=0; //since it is the first one
	H = st.squaredDistance(en);
	if(H<0) H=H*-1;//distance always positive
	
	Vfaces[start].G=G;
	Vfaces[start].H=H;
	Vfaces[start].F=G+H;
	
	
	//loop this
	while(open.size())
	  {
	    //a)look for lowest cost F square on open list called cur_node
	    //by default it is set to 0 so you have to calculate it
	    // size_t first_index = *(open.begin());
	    float f_cost =FLT_MAX;// Vfaces[first_index].F;
	    size_t index_of_smallest_fcost=0;
	    
	    for (set<int>::iterator it = open.begin(); it != open.end(); ++it)
	      {
		float node_f_cost =Vfaces[*it].F;
		if(node_f_cost <f_cost)
		  {
		    f_cost = node_f_cost;
		    index_of_smallest_fcost= *it;
		    
		  }
	      }
	    if(index_of_smallest_fcost == end)
	      {
		size_t current_node = end;
		deque<int> triangle_path_solution;
		while(current_node != start){
		  triangle_path_solution.push_front(current_node);
		  current_node = Vfaces[current_node].parent;
		}
		triangle_path_solution.push_front(start);
		return triangle_path_solution;
	      }
	    cur_node = &Vfaces[index_of_smallest_fcost];//pointer to an Fnode
	    open.erase(index_of_smallest_fcost);// takes it out of open list
	    //b)put cur_node on closed list.
	    closed.insert(index_of_smallest_fcost);
	    
	    //for each of the adjecent nodes to the current....
	    std::set<int> adj_nodes;
	    for(size_t i = 0; i < Vfaces.size();++i)
	      {
		if(1==faceAdjMat[i+ Vfaces.size()*cur_node->index]) adj_nodes.insert(i);
	      }
	    
	    //if its not in the open list add it to the open list
	    //make the current square the parent of this square
	    //record F,G,H costs
	    
	    for (set<int>::iterator it = adj_nodes.begin(); it != adj_nodes.end(); ++it)
	      {
		bool tentative_is_better=false;
		if(closed.find(*it)!= closed.end())//if in closed list ignore
		  {
		    continue;
		  }

		  float tentative_g_score=0;
		  if(cur_node->index == start){
		    tentative_g_score= cur_node->G +   st.distance( Vfaces[*it].centroid);
		  }else{
		    tentative_g_score= cur_node->G +   Vfaces[cur_node->index].midHyp.distance( Vfaces[*it].midHyp);
		  }
		  if(open.find(*it)==open.end())//if not in open list
		    {
		      open.insert(*it);
		      tentative_is_better = true;
		    }
		  else if(tentative_g_score < Vfaces[*it].G){
		    tentative_is_better= true;
		  }
		  else{//it is on open list
		    tentative_is_better = false;
		  }
		  if (tentative_is_better == true)
		    {
		      Vfaces[*it].parent = cur_node->index;// cur_node is the parent
		      Vfaces[*it].G= tentative_g_score;
		      Vfaces[*it].H= Vfaces[*it].centroid.distance(en);
		      Vfaces[*it].F= Vfaces[*it].G + Vfaces[*it].H;
		    }	
	      }	    
	    //if it is on the open list, check to see if it is better
	    //by getting the G cost.  if it IS BETTER then set the parent
	    // of the current node as the node that is better
	    
	    //stop when target is found
	    //stop when open list is empty.  this implies no solution
	    
	    
	  }//while loop end
	deque<int> triangle_path;
	//
	//returns an empty vector because it failed
	//
	return triangle_path;
}

void Pathfind::printAllFaces(){
	for(size_t j=0; j<o.get_face_count(); ++j)
	{
		obj::face f_j = o.get_face(j);

		//the three vertex of each face
		const float* vert1 = o.get_vertex(f_j.vind[0]);
		const float* vert2 = o.get_vertex(f_j.vind[1]);
		const float* vert3 = o.get_vertex(f_j.vind[2]);

		cout <<"(" << vert1[0] << ", " << vert1[1] << ", " << vert1[2] << ") ";
		cout <<"(" << vert2[0] << ", " << vert2[1] << ", " << vert2[2] << ") ";
		cout <<"(" << vert3[0] << ", " << vert3[1] << ", " << vert3[2] << ") ";
		cout << endl;
	}
}

void Pathfind::createFaceVector()
{
	for(size_t j=0; j<o.get_face_count(); ++j)
	{
		obj::face f_j = o.get_face(j);

		//the three vertex of each face
		const float* vert1 = o.get_vertex(f_j.vind[0]);
		const float* vert2 = o.get_vertex(f_j.vind[1]);
		const float* vert3 = o.get_vertex(f_j.vind[2]);
		Ogre::Vector3 v1(vert1[0], vert1[1], vert1[2]);
		Ogre::Vector3 v2(vert2[0], vert2[1], vert2[2]);
		Ogre::Vector3 v3(vert3[0], vert3[1], vert3[2]);
		Vfaces.push_back(Fnode(v1,v2,v3));
		Vfaces[j].index=j;
		//cout << v1 << " " << v2 << " " << v3 << endl;
	}

	//cout << "========================" << endl;
	//    for(size_t i = 0; i < Vfaces.size();++i)//prints all faces
	//    {
	//      cout << Vfaces[i] << endl;
	//    }
	//cout << "========================" << endl;
}


#endif
