// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_POINT_3D_H_INCLUDED__
#define __IRR_POINT_3D_H_INCLUDED__

#include "irrMath.h"

namespace irr
{
namespace core
{

	//! 3d vector template class with lots of operators and methods.
	/** The vector3d class is used in Irrlicht for three main purposes: 
		1) As a direction vector (most of the methods assume this).
		2) As a position in 3d space (which is synonymous with a direction vector from the origin to this position).
		3) To hold three Euler rotations, where X is pitch, Y is yaw and Z is roll.
	*/
	template <class T>
	class vector3d
	{
	public:
		//! Default constructor (null vector).
		vector3d() : X(0), Y(0), Z(0) {}
		//! Constructor with three different values
		vector3d(T nx, T ny, T nz) : X(nx), Y(ny), Z(nz) {}
		//! Constructor with the same value for all elements
		explicit vector3d(T n) : X(n), Y(n), Z(n) {}
		//! Copy constructor
		vector3d(const vector3d<T>& other) : X(other.X), Y(other.Y), Z(other.Z) {}

		// operators

		vector3d<T> operator-() const { return vector3d<T>(-X, -Y, -Z); }

		vector3d<T>& operator=(const vector3d<T>& other) { X = other.X; Y = other.Y; Z = other.Z; return *this; }

		vector3d<T> operator+(const vector3d<T>& other) const { return vector3d<T>(X + other.X, Y + other.Y, Z + other.Z); }
		vector3d<T>& operator+=(const vector3d<T>& other) { X+=other.X; Y+=other.Y; Z+=other.Z; return *this; }
		vector3d<T> operator+(const T val) const { return vector3d<T>(X + val, Y + val, Z + val); }
		vector3d<T>& operator+=(const T val) { X+=val; Y+=val; Z+=val; return *this; }

		vector3d<T> operator-(const vector3d<T>& other) const { return vector3d<T>(X - other.X, Y - other.Y, Z - other.Z); }
		vector3d<T>& operator-=(const vector3d<T>& other) { X-=other.X; Y-=other.Y; Z-=other.Z; return *this; }
		vector3d<T> operator-(const T val) const { return vector3d<T>(X - val, Y - val, Z - val); }
		vector3d<T>& operator-=(const T val) { X-=val; Y-=val; Z-=val; return *this; }

		vector3d<T> operator*(const vector3d<T>& other) const { return vector3d<T>(X * other.X, Y * other.Y, Z * other.Z); }
		vector3d<T>& operator*=(const vector3d<T>& other) { X*=other.X; Y*=other.Y; Z*=other.Z; return *this; }
		vector3d<T> operator*(const T v) const { return vector3d<T>(X * v, Y * v, Z * v); }
		vector3d<T>& operator*=(const T v) { X*=v; Y*=v; Z*=v; return *this; }

		vector3d<T> operator/(const vector3d<T>& other) const { return vector3d<T>(X / other.X, Y / other.Y, Z / other.Z); }
		vector3d<T>& operator/=(const vector3d<T>& other) { X/=other.X; Y/=other.Y; Z/=other.Z; return *this; }
		vector3d<T> operator/(const T v) const { T i=(T)1.0/v; return vector3d<T>(X * i, Y * i, Z * i); }
		vector3d<T>& operator/=(const T v) { T i=(T)1.0/v; X*=i; Y*=i; Z*=i; return *this; }

		bool operator<=(const vector3d<T>&other) const { return X<=other.X && Y<=other.Y && Z<=other.Z;}
		bool operator>=(const vector3d<T>&other) const { return X>=other.X && Y>=other.Y && Z>=other.Z;}
		bool operator<(const vector3d<T>&other) const { return X<other.X && Y<other.Y && Z<other.Z;}
		bool operator>(const vector3d<T>&other) const { return X>other.X && Y>other.Y && Z>other.Z;}

		//! use weak float compare
		bool operator==(const vector3d<T>& other) const
		{
			return this->equals(other);
		}

		bool operator!=(const vector3d<T>& other) const
		{
			return !this->equals(other);
		}

		// functions

		//! returns if this vector equals the other one, taking floating point rounding errors into account
		bool equals(const vector3d<T>& other, const T tolerance = (T)ROUNDING_ERROR_32 ) const
		{
			return core::equals(X, other.X, tolerance) &&
				core::equals(Y, other.Y, tolerance) &&
				core::equals(Z, other.Z, tolerance);
		}

		vector3d<T>& set(const T nx, const T ny, const T nz) {X=nx; Y=ny; Z=nz; return *this;}
		vector3d<T>& set(const vector3d<T>& p) {X=p.X; Y=p.Y; Z=p.Z;return *this;}

		//! Get length of the vector.
		T getLength() const { return (T) sqrt((f64)(X*X + Y*Y + Z*Z)); }

		//! Get squared length of the vector.
		/** This is useful because it is much faster than getLength().
		\return Squared length of the vector. */
		T getLengthSQ() const { return X*X + Y*Y + Z*Z; }

