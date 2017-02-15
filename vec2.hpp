#ifndef Vec2_HPP
#define Vec2_HPP
 
#include <iostream>
#include <math.h>
#include <stdlib.h>
 
template <class T> class Vec2
{
	public:

		T x, y;

		// ------------ Constructors ------------
 
		// Default constructor
        Vec2()
		{
			x = y = 0;
		}
 
		// Two parameter constructor
		Vec2(T xValue, T yValue)
		{
			x = xValue;
			y = yValue;
		}
 
		// ------------ Getters and setters ------------
 
		void set(const T &xValue, const T &yValue)
		{
			x = xValue;
			y = yValue;
		}
 
		T getX() const { return x; }
		T getY() const { return y; }
 
		void setX(const T &xValue)
		{
			x = xValue;
		}
 
		void setY(const T &yValue)
		{
			y = yValue;
		}
 
 
		// ------------ Helper methods ------------
 
		// Method to reset a vector to zero
		void zero()
		{
			x = y = 0;
		}
 
		// Method to normalise a vector
		void normalise()
		{
			// Calculate the magnitude of our vector
			T magnitude = sqrt((x * x) + (y * y));
 
			// As long as the magnitude isn't zero, divide each element by the magnitude
			// to get the normalised value between -1 and +1
			if (magnitude != 0)
			{
				x /= magnitude;
				y /= magnitude;
			}
		}
 
		// Static method to calculate and return the scalar dot product of two vectors
		//
		// Note: The dot product of two vectors tell us things about the angle between
		// the vectors. That is, it tells us if they are pointing in the same direction
		// (i.e. are they parallel? If so, the dot product will be 1), or if they're
		// perpendicular (i.e. at 90 degrees to each other) the dot product will be 0,
		// or if they're pointing in opposite directions then the dot product will be -1.
		//
		// Usage example: double foo = Vec2<double>::dotProduct(vectorA, vectorB);
		static T dotProduct(const Vec2 &vec1, const Vec2 &vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y;
		}
 
		// Non-static method to calculate and return the scalar dot product of this vector and another vector
		//
		// Usage example: double foo = vectorA.dotProduct(vectorB);
		T dotProduct(const Vec2 &vec) const
		{
			return x * vec.x + y * vec.y;
		}
 
		// Static method to calculate and return a vector which is the cross product of two vectors
		//
		// Note: The cross product is simply a vector which is perpendicular to the plane formed by
		// the first two vectors. Think of a desk like the one your laptop or keyboard is sitting on.
		// If you put one pencil pointing directly away from you, and then another pencil pointing to the
		// right so they form a "L" shape, the vector perpendicular to the plane made by these two pencils
		// points directly upwards.
		//
		// Whether the vector is perpendicularly pointing "up" or "down" depends on the "handedness" of the
		// coordinate system that you're using.
		//
		// Further reading: http://en.wikipedia.org/wiki/Cross_product
		//
		// Usage example: Vec2<double> crossVect = Vec2<double>::crossProduct(vectorA, vectorB);
		/*static Vec2 crossProduct(const Vec2 &vec1, const Vec2 &vec2)
		{
			return Vec2(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
		}*/
 
		// Easy adders
		void addX(T value)
		{
			x += value;
		}
 
		void addY(T value)
		{
			y += value;
		}
 
		// Method to return the distance between two vectors in 3D space
		//
		// Note: This is accurate, but not especially fast - depending on your needs you might
		// like to use the Manhattan Distance instead: http://en.wikipedia.org/wiki/Taxicab_geometry
		// There's a good discussion of it here: http://stackoverflow.com/questions/3693514/very-fast-3d-distance-check
		// The gist is, to find if we're within a given distance between two vectors you can use:
		//
		// bool within3DManhattanDistance(Vec2 c1, Vec2 c2, float distance)
		// {
		//      float dx = abs(c2.x - c1.x);
		//      if (dx > distance) return false; // too far in x direction
		//
		//      float dy = abs(c2.y - c1.y);
		//      if (dy > distance) return false; // too far in y direction
		//
		//      float dz = abs(c2.z - c1.z);
		//      if (dz > distance) return false; // too far in z direction
		//
		//      return true; // we're within the cube
		// }
		//
		// Or to just calculate the straight Manhattan distance you could use:
		//
		// float getManhattanDistance(Vec2 c1, Vec2 c2)
		// {
		//      float dx = abs(c2.x - c1.x);
		//      float dy = abs(c2.y - c1.y);
		//      float dz = abs(c2.z - c1.z);
		//      return dx+dy+dz;
		// }
		//
 
		T getManhattanDistance(Vec2 v)
		{
			T dx = abs(v.x - x);
			T dy = abs(v.y - y);
 
			return dx + dy;
		}
 
		bool withinManhattanDistance(Vec2 v, T distance)
		{
			T dx = abs(v.x - x);
			T dy = abs(v.y - y);
 
			return dx + dy < distance;
		}
 
		static T getDistance(const Vec2 &v1, const Vec2 &v2)
		{
			T dx = v2.x - v1.x;
			T dy = v2.y - v1.y;
			return sqrt(dx * dx + dy * dy);
 
		}
 
		Vec2<T> getVectorTo(const Vec2 &v)
		{
			Vec2<T> temp(v.x - x, v.y - y);
 
			temp.normalise();
 
			return temp;
		}
 
		// Method to display the vector so you can easily check the values
		void display()
 
		{
			std::cout << "X: " << x << "\t Y: " << y << std::endl;
		}
 
		// ------------ Overloaded operators ------------
 
		// Overloaded addition operator to add Vec2s together
		Vec2 operator+(const Vec2 &vector) const
		{
			return Vec2<T>(x + vector.x, y + vector.y);
		}
 
		// Overloaded add and asssign operator to add Vec2s together
		void operator+=(const Vec2 &vector)
		{
			x += vector.x;
			y += vector.y;
		}
 
		// Overloaded subtraction operator to subtract a Vec2 from another Vec2
		Vec2 operator-(const Vec2 &vector) const
		{
			return Vec2<T>(x - vector.x, y - vector.y);
		}
 
		// Overloaded subtract and asssign operator to subtract a Vec2 from another Vec2
		void operator-=(const Vec2 &vector)
		{
			x -= vector.x;
			y -= vector.y;
		}
 
		// Overloaded multiplication operator to multiply two Vec2s together
		Vec2 operator*(const Vec2 &vector) const
		{
			return Vec2<T>(x * vector.x, y * vector.y);
		}
 
		// Overloaded multiply operator to multiply a vector by a scalar
		Vec2 operator*(const T &value) const
		{
			return Vec2<T>(x * value, y * value);
		}
 
		// Overloaded multiply and assign operator to multiply a vector by a scalar
		void operator*=(const T &value)
		{
			x *= value;
			y *= value;
		}
 
		// Overloaded multiply and assign operator to multiply a vector by a scalar
		void operator*=(const Vec2 & vector)
		{
			x *= vector.x;
			y *= vector.y;
			//return Vec2<T>(x * vector.x, y * vector.y);
		}
 
		// Overloaded multiply operator to multiply a vector by a scalar
		Vec2 operator/(const T &value) const
		{
			return Vec2<T>(x / value, y / value);
		}
 
		// Overloaded multiply and assign operator to multiply a vector by a scalar
		void operator/=(const T &value)
		{
			x /= value;
			y /= value;
		}

        friend std::ostream& operator<<(std::ostream& os, const Vec2<T>& v) {
            os << "<" << v.x << ", " << v.y << ">";
            return os;
        }
};

typedef Vec2<double>          Vec2d;
typedef Vec2<int>             Vec2i;
typedef Vec2<float>           Vec2f;
 
#endif