		//! Get the dot product with another vector.
		T dotProduct(const vector3d<T>& other) const
		{
			return X*other.X + Y*other.Y + Z*other.Z;
		}

		//! Get distance from another point.
		/** Here, the vector is interpreted as point in 3 dimensional space. */
		T getDistanceFrom(const vector3d<T>& other) const
		{
			return vector3d<T>(X - other.X, Y - other.Y, Z - other.Z).getLength();
		}

		//! Returns squared distance from another point.
		/** Here, the vector is interpreted as point in 3 dimensional space. */
		T getDistanceFromSQ(const vector3d<T>& other) const
		{
			return vector3d<T>(X - other.X, Y - other.Y, Z - other.Z).getLengthSQ();
		}

		//! Calculates the cross product with another vector.
		/** \param p Vector to multiply with.
		\return Crossproduct of this vector with p. */
		vector3d<T> crossProduct(const vector3d<T>& p) const
		{
			return vector3d<T>(Y * p.Z - Z * p.Y, Z * p.X - X * p.Z, X * p.Y - Y * p.X);
		}

		//! Returns if this vector interpreted as a point is on a line between two other points.
		/** It is assumed that the point is on the line.
		\param begin Beginning vector to compare between.
		\param end Ending vector to compare between.
		\return True if this vector is between begin and end, false if not. */
		bool isBetweenPoints(const vector3d<T>& begin, const vector3d<T>& end) const
		{
			const T f = (end - begin).getLengthSQ();
			return getDistanceFromSQ(begin) <= f &&
				getDistanceFromSQ(end) <= f;
		}

		//! Normalizes the vector.
		/** In case of the 0 vector the result is still 0, otherwise
		the length of the vector will be 1.
		TODO: 64 Bit template doesnt work.. need specialized template
		\return Reference to this vector after normalization. */
		vector3d<T>& normalize()
		{
			T l = X*X + Y*Y + Z*Z;
			if (l == 0)
				return *this;
			l = (T) reciprocal_squareroot ( (f32)l );
			X *= l;
			Y *= l;
			Z *= l;
			return *this;
		}

		//! Sets the length of the vector to a new value
		vector3d<T>& setLength(T newlength)
		{
			normalize();
			return (*this *= newlength);
		}

		//! Inverts the vector.
		vector3d<T>& invert()
		{
			X *= -1.0f;
			Y *= -1.0f;
			Z *= -1.0f;
			return *this;
		}

		//! Rotates the vector by a specified number of degrees around the Y axis and the specified center.
		/** \param degrees Number of degrees to rotate around the Y axis.
		\param center The center of the rotation. */
		void rotateXZBy(f64 degrees, const vector3d<T>& center=vector3d<T>())
		{
			degrees *= DEGTORAD64;
			T cs = (T)cos(degrees);
			T sn = (T)sin(degrees);
			X -= center.X;
			Z -= center.Z;
			set(X*cs - Z*sn, Y, X*sn + Z*cs);
			X += center.X;
			Z += center.Z;
		}

		//! Rotates the vector by a specified number of degrees around the Z axis and the specified center.
		/** \param degrees: Number of degrees to rotate around the Z axis.
		\param center: The center of the rotation. */
		void rotateXYBy(f64 degrees, const vector3d<T>& center=vector3d<T>())
		{
			degrees *= DEGTORAD64;
			T cs = (T)cos(degrees);
			T sn = (T)sin(degrees);
			X -= center.X;
			Y -= center.Y;
			set(X*cs - Y*sn, X*sn + Y*cs, Z);
			X += center.X;
			Y += center.Y;
		}

		//! Rotates the vector by a specified number of degrees around the X axis and the specified center.
		/** \param degrees: Number of degrees to rotate around the X axis.
		\param center: The center of the rotation. */
		void rotateYZBy(f64 degrees, const vector3d<T>& center=vector3d<T>())
		{
			degrees *= DEGTORAD64;
			T cs = (T)cos(degrees);
			T sn = (T)sin(degrees);
			Z -= center.Z;
			Y -= center.Y;
			set(X, Y*cs - Z*sn, Y*sn + Z*cs);
			Z += center.Z;
			Y += center.Y;
		}

		//! Returns interpolated vector.
		/** \param other Other vector to interpolate between
		\param d Value between 0.0f and 1.0f. */
		vector3d<T> getInterpolated(const vector3d<T>& other, const T d) const
		{
			const T inv = (T) 1.0 - d;
			return vector3d<T>(other.X*inv + X*d, other.Y*inv + Y*d, other.Z*inv + Z*d);
		}

		//! Returns interpolated vector. ( quadratic )
		/** \param v2 Second vector to interpolate with
		\param v3 Third vector to interpolate with
		\param d Value between 0.0f and 1.0f. */
		vector3d<T> getInterpolated_quadratic(const vector3d<T>& v2, const vector3d<T>& v3, const T d) const
		{
			// this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
			const T inv = (T) 1.0 - d;
			const T mul0 = inv * inv;
			const T mul1 = (T) 2.0 * d * inv;
			const T mul2 = d * d;

			return vector3d<T> ( X * mul0 + v2.X * mul1 + v3.X * mul2,
					Y * mul0 + v2.Y * mul1 + v3.Y * mul2,
					Z * mul0 + v2.Z * mul1 + v3.Z * mul2);
		}

		//! Get the rotations that would make a (0,0,1) direction vector point in the same direction as this direction vector.
		/** Thanks to Arras on the Irrlicht forums for this method.  This utility method is very useful for
		orienting scene nodes towards specific targets.  For example, if this vector represents the difference
		between two scene nodes, then applying the result of getHorizontalAngle() to one scene node will point
		it at the other one.
		Example code:
		// Where target and seeker are of type ISceneNode*
		const vector3df toTarget(target->getAbsolutePosition() - seeker->getAbsolutePosition());
		const vector3df requiredRotation = toTarget.getHorizontalAngle();
		seeker->setRotation(requiredRotation); 

		\return A rotation vector containing the X (pitch) and Y (raw) rotations (in degrees) that when applied to a 
		+Z (e.g. 0, 0, 1) direction vector would make it point in the same direction as this vector. The Z (roll) rotation 
		is always 0, since two Euler rotations are sufficient to point in any given direction. */
		vector3d<T> getHorizontalAngle() const
		{
			vector3d<T> angle;

			angle.Y = (T)(atan2(X, Z) * RADTODEG64);

			if (angle.Y < 0.0f)
				angle.Y += 360.0f;
			if (angle.Y >= 360.0f)
				angle.Y -= 360.0f;

			const f64 z1 = sqrt(X*X + Z*Z);

			angle.X = (T)(atan2(z1, (f64)Y) * RADTODEG64 - 90.0);

			if (angle.X < 0.0f)
				angle.X += 360.0f;
			if (angle.X >= 360.0f)
				angle.X -= 360.0f;

			return angle;
		}

		//! Builds a direction vector from (this) rotation vector.
		/** This vector is assumed to be a rotation vector composed of 3 Euler angle rotations, in degrees.
		The implementation performs the same calculations as using a matrix to do the rotation.

		\param[in] forwards  The direction representing "forwards" which will be rotated by this vector. 
		If you do not provide a direction, then the +Z axis (0, 0, 1) will be assumed to be forwards.
		\return A direction vector calculated by rotating the forwards direction by the 3 Euler angles 
		(in degrees) represented by this vector. */
		vector3d<T> rotationToDirection(const vector3d<T> & forwards = vector3d<T>(0, 0, 1)) const
		{
			const f64 cr = cos( core::DEGTORAD64 * X );
			const f64 sr = sin( core::DEGTORAD64 * X );
			const f64 cp = cos( core::DEGTORAD64 * Y );
			const f64 sp = sin( core::DEGTORAD64 * Y );
			const f64 cy = cos( core::DEGTORAD64 * Z );
			const f64 sy = sin( core::DEGTORAD64 * Z );

			const f64 srsp = sr*sp;
			const f64 crsp = cr*sp;

			const f64 pseudoMatrix[] = {
				( cp*cy ), ( cp*sy ), ( -sp ),
				( srsp*cy-cr*sy ), ( srsp*sy+cr*cy ), ( sr*cp ),
				( crsp*cy+sr*sy ), ( crsp*sy-sr*cy ), ( cr*cp )};

			return vector3d<T>(
				(T)(forwards.X * pseudoMatrix[0] +
					forwards.Y * pseudoMatrix[3] +
					forwards.Z * pseudoMatrix[6]),
				(T)(forwards.X * pseudoMatrix[1] +
					forwards.Y * pseudoMatrix[4] +
					forwards.Z * pseudoMatrix[7]),
				(T)(forwards.X * pseudoMatrix[2] +
					forwards.Y * pseudoMatrix[5] +
					forwards.Z * pseudoMatrix[8]));
		}

		//! Fills an array of 4 values with the vector data (usually floats).
		/** Useful for setting in shader constants for example. The fourth value
		will always be 0. */
		void getAs4Values(T* array) const
		{
			array[0] = X;
			array[1] = Y;
			array[2] = Z;
			array[3] = 0;
		}

		//! X coordinate of the vector
		T X;
		//! Y coordinate of the vector
		T Y;
		//! Z coordinate of the vector
		T Z;
	};


	//! Typedef for a f32 3d vector.
	typedef vector3d<f32> vector3df;
	//! Typedef for an integer 3d vector.
	typedef vector3d<s32> vector3di;

	//! Function multiplying a scalar and a vector component-wise.
	template<class S, class T>
	vector3d<T> operator*(const S scalar, const vector3d<T>& vector) { return vector*scalar; }

} // end namespace core
} // end namespace irr

#endif